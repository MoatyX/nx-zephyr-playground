*******************
Simple LwM2M Clinet
*******************

Overview
########
this a simple demo, showing the bare-bone minimum to have a LwM2M client running on either a qemu_x86 target or a board, and interacting with a Leshan server (LwM2M server) running on the localhost.

LwM2M Specification: http://www.openmobilealliance.org/release/LightweightM2M/V1_0-20170208-A/OMA-TS-LightweightM2M-V1_0-20170208-A.pdf

| LwM2M has this principle of objects, each object represents an entity, an entity is some kind of hardware or related data. 
| for example: the most basic object that **MUST** be defined, is the *Device* Object.
    within that object, in addition to other basic things, is some read-only data about the system, written by the user.
    other objects could be some sensors or motors attached to the system.
| for more information about standard Objects, please refer to the OMA Specification above


Building and running
####################
| this demo could be compiled and executed on either a qemu_x86 target, or any Board with networking features.
| An STM Nucleo_F746zg was used to test this client.

Running the Leshan Server
******************************
| Download a demo Leshan Server from Eclipse and run it. it also comes a nice web front end showing connected clients on localhost:8080

    | $ wget https://hudson.eclipse.org/leshan/job/leshan/lastSuccessfulBuild/artifact/leshan-server-demo.jar
    | $ java -jar ./leshan-server-demo.jar -wp 8080

Running on a qemu_x86
**************************
| in order to build and run for qemu, you'll have to be on linux machine, and grab some tools from github.
| grab net tools from github: 

    | $ git clone https://github.com/zephyrproject-rtos/net-tools
    | $ cd net-tools
    | $ make

| open 2 Terminals, in the first one run: 

    | $ ./loop-socat.sh

| in the 2nd Terminal run:

    | $ sudo ./loop-slip-tap.sh

| in the prj.conf, edit the following:

    | CONFIG_NET_CONFIG_MY_IPV4_ADDR="192.0.2.69"
    | CONFIG_NET_CONFIG_PEER_IPV4_ADDR="192.0.2.2"

| Now you can build and run for qemu_x86. in a 3rd Terminal run:

    | $ west build -p auto -b qemu_x86 LwM2M_Client/
    | $ west build -t run

for more information about networking with qemu visit: `Networking With Qemu <https://docs.zephyrproject.org/latest/guides/networking/networking_with_host.html>`_

Running on a board (STM Nucleo_F746zg)
****************************************
| I have Linux running in a Virtual Machine on a Windows Host. so these configurations will not work if you use a native Linux machine.
| but the idea should be the same, we need to hook the board to the same network the machine is on, give it an IP address and then configure the client to message that network's Host IP address.
| we will be using IPv4 here.
|
| continue with these instructions if you have Linux running in VM on a Windows Host.
|

* start with connecting the board with the computer through Ethernet
* Now we need to bridge that interface with the Virtual Machine:
    in VirtualBox select your Virtual Machine and go to: **Settings -> network -> Adaptor 2 (or any free adaptor)**

    * tick "Enable Network Adaptor"
    * set "Attached to" to "Bridged Adaptor"
    * Set "Name" to the Ethernet Adaptor the board is connected to.
* Start your virtual Machine and you should see a new internet adaptor created.
  configure it to use any static IP you wish, so that we don't alway have to reconfigure the board's target IP address every time the adaptor gets a new IP from the DHCP server.
  
  the new configured IP address must be within the same network, as the Ethernet Adaptor's IP address from the windows Machine.

  Example: 
    | Windows Machine Ehternet IP address: **192.168.137**.1
    | picked static IP on the Linux Machine: **192.168.137**.75

  the Gateway IP address must be the IP address of the Windows Machine Ethernet Adaptor

* Finally all we need to do is configure the Board's Network Interface with the IP addresses we have been configuring so far.
    in *prj.conf* set the following:

    - CONFIG_NET_CONFIG_MY_IPV4_ADDR = **192.168.137**.<any_number_not taken before>
    - CONFIG_NET_CONFIG_MY_IPV4_NETMASK="255.255.255.0" by default or as wished
    - CONFIG_NET_CONFIG_MY_IPV4_GW = (optional) set to any Gateway IP, this can be used to get access to the internet or other LAN
    - CONFIG_NET_CONFIG_PEER_IPV4_ADDR="192.168.137.75" the IP address of the configured Network Interface on the Linux Machine

