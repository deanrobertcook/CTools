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

#common objects
OBJ=$(BUILD_LOC)/utils.o \
$(BUILD_LOC)/timer.o

OBJ_TIMER_TEST = $(OBJ) \
$(BUILD_LOC)/timer_test_driver.o

OBJ_DLLIST_TEST = $(OBJ) \
$(BUILD_LOC)/dllist.o \
$(BUILD_LOC)/dllist_test_driver.o

testTimer: clean build_location $(OBJ_TIMER_TEST)
	$(CC) $(OBJ_TIMER_TEST) -o test_driver

testDllist: clean build_location $(OBJ_DLLIST_TEST)
	$(CC) $(OBJ_DLLIST_TEST) -o test_driver

#Core modules
$(BUILD_LOC)/utils.o:
	$(COMPILE) src/utils/utils.c -o $(BUILD_LOC)/utils.o

$(BUILD_LOC)/timer.o:
	$(COMPILE) src/timer/timer.c -o $(BUILD_LOC)/timer.o

#Data type modules
$(BUILD_LOC)/dllist.o:
	$(COMPILE) src/dllist/dllist.c -o $(BUILD_LOC)/dllist.o

#Test modules
$(BUILD_LOC)/timer_test_driver.o:
	$(COMPILE) test/timer/test_driver.c -o $(BUILD_LOC)/timer_test_driver.o
$(BUILD_LOC)/dllist_test_driver.o:
	$(COMPILE) test/dllist/test_driver.c -o $(BUILD_LOC)/dllist_test_driver.o
