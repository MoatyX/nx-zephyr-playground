//
// Created by moaty on 09.11.20.
//

#include "lwm2m_object_resource.h"

#include <zephyr.h>

namespace nx {
    void lwm2m_object_resource::set_read_callback(lwm2m_engine_get_data_cb_t read_callback) {
        read_cb = read_callback;
    }

    void lwm2m_object_resource::set_post_write_callback(lwm2m_engine_set_data_cb_t write_callback) {
        write_cb = write_callback;
    }

    lwm2m_engine_get_data_cb_t lwm2m_object_resource::get_read_cb() {
        return read_cb;
    }

    lwm2m_engine_set_data_cb_t lwm2m_object_resource::get_post_write_cb() {
        return write_cb;
    }

    lwm2m_object_resource::lwm2m_object_resource(uint16_t resource_id, resource_type_t res_type,
                                                 resource_operations_t op, member_pointer mem_ptr, uint16_t mem_size) {
        this->resource_id = resource_id;
        this->mem_ptr = mem_ptr;
        this->member_size = mem_size;
        this->operation = op;
        if (operation == resource_operations::EXEC)
            this->type = resource_type::PTR;    //execute resource types are automatically a pointer type
        else this->type = res_type;
    }
}
