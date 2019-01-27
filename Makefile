CXX			= g++
CXXFLAGS	= -std=c++14 -O3 -Wall -pedantic
INCLUDES	= -I.

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

.PHONY: clean
clean:
	$(RM) *.o *~
