//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_OBJECTS_H
#define LWM2M_CLIENT_CPP_OBJECTS_H

#include <errno.h>      //use this for returning standard zephyr error codes

#include "lwm2m_object_base.h"
#include "nx_string.h"

namespace nx {
    typedef lwm2m_engine_user_cb_t executable;

#define MEMBER_SIZE(member) sizeof(decltype((member)))

#define RESOURCE(id, type, op, member_ptr, member_size, resource_name)   \
    lwm2m_object_resource resource_name{(id), (type), (op), (member_ptr), (member_size)}
}

#endif //LWM2M_CLIENT_CPP_OBJECTS_H
