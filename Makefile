
# Basic
CXX ?= g++

CXXFLAGS = -Wall -std=c++11 $(INCFLAGS)
LDFLAGS := -lncurses -lsfml-graphics -lsfml-window -lsfml-system

DEBUG = 1

ifeq ($(DEBUG), 1)
CXXFLAGS += -g
else
CXXFLAGS += -O3
endif

# Files and locations
TARGET := ./gomoku

SRC_ROOTDIR := src

# Add folder here
SRC_SUBDIRS := game gui gui/sfml exceptions actors

SRC_ALLDIRS := $(SRC_ROOTDIR) $(foreach sub_dir, $(SRC_SUBDIRS), $(SRC_ROOTDIR)/$(sub_dir))

SRC := $(foreach dir, $(SRC_ALLDIRS), $(wildcard $(dir)/*.cpp))
INCFLAGS := $(foreach dir, $(SRC_ALLDIRS), -I $(dir)/)

# Generated object files
OBJ := $(SRC:.cpp=.o)

# Utils
RM := rm -vf

# Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re: fclean all
