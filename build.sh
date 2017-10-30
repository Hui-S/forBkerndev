#!/bin/bash
#Author: Hui
#Date: 2017-10-30

echo "Now assembling, compiling, and linking your kernel:"

nasm -f aout -o start.o start.asm

# Remember this spot here: We will add 'gcc' command here to compile C sources



# This links all your files. Remember that as you add *.o files, you need to
# add them after start.o. If you don't add them at all, they won't be in your kernel!
echo "Done!"