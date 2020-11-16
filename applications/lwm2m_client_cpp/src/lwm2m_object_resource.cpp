//
// Created by moaty on 09.11.20.
//

#include "lwm2m_object_resource.h"

#include <zephyr.h>

namespace nx {
    lwm2m_object_resource::lwm2m_object_resource(uint16_t resource_id, resource_operations op) {
        this->resource_id=resource_id;
        this->operation=op;
    }

    lwm2m_object_resource::lwm2m_object_resource(uint16_t resource_id, resource_operations op, member_pointer mem_ptr,
                                                 uint16_t member_size) {
        this->resource_id=resource_id;
        this->operation=op;
        this->mem_ptr = mem_ptr;
        this->member_size = member_size;
    }

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
}
