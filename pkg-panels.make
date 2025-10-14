
# Get the panels specific compiler options if we can.

libdir := $(shell pkg-config --variable=libdir panels)

# At run-time the environment variable LD_LIBRARY_PATH can override the
# DSO library file that it used at build-time by using the
# --enable-new-dtags linker option below:
#
PANELS_LDFLAGS := $(shell pkg-config --libs panels)\
 -Wl,--enable-new-dtags,-rpath,$(libdir)
PANELS_CFLAGS := $(shell pkg-config --cflags panels)

ifeq ($(libdir),)
$(error software package panels was not found)
endif

# Spew what panels compiler options we have found
#$(info PANELS_CFLAGS="$(PANELS_CFLAGS)" PANELS_LDFLAGS="$(PANELS_LDFLAGS)")

undefine libdir

