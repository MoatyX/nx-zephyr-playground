/*
 * Copyright (c) 2020 Navimatix GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <autoconf.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(NX_LWM2M_CPP_CLIENT, LOG_LEVEL_DBG);

#include "lwm2m_context.h"
#include "utility.h"

#include <generated_lwm2m_objects/push_button_id3347.h>

#define DEVICE_NAME CONFIG_BOARD
#define SERVER_ADDR CONFIG_NET_CONFIG_PEER_IPV4_ADDR

static void rd_client_event(struct lwm2m_ctx *client, enum lwm2m_rd_client_event client_event);

nx::lwm2m_context context(DEVICE_NAME);
nx::id3347::object push_button_obj;
nx::id3347::instance button_inst;

void *app_type_read_cb(uint16_t obj_inst_id, uint16_t res_id, uint16_t res_inst_id, size_t *data_len) {
    static char* output = "Hello Read callback!";
    *data_len = strlen(output);
    return output;
}

int inst_delete(uint16_t inst_id) {
    printk("deleting instance %d\n", inst_id);

    /* some processing.... */

    return 0;   //return 0 if all good, otherwise a negative error code from errorno.h
}

//example of binding the reboot callback of the device object (id3) to this function
int device_reboot_cb(uint16_t inst_id) {
    printk("REBOOOTING!!!\n");

    /* some processing.... */

    return 0;   //return 0 if all good, otherwise a negative error code from errorno.h
}

void main() {
    LOG_INF("LwM2M C++ Client is starting....");
    context.set_server_address(69, SERVER_ADDR);

    //set some data to the Button Instance object
    button_inst.instance_id = 0;
    button_inst.digital_input_state = false;
    button_inst.digital_input_counter = 1337;
    button_inst.set_delete_cb(inst_delete);
    push_button_obj.application_type.set_read_callback(app_type_read_cb);
    push_button_obj.register_instance(&button_inst);

    context.device_instance.manufacturer = "Navimatix";
    context.device_instance.device_type = "Zephyr LwM2M C++ Client model";
    context.device_instance.reboot = device_reboot_cb;
    context.device_instance.available_power_sources.allocate_instance(69);      //multi instance resource demo

    context.register_object(&push_button_obj);
    context.start(0, rd_client_event);
}

// Client event callback function
static void rd_client_event(struct lwm2m_ctx *client, enum lwm2m_rd_client_event client_event)
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

