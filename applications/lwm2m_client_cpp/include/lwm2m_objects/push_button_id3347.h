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

        class object : public lwm2m_object_base {
        public:
            object() : lwm2m_object_base(3347){};
            ~object() = default;

            Resource(5500, resource_operations::R, digital_input_state);
            Resource(5501, resource_operations::R, digital_input_counter);
            Resource(5750, resource_operations::RW, application_type);

            const lwm2m_object_resource ** get_all_res() const override {
                return nullptr;
            }

            lwm2m_object_resource** ress() {
//                return const_cast<lwm2m_object_resource **>(all_res);
//                return static_cast<const lwm2m_object_resource **>(all_res);
            }

        private:
            const lwm2m_object_resource *all_res[3]{&digital_input_state, &digital_input_counter, &application_type};
        };
    }

}

#endif //LWM2M_CLIENT_CPP_PUSH_BUTTON_ID3347_H
