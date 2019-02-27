#!/bin/bash

make -C /usr/src/linux-headers-$(uname -r)/ SUBDIRS=$(pwd) modules

make test_buffer

sudo insmode buffer_driver.ko

sudo ./test_buffer

sudo rmmode buffer_driver