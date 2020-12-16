//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_OBJECTS_H
#define LWM2M_CLIENT_CPP_OBJECTS_H

#include <errno.h>      //use this for returning standard zephyr error codes

#include "lwm2m_object_base.h"
#include "nx_string.h"
#include "multi_inst_resources.h"

namespace nx {
    typedef lwm2m_engine_user_cb_t executable;

#define MEMBER_SIZE(member) sizeof(decltype((member)))      //BUG: this will not work with pointer type resources (char*)

#define RESOURCE(id, type, op, member_ptr, resource_name)   \
    lwm2m_object_resource resource_name{(id), (type), (op), (member_ptr)}
}

#endif //LWM2M_CLIENT_CPP_OBJECTS_H
