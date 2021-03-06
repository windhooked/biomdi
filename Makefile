#
# This software was developed at the National Institute of Standards and
# Technology (NIST) by employees of the Federal Government in the course
# of their official duties. Pursuant to title 17 Section 105 of the
# United States Code, this software is not subject to copyright protection
# and is in the public domain. NIST assumes no responsibility  whatsoever for
# its use by other parties, and makes no guarantees, expressed or implied,
# about its quality, reliability, or any other characteristic.
#
PWD := $(shell pwd)

#
# Because the library and executable names for Iris image data formats
# 2005 and 2011 versions are the same, you may want to compile only one
# version. Note that both will compile, but installing will cause one
# version to overwrite the other version.
#
#SUBDIRS := common fingerminutia fingerimage facerecognition irisimage
SUBDIRS := common fingerminutia fingerimage facerecognition irisimage2011
OS := $(shell uname -s)

ifeq ($(findstring CYGWIN,$(OS)), CYGWIN)
	ROOT = Administrator
else
	ROOT  = root
endif

INCPATH := /usr/local/include

all:
	@for subdir in $(SUBDIRS); do \
		(cd $$subdir && $(MAKE) all) || exit 1; \
	done

install:
	@for subdir in $(SUBDIRS); do \
		(cd $$subdir && $(MAKE) install) || exit 1; \
	done

clean:
	@for subdir in $(SUBDIRS); do \
		(cd $$subdir && $(MAKE) clean) || exit 1; \
	done
