/*
 * Copyright (c) 2020 Navimatix GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

sys_slist_t list = SYS_SLIST_STATIC_INIT(); //make a list and initialise it

//create a struct to embody the data and the list node
typedef struct node_data
{
    sys_snode_t node; //embedding the node accoroding to the docs
    int x;            //some data
} node_data_t;

#define MAX_INST 2

void main(void)
{
    printk("Hello World! today we learn how to use linked lists in zephyr!\n");

    //make some statically allocated test data
    node_data_t data1 = {
        .x = 69};

    node_data_t data2 = {
        .x = 420};

    sys_slist_append(&list, (sys_snode_t *)&data1);
    sys_slist_append(&list, (sys_snode_t *)&data2);

    //============================================

    //make some dynamically allocated test data
    /*there are 3 ways to allocate memory, each have use cases. to keep it simple. i will just allocate a a memory slab
            *https://docs.zephyrproject.org/1.12.0/kernel/memory/memory.html
            */
    struct k_mem_slab data_slab;
    const int node_data_size = sizeof(node_data_t);
    char __aligned(4) data_buffer[MAX_INST * node_data_size]; //create MAX_INST blocks, each "node_data_size" big, to store 2 node_data_t instances

    k_mem_slab_init(&data_slab, data_buffer, node_data_size, MAX_INST);

    //create some test values
    int test_values[MAX_INST];
    for (size_t i = 0; i < MAX_INST; i++)
    {
        test_values[i] = 2 * i + 1; //some odd numbers
    }

    //now allocate space dynamically....
    for (size_t i = 0; i < MAX_INST; i++)
    {
        node_data_t *dynamic_data = NULL;
        if (k_mem_slab_alloc(&data_slab, (void **)&dynamic_data, K_MSEC(100)) == 0)
        {
            printk("memeory allocated at %p\n", dynamic_data);
            dynamic_data->x = test_values[i];
            sys_slist_append(&list, dynamic_data);
        }
        else
        {
            printk("failed to allocate dynamic memory\n");
        }
    }
    //============================================

    printk("List is Empty: %s \n", sys_slist_is_empty(&list) == 1 ? "true" : "false");

    //use a foreach loop to go through the list
    node_data_t *i;
    SYS_SLIST_FOR_EACH_CONTAINER(&list, i, node)
    {
        printk("val: %d\n", i->x);
    };

    printk("Program finished\n");
}