#!/bin/bash
#Author: Hui
#Date: 2017-10-30

DIR="$( cd "$( dirname "$0" )" && pwd )"
ObjDIR="${DIR}/obj"
BinDIR="${DIR}/bin"

echo -e "Current directory: ${DIR}\n"

echo "Now assembling, compiling, and linking your kernel:"

if [ ! -d ${ObjDIR} ]; then
    mkdir ${ObjDIR}
fi

if [ ! -d ${BinDIR} ]; then
    mkdir ${BinDIR}
fi

nasm -f aout -o ${ObjDIR}/start.o start.asm

# Remember this spot here: We will add 'gcc' command here to compile C sources
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I include/ -c -o ${ObjDIR}/main.o main.c


# This links all your files. Remember that as you add *.o files, you need to
# add them after start.o. If you don't add them at all, they won't be in your kernel!
ld -T link.ld -o ${BinDIR}/kernel.bin ${ObjDIR}/start.o ${ObjDIR}/main.o
echo "Done!"