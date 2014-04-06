CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc

CFLAGS= -Wall -std=c99 -O2
CFILES=main.c morse.c
OBJS=$(addprefix build/, $(CFILES:.c=.o))
BINFILE=morse

STATIC_LIB_CFILES= morse.c
STATIC_LIB_OBJS=$(addprefix build/, $(STATIC_LIB_CFILES:.c=.o))
STATIC_LIB=libmorse.a

.PHONY: tests

all: pre-build $(BINFILE) $(STATIC_LIB) tests

pre-build:
	@mkdir -p build

armhf:
	make CROSS_COMPILE=arm-linux-gnueabihf- 

build/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINFILE): $(OBJS)
	$(CC) -o $@ $^

$(STATIC_LIB): $(STATIC_LIB_OBJS)
	$(AR) cru $@ $^

tests: $(BINFILE) 
ifeq ($(CROSS_COMPILE),)
	sh ./tests.sh
endif

clean:
	rm -f $(OBJS) $(BINFILE) $(STATIC_LIB)
