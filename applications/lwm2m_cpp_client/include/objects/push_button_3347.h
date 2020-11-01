//
// Created by moaty on 01.11.20.
//

#ifndef LWM2M_CPP_CLIENT_PUSH_BUTTON_3347_H
#define LWM2M_CPP_CLIENT_PUSH_BUTTON_3347_H


#include "objects.h"

namespace nx {
    class push_button_3347 : public lwm2m_object_base<3347> {
    public:
        push_button_3347() = default;
        ~push_button_3347() = default;

    public:
        lwm2m_object_resource<5500> digital_input_state;
    };

    class push_button_3347_inst : public lwm2m_instance_base {
    public:
        bool digital_input_state;
    };
}

#endif //LWM2M_CPP_CLIENT_PUSH_BUTTON_3347_H
