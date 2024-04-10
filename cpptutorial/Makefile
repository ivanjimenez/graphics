all: $(patsubst %.cpp,%,$(wildcard *.cpp))

%: %.cpp
	g++ -std=c++20 -Wall -Wextra -pedantic $< -o $@

clean:
	del *.exe
