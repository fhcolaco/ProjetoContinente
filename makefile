CC = gcc
CFLAGS = -w -g
DEPS = source/functions.c source/genericList.h source/clients.h source/employee.h source/eventHorizon.h source/checkout.h source/checkoutList.h
OBJS = build/main.o build/genericList.o build/clients.o build/employee.o build/eventHorizon.o build/checkout.o build/checkoutList.o

DB= gdb

all: continente

debug: $(OBJS)
	$(DB) continente

continente: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

build/%.o: source/%.c $(DEPS)
	$(CC) $< $(CFLAGS) -c -o $@

