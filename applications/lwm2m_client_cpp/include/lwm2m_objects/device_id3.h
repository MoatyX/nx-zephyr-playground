//
// Created by moaty on 20.11.20.
//

#ifndef LWM2M_CLIENT_CPP_DEVICE_ID3_H
#define LWM2M_CLIENT_CPP_DEVICE_ID3_H

#include "objects.h"

namespace nx {
    namespace id3 {
        class instance : public lwm2m_instance_base {
        public:
            char *manufacturer;
            char *model_number;
            char *serial_umber;
            char *firmware_version;

            executable reboot;
            executable factory_rest;

            multi_inst_resource<int, 5> available_power_sources;
            multi_inst_resource<int, 5> power_source_voltage;
            multi_inst_resource<int, 5> power_source_current;

            int battery_level;
            int memory_free;
            multi_inst_resource<int, 7> error_code;

            executable reset_error_code;

            char current_time[DEFAULT_MAX_STR_LEN];
            char utc_offset[DEFAULT_MAX_STR_LEN];
            char timezone[DEFAULT_MAX_STR_LEN];

            char *supported_binding_and_modes;
            char *device_type;
            char *hardware_version;
            char *software_version;

            int battery_status;
            int memory_total;

            // Objlnk resources are not supported yet - ExtDevInfo;
        };

#define ID3_RES_COUNT   22

        class object : public lwm2m_object_base {
        public:
            object() : lwm2m_object_base(3) {};

            ~object() = default;

            RESOURCE(0, resource_type::PTR, resource_operations::R,
                     ((member_pointer)(&instance::manufacturer)), manufacturer);
            RESOURCE(1, resource_type::PTR, resource_operations::R,
                     ((member_pointer)(&instance::model_number)), model_number);
            RESOURCE(2, resource_type::PTR, resource_operations::R,
                     ((member_pointer)(&instance::serial_umber)), serial_umber);
            RESOURCE(3, resource_type::PTR, resource_operations::R,
                     ((member_pointer)(&instance::firmware_version)), firmware_version);

            RESOURCE(4, resource_type::PTR, resource_operations::EXEC,
                     ((member_pointer)(&instance::reboot)), reboot);
            RESOURCE(5, resource_type::PTR, resource_operations::EXEC,
                     ((member_pointer)(&instance::factory_rest)), factory_rest);

            RESOURCE(6, resource_type::MULTIPLE, resource_operations::R,
                     ((member_pointer)(&instance::available_power_sources)), available_power_sources);
            RESOURCE(7, resource_type::MULTIPLE, resource_operations::R,

                     ((member_pointer)(&instance::power_source_voltage)), power_source_voltage);
            RESOURCE(8, resource_type::MULTIPLE, resource_operations::R,

                     ((member_pointer)(&instance::power_source_current)), power_source_current);


            RESOURCE(9, resource_type::SINGLE, resource_operations::R,
                     ((member_pointer)(&instance::battery_level)), battery_level);
            RESOURCE(10, resource_type::SINGLE, resource_operations::R,
                     ((member_pointer)(&instance::memory_free)), memory_free);
            RESOURCE(11, resource_type::MULTIPLE, resource_operations::R,
                     ((member_pointer)(&instance::error_code)), error_code);

            RESOURCE(12, resource_type::PTR, resource_operations::EXEC,
                     ((member_pointer)(&instance::reset_error_code)), reset_error_code);

            RESOURCE(13, resource_type::SINGLE, resource_operations::RW,
                     ((member_pointer)(&instance::current_time)), current_time);
            RESOURCE(14, resource_type::SINGLE, resource_operations::RW,
                     ((member_pointer)(&instance::utc_offset)), utc_offset);
            RESOURCE(15, resource_type::SINGLE, resource_operations::RW,
                     ((member_pointer)(&instance::timezone)), timezone);

            RESOURCE(16, resource_type::PTR, resource_operations::R,
                     ((member_pointer)(&instance::supported_binding_and_modes)), supported_binding_and_modes);
            RESOURCE(17, resource_type::PTR, resource_operations::R,
                     ((member_pointer)(&instance::device_type)), device_type);
            RESOURCE(18, resource_type::PTR, resource_operations::R,
                     ((member_pointer)(&instance::hardware_version)), hardware_version);
            RESOURCE(19, resource_type::PTR, resource_operations::R,
                     ((member_pointer)(&instance::software_version)), software_version);

            RESOURCE(20, resource_type::SINGLE, resource_operations::R,
                     ((member_pointer)(&instance::battery_status)), battery_status);
            RESOURCE(21, resource_type::SINGLE, resource_operations::R,
                     ((member_pointer)(&instance::memory_total)), memory_total);

        public:
            lwm2m_object_resource **get_all_res(size_t *res_count) override {
                *res_count = ID3_RES_COUNT;
                return all_res;
            }

        private:
            lwm2m_object_resource *all_res[ID3_RES_COUNT]{
                    &manufacturer,
                    &model_number,
                    &serial_umber,
                    &firmware_version,
                    &reboot,
                    &factory_rest,
                    &available_power_sources,
                    &power_source_voltage,
                    &power_source_current,
                    &battery_level,
                    &memory_free,
                    &error_code,
                    &reset_error_code,
                    &current_time,
                    &utc_offset,
                    &timezone,
                    &supported_binding_and_modes,
                    &device_type,
                    &hardware_version,
                    &software_version,
                    &battery_status,
                    &memory_total
            };
        };
    }
}

#endif //LWM2M_CLIENT_CPP_DEVICE_ID3_H
