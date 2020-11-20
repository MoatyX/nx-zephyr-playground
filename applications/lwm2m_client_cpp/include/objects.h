//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_OBJECTS_H
#define LWM2M_CLIENT_CPP_OBJECTS_H

#include <errno.h>      //use this for returning standard zephyr error codes

#include "lwm2m_object_base.h"
#include "nx_string.h"

namespace nx {
    typedef lwm2m_engine_set_data_cb_t executable;

#define RESOURCE(id, op, member_ptr, member_size, resource_name)   lwm2m_object_resource resource_name{(id), (op), (member_ptr), (member_size)}
#define MEMBER_SIZE(member) sizeof(decltype((member)))
}

#endif //LWM2M_CLIENT_CPP_OBJECTS_H
