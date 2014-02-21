CORE=src/laurena

CFLAGS= -std=c++11 -Wno-write-strings -I src -I ../include

CC=c++

OBJECTS= $(CORE)/xml/xml_dao.o \
	$(CORE)/xml/xml_iarchive.o \
	$(CORE)/xml/xml_interface.o \
	$(CORE)/xml/xml_language.o \
	$(CORE)/xml/xml_oarchive.o

TARGET=xml

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
	
