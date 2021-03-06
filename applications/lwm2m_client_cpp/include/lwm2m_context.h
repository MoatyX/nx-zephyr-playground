//
// Created by moaty on 04.11.20.
//

#ifndef LWM2M_CLIENT_CPP_LWM2M_CONTEXT_H
#define LWM2M_CLIENT_CPP_LWM2M_CONTEXT_H

#include "lwm2m_cpp.h"

#include "objects.h"

#include "lwm2m_objects/device_id3.h"

namespace nx {
    class lwm2m_context {
    public:

        /**
         * @param endpoint_name[in] the name of the endpoint wished to be.
         */
        explicit lwm2m_context(const char *endpoint_name);
        ~lwm2m_context() = default;

        /**
        * @brief set a target server to connect with
        *
        * @param[in] A unique server id
        * @param[in] the IP address of the target server
        *
        */
        void set_server_address(uint16_t short_server_id, const char *server_addr);

        /**
         * @brief start a connection with a server
         * @param[in] flags: extra configuration to the lwm2m engine if needed.
         * @param[in] client_event_callback: callback to function for every client event
         */
        void start(uint32_t flags, lwm2m_ctx_event_cb_t client_event_callback);

        /**
         * try register a new lwm2m object
         * @param obj pointer to the object's class
         * @return true if registration successful
         */
        bool register_object(lwm2m_object_base* obj, bool internal_obj = false);

        /**
         * @brief unregister (delete) an object instance
         * @param obj
         * @param instance_id
         */
        void unregister_object_instance(uint16_t object_id, uint16_t instance_id);

    public:
        id3::object device;
        id3::instance device_instance;

    private:
        const char *endpoint_name;
        char *server_address;

        struct lwm2m_ctx client{};
    };
}


#endif //LWM2M_CLIENT_CPP_LWM2M_CONTEXT_H
