##############################
#Makefile for Bkerndev
##############################

DIR = $(shell pwd)
BinDIR = $(DIR)/bin
ObjDIR = $(DIR)/obj
MntDIR = $(DIR)/hd
SourceDIR = $(DIR)/sources

IMG = $(DIR)/disk.img

KERNEL = $(BinDIR)/kernel.bin

STARTO = $(ObjDIR)/start.o
MAINO = $(ObjDIR)/main.o
SCRNO = $(ObjDIR)/scrn.o
GDTO = $(ObjDIR)/gdt.o
IDTO = $(ObjDIR)/idt.o
ISRSO = $(ObjDIR)/isrs.o
IRQO = $(ObjDIR)/irq.o
TIMERO = $(ObjDIR)/timer.o
KBO = $(ObjDIR)/kb.o

STARTASM = $(SourceDIR)/start.asm
MAINC = $(SourceDIR)/main.c
SCRNC = $(SourceDIR)/scrn.c
GDTC = $(SourceDIR)/gdt.c
IDTC = $(SourceDIR)/idt.c
ISRSC = $(SourceDIR)/isrs.c
IRQC = $(SourceDIR)/irq.c
TIMERC = $(SourceDIR)/timer.c
KBC = $(SourceDIR)/kb.c

GRUBCFG = $(DIR)/grub.cfg

ASM = nasm
CC = gcc
LD = ld

ASMFLAGS = -f elf
CFLAGS = -I./include -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c
LDFLAGS = -T link.ld -s

all: clean build

clean: reclean

image: build buildimage

reclean:
	rm -rf $(BinDIR)/*
	rm -rf $(ObjDIR)/*

buildimage: 
	sudo mount -o loop,offset=1048576 $(IMG) $(MntDIR)
	sudo cp $(KERNEL) $(MntDIR)
	sudo cp $(GRUBCFG) $(MntDIR)/boot/grub
	sudo umount $(MntDIR)

build: $(KERNEL)

$(KERNEL): $(STARTO) $(MAINO) $(SCRNO) $(GDTO) $(IDTO) $(ISRSO) $(IRQO) $(TIMERO) $(KBO)
	$(LD) $(LDFLAGS) -o $@ $^

$(STARTO): $(STARTASM)
	$(ASM) $(ASMFLAGS) -o $@ $<

$(MAINO): $(MAINC)
	$(CC) $(CFLAGS) -o $@ $<

$(SCRNO): $(SCRNC)
	$(CC) $(CFLAGS) -o $@ $<

$(GDTO): $(GDTC)
	$(CC) $(CFLAGS) -o $@ $<

$(IDTO): $(IDTC)
	$(CC) $(CFLAGS) -o $@ $<

$(ISRSO): $(ISRSC)
	$(CC) $(CFLAGS) -o $@ $<

$(IRQO): $(IRQC)
	$(CC) $(CFLAGS) -o $@ $<

$(TIMERO): $(TIMERC)
	$(CC) $(CFLAGS) -o $@ $<

$(KBO): $(KBC)
	$(CC) $(CFLAGS) -o $@ $<
