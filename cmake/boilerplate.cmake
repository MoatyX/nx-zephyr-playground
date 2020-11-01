#
# Copyright (c) 2019 Navimatix GmbH
#
# SPDX-License-Identifier: Apache-2.0
#

# Point to NX root directory.
set(NX_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

################################################################################

if(NOT BOARD)
	set(BOARD $ENV{BOARD})
endif()

# Check if selected board is supported.
if(DEFINED NX_SUPPORTED_BOARDS)
	if(NOT BOARD IN_LIST NX_SUPPORTED_BOARDS)
		message(FATAL_ERROR "board ${BOARD} is not supported")
	endif()
endif()

################################################################################

# Check if selected build type is supported.
if(DEFINED NX_SUPPORTED_BUILD_TYPES)
	if(NOT CMAKE_BUILD_TYPE IN_LIST NX_SUPPORTED_BUILD_TYPES)
		message(FATAL_ERROR "${CMAKE_BUILD_TYPE} variant is not supported")
	endif()
endif()

################################################################################

# Add NX_DIR as a BOARD_ROOT in case the board is in NX_DIR
list(APPEND BOARD_ROOT ${NX_DIR})

# Add NX_DIR as a DTS_ROOT to include NX/dts
list(APPEND DTS_ROOT ${NX_DIR})

################################################################################

# Preset the CONF_FILE and extend the original behaviour in Zephyr's
# boilerplate code. So we are able to respect board specific config
# file even in case of CONF_FILE has been specified on the cmake CLI.

if(CONF_FILE)
	# CONF_FILE has either been specified on the cmake CLI or is already
	# in the CMakeCache.txt. This has precedence over the environment
	# variable CONF_FILE and the default prj.conf
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD}.conf)
		set(CONF_FILE "${CONF_FILE} boards/${BOARD}.conf")
	endif()
endif()

set(CONF_FILE ${CONF_FILE} CACHE STRING "If desired, you can build the application using \
the configuration settings specified in an alternate .conf file using this parameter. \
These settings will override the settings in the application’s .config file or its default \
.conf file. Multiple files may be listed, e.g. CONF_FILE=\"prj1.conf prj2.conf\"" FORCE)

# Boilerplate code, which pulls in the Zephyr build system.
# include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

################################################################################
