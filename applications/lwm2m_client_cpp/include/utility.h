//
// Created by moaty on 04.11.20.
//

#ifndef LWM2M_CLIENT_CPP_UTILITY_H
#define LWM2M_CLIENT_CPP_UTILITY_H

#include <stdint.h>

/**
 * @brief this header provides a set of utility methods for common lwm2m operations on the ZephyrRTOS
 * NOTE: this header has an internal buffer of length NX_UTILITY_MAX_BUFFER_SIZE to output strings,
 * so the user doesn't have to provide buffers themselves
 */

#define NX_UTILITY_MAX_BUFFER_SIZE  50

namespace nx {
    char* lwm2m_object_to_path(uint16_t obj_id, uint16_t obj_inst_id);
    char* lwm2m_object_to_path(uint16_t obj_id, uint16_t obj_inst_id, uint16_t resource_id, uint16_t resource_inst_id);
}
#endif //LWM2M_CLIENT_CPP_UTILITY_H
