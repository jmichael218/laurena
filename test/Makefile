CORE=src

CFLAGS= -std=c++11 -Wno-write-strings -I /boost -I src -I ../include

ARCHIVES= mdl.a json.a laurena.a

LIBRARIES=

CC=c++

OBJECTS= $(CORE)/any_descriptor_test.o \
	$(CORE)/bitset_descriptor_test.o \
	$(CORE)/cstring_test.o \
	$(CORE)/json_serialization_test.o \
	main.o \
	$(CORE)/mdl_serialization_test.o \
	$(CORE)/numeric_descriptors_test.o \
	$(CORE)/string_array_descriptor_test.o


TARGET=test

all: $(TARGET)

clean: clear $(TARGET)

$(TARGET): $(OBJECTS)    
	cp ../bin/debug/*.a .
	$(CC) $(CFLAGS) $(OBJECTS) $(ARCHIVES) $(LIBRARIES) -o $(TARGET)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	find . -type f -name "*.o" -exec rm -f {} \;
	

