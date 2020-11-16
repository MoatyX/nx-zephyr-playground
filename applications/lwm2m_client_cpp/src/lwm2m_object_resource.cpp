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
}
