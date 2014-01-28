all:
	cd laurena0; make
	cd laurena; make clean
	cd json; make clean
	cd mdl; make clean
	cd velocity; make clean
	cd sql; make clean
	cd test; make clean
	cd examples; make clean
	cd tutorials/t01_simple_example; make clean
	cd tutorials/t02_polymorphic_example; make clean
	cd tutorials/t03_list_example; make clean
	cd tutorials/t04_vector_example; make clean
	cd tutorials/t05_enum_example; make clean
	cd tutorials/t06_bitfield_example; make clean
	cd tutorials/t07_epoch_example; make clean