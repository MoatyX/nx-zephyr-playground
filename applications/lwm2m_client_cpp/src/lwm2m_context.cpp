//
// Created by moaty on 04.11.20.
//

#include "lwm2m_context.h"
#include "utility.h"

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
        lwm2m_engine_get_res_data("0/0/0", (void **)&server_address, &server_url_len, &server_url_flags);

        // TODO: remove later to support DTLS and Bootrapping
        snprintk(server_address, server_url_len, "coap://%s", server_addr);

        // Match Security object instance ID with a Short Server ID of the Server instance
        lwm2m_engine_set_u16("0/0/10", short_server_id); //security object instance "ID"
        lwm2m_engine_set_u16("1/0/0", short_server_id);  //server object instance "Short Server ID"
        lwm2m_engine_set_string("0/0/0", server_address);
    }

    void lwm2m_context::start(uint32_t flags, lwm2m_ctx_event_cb_t client_event_callback) {
        memset(&client, 0, sizeof(client));
        lwm2m_rd_client_start(&client, endpoint_name, flags, client_event_callback); //start client
    }

    bool lwm2m_context::register_object(lwm2m_object_base *obj) {
        //creating obj instance: lwm2m_engine_create_obj_inst("<obj_id>/<obj_inst_id>");
        //creating resource instance: lwm2m_engine_create_res_inst("<obj_id>/<obj_inst_id>/<obj_res_id>/<res_instance>");
        //setting resource data: lwm2m_engine_set_res_data(...)
        //setting callback data:lwm2m_engine_register_exec_callback(...)
        /*  Algorithm:
         *  -create all instances registered inside the lwm2m_object_base
         *  for all object_instances do {
         *      -create res instances if any
         *      -set callbacks if any
         *      -set res data if any
         *  }
         */

        bool output = false;
        for (size_t i = 0; i < obj->current_instances_count; ++i) {
            char* obj_inst_path = lwm2m_object_to_path(obj->object_id, i);
            output |= (bool)lwm2m_engine_create_obj_inst(obj_inst_path);

            //skip creating resource instances for now... TODO: do it

            //bind zephyr callbacks with the user-defined ones
            size_t res_count = 0;
            lwm2m_object_resource** all_res = obj->get_all_res(&res_count);
            auto inst = obj->get_instance(i);
            for (size_t j = 0; j < res_count; ++j) {
                lwm2m_object_resource* res = all_res[j];
                char* res_path = lwm2m_object_to_path(obj->object_id, i, res->resource_id, 0);
                //register read callbacks
//                lwm2m_engine_register_read_callback(res_path, )

                //allow user to set resource data
                void* data = &(inst->*(res->mem_ptr));
                if(data != nullptr) {
                    lwm2m_engine_set_res_data(res_path, data, res->member_size, res->user_data_flags);
                }
            }
        }

        return output;
    }
}