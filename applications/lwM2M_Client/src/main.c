/*
 * Copyright (c) 2020 Navimatix GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <net/lwm2m.h>
#include <stdio.h>
#include <autoconf.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(LwM2M_Client_Demo, LOG_LEVEL_DBG);

#define CLIENT_MANUFACTURER		"Navimatix"
#define CLIENT_NAME				CONFIG_BOARD

#define HOST_ADDR	CONFIG_NET_CONFIG_PEER_IPV4_ADDR

static struct lwm2m_ctx client;

static int cb_reboot_device(uint16_t obj_inst_id)
{
	LOG_INF("DEVICE: REBOOT");

	//insert reboot logic here....

	return 0;
}

static int lwm2m_setup(void)
{
	LOG_DBG("lwm2m setup");

	//set server address
	char* addr;
	uint16_t server_url_len = 0;
	uint8_t server_url_flags = 0;
	lwm2m_engine_get_res_data("0/0/0", (void **)&addr, &server_url_len, &server_url_flags);
	sprintf(addr, "coap://%s", HOST_ADDR);
	LOG_INF("trying to connect to: %s", log_strdup(addr));

	lwm2m_engine_set_string("0/0/0", addr);

	/* Security Mode */
	lwm2m_engine_set_u8("0/0/2", 3);	// no security

	// Match Security object instance ID with a Short Server ID of the Server instance
	lwm2m_engine_set_u16("0/0/10", 101);		//security object instance "ID"
	lwm2m_engine_set_u16("1/0/0", 101);			//server object instance "Short Server ID"

	//set device Mandatory data: CLIENT_MANUFACTURER
	lwm2m_engine_set_res_data("3/0/0", CLIENT_MANUFACTURER,
				  sizeof(CLIENT_MANUFACTURER),
				  LWM2M_RES_DATA_FLAG_RO);

	//set device mandatory callback: device reboot command
	lwm2m_engine_register_exec_callback("3/0/4", cb_reboot_device);

	return 0;
}

// Client event callback function
static void rd_client_event(struct lwm2m_ctx *client,
			    enum lwm2m_rd_client_event client_event)
{
	switch (client_event) {

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

	}
}

void main(void)
{
	LOG_INF("LwM2M client demo start....");
	lwm2m_setup();		//create LWM2M resources and objects

	lwm2m_rd_client_start(&client, CLIENT_NAME, 0, rd_client_event);	//start client
}
