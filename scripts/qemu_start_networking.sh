#!/bin/bash

zephyr_folder=$ZEPHYR_HOME_DIR/../tools/
if [ -z $zephyr_folder ]
then
    echo "ZEPHYR_BASE is not define. please define it to the path of where zephyr is installed"
fi

cd $zephyr_folder

net_tools="net-tools"
if [ ! -d $net_tools ]
then
    echo "the zephyr net-tools are not installed in this directory: $zephyr_folder. please make sure the net-tools are installed"
fi

cd $net_tools

echo "starting socat in the background..."
./loop-socat.sh &
socat_pid=$!
echo "a loop socat has been started"

echo "starting slip tap...."
sudo ./loop-slip-tap.sh

echo "qemu networking ended"
kill $socat_pid