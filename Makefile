SHELL := /bin/sh

CC := g++
LD := g++

SOURCE := src
BUILD := build
BINARY := simple-http-server

MODULES := utils network .
SOURCE_DIRS := $(addprefix $(SOURCE)/,$(MODULES))
BUILD_DIRS := $(addprefix $(BUILD)/,$(MODULES))

SOURCE_FILES := $(foreach source_dir,$(SOURCE_DIRS),$(wildcard $(source_dir)/*.cpp))
OBJECT_FILES := $(patsubst $(SOURCE)/%.cpp,$(BUILD)/%.o,$(SOURCE_FILES))
INCLUDES := -Iinclude $(addprefix -I,$(SOURCE_DIRS))
CFLAGS := -ggdb -Wall -Wextra -Wconversion -Wsign-conversion -Weffc++

vpath %.cpp $(SOURCE_DIRS)

define make-goal
$1/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all clean

all: $(BUILD_DIRS) $(BUILD)/$(BINARY)

$(BUILD)/$(BINARY): $(OBJECT_FILES)
	$(LD) $^ -o $@

$(BUILD_DIRS):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD)

$(foreach build_dir,$(BUILD_DIRS),$(eval $(call make-goal,$(build_dir))))
