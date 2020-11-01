//
// Created by moaty on 01.11.20.
//

#ifndef LWM2M_CPP_CLIENT_OBJECTS_H
#define LWM2M_CPP_CLIENT_OBJECTS_H

#include <inttypes.h>
#include <zephyr.h>

namespace nx {
    struct lwm2m_instance_base {
        uint16_t instance_id;
    };

    typedef void*(*read_cb_t)(lwm2m_instance_base* instance);

    template<uint16_t res_id>
    struct lwm2m_object_resource{
        uint16_t obj_id;
        read_cb_t read_cb;
        void* user_data;
    };

    template <uint16_t obj_id>
    struct lwm2m_object_base {
        uint16_t object_id {obj_id};
        sys_slist_t instances_list SYS_SLIST_STATIC_INIT(instances_list);

        void register_instance(lwm2m_instance_base* instance);
        void delete_instance(uint16_t id);
    };
}

#endif //LWM2M_CPP_CLIENT_OBJECTS_H
