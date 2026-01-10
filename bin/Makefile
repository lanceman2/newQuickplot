# This is a "GNU make" make file.

root := ..

include $(root)/pkg-panels.make


INSTALL_DIR = $(PREFIX)/bin

BUILD_NO_INSTALL :=


quickplot_SOURCES :=\
 quickplot.c\
 getOpt.c\
 $(root)/lib/debug.c\
 $(common_sources)

quickplot_CPPFLAGS :=\
 -DUSER_PREFIX=\"QP_\"\
 $(PANELS_CFLAGS)

quickplot_LDFLAGS :=\
 $(PANELS_LDFLAGS)\
 -lm


include ../quickbuild.make
