
/**
* AUTOMATICALLY GENERATED CODE
* python LwM2M Objects Generator tool: https://github.com/MoatyX/lwm2m-objects-generator
* Gen Date: 12/2020
*/

#ifndef NX_GENERATED_PUSH_BUTTON_ID_3347_H_
#define NX_GENERATED_PUSH_BUTTON_ID_3347_H_

#include "objects.h"        //class definitions and macros to help construct lwm2m objects in C++

namespace nx {
    namespace id3347 {
#define id3347_RES_COUNT    3         //number of resource this object has

        /**
         * @brief return the number of resources Object 3347 has
         */
        static constexpr uint32_t RES_COUNT() {
            return id3347_RES_COUNT;
        }

        class instance : public lwm2m_instance_base {
        public:
            instance() = default;
            ~instance() = default;

        public:
            bool digital_input_state;
            uint64_t digital_input_counter;
            char* application_type;
        };

        class object : public lwm2m_object_base {
        public:
            object() : lwm2m_object_base(3347) {};
            ~object() = default;

            //Lwm2mResource definitions
            RESOURCE(5500, resource_type::SINGLE, resource_operations::R,
                     (member_pointer)(&instance::digital_input_state), digital_input_state);

            RESOURCE(5501, resource_type::SINGLE, resource_operations::R,
                     (member_pointer)(&instance::digital_input_counter), digital_input_counter);

            RESOURCE(5750, resource_type::PTR, resource_operations::RW,
                     (member_pointer)(&instance::application_type), application_type);


        public:

            /**
            * @brief interface function to return a pointer array of all the resource a derived object has
            * @param[out] res_count: number of the total resources
            * @return array of pointers to the resources an object has
            */
            lwm2m_object_resource **get_all_res(size_t *res_count) override {
                if(res_count != nullptr) *res_count = RES_COUNT();
                return all_res;
            }

        private:
            //define all resources
            lwm2m_object_resource* all_res[RES_COUNT()] {
                    &digital_input_state,
                    &digital_input_counter,
                    &application_type
            };
        };
    }
}

#endif  //NX_GENERATED_PUSH_BUTTON_ID_3347_H_