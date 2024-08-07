CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
PROG = Mordle
DEPS = $(PROG).hpp
OBJ = $(PROG).o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROG): main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o $(PROG) 