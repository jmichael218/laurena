CORE=src/laurena

CFLAGS= -std=c++11 -Wno-write-strings -I src -I ../include

CC=c++

OBJECTS= $(CORE)/archives/iarchive.o \
	$(CORE)/archives/oarchive.o \
	$(CORE)/constants/const_strings.o \
	$(CORE)/debug/debug.o \
	$(CORE)/debug/debug_stream.o \
	$(CORE)/debug/testunit.o \
	$(CORE)/descriptors/features/class_feature.o \
    $(CORE)/descriptors/features/polymorphic_feature.o \
	$(CORE)/descriptors/annotation.o \
    $(CORE)/descriptors/any_descriptor.o \
    $(CORE)/descriptors/bitset_descriptor.o \
	$(CORE)/descriptors/bool_descriptor.o \
	$(CORE)/descriptors/classes.o \
	$(CORE)/descriptors/const_ptr_descriptor_descriptor.o \
	$(CORE)/descriptors/descriptable.o \
    $(CORE)/descriptors/descriptor.o \
    $(CORE)/descriptors/field.o \
	$(CORE)/descriptors/list_descriptor.o \
	$(CORE)/descriptors/numeric_type_descriptors.o \
	$(CORE)/descriptors/parameter_descriptor.o \
    $(CORE)/descriptors/polymorphic_class_descriptor.o \
	$(CORE)/descriptors/serial_entry_descriptor.o \
	$(CORE)/descriptors/standard_class_descriptor.o \
    $(CORE)/descriptors/string_array_descriptor.o \
    $(CORE)/descriptors/string_descriptor.o \
	$(CORE)/descriptors/unique_descriptor.o \
    $(CORE)/descriptors/variable_descriptor.o \
	$(CORE)/descriptors/vector_descriptor.o \
    $(CORE)/exceptions/bad_cast_exception.o \
	$(CORE)/exceptions/exception.o \
    $(CORE)/exceptions/failed_parsing_exception.o \
    $(CORE)/exceptions/file_not_found_exception.o \
    $(CORE)/exceptions/null_pointer_exception.o \
    $(CORE)/exceptions/unimplemented_exception.o \
    $(CORE)/formatting/format.o \
	$(CORE)/formatting/format_bitset.o \
	$(CORE)/formatting/format_enum.o \
	$(CORE)/formatting/format_epoch.o \
	$(CORE)/functions/parameter.o \
	$(CORE)/languages/language.o \
    $(CORE)/memory/memory_functions.o \
	$(CORE)/parsing/basic_parsers.o \
    $(CORE)/parsing/token.o \
    $(CORE)/parsing/tokenizer.o \
	$(CORE)/persistance/dao.o \
	$(CORE)/persistance/file_dao.o \
	$(CORE)/persistance/file_serial_manager.o \
	$(CORE)/persistance/persistance.o \
	$(CORE)/persistance/serial_manager.o \
	$(CORE)/toolboxes/bitset.o \
	$(CORE)/toolboxes/filename.o \
	$(CORE)/types/any.o \
	$(CORE)/types/context.o \
	$(CORE)/types/datetime_format.o \
	$(CORE)/types/literator.o \
	$(CORE)/types/serial_entry.o \
	$(CORE)/types/string_array.o \
	$(CORE)/types/unique.o \
	$(CORE)/types/variable.o

TARGET=laurena

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
	

