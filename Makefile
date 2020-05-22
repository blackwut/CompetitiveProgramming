CXX			= g++
CXXFLAGS	= -std=c++17 -O3 -Wall -pedantic
INCLUDES	= -I. -I./Structures

%:%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

.PHONY: clean
clean:
	$(RM) -rf *.o *~ *.dSYM
