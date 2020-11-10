//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_OBJECTS_H
#define LWM2M_CLIENT_CPP_OBJECTS_H

#include "lwm2m_object_base.h"

namespace nx {
#define Resource(id, op, resource_name)   lwm2m_object_resource resource_name{(id), (op)}
#define Resource2(id, op, member_ptr, resource_name)   lwm2m_object_resource resource_name{(id), (op), (member_ptr)}
}

#endif //LWM2M_CLIENT_CPP_OBJECTS_H
