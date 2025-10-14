# This is a "GNU make" make file.

root := ..

include $(root)/pkg-cairo.make
include $(root)/pkg-panels.make
include $(root)/pkg-cairo.make


INSTALL_DIR = $(PREFIX)/bin

BUILD_NO_INSTALL :=


common_sources :=\
 getOpt.c

quickplot_SOURCES :=\
 quickplot.c\
 $(common_sources)

quickplot_CPPFLAGS :=\
 $(PANELS_CFLAGS)\
 $(CAIRO_CFLAGS)

quickplot_LDFLAGS :=\
 $(PANELS_LDFLAGS)\
 $(CAIRO_LDFLAGS)\
 -L../lib -lquickplot\
 -Wl,-rpath=\$$ORIGIN/../lib -lm


include ../quickbuild.make
