//
// Created by moaty on 09.11.20.
//

#include "lwm2m_instance_base.h"


lwm2m_engine_user_cb_t lwm2m_instance_base::get_delete_cb() {
    return delete_cb;
}

void lwm2m_instance_base::set_delete_cb(lwm2m_engine_user_cb_t cb) {
    delete_cb = cb;
}
