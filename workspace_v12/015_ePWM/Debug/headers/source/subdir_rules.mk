################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
headers/source/F2806x_GlobalVariableDefs.obj: C:/ti/c2000/C2000Ware_4_01_00_00/device_support/f2806x/headers/source/F2806x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/ibrahim/workspace_v12/015_ePWM" --include_path="C:/Users/ibrahim/workspace_v12/015_ePWM/include" --include_path="C:/ti/c2000/C2000Ware_4_01_00_00/device_support/f2806x/common/include" --include_path="C:/ti/c2000/C2000Ware_4_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="headers/source/$(basename $(<F)).d_raw" --obj_directory="headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


