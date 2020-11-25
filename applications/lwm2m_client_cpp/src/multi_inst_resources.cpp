//
// Created by moaty on 24.11.20.
//

#include "multi_inst_resources.h"

namespace nx {
    bool multi_inst_resource::allocate_instance(int inst_val) {
        if (current_alloc_head + 1 > DEFAULT_MAX_INST_COUNT) return false;

        instances_val[current_alloc_head] = inst_val;
        current_alloc_head++;

        return true;
    }

    bool multi_inst_resource::index(int i, int *out_val) {
        if (i >= DEFAULT_MAX_INST_COUNT) return false;
        *out_val = instances_val[i];
        return true;
    }

    int multi_inst_resource::get_allocated_count() const {
        return current_alloc_head;
    }

    bool multi_inst_resource::index(int i, int **out_ptr_val) {
        if (i >= DEFAULT_MAX_INST_COUNT) return false;
        *out_ptr_val = &instances_val[i];
        return true;
    }
}
