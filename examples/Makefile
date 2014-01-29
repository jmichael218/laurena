CORE=src

CFLAGS= -std=c++11 -Wno-write-strings -I src -I ../include

ARCHIVES=mdl.a json.a sql.a velocity.a laurena.a

LIBRARIES=-lboost_system

CC=c++

OBJECTS= $(CORE)/ABitSetExample.o \
	$(CORE)/ACustomizedTypeFormat.o \
	$(CORE)/aListClass.o \
	$(CORE)/anEnumExample.o \
	$(CORE)/aPolymorphicClass.o \
	$(CORE)/APrivateClass.o \
	$(CORE)/aSimpleClass.o \
	$(CORE)/aVectorClass.o \
	$(CORE)/classesExamples.o \
	$(CORE)/main.o


TARGET=examples

all: $(TARGET)

clean: clear $(TARGET)

$(TARGET): $(OBJECTS)    
	cp ../bin/debug/*.a .
	$(CC) $(CFLAGS) $(OBJECTS) $(ARCHIVES) $(LIBRARIES) -o $(TARGET)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	find . -type f -name "*.o" -exec rm -f {} \;