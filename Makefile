SHELL := /bin/sh

CXX := g++
LD := g++

SOURCE := src
BUILD := build
BINARY := simple-http-server

MODULES := . network utils
SOURCE_DIRS := $(addprefix $(SOURCE)/,$(MODULES))
BUILD_DIRS := $(addprefix $(BUILD)/,$(MODULES))

SOURCE_FILES := $(foreach source_dir,$(SOURCE_DIRS),$(wildcard $(source_dir)/*.cpp))
OBJECT_FILES := $(patsubst $(SOURCE)/%.cpp,$(BUILD)/%.o,$(SOURCE_FILES))
HEADERS := -I include -I lib/boost_1_82_0
CXXFLAGS := -ggdb -Wall -Wextra -Wconversion -Wsign-conversion -Weffc++

.PHONY: all clean

all: $(BUILD_DIRS) $(BUILD)/$(BINARY)

$(BUILD)/$(BINARY): $(OBJECT_FILES)
	$(LD) $^ -o $@

$(BUILD_DIRS):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD)

vpath %.cpp $(SOURCE_DIRS)

define make-goal
$1/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) -c $$< -o $$@
endef

$(foreach build_dir,$(BUILD_DIRS),$(eval $(call make-goal,$(build_dir))))
