# This is a "GNU make" make file.

root := ..

include $(root)/pkg-panels.make


INSTALL_DIR = $(PREFIX)/bin

#If we need a libquickplot library
#QP_LIB := -L../lib -lquickplot -Wl,-rpath=\$$ORIGIN/../lib

BUILD_NO_INSTALL :=


define MkProgram
  # $(1) = program_name
  # $(2) = Add a source.c
  $(1)_SOURCES := $(root)/lib/debug.c
  ifneq ($(2),)
    $(1)_SOURCES += $(2)
  else
    $(1)_SOURCES += $(1).c
  endif
  $(1)_CPPFLAGS :=\
 -DUSER_PREFIX=\"QP_\"\
 $(PANELS_CFLAGS)
  $(1)_LDFLAGS :=\
 $(QP_LIB)\
 $(PANELS_LDFLAGS)\
 -lm
endef


$(eval $(call MkProgram, quickplot))
$(eval $(call MkProgram, StaticPlot_0))
$(eval $(call MkProgram, Mic_ScopePlot_0))
$(eval $(call MkProgram, ScopePlot_0))





include ../quickbuild.make
