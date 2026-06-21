TARGET = eboot

OBJS = main.o


BUILD_PRX = 1

CFLAGS = -Wall

PSP_EBOOT_TITLE = system dreg/ireg dumper for DAM

ENCRYPT = 1


PSP_EBOOT_ICON = icons/ICON0.PNG

EXTRA_TARGETS = EBOOT.PBP


LIBS = -lpspctrl


PSPSDK=$(shell psp-config -p)
include $(PSPSDK)/lib/build.mak
