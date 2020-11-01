#include <zephyr.h>
#include <autoconf.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(NX_LWM2M_CPP_CLIENT, LOG_LEVEL_DBG);

#include "lwm2m_context.h"

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

void main()
{
    LOG_INF("Starting the C++ Client");
    nx::lwm2m_context context(DEVICE_NAME);
    context.set_server_address(101, SERVER_ADDR);
    context.start(0, rd_client_event);
}