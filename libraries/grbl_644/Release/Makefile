################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../coolant_control.c \
../eeprom.c \
../gcode.c \
../jog.c \
../jogpad.c \
../limits.c \
../main.c \
../motion_control.c \
../nuts_bolts.c \
../planner.c \
../print.c \
../probe.c \
../protocol.c \
../report.c \
../serial.c \
../settings.c \
../spindle_control.c \
../spi_sr.c \
../stepper.c \
../system.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
coolant_control.o \
eeprom.o \
gcode.o \
jog.o \
jogpad.o \
limits.o \
main.o \
motion_control.o \
nuts_bolts.o \
planner.o \
print.o \
probe.o \
protocol.o \
report.o \
serial.o \
settings.o \
spindle_control.o \
spi_sr.o \
stepper.o \
system.o

OBJS_AS_ARGS +=  \
coolant_control.o \
eeprom.o \
gcode.o \
jog.o \
jogpad.o \
limits.o \
main.o \
motion_control.o \
nuts_bolts.o \
planner.o \
print.o \
probe.o \
protocol.o \
report.o \
serial.o \
settings.o \
spindle_control.o \
spi_sr.o \
stepper.o \
system.o

C_DEPS +=  \
coolant_control.d \
eeprom.d \
gcode.d \
jog.d \
jogpad.d \
limits.d \
main.d \
motion_control.d \
nuts_bolts.d \
planner.d \
print.d \
probe.d \
protocol.d \
report.d \
serial.d \
settings.d \
spindle_control.d \
spi_sr.d \
stepper.d \
system.d

C_DEPS_AS_ARGS +=  \
coolant_control.d \
eeprom.d \
gcode.d \
jog.d \
jogpad.d \
limits.d \
main.d \
motion_control.d \
nuts_bolts.d \
planner.d \
print.d \
probe.d \
protocol.d \
report.d \
serial.d \
settings.d \
spindle_control.d \
spi_sr.d \
stepper.d \
system.d

OUTPUT_FILE_PATH +=grbl_644.elf

OUTPUT_FILE_PATH_AS_ARGS +=grbl_644.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler









































./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DNDEBUG -DF_CPU=16000000U  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\include"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -mmcu=atmega644a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega644a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="grbl_644.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,-L"D:\OneDrive\Dokumente\Projekte\CNC\MaXYposi\Git_MaXYposi_Grbl_644\libraries\grbl_644"  -Wl,--gc-sections -mmcu=atmega644a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega644a"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "grbl_644.elf" "grbl_644.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "grbl_644.elf" "grbl_644.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "grbl_644.elf" > "grbl_644.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "grbl_644.elf" "grbl_644.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "grbl_644.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "grbl_644.elf" "grbl_644.a" "grbl_644.hex" "grbl_644.lss" "grbl_644.eep" "grbl_644.map" "grbl_644.srec" "grbl_644.usersignatures"
	