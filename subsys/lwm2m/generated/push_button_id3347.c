

/**
* AUTOMATICALLY GENERATED CODE
* python LwM2M Objects Generator tool: https://github.com/MoatyX/lwm2m-objects-generator
* Gen Date: 01/2021
*/

#include <init.h>
#include <device.h>

#include <net/lwm2m.h>
#include "lwm2m_object.h"
#include "lwm2m_engine.h"

#define LOG_MODULE_NAME lwm2m_Push_button
#define LOG_LEVEL CONFIG_LWM2M_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL);

/*Object Definitions*/
#define PUSH_BUTTON_OBJECT_ID         3347
#define OBJ_RESOURCES_COUNT     3

#define PUSH_BUTTON_DIGITAL_INPUT_STATE_ID     5500
#define PUSH_BUTTON_DIGITAL_INPUT_COUNTER_ID     5501
#define PUSH_BUTTON_APPLICATION_TYPE_ID     5750
//---------------------------

/*other defines*/
#define MAX_INSTANCE_COUNT				CONFIG_LWM2M_CPP_PUSH_BUTTON_MAX_INSTANCE_COUNT
//---------------------------

//object management
static struct lwm2m_engine_obj lwm2m_obj;
static struct lwm2m_engine_obj_field fields[] = {
        OBJ_FIELD_DATA(PUSH_BUTTON_DIGITAL_INPUT_STATE_ID, R, BOOL),
        OBJ_FIELD_DATA(PUSH_BUTTON_DIGITAL_INPUT_COUNTER_ID, R_OPT, S64),
        OBJ_FIELD_DATA(PUSH_BUTTON_APPLICATION_TYPE_ID, RW_OPT, STRING),
};
//---------------------------

//instance management
static struct lwm2m_engine_obj_inst instances[MAX_INSTANCE_COUNT];
static struct lwm2m_engine_res res[MAX_INSTANCE_COUNT][OBJ_RESOURCES_COUNT];
static struct lwm2m_engine_res_inst res_inst[MAX_INSTANCE_COUNT][OBJ_RESOURCES_COUNT];
//---------------------------

/**
* called once each time a new object instance is requested to be created.
* @brief this function creates and initializes a new instance.
*/
static struct lwm2m_engine_obj_inst* object_create_callback(uint16_t obj_inst_id) {
	int avail = -1, i = 0, j = 0;

	/* Check that there is no other instance with this ID */
	for (int i = 0; i < MAX_INSTANCE_COUNT; i++) {
		if (instances[i].obj && instances[i].obj_inst_id == obj_inst_id) {
			LOG_ERR("Can not create instance - " "already existing: %u", obj_inst_id);
			return NULL;
		}

		/* Save first available slot i */
		if (avail < 0 && !instances[i].obj) {
			avail = i;
		}
	}

	if (avail < 0) {
		LOG_ERR("Can not create instance - no more room: %u", obj_inst_id);
		return NULL;
	}

    /* instances and resources initialization */
	memset(res[avail], 0, sizeof(res[avail][0]) * OBJ_RESOURCES_COUNT); //set every instance resource pointer to NULL
    init_res_instance(res_inst[avail], OBJ_RESOURCES_COUNT);            //set pointers to NULL and flag to RES_INSTANCE_NOT_CREATED

    //after setting everything to NULL, now assign the IDs and bind res with res_inst for every res
    INIT_OBJ_RES_OPTDATA(PUSH_BUTTON_DIGITAL_INPUT_STATE_ID, res[avail], i, res_inst[avail], j);
    INIT_OBJ_RES_OPTDATA(PUSH_BUTTON_DIGITAL_INPUT_COUNTER_ID, res[avail], i, res_inst[avail], j);
    INIT_OBJ_RES_OPTDATA(PUSH_BUTTON_APPLICATION_TYPE_ID, res[avail], i, res_inst[avail], j);

    instances[avail].resources = res[avail];
    instances[avail].resource_count = i;

    LOG_DBG("Create Push_button instance: %d", obj_inst_id);
    return &instances[avail];
}

#include <sys/printk.h>
//called once by the Kernel
static int register_Push_button_object(const struct device *dev) {
    lwm2m_obj.obj_id = PUSH_BUTTON_OBJECT_ID;
    lwm2m_obj.fields = fields;
    lwm2m_obj.field_count = OBJ_RESOURCES_COUNT;            //TODO: make dynamic for supporting the non-standard TIME_STAMP resource as an extension for example?
    lwm2m_obj.max_instance_count = MAX_INSTANCE_COUNT;
    lwm2m_obj.create_cb = object_create_callback;

    lwm2m_register_obj(&lwm2m_obj);
    return 0;
}

SYS_INIT(register_Push_button_object, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);