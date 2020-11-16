//
// Created by moaty on 04.11.20.
//

#ifndef LWM2M_CLIENT_CPP_PUSH_BUTTON_ID3347_H
#define LWM2M_CLIENT_CPP_PUSH_BUTTON_ID3347_H

#include "objects.h"

namespace nx {
    namespace id3347 {
        class instance : public lwm2m_instance_base {
        public:
            instance() = default;
            ~instance() = default;

            bool digital_input_state;
            uint64_t digital_input_counter;
            char application_type[DEFAULT_MAX_STR_LEN];
        };

#define ID3347_RES_COUNT    3
        class object : public lwm2m_object_base {
        public:
            object() : lwm2m_object_base(3347){};
            ~object() = default;

            Resource(5500, resource_operations::R, ((member_pointer)(&instance::digital_input_state)),
                     MemberSize(instance::digital_input_state), digital_input_state);
            Resource(5501, resource_operations::R,((member_pointer)(&instance::digital_input_counter)),
                     MemberSize(instance::digital_input_counter), digital_input_counter);
            Resource(5750, resource_operations::RW, ((member_pointer)(&instance::application_type)),
                     MemberSize(instance::application_type), application_type);

        public:
            lwm2m_object_resource ** get_all_res(size_t* res_count) override {
                *res_count = ID3347_RES_COUNT;
                return all_res;
            }

        private:
            lwm2m_object_resource *all_res[ID3347_RES_COUNT]{&digital_input_state, &digital_input_counter, &application_type};
        };
    }

}

#endif //LWM2M_CLIENT_CPP_PUSH_BUTTON_ID3347_H
