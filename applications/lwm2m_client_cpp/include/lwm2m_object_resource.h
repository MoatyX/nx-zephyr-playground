//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_LWM2M_OBJECT_RESOURCE_H
#define LWM2M_CLIENT_CPP_LWM2M_OBJECT_RESOURCE_H

#include "lwm2m_instance_base.h"

namespace nx {

    typedef enum class resource_operations {
        R,
        RW,
        EXEC
    } resource_operations_t;

/**
 * @brief a struct that contains base members for each lwm2m object resource
 * @tparam res_id
 */
typedef void* lwm2m_instance_base::* member_pointer;
    class lwm2m_object_resource {
    public:
        lwm2m_object_resource(uint16_t resource_id, resource_operations op);
        lwm2m_object_resource(uint16_t resource_id, resource_operations op, member_pointer mem_ptr, uint16_t member_size);

        ~lwm2m_object_resource() = default;

    public:
        uint16_t resource_id;
        resource_operations_t operation;
    public:
        member_pointer mem_ptr;
        uint16_t member_size;
        uint8_t user_data_flags{0};
    };
}


#endif //LWM2M_CLIENT_CPP_LWM2M_OBJECT_RESOURCE_H