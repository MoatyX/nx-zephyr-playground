//
// Created by moaty on 24.11.20.
//

#ifndef LWM2M_CLIENT_CPP_MULTI_INST_RESOUCE_H
#define LWM2M_CLIENT_CPP_MULTI_INST_RESOUCE_H

#define DEFAULT_MAX_INST_COUNT  10

/**
 * a class to manage multi-instance resources
 */
class multi_inst_resource {
public:
    multi_inst_resource() = default;
    ~multi_inst_resource() = default;

    /**
     *
     * @param inst_val
     * @return
     */
    bool allocate_instance(int inst_val);
    bool index(int i, int* out_val);

private:
    int current_alloc_head;
    int instances_val[DEFAULT_MAX_INST_COUNT];
};


#endif //LWM2M_CLIENT_CPP_MULTI_INST_RESOUCE_H
