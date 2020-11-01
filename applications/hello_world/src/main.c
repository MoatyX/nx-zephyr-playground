/*
 * Copyright (c) 2020 Navimatix GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <autoconf.h>

void main(void) {
    printk("Hello World from %s\n", CONFIG_BOARD);
}

