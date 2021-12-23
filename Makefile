# This file adapted from the CS 225 standard makefile, made by Wade Fagen-Ulmschneider and Jeffrey Tolar
# as well as a makefile posted on https://spin.atomicobject.com/2016/08/26/makefile-c-projects/ by Job Vranish

EXE = flights
TEST = test

EXE_OBJ = main.o
OBJS = main.o DisjointSets.o Graph.o GraphAlgos.o Utils.o

CLEAN_RM = 	*.o *.d tests/*.o tests/*.d cs225/*.d cs225/*.o \
						cs225/lodepng/*.o cs225/lodepng/*.d \
						cs225/catch/*.o cs225/catch/*.d

# Use v cs225 makefile template:
include cs225/make/cs225.mk

#Venkat, I commented out your make file
# CXX = clang++
# LD = clang++
# TARGET_EXEC = flights

# BUILD_DIR = obj
# SRC_DIRS = src

# SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
# OBJS := $(SRCS:$(SRC_DIRS)/%.cpp=$(BUILD_DIR)/%.o)
# DEPS := $(OBJS:.o=.d)

# INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# CPPFLAGS ?= $(INC_FLAGS) -MMD -MP 
# WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
# CPPFLAGS += -std=c++1y -stdlib=libc++ -O2 $(WARNINGS) $(DEPFILE_FLAGS) -g
# LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

# $(TARGET_EXEC): $(OBJS)
# 	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# $(BUILD_DIR)/%.o: $(SRC_DIRS)/%.cpp $(BUILD_DIR)
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# $(BUILD_DIR):
# 	mkdir -p $(BUILD_DIR)
# .PHONY: clean all

# clean:
# 	$(RM) -r $(BUILD_DIR)
# 	$(RM) $(TARGET_EXEC)

# all: $(TARGET_EXEC)

# -include $(DEPS)