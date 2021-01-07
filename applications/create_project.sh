#!/bin/bash

project_name=$1
board_name=$2

#check a directory with the same name does not exist
if [ -d $project_name ] 
then
    echo "Directory $project_name exists."
    exit 
fi

# create project directory
mkdir $1
cd $1

current_year=`date +'%Y'`

# create the CMake
touch "CMakeLists.txt"
cat > "CMakeLists.txt" <<EOF
#
# Copyright (c) $current_year Navimatix GmbH
#
# SPDX-License-Identifier: Apache-2.0
#


################################################################################

cmake_minimum_required(VERSION 3.13.1)

set(NX_SUPPORTED_BOARDS
  $board_name
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
project($project_name VERSION 0.1)

# Add your source file to the "app" target. This must come after
# the boilerplate code, which defines the target.
FILE(GLOB source_files src/*.c*)
target_sources(app PRIVATE \${source_files})
include_directories("include")
EOF

# create the project configuration file
touch prj.conf
cat > prj.conf <<EOF
CONFIG_PRINTK=y         #enables using printk() to print to console
EOF

project_root=$PWD
mkdir "include"
mkdir "src"
cd "src"

# create main.c and write basic code in it
touch "main.c"
cat > "main.c" <<EOF
/*
 * Copyright (c) $current_year Navimatix GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

void main(void) {
    printk("Hello World! \n");
}

EOF

cd $project_root

# open project in vscode if it exsits
if hash code
then
    mkdir ".vscode"
    cd ".vscode"
    touch "c_cpp_properties.json"
    cat > "c_cpp_properties.json" <<EOF
  {
  "configurations": [
      {
          "name": "Linux",
          "includePath": [
              "\${workspaceFolder}/**",
              "\${env:ZEPHYR_HOME_DIR}/",
              "\${env:ZEPHYR_HOME_DIR}/include/",
              "\${env:ZEPHYR_HOME_DIR}/subsys/**"
          ],
          "defines": [],
          "compilerPath": "/usr/bin/gcc",
          "cStandard": "gnu17",
          "cppStandard": "gnu++14",
          "intelliSenseMode": "gcc-x64"
       }
    ],
  "version": 4
  }
EOF

    code $project_root
fi

echo "project created! configure the project further using CMakeLists.txt and prj.conf"

