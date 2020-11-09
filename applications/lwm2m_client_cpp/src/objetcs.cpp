//
// Created by moaty on 04.11.20.
//

#include "objects.h"

namespace nx {
//    enabling this causes cxa_pure_function error
//    lwm2m_object_base::lwm2m_object_base(uint16_t obj_id) : object_id(obj_id) {
//        current_instances_count = 0;
//    }

    void lwm2m_object_base::register_instance(lwm2m_instance_base *instance) {
        //TODO: remove this and use dynamic memory at some point
        if(current_instances_count >= MAX_INSTANCES) return;

        instances_list[current_instances_count] = instance;
        current_instances_count++;
        //=======================================================
    }

    lwm2m_instance_base *lwm2m_object_base::get_instance(size_t index) {
        //TODO: do dynamic memory stuff...
        if(index > MAX_INSTANCES - 1) return nullptr;
        return instances_list[index];
        //==================================================
    }

    lwm2m_object_resource::lwm2m_object_resource(uint16_t obj_id, resource_operations op) {
        this->obj_id=obj_id;
        this->operation=op;
    }
}

