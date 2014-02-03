CORE=src

CFLAGS= -std=c++11 -Wno-write-strings -I src -I ../../include

ARCHIVES=xml.a laurena.a

LIBRARIES=-lboost_system -lboost_filesystem

CC=c++

OBJECTS= main.o

TARGET=t10

all: $(TARGET)

clean: clear $(TARGET)

$(TARGET): $(OBJECTS)    
	cp ../../bin/debug/*.a .
	$(CC) $(CFLAGS) $(OBJECTS) $(ARCHIVES) $(LIBRARIES) -o $(TARGET)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	find . -type f -name "*.o" -exec rm -f {} \;
