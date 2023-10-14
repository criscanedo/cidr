CC = cc
CFLAGS = -std=c99 -pedantic -Wall

PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# OpenBSD
#MANPREFIX = ${PREFIX}/man

all: cidr

clean:
	rm -f cidr

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f cidr ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/cidr
	cp -f cidr.1 ${DESTDIR}${MANPREFIX}/man1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/cidr.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/cidr\
		${DESTDIR}${MANPREFIX}/man1/cidr.1
