//
// Created by moaty on 04.11.20.
//

#include "utility.h"

#include <zephyr.h>
#include <string.h>
#include <stdio.h>

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

    char* lwm2m_object_to_path(uint16_t obj_id, uint16_t obj_inst_id, uint16_t resource_id) {
        clear_buffer();
        snprintk(buffer, NX_UTILITY_MAX_BUFFER_SIZE, "%d/%d/%d", obj_id, obj_inst_id, resource_id);
        return buffer;
    }

    void set_str(char *src, size_t strlen, const char *target) {
        snprintf(src, strlen, "%s", target);
    }

    void set_str(char *src, const char *target) {
        set_str(src, strlen(target) + 1, target);
    }

    void hex_dump(const char *desc, const void *addr, int len) {
        int i;
        unsigned char buff[17];
        const auto * pc = (const unsigned char *)addr;

        // Output description if given.

        if (desc != NULL)
            printk ("%s:\n", desc);

        // Length checks.

        if (len == 0) {
            printk("  ZERO LENGTH\n");
            return;
        }
        else if (len < 0) {
            printk("  NEGATIVE LENGTH: %d\n", len);
            return;
        }

        // Process every byte in the data.

        for (i = 0; i < len; i++) {
            // Multiple of 16 means new line (with line offset).

            if ((i % 16) == 0) {
                // Don't print ASCII buffer for the "zeroth" line.

                if (i != 0)
                    printk ("  %s\n", buff);

                // Output the offset.

                printk ("  %04x ", i);
            }

            // Now the hex code for the specific character.
            printk (" %02x", pc[i]);

            // And buffer a printable ASCII character for later.

            if ((pc[i] < 0x20) || (pc[i] > 0x7e)) // isprint() may be better.
                buff[i % 16] = '.';
            else
                buff[i % 16] = pc[i];
            buff[(i % 16) + 1] = '\0';
        }

        // Pad out last line if not exactly 16 characters.

        while ((i % 16) != 0) {
            printk ("   ");
            i++;
        }

        // And print the final ASCII buffer.

        printf ("  %s\n", buff);
    }
}
