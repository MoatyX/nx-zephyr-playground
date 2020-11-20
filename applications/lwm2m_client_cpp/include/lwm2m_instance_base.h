//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_LWM2M_INSTANCE_BASE_H
#define LWM2M_CLIENT_CPP_LWM2M_INSTANCE_BASE_H

#include <inttypes.h>
#include "lwm2m_cpp.h"

#define DEFAULT_MAX_STR_LEN 64

/**
* @brief base struct for all lwm2m instance
*/
class lwm2m_instance_base {
public:
    lwm2m_instance_base() = default;
    ~lwm2m_instance_base() = default;

    lwm2m_engine_user_cb_t  get_delete_cb();
    void set_delete_cb(lwm2m_engine_user_cb_t cb);

public:
    uint16_t instance_id;

private:
    lwm2m_engine_user_cb_t  delete_cb;
};

#endif //LWM2M_CLIENT_CPP_LWM2M_INSTANCE_BASE_H
