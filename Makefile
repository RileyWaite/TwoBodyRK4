CC = g++
CFLAGS = -O2 -std=c++11
DEPS = headers/vecManip.hpp headers/RK4.hpp
TARGET = bin/propagation

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(DEPS)
	$(CC) $(CFLAGS) -c src/propagation.cpp -o bin/propagation.o

clean:
	$(RM) count *.o *~
	$(RM) bin/*
