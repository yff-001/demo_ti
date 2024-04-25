CC = C:\ti\gcc_arm_none_eabi_9_2_1\bin\arm-none-eabi-gcc.exe

CFLAGS = -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -D__MSPM0C1104__ -I"C:/Users/yff/workspace_ccstheia/demo_c1104" -I"C:/ti/mspm0_sdk_2_00_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_00_00_03/source" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -std=c99
LDFLAGS = -D__MSPM0C1104__ -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -mthumb -mfloat-abi=soft -Wl,-Map,"demo_c1104.map" -nostartfiles -static -Wl,--gc-sections -L"C:/ti/mspm0_sdk_2_00_00_03/source/ti/driverlib/lib/gcc/m0p/mspm0c110x" -L"C:/ti/mspm0_sdk_2_00_00_03/source" -L"C:/Users/yff/workspace_ccstheia/demo_c1104" -L"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/lib/thumb/v6-m/nofp" -march=armv6-m -mthumb

ORDERED_OBJS += \
-Wl,-T"mspm0c1104.lds" \
"C:/ti/mspm0_sdk_2_00_00_03/source/ti/driverlib/lib/gcc/m0p/mspm0c110x/driverlib.a" \
-l:driverlib.a \
-lgcc \
-lc \
-lm \
-lnosys \

BIN_DIR = bin
SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TARGET = $(BIN_DIR)/app.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(ORDERED_OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

size:
	C:\ti\gcc_arm_none_eabi_9_2_1\bin\arm-none-eabi-size.exe $(TARGET)
clean:
	del obj\*.o
	del bin\*.out 
	del *.map
	del *.d_raw