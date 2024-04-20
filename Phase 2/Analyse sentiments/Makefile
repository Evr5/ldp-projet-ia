# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source files
SRCS = analyse_sentiments.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = analyse_sentiments

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
