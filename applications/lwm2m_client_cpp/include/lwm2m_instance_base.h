//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_LWM2M_INSTANCE_BASE_H
#define LWM2M_CLIENT_CPP_LWM2M_INSTANCE_BASE_H

#include <inttypes.h>

#define DEFAULT_MAX_STR_LEN 64

/**
* @brief base struct for all lwm2m instance
*/
class lwm2m_instance_base {
public:
    lwm2m_instance_base() = default;
    ~lwm2m_instance_base() = default;

    uint16_t instance_id;
};

#endif //LWM2M_CLIENT_CPP_LWM2M_INSTANCE_BASE_H
