CFLAGS = -std=c++17 -Wall -Wextra -Wsign-conversion
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CXX=g++
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

simulation: $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LFLAGS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $^ -o $@

clean:
	rm *.o simulation
