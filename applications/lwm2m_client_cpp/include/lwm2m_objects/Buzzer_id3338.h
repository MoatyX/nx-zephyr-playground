

/**
* AUTOMATICALLY GENERATED CODE
* python LwM2M Objects Generator tool: https://github.com/MoatyX/lwm2m-objects-generator
* Gen Date: 12/2020
*/

#ifndef NX_GENERATED_BUZZER_ID_3338_H_
#define NX_GENERATED_BUZZER_ID_3338_H_

#include "objects.h"        //class definitions and macros to help construct lwm2m objects in C++

namespace nx {
    namespace id3338 {
        #define ID3338_RES_COUNT    5         //number of resource this object has

        class instance : public lwm2m_instance_base {
        public:
            instance() = default;
            ~instance() = default;

        public:
            bool on_off;
            int64_t dimmer;
            float delay_duration;
            float minimum_off_time;
            char* application_type;
            
        };

        class object : public lwm2m_object_base {
        public:
            object() : lwm2m_object_base(3338) {};
            ~object() = default;

            //Lwm2mResource definitions
            RESOURCE(5850, resource_type::SINGLE, resource_operations::RW,
                    (member_pointer)(&instance::on_off), on_off);
            RESOURCE(5851, resource_type::SINGLE, resource_operations::RW,
                    (member_pointer)(&instance::dimmer), dimmer);
            RESOURCE(5521, resource_type::SINGLE, resource_operations::RW,
                    (member_pointer)(&instance::delay_duration), delay_duration);
            RESOURCE(5525, resource_type::SINGLE, resource_operations::RW,
                    (member_pointer)(&instance::minimum_off_time), minimum_off_time);
            RESOURCE(5750, resource_type::PTR, resource_operations::RW,
                    (member_pointer)(&instance::application_type), application_type);
            

        public:

            /**
            * @brief interface function to return a pointer array of all the resource a derived object has
            * @param[out] res_count: number of the total resources
            * @return array of pointers to the resources an object has
            */
            lwm2m_object_resource **get_all_res(size_t *res_count) override {
                if(res_count != nullptr) *res_count = ID3338_RES_COUNT;
                return all_res;
            }

        private:
            //define all resources
            lwm2m_object_resource* all_res[ID3338_RES_COUNT] {
                &on_off,
                &dimmer,
                &delay_duration,
                &minimum_off_time,
                &application_type
                
            };
        };
    }
}

#endif  //NX_GENERATED_BUZZER_ID_3338_H_