CORE=src

CFLAGS= -std=c++11 -Wno-write-strings -I src -I ../../include

ARCHIVES=json.a sql.a laurena.a

LIBRARIES=

CC=c++

OBJECTS= main.o

TARGET=t04

all: $(TARGET)

clean: clear $(TARGET)

$(TARGET): $(OBJECTS)    
	cp ../../bin/debug/*.a .
	$(CC) $(CFLAGS) $(OBJECTS) $(ARCHIVES) $(LIBRARIES) -o $(TARGET)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	find . -type f -name "*.o" -exec rm -f {} \;
