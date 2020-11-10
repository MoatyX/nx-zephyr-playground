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

    void lwm2m_object_resource::set_resource_data(void *usr_data, uint8_t data_len, uint8_t data_flags) {
        user_data = usr_data;
        user_data_len = data_len;
        user_data_flags = data_flags;
    }

    lwm2m_object_resource::lwm2m_object_resource(uint16_t resource_id, resource_operations op, test_type lwm2m_instance_base::*member_ptr) {
        this->resource_id=resource_id;
        this->operation=op;
        member_pointer = member_ptr;
    }
}
