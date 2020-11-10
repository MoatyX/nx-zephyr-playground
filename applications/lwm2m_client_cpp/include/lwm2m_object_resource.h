//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_LWM2M_OBJECT_RESOURCE_H
#define LWM2M_CLIENT_CPP_LWM2M_OBJECT_RESOURCE_H

#include <stdint.h>
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
#define test_type bool
    class lwm2m_object_resource {
    public:
        lwm2m_object_resource(uint16_t resource_id, resource_operations op);
        lwm2m_object_resource(uint16_t resource_id, resource_operations op, test_type lwm2m_instance_base::*member_ptr);

        ~lwm2m_object_resource() = default;

        void set_resource_data(void *user_data, uint8_t data_len, uint8_t data_flags);

    public:
        uint16_t resource_id;
        resource_operations_t operation;
    public:
        test_type lwm2m_instance_base::*member_pointer{nullptr};
        void *user_data{nullptr};
        uint16_t user_data_len{0};
        uint8_t user_data_flags{0};
    };
}


#endif //LWM2M_CLIENT_CPP_LWM2M_OBJECT_RESOURCE_H
