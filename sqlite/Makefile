CORE=src/laurena

CFLAGS= -fpermissive -std=c++11 -Wno-write-strings -Wfatal-errors -I src -I ../include

CC=c++

OBJECTS= $(CORE)/sql/sqlite/sqlite3.o \
	$(CORE)/sql/sqlite/sqlite_database.o \
	$(CORE)/sql/sqlite/sqlite_statement.o

TARGET=sqlite

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