# Current tools are eepmake and eepdump

CC ?= gcc
CFLAGS ?= -Wall -Wextra
prefix ?= /usr/local
exec_prefix = ${prefix}

all: eepmake eepdump

eepmake: eeptypes.h eepmake.c
	$(CC) $(CFLAGS) eepmake.c -o eepmake

eepdump: eeptypes.h eepdump.c
	$(CC) $(CFLAGS) eepdump.c -o eepdump

install: all
	install -d $(DESTDIR)$(exec_prefix)/sbin
	install -d $(DESTDIR)$(prefix)/bin
	install eepmake $(DESTDIR)$(prefix)/bin/
	install eepdump $(DESTDIR)$(prefix)/bin/
	install eepflash.sh $(DESTDIR)$(exec_prefix)/sbin/

uninstall:
	rm -f eepmake
	rm -f eepdump
clean:
	rm -f eepmake eepdump
