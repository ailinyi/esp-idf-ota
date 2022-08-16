#!/bin/bash

idf.py build

cp ./build/simple_ota.bin /mnt/hgfs/share/

cp ./build/bootloader/bootloader.bin /mnt/hgfs/share/

cp ./build/partition_table/partition-table.bin /mnt/hgfs/share/

