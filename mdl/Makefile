CORE=src/laurena

CFLAGS= -std=c++11 -Wno-write-strings -I src -I ../include

CC=c++

OBJECTS= $(CORE)/mdl/iarchive_mdl.o \
	$(CORE)/mdl/mdl_language.o \
	$(CORE)/mdl/mdl_interface.o \
	$(CORE)/mdl/mdl_dao.o \
	$(CORE)/mdl/oarchive_mdl.o

TARGET=mdl

all: $(TARGET)

clean: clear $(TARGET)

$(TARGET): $(OBJECTS)    
	rm -f $(TARGET).a
	rm -f $(TARGET).so
	$(CC) $(CFLAGS) -L bin -shared $(OBJECTS) -o $(TARGET).so
	ar -r $(TARGET).a $(OBJECTS)
	cp $(TARGET).so ../bin/debug
	cp $(TARGET).a ../bin/debug
	cd src; find ./ -name '*.hpp' | xargs cp -a --target-directory=../../include --parents

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	find . -type f -name "*.o" -exec rm -f {} \;
	

