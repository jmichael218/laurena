CORE=src

CFLAGS= -std=c++11 -Wno-write-strings -I /boost -I src -I ../include

ARCHIVES=

LIBRARIES=

CC=c++

OBJECTS= $(CORE)/test_alphabet.o \
	$(CORE)/test_prefix.o \
	$(CORE)/test_readinteger.o \
	$(CORE)/test_readwhile.o \
	$(CORE)/test_rules.o \
	$(CORE)/test_tabs.o \
	main.o \
	$(CORE)/test_charset.o \
	$(CORE)/test_const_charset.o \
	$(CORE)/test_sliteral.o


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
	

