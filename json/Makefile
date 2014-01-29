CORE=src/laurena

CFLAGS= -std=c++11 -Wno-write-strings -I src -I ../include

CC=c++

OBJECTS= $(CORE)/json/iarchive_json.o \
	$(CORE)/json/language_json.o \
	$(CORE)/json/json_interface.o \
	$(CORE)/json/json_dao.o \
	$(CORE)/json/oarchive_json.o

TARGET=json

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
	

