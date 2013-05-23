AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CFLAGS = -I$(srcdir)/arch/@ARCH@/ \
	    -I$(srcdir)/include -nostdlib -nostartfiles
AM_LDFLAGS = -nostdlib -nostartfiles 

bin_PROGRAMS = vloader

vloader_SOURCES = main/vloader.c 
