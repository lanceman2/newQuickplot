root := ..

include $(root)/config.make
include $(root)/pkg-panels.make
include $(root)/pkg-cairo.make

INSTALL_DIR = $(PREFIX)/lib

SUBDIRS := pkgconfig


libquickplot.so_SOURCES :=\
 debug.c\
 constructor.c


libquickplot.so_CPPFLAGS :=\
 -DPANELS_LIB_CODE\
 $(PANELS_CFLAGS)

libquickplot.so_CFLAGS :=\
 -fvisibility=hidden\
 -DQP_EXPORT="__attribute__((visibility(\"default\"))) extern"\
 -DEXPORT="QP_EXPORT"
#
# good read:
#   https://amir.rachum.com/shared-libraries/
#
# The order of these LDFLAGS can matter if we add more library
# dependencies.
#
# At some point we need an operating system package manager that
# fixes this kind of (DSO dependency hell) shit, like NixOS.
#
# Handy commands to run in a shell:
#
#   readelf -d libquickplot.so
#
#   nm --extern-only libquickplot.so
#   nm -D libquickplot.so
#
libquickplot.so_LDFLAGS :=\
 $(PANELS_LDFLAGS)\
 -Wl,--retain-symbols-file=retain-symbols.txt

libquickplot.so: retain-symbols.txt


include ../quickbuild.make

