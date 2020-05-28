CXX			= g++
CXXFLAGS	= -std=c++11 -O3 -Wall -pedantic
INCLUDES	= -I. -I./Structures

%:%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

.PHONY: clean
clean:
	$(RM) -rf *.o *~ *.dSYM
