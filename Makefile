BUILD_DIR := ./build
SRC_DIRS := ./src

CC := gcc
# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Linked libs
CFLAGS := -lm -lfftw3

makematrix: SRCS    
    $(CC) -o makematrix SRCS.