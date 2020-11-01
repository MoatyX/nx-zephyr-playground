#if !defined(LWM2M_CONTEXT_H_)
#define LWM2M_CONTEXT_H_

#include "objects.h"

extern "C" {
#include <net/lwm2m.h>
}

namespace nx
{
    /*
    * inital implementation of a c++ lwm2m_client
    * what this class DOES NOT do yet:
    *   - Support for bootstrapping
    *   - Support for DTLS connections
    */
    class lwm2m_context
    {
    public:
        lwm2m_context(const char *endpoint_name);
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

        template<uint16_t obj_id>
        void register_object(lwm2m_object_base<obj_id>* obj);

        void delete_object(uint16_t obj_id);

    private:
        const char *endpoint_name_;
        char *server_address_;

        struct lwm2m_ctx client{};
    };
} // namespace nx

#endif // LWM2M_CONTEXT_H_
