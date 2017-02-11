CC = gcc
LIB_DIR = ../../lib
CFLAGS = -std=c11
PROGRAM = array_of_client_struct
OBJS = array_of_client_struct.o $(LIB_DIR)/client_struct.o

$(PROGRAM): $(OBJS)
	$(CC) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(PROGRAM)
test:
	make -f $(PROGRAM).make
	./$(PROGRAM) test_data.csv
	make clean -f $(PROGRAM).make



