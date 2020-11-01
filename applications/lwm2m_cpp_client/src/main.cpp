#include <zephyr.h>
#include <autoconf.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(NX_LWM2M_CPP_CLIENT, LOG_LEVEL_DBG);

#include "objects.h"
#include "lwm2m_context.h"
#include "objects/push_button_3347.h"

#define DEVICE_NAME CONFIG_BOARD
#define SERVER_ADDR CONFIG_NET_CONFIG_PEER_IPV4_ADDR

// Client event callback function
static void rd_client_event(struct lwm2m_ctx *client,
                            enum lwm2m_rd_client_event client_event)
{
    switch (client_event)
    {

    case LWM2M_RD_CLIENT_EVENT_NONE:
        /* do nothing */
        break;

    case LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_FAILURE:
        LOG_DBG("Bootstrap registration failure!");
        break;

    case LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_COMPLETE:
        LOG_DBG("Bootstrap registration complete");
        break;

    case LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_TRANSFER_COMPLETE:
        LOG_DBG("Bootstrap transfer complete");
        break;

    case LWM2M_RD_CLIENT_EVENT_REGISTRATION_FAILURE:
        LOG_DBG("Registration failure!");
        break;

    case LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE:
        LOG_DBG("Registration complete");
        break;

    case LWM2M_RD_CLIENT_EVENT_REG_UPDATE_FAILURE:
        LOG_DBG("Registration update failure!");
        break;

    case LWM2M_RD_CLIENT_EVENT_REG_UPDATE_COMPLETE:
        LOG_DBG("Registration update complete");
        break;

    case LWM2M_RD_CLIENT_EVENT_DEREGISTER_FAILURE:
        LOG_DBG("Deregister failure!");
        break;

    case LWM2M_RD_CLIENT_EVENT_DISCONNECT:
        LOG_DBG("Disconnected");
        break;

    case LWM2M_RD_CLIENT_EVENT_QUEUE_MODE_RX_OFF:
        LOG_DBG("Queue mode RX window closed");
        break;
    }
}

void* digital_button_read_cb(nx::push_button_3347_inst* instance) {
    return &instance->digital_input_state;
}

void main()
{
    LOG_INF("Starting the C++ Client");
    nx::lwm2m_context context(DEVICE_NAME);
    context.set_server_address(101, SERVER_ADDR);

    /*register objects*/

    //example: push button object
    static bool push_button_state = false;
    static nx::push_button_3347 push_button_obj;
    static nx::push_button_3347_inst push_button_inst;

    //now initialise that object
    push_button_obj.digital_input_state.user_data = &push_button_state;     //provide a pointer to the data that represents this resource
    push_button_obj.digital_input_state.read_cb = reinterpret_cast<nx::read_cb_t>(&digital_button_read_cb);  //some read callback function
    push_button_obj.register_instance(&push_button_inst);                   //register the instance
    context.register_object(&push_button_obj);
    //===========================================================================

    /*start the connection*/
    context.start(0, rd_client_event);
}