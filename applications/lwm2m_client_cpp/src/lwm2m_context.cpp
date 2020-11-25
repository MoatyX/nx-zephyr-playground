//
// Created by moaty on 04.11.20.
//

#include "lwm2m_context.h"
#include "utility.h"

extern "C" {
#include <lwm2m_engine.h>
}
namespace nx {
    lwm2m_context::lwm2m_context(const char *endpoint_name) {
        this->endpoint_name = endpoint_name;
        server_address = nullptr;
    }

    void lwm2m_context::set_server_address(uint16_t short_server_id, const char *server_addr) {
        /*
        * later once we have a working Template.
        * we will use member lwm2m instances to do the following steps
        */
        uint16_t server_url_len = 0;
        uint8_t server_url_flags = 0;
        lwm2m_engine_get_res_data("0/0/0", (void **) &server_address, &server_url_len, &server_url_flags);

        // TODO: remove later to support DTLS and Bootrapping
        snprintk(server_address, server_url_len, "coap://%s", server_addr);

        // Match Security object instance ID with a Short Server ID of the Server instance
        lwm2m_engine_set_u16("0/0/10", short_server_id); //security object instance "ID"
        lwm2m_engine_set_u16("1/0/0", short_server_id);  //server object instance "Short Server ID"
        lwm2m_engine_set_string("0/0/0", server_address);
    }

    void lwm2m_context::start(uint32_t flags, lwm2m_ctx_event_cb_t client_event_callback) {
        memset(&client, 0, sizeof(client));

        //register internal objects
        device.register_instance(&device_instance);
        register_object(&device, true);

        lwm2m_rd_client_start(&client, endpoint_name, flags, client_event_callback); //start client
    }

    bool lwm2m_context::register_object(lwm2m_object_base *obj, bool is_intern) {
        //creating obj instance: lwm2m_engine_create_obj_inst("<obj_id>/<obj_inst_id>");
        //creating resource instance: lwm2m_engine_create_res_inst("<obj_id>/<obj_inst_id>/<obj_res_id>/<res_instance>");
        //setting resource data: lwm2m_engine_set_res_data(...)
        //setting callback data:lwm2m_engine_register_exec_callback(...)
        /*  pseudo Algorithm:
         *  -create all instances registered inside the lwm2m_object_base
         *  for all object_instances do {
         *      -create res instances if any
         *      -set callbacks if any
         *      -set res data if any
         *  }
         */

        bool output = is_intern;
        for (size_t i = 0; i < obj->current_instances_count; ++i) {
            char *obj_inst_path = lwm2m_object_to_path(obj->object_id, i);

            if (!is_intern)
                output |= (bool) lwm2m_engine_create_obj_inst(obj_inst_path);

            //bind zephyr callbacks with the user-defined ones
            size_t res_count = 0;
            lwm2m_object_resource **all_res = obj->get_all_res(&res_count);
            auto inst = obj->get_instance(i);
            for (size_t j = 0; j < res_count; ++j) {
                lwm2m_object_resource *res = all_res[j];
                char *res_path = nullptr;

                //register read/write callbacks
                lwm2m_engine_get_data_cb_t read_cb = res->get_read_cb();
                lwm2m_engine_set_data_cb_t post_write_cb = res->get_post_write_cb();
                if (read_cb != nullptr) lwm2m_engine_register_read_callback(res_path, read_cb);
                if (post_write_cb != nullptr) lwm2m_engine_register_post_write_callback(res_path, post_write_cb);

                /* allow user to set resource data.
                 * choose a proper way to interpret the pointers to the user data based on the resource type
                 */
                void *data = nullptr;
                switch (res->type) {
                    case resource_type::SINGLE:
                        data = &(inst->*(res->mem_ptr));
                        res_path = lwm2m_object_to_path(obj->object_id, i, res->resource_id, 0);
                        break;
                    case resource_type::MULTIPLE: {
                        multi_inst_resource *res_data = (multi_inst_resource *) (&(inst->*(res->mem_ptr)));;
                        int alloc = res_data->get_allocated_count();

                        //bind all allocated instances to the lwm2m engine
                        for (int k = 0; k < alloc; ++k) {
                            bool ret = res_data->index(k, reinterpret_cast<int **>(&data));
                            if (!ret) continue;

                            res_path = lwm2m_object_to_path(obj->object_id, i, res->resource_id, k);
                            lwm2m_engine_create_res_inst(res_path);
                        }
                    }
                        break;
                    case resource_type::PTR:
                        data = (inst->*(res->mem_ptr));
                        res_path = lwm2m_object_to_path(obj->object_id, i, res->resource_id, 0);
                        break;
                }

                //now call the appropriate binding function based on the operation type of the resource
                if (data != nullptr) {
                    switch (res->operation) {
                        case resource_operations::R:
                        case resource_operations::RW:
                            lwm2m_engine_set_res_data(res_path, data, res->member_size, res->user_data_flags);
                            break;
                        case resource_operations::EXEC:
                            lwm2m_engine_register_exec_callback(res_path, reinterpret_cast<executable>(data));
                            break;
                    }
                }
            }

            //register a callback when an instance is deleted
            lwm2m_engine_user_cb_t inst_delete_cb = inst->get_delete_cb();
            if (inst_delete_cb != nullptr) lwm2m_engine_register_delete_callback(obj->object_id, inst_delete_cb);
        }
        return output;
    }

    void lwm2m_context::unregister_object_instance(const uint16_t object_id, const uint16_t instance_id) {
        lwm2m_delete_obj_inst(object_id, instance_id);
    }
}