//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_LWM2M_OBJECT_BASE_H
#define LWM2M_CLIENT_CPP_LWM2M_OBJECT_BASE_H


#include "lwm2m_instance_base.h"
#include "lwm2m_object_resource.h"
#include <zephyr.h>

namespace nx {

    class lwm2m_object_base {
    public:
        explicit inline lwm2m_object_base(uint16_t obj_id) : object_id{obj_id} {
            current_instances_count = 0;
        }

        ~lwm2m_object_base() = default;

        bool register_instance(lwm2m_instance_base* instance);
        lwm2m_instance_base* get_instance(size_t index);

        /**
         * get a reference to all resource of a lwm2m object
         * @param[out] res_count: gives out an integer which tells how many resource the lwm2m object have
         * @return an array of pointers to all the resources a lwm2m object have
         */
        virtual lwm2m_object_resource** get_all_res(size_t* res_count) = 0;

    public:
        const uint16_t object_id;
        size_t current_instances_count;
    private:
        //Static memory allocation
#define MAX_INSTANCES   2
        lwm2m_instance_base* instances_list[MAX_INSTANCES]{nullptr};
        //=============================================================
    };
}


#endif //LWM2M_CLIENT_CPP_LWM2M_OBJECT_BASE_H
