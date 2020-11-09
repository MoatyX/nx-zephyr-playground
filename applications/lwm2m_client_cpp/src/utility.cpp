//
// Created by moaty on 04.11.20.
//

#include "utility.h"

#include <zephyr.h>
#include <string.h>

namespace nx {

    char buffer[NX_UTILITY_MAX_BUFFER_SIZE] = {0};

    void clear_buffer() {
        memset(buffer, 0, NX_UTILITY_MAX_BUFFER_SIZE);
    }

    char* lwm2m_object_to_path(uint16_t obj_id, uint16_t obj_inst_id) {
        clear_buffer();
        snprintk(buffer, NX_UTILITY_MAX_BUFFER_SIZE, "%d/%d", obj_id, obj_inst_id);
        return buffer;
    }
    char* lwm2m_object_to_path(uint16_t obj_id, uint16_t obj_inst_id, uint16_t resource_id, uint16_t resource_inst_id) {
        clear_buffer();
        snprintk(buffer, NX_UTILITY_MAX_BUFFER_SIZE, "%d/%d/%d/%d", obj_id, obj_inst_id, resource_id, resource_inst_id);
        return buffer;
    }
}
