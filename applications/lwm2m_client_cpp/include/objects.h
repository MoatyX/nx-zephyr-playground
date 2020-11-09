//
// Created by moaty on 04.11.20.
//

#ifndef LWM2M_CLIENT_CPP_OBJECTS_H
#define LWM2M_CLIENT_CPP_OBJECTS_H

#include <zephyr.h>

namespace nx {

    /**
    * @brief base struct for all lwm2m instance
    */
    class lwm2m_instance_base {
    public:
        lwm2m_instance_base() = default;
        ~lwm2m_instance_base() = default;

        uint16_t instance_id;
    };

    /**
     * @brief a function pointer to a read callback
     * @param[in] instance: a pointer to the instance from which a resource is read
     */
    typedef void*(*read_cb_t)(lwm2m_instance_base* instance);

    typedef enum class resource_operations {
        R,
        RW,
        EXEC
    } resource_operations_t;

    /**
     * @brief a struct that contains base members for each lwm2m object resource
     * @tparam res_id
     */
    struct lwm2m_object_resource{
        lwm2m_object_resource(uint16_t obj_id, resource_operations op);

        uint16_t obj_id;
        read_cb_t read_cb{nullptr};
        resource_operations_t operation;
        void* p_user_data{nullptr};
    };

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

        constexpr virtual const lwm2m_object_resource** get_all_res() const = 0;

//        virtual void test_function() = 0;

    public:
        const uint16_t object_id;
        size_t current_instances_count;

    private:
        //TODO: remove later and use dynamic memory. use this for testing and development purposes only
#define MAX_INSTANCES   2
        lwm2m_instance_base* instances_list[MAX_INSTANCES]{nullptr};
        //=============================================================
    };

#define Resource(id, op, resource_name)   lwm2m_object_resource resource_name{(id), (op)}
}

#endif //LWM2M_CLIENT_CPP_OBJECTS_H
