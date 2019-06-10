CXX			= g++
CXXFLAGS	= -std=c++14 -O3 -Wall -pedantic
INCLUDES	= -I.

%:%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@.o

.PHONY: clean
clean:
	$(RM) -rf *.o *~ *.dSYM
