//
// Created by moaty on 01.11.20.
//

#include "objects.h"


namespace nx {
    template<uint16_t obj_id>
    void lwm2m_object_base<obj_id>::register_instance(lwm2m_instance_base *instance) {
//        sys_snode_t node;
//        sys_slist_append(&instances_list, nullptr);
    }

    template<uint16_t obj_id>
    void lwm2m_object_base<obj_id>::delete_instance(uint16_t id) {

    }
}
