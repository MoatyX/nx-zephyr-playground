#include "lwm2m_context.h"
#include <zephyr.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(NX_LWM2M_CONTEXT, LOG_LEVEL_DBG);

namespace nx
{
    lwm2m_context::lwm2m_context(const char *endpoint_name)
    {
        endpoint_name_ = endpoint_name;
    }

    void lwm2m_context::set_server_address(uint16_t short_server_id, const char *server_addr)
    {
        /*
        * later once we have a working Template. 
        * we will use member lwm2m instances to do the following steps
        */
        uint16_t server_url_len = 0;
        uint8_t server_url_flags = 0;
        lwm2m_engine_get_res_data("0/0/0", (void **)&server_address_, &server_url_len, &server_url_flags);

        // TODO: remove later to support DTLS and Bootrapping
        snprintk(server_address_, server_url_len, "coap://%s", server_addr);

        // Match Security object instance ID with a Short Server ID of the Server instance
        lwm2m_engine_set_u16("0/0/10", short_server_id); //security object instance "ID"
        lwm2m_engine_set_u16("1/0/0", short_server_id);  //server object instance "Short Server ID"
        lwm2m_engine_set_string("0/0/0", "coap://192.0.2.2");
    }

    void lwm2m_context::start(uint32_t flags, lwm2m_ctx_event_cb_t client_event_callback)
    {
        lwm2m_rd_client_start(&client, endpoint_name_, flags, client_event_callback); //start client
    }

    template<uint16_t obj_id>
    void lwm2m_context::register_object(lwm2m_object_base<obj_id> *obj) {

    }

    void lwm2m_context::delete_object(uint16_t obj_id) {

    }

} // namespace nx