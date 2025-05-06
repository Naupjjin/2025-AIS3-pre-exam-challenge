#!/bin/sh

exec 2>/dev/null
LD_PRELOAD=/home/chal/lib/libc_patch.so.6 /home/chal/chal
