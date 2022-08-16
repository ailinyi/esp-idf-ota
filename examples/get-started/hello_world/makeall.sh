#!/bin/bash

idf.py build

cp ./build/hello-world.bin /mnt/hgfs/share/

cp ./build/bootloader/bootloader.bin /mnt/hgfs/share/

