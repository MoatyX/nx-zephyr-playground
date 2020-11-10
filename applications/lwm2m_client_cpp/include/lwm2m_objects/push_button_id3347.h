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
            int digital_input_counter;
            char application_type[60];
        };

#define ID3347_RES_COUNT    3
        class object : public lwm2m_object_base {
        public:
            object() : lwm2m_object_base(3347){};
            ~object() = default;

            Resource2(5500, resource_operations::R, (bool lwm2m_instance_base::*)(&instance::digital_input_state), digital_input_state);
//            Resource(5500, resource_operations::R, digital_input_state);
            Resource(5501, resource_operations::R, digital_input_counter);
            Resource(5750, resource_operations::RW, application_type);

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
