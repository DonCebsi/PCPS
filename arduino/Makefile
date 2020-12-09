################################################################################
# Directories with source files in it, files must have .cpp ending.
# You may specify more than one directory.
SOURCES := src/ lib/ .piolibdeps/

# Where your tests are (files must have format Test*.cpp).
TEST_DIR := test/

# Where build artefacts will be stored.
BUILD_DIR := .build/

# Where the unit test library folder is.
UNIT_DIR := $(TEST_DIR)Unit/

################################################################################
# Builds the project
build:
	platformio run

# Uploads the project to the arduino
upload:
	platformio run --target upload

################################################################################
# Includes folders, cpp files and header files.
INCLUDE_DIRS = $(foreach dir, $(SOURCES), $(shell find $(dir) -type d))
CPP_FILES := $(foreach dir, $(SOURCES), $(shell find $(dir) -type f -name *.cpp)) $(wildcard $(UNIT_DIR)*.cpp)
H_FILES := $(foreach dir, $(SOURCES), $(shell find $(dir) -type f -name *.h)) $(wildcard $(UNIT_DIR)*.h)

# Test files
TEST_FILES := $(wildcard $(TEST_DIR)Test*.cpp)
TEST_BINS := $(patsubst %.cpp, $(BUILD_DIR)%, $(TEST_FILES))

# Runs all tests in folder $(TEST_DIR) with the format Test*.cpp.
test: $(TEST_BINS)
	@echo "Running all tests.\n"
	@for bin in $(TEST_BINS); do \
		basename "$$bin"; \
		$$bin | sed 's/^/    /'; \
		echo; \
	done

# All flags for header files.
INCLUDES := -I$(UNIT_DIR) $(foreach dir, $(INCLUDE_DIRS), -I$(dir))

# Compiles shared library of your code.
$(BUILD_DIR)lib.so: $(CPP_FILES) $(H_FILES)
	@echo "Compiling libraries ..."
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)$(TEST_DIR)
	@g++ -std=c++11 -shared -fPIC -o $@ $(INCLUDES) $(CPP_FILES)

# Compiles one test.
$(BUILD_DIR)$(TEST_DIR)%: $(TEST_DIR)%.cpp $(BUILD_DIR)lib.so
	@g++ -std=c++11 -o $@ $(INCLUDES) $< $(BUILD_DIR)lib.so

# Removes build files.
clean:
	@rm -rf .pioenvs $(BUILD_DIR)

################################################################################
.PHONY: all build upload test clean
