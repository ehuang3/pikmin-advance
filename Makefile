################################################################################
# These are variables for the GBA toolchain build
# You can add others if you wish to
# Name:  Eric Huang
################################################################################

# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing binary data
# INCLUDES is a list of directories containing header files
BUILD    := build
SOURCES  := src
DATA     := 
INCLUDES := 

# The name of your desired GBA game
# No SPACES AFTER THE NAME.
PROGNAME = Pikmin

################################################################################
# Automatically build a list of object files
################################################################################

CFILES      := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
DATAFILES   := $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.c)))
OFILES      := $(CFILES:.c=.o) $(DATAFILES:.c=.o)
HFILES      := $(foreach dir,$(INCLUDES),$(notdir $(wildcard $(dir)/*.h)))

VPATH       :=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
					$(BUILD)

################################################################################
# These are various settings used to make the GBA toolchain work
# DO NOT EDIT BELOW.
################################################################################

TOOLDIR  = /usr/local/cs2110-tools
ARMLIB   = $(TOOLDIR)/arm-thumb-eabi/lib
CFLAGS   = -Wall -Werror -std=c99 -pedantic 
CFLAGS   += -mthumb-interwork -mlong-calls -nostartfiles -MMD -MP -I $(TOOLDIR)/include
LDFLAGS = -L $(TOOLDIR)/lib \
		  -L $(TOOLDIR)/lib/gcc/arm-thumb-eabi/4.4.1/thumb \
		  -L $(ARMLIB) \
		  --script $(ARMLIB)/arm-gba.ld
LDDEBUG  = -L $(TOOLDIR)/lib -lgbaio
CDEBUG   = -g -DDEBUG
CRELEASE = -O2 
CC       = $(TOOLDIR)/bin/arm-thumb-eabi-gcc
AS       = $(TOOLDIR)/bin/arm-thumb-eabi-as
LD       = $(TOOLDIR)/bin/arm-thumb-eabi-ld
OBJCOPY  = $(TOOLDIR)/bin/arm-thumb-eabi-objcopy
GDB      = $(TOOLDIR)/bin/arm-thumb-eabi-gdb

################################################################################
# These are the targets for the GBA build system
################################################################################

all : CFLAGS += $(CRELEASE)
all : $(PROGNAME).gba
	@echo "[FINISH] Generated $(PROGNAME).gba"

.PHONY : all clean

$(PROGNAME).gba : $(PROGNAME).elf
	@echo "[LINK] Linking objects together to create $(PROGNAME).gba"
	@cd $(BUILD) && $(OBJCOPY) -O binary $(PROGNAME).elf $(PROGNAME).gba

$(PROGNAME).elf : crt0.o $(OFILES) 
	@cd $(BUILD) && $(LD) $(LDFLAGS) -o $(PROGNAME).elf $(notdir $^) -lgcc -lc -lgcc $(LDDEBUG)

crt0.o : $(ARMLIB)/crt0.s
	@cd $(BUILD) && $(AS) -mthumb-interwork $^ -o crt0.o

%.o : %.c
	@echo "[COMPILE] Compiling $<"
	@cd $(BUILD) && $(CC) $(CFLAGS) -c $< -o $@

clean :
	@echo "[CLEAN] Removing all compiled files"
	@cd $(BUILD) && rm -f *.o *.elf *.gba *.d

vba : CFLAGS += $(CRELEASE)
vba : $(PROGNAME).gba
	@echo "[EXECUTE] Running Emulator VBA-M"
	@vbam $(VBAOPT) $(BUILD)/$(PROGNAME).gba > /dev/null 2> /dev/null

wxvba : CFLAGS += $(CRELEASE)
wxvba : $(PROGNAME).gba
	@echo "[EXECUTE] Running Emulator WXVBAM"
	@wxvbam $(BUILD)/$(PROGNAME).gba

debugvba : CFLAGS += $(CDEBUG)
debugvba : $(PROGNAME).gba
	@echo "[DEBUG] Running game in VBA-M"
	@vbam $(VBAOPT) $(BUILD)/$(PROGNAME).gba

debugwxvba : CFLAGS += $(CDEBUG)
debugwxvba : $(PROGNAME).gba
	@echo "[DEBUG] Running game in WXVBAM"
	@wxvbam $(BUILD)/$(PROGNAME).gba

-include $(addprefix $(CURDIR)/$(BUILD)/, $(CFILES:%.c=%.d))
