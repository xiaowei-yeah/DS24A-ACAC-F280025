################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
C2000ware/device/%.obj: ../C2000ware/device/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/App" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/Bsp" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/C2000ware/c2000ware" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/C2000ware/c2000ware/inc" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/C2000ware/device" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/C2000ware/headers/include" --include_path="D:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="C2000ware/device/$(basename $(<F)).d_raw" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/Debug/syscfg" --obj_directory="C2000ware/device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C2000ware/device/%.obj: ../C2000ware/device/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/App" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/Bsp" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/C2000ware/c2000ware" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/C2000ware/c2000ware/inc" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/C2000ware/device" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/C2000ware/headers/include" --include_path="D:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="C2000ware/device/$(basename $(<F)).d_raw" --include_path="D:/DDSK/Desktop/CCS_Works/F280025_Empty/Debug/syscfg" --obj_directory="C2000ware/device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


