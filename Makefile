CC=gcc -w
#checks for all header files in the root directory with " -I . "
C_FLAGS=-c -I .
COMPILE = $(CC) $(C_FLAGS)
RM=rm -f
BUILD_LOC=build

#helper targets
clean:
	$(RM) -r $(BUILD_LOC)
	$(RM) test_driver
	
build_location:
	mkdir $(BUILD_LOC)
	
#Timer test compilation
OBJ=$(BUILD_LOC)/utils.o \
$(BUILD_LOC)/timer.o \
$(BUILD_LOC)/test_driver.o
	
testTimer: clean build_location $(OBJ)
	$(CC) $(OBJ) -o test_driver

#Core modules
$(BUILD_LOC)/utils.o:
	$(COMPILE) src/utils/utils.c -o $(BUILD_LOC)/utils.o
	
$(BUILD_LOC)/timer.o:
	$(COMPILE) src/timer/timer.c -o $(BUILD_LOC)/timer.o
	

#Test modules
$(BUILD_LOC)/test_driver.o:
	$(COMPILE) test/timer/test_driver.c -o $(BUILD_LOC)/test_driver.o