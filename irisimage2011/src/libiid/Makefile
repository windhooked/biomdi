#
# This software was developed at the National Institute of Standards and
# Technology (NIST) by employees of the Federal Government in the course
# of their official duties. Pursuant to title 17 Section 105 of the
# United States Code, this software is not subject to copyright protection
# and is in the public domain. NIST assumes no responsibility  whatsoever for
# its use by other parties, and makes no guarantees, expressed or implied,
# about its quality, reliability, or any other characteristic.
#
# Set a variable so we can check the OS name; Mac OS-X (Darwin) uses a different
# form of linking libraries.
#
include ../common.mk
OS := $(shell uname -s)
SOURCES = iid.c validate.c
OBJECTS = iid.o validate.o

all: $(SOURCES)
ifeq ($(OS), Darwin)
	$(CC) -dynamiclib $(CFLAGS) $(SOURCES) $(EXTRALIBS) -o libiid.dylib
	$(CP) libiid.dylib $(LOCALLIB)
else
ifeq ($(findstring CYGWIN,$(OS)), CYGWIN)
	$(CC) $(CFLAGS) -c $(SOURCES)
	ar rs libiid.a $(OBJECTS)
	ranlib libiid.a
	$(CC) -shared -o libiid.dll -Wl,--out-implib=libiid.dll.a -Wl,--export-all-symbols -Wl,--enable-auto-import -Wl,--whole-archive libiid.a -Wl,--no-whole-archive $(CFLAGS)
	$(CP) libiid.a $(LOCALLIB)
	$(CP) libiid.dll.a $(LOCALLIB)
	$(CP) libiid.dll $(LOCALLIB)
else
	$(CC) -shared $(SOURCES) $(CFLAGS) -o libiid.so
	$(CP) libiid*.so $(LOCALLIB)
endif
endif

clean:
	$(RM) $(DISPOSABLEFILES)
	$(RM) -r $(DISPOSABLEDIRS)
