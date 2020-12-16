//
// Created by moaty on 24.11.20.
//

#ifndef LWM2M_CLIENT_CPP_MULTI_INST_RESOUCE_H
#define LWM2M_CLIENT_CPP_MULTI_INST_RESOUCE_H

#include <inttypes.h>

namespace nx {

/**
 * a class to manage multi-instance resources
 */
    template<typename T, uint16_t max_count>
    class multi_inst_resource {
    public:
        multi_inst_resource() = default;

        ~multi_inst_resource() = default;

        bool allocate_instance(T inst_val);

        //access an element by index
        bool index(int i, T *out_val);

        //access an element by index
        bool index(int i, T** out_ptr_val);
        int get_allocated_count() const;

        constexpr inline static int size() {
            return sizeof(decltype(instances_val));
        };

    private:
        int current_alloc_head = 0;
        T instances_val[max_count];
    };

    template<typename T, uint16_t max_count>
    bool multi_inst_resource<T, max_count>::allocate_instance(T inst_val) {
        if (current_alloc_head + 1 > max_count) return false;

        instances_val[current_alloc_head] = inst_val;
        current_alloc_head++;

        return true;
    }

    template<typename T, uint16_t max_count>
    bool multi_inst_resource<T, max_count>::index(int i, T *out_val) {
        if (i >= max_count) return false;
        *out_val = instances_val[i];
        return true;
    }

    template<typename T, uint16_t max_count>
    int multi_inst_resource<T, max_count>::get_allocated_count() const {
        return current_alloc_head;
    }

    template<typename T, uint16_t max_count>
    bool multi_inst_resource<T, max_count>::index(int i, T **out_ptr_val) {
        if (i >= max_count) return false;
        *out_ptr_val = &instances_val[i];
        return true;
    }
}


#endif //LWM2M_CLIENT_CPP_MULTI_INST_RESOUCE_H
