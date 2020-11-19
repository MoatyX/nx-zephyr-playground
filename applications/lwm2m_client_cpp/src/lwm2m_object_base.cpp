//
// Created by moaty on 09.11.20.
//

#include "lwm2m_object_base.h"

namespace nx {
//    enabling this causes cxa_pure_function error
//    lwm2m_object_base::lwm2m_object_base(uint16_t obj_id) : object_id(obj_id) {
//        current_instances_count = 0;
//    }

    bool lwm2m_object_base::register_instance(lwm2m_instance_base *instance) {
        //statically allocated memory
        if(current_instances_count >= MAX_INSTANCES) return false;

        instances_list[current_instances_count] = instance;
        current_instances_count++;
        return true;
        //=======================================================
    }

    lwm2m_instance_base *lwm2m_object_base::get_instance(size_t index) {
        //statically allocated memory
        if(index > MAX_INSTANCES - 1) return nullptr;
        return instances_list[index];
        //==================================================
    }
}