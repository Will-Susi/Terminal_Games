CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
DEPS = MasterMind.hpp
OBJ = MasterMind.o
PROG = MasterMind

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROG): main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o $(PROG) 