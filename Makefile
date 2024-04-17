# Phony target to avoid conflicts with files named 'clean' or 'all'
.PHONY: clean

# Compiler settings
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra

# Source directory
SRCDIR := src

# Source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Object directory
OBJDIR := obj

# Object files
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Executable name
TARGET := bin/snake-life

# Main target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) -pthread

# Rule to compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Phony target to avoid conflicts with files named 'clean' or 'all'
.PHONY: clean
