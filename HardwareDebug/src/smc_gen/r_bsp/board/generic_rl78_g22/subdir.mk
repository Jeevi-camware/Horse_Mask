################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/board/generic_rl78_g22/hdwinit.c \
../src/smc_gen/r_bsp/board/generic_rl78_g22/r_bsp_init.c 

ASM_SRCS += \
../src/smc_gen/r_bsp/board/generic_rl78_g22/stkinit.asm 

ASSEMBLER_OBJS += \
src/smc_gen/r_bsp/board/generic_rl78_g22/stkinit.obj 

ASM_DEPS += \
src/smc_gen/r_bsp/board/generic_rl78_g22/stkinit.d 

COMPILER_OBJS += \
src/smc_gen/r_bsp/board/generic_rl78_g22/hdwinit.obj \
src/smc_gen/r_bsp/board/generic_rl78_g22/r_bsp_init.obj 

C_DEPS += \
src/smc_gen/r_bsp/board/generic_rl78_g22/hdwinit.d \
src/smc_gen/r_bsp/board/generic_rl78_g22/r_bsp_init.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/board/generic_rl78_g22/%.obj: ../src/smc_gen/r_bsp/board/generic_rl78_g22/%.c 
	@echo 'Scanning and building file: $<'
	@echo src\smc_gen\r_bsp\board\generic_rl78_g22\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rl78_g22\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\board\generic_rl78_g22\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_bsp\board\generic_rl78_g22\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rl78_g22\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\board\generic_rl78_g22\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"


src/smc_gen/r_bsp/board/generic_rl78_g22/%.obj: ../src/smc_gen/r_bsp/board/generic_rl78_g22/%.asm 
	@echo 'Scanning and building file: $<'
	@echo src\smc_gen\r_bsp\board\generic_rl78_g22\asmDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rl78_g22\asmDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\board\generic_rl78_g22\asmDepSubCommand.tmp" -asmopt=-MF="$(@:%.obj=%.d)" -asmopt=-MT="$(@:%.obj=%.obj)" -asmopt=-MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_bsp\board\generic_rl78_g22\asmSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rl78_g22\asmSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\board\generic_rl78_g22\asmSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"


