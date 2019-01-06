#!/bin/bash

make -C /usr/src/linux-headers-$(uname -r)/ SUBDIRS=$(pwd) modules