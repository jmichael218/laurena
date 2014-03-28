CORE=src

CFLAGS= -std=c++11 -Wno-write-strings -I src -I ../include

ARCHIVES=mdl.a json.a sql.a velocity.a laurena.a

LIBRARIES=-lboost_system -lboost_filesystem

CC=c++

OBJECTS= $(CORE)/any_descriptor_test.o \
	$(CORE)/bitset_descriptor_test.o \
	$(CORE)/bool_descriptor.o \
	$(CORE)/cstring_test.o \
	$(CORE)/json_serialization_test.o \
	main.o \
	$(CORE)/mdl_serialization_test.o \
	$(CORE)/new_field_init.o \
	$(CORE)/numeric_descriptors_test.o \
	$(CORE)/parameters_test.o \
	$(CORE)/sql_test.o \
	$(CORE)/string_array_descriptor_test.o \
	$(CORE)/shared_pointer_test.o \
	$(CORE)/velocity_test.o
	
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
	

