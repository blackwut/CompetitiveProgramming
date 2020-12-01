CXX			= g++
CXXFLAGS	= -std=c++11 -g -Wall -Wextra -pedantic -fsanitize=address -fsanitize=pointer-overflow
INCLUDES	= -I. -I./Structures

%:%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@.o

.PHONY: clean
clean:
	$(RM) -rf *.o *~ *.dSYM
