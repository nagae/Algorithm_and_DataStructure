all:
	gcc naive_array.c && ./a.out
	g++ naive_array.cpp && ./a.out
	gcc array_with_initialize.c && ./a.out
	g++ array_with_initialize.cpp && ./a.out
	gcc array_from_txt.c && ./a.out
	g++ array_from_txt.cpp && ./a.out
	gcc array_from_csv.c && ./a.out
	g++ array_from_csv.cpp && ./a.out
	gcc array_of_struct.c && ./a.out
	g++ array_of_class.cpp && ./a.out
	make -f array_of_client_struct.make
	make test -f array_of_client_struct.make
	make -f array_of_client_class.make
	make test -f array_of_client_class.make


