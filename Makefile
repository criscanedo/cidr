CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Os

PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# OpenBSD
#MANPREFIX = ${PREFIX}/man

all: cidr

clean:
	rm -f cidr cidr.tar.gz

dist: clean
	mkdir cidr
	cp LICENSE Makefile README cidr.c cidr.1 cidr
	tar -cf cidr.tar cidr
	gzip cidr.tar
	rm -rf cidr

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f cidr ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/cidr
	cp -f cidr.1 ${DESTDIR}${MANPREFIX}/man1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/cidr.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/cidr\
		${DESTDIR}${MANPREFIX}/man1/cidr.1

.PHONY: all clean dist install uninstall
