//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_OBJECTS_H
#define LWM2M_CLIENT_CPP_OBJECTS_H

#include "lwm2m_object_base.h"
#include "nx_string.h"

namespace nx {
#define Resource(id, op, member_ptr, member_size, resource_name)   lwm2m_object_resource resource_name{(id), (op), (member_ptr), (member_size)}
#define MemberSize(member) sizeof(decltype((member)))
}

#endif //LWM2M_CLIENT_CPP_OBJECTS_H
