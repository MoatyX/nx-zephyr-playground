//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_LWM2M_OBJECT_BASE_H
#define LWM2M_CLIENT_CPP_LWM2M_OBJECT_BASE_H


#include "lwm2m_instance_base.h"
#include "lwm2m_object_resource.h"
#include <zephyr.h>

namespace nx {

    /**
     * @brief an internal struct used for creating linked list containing pointers to all instances of a lwm2m objects
     */
    typedef struct instance_node {
        sys_snode_t list_node;      //internal use
        lwm2m_instance_base* lwm2m_instance;
    } instance_node_t;

    class lwm2m_object_base {
    public:
        explicit inline lwm2m_object_base(uint16_t obj_id) : object_id{obj_id} {
            current_instances_count = 0;
        };
        ~lwm2m_object_base() = default;

        void register_instance(lwm2m_instance_base* instance);
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

    protected:

    private:
        //TODO: remove later and use dynamic memory. use this for testing and development purposes only
#define MAX_INSTANCES   2
        lwm2m_instance_base* instances_list[MAX_INSTANCES]{nullptr};
        //=============================================================

//        void * obj_internal_read_cb(uint16_t obj_inst_id, uint16_t res_id, uint16_t res_inst_id, size_t *data_len);
    };
}


#endif //LWM2M_CLIENT_CPP_LWM2M_OBJECT_BASE_H
