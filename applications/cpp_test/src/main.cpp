/*
 * Copyright (c) 2020 Navimatix GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

template<uint16_t id>
class interface
{
public:
    virtual int xx() = 0;
};

class test : public interface<100> {
public:
    virtual int xx() override {
        return 100;
    }
};


void main(void) {
    printk("Hello World! \n");

    test obj;
    obj.xx();
}

