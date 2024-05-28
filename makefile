CC = gcc
CFLAGS = -w -g
DEPS = source/genericList.h source/employee.h source/clients.h source/eventHorizon.h source/checkout.h source/checkoutList.h
OBJS = build/main.o build/genericList.o build/employee.o build/clients.o build/eventHorizon.o  build/checkout.o build/checkoutList.o

all: continente

continente: $(OBJS)
	chcp 65001
	$(CC) $(CFLAGS) $(OBJS) -o $@

build/%.o: source/%.c $(DEPS)
	$(CC) $< $(CFLAGS) -c -o $@

