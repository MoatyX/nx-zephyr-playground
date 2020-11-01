#
# Copyright (c) 2020 Navimatix GmbH
#
# SPDX-License-Identifier: Apache-2.0
#


################################################################################

cmake_minimum_required(VERSION 3.13.1)

set(NX_SUPPORTED_BOARDS
    qemu_x86
)

set(NX_SUPPORTED_BUILD_TYPES
  ZDebug
  ZDebugWithShell
  ZRelease
)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE ZRelease)
endif()

################################################################################

# Boilerplate code, which checks the given application setup.
include(../../cmake/boilerplate.cmake)

project("LwM2M Client" VERSION 0.1)
target_sources(app PRIVATE src/main.c)