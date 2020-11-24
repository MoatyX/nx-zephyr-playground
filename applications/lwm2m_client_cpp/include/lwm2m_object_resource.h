//
// Created by moaty on 09.11.20.
//

#ifndef LWM2M_CLIENT_CPP_LWM2M_OBJECT_RESOURCE_H
#define LWM2M_CLIENT_CPP_LWM2M_OBJECT_RESOURCE_H

#include "lwm2m_instance_base.h"
#include "lwm2m_cpp.h"

namespace nx {

    /**
     * type of operations. this effects only how the bind with the internal lwm2m engine is made
     */
    typedef enum class resource_operations {
        R,
        RW,
        EXEC
    } resource_operations_t;

    typedef enum class resource_type{
        /**
         * single resource instance.
         * CAN be used with all data types EXCEPT: pointer types (char*, int*, execute types)
         * and types that are specified according to standards, as Single instance types (i.e: can have only 1 instance)
         */
        SINGLE,
        /**
         * multiple resource instance.
         * CAN be used only with types specified as Multiple instance types
         */
        MULTIPLE,
        /**
         * a single pointer type, ex: char*
         * this option effects only how pointers to the data are internally interpreted.
         * CAN only be used with pointer types (char*, int*, ...) and execute resource type
         */
        PTR
    } resource_type_t;

/**
 * @brief a struct that contains base members for each lwm2m object resource
 * @tparam res_id
 */
typedef void* lwm2m_instance_base::* member_pointer;
    class lwm2m_object_resource {
    public:
        lwm2m_object_resource(uint16_t resource_ud, resource_type_t res_type, resource_operations_t op,
                              member_pointer mem_ptr, uint16_t mem_size);
        ~lwm2m_object_resource() = default;

        void set_read_callback(lwm2m_engine_get_data_cb_t read_callback);
        void set_post_write_callback(lwm2m_engine_set_data_cb_t write_callback);
        lwm2m_engine_get_data_cb_t get_read_cb();
        lwm2m_engine_set_data_cb_t get_post_write_cb();

    public:
        member_pointer mem_ptr;
        uint16_t resource_id;
        resource_operations_t operation;
        resource_type_t  type;
        uint16_t member_size;
        uint8_t user_data_flags{0};

    private:
        lwm2m_engine_get_data_cb_t read_cb {nullptr};
        lwm2m_engine_set_data_cb_t write_cb {nullptr};
        lwm2m_engine_user_cb_t  delete_cb {nullptr};
    };
}


#endif //LWM2M_CLIENT_CPP_LWM2M_OBJECT_RESOURCE_H
