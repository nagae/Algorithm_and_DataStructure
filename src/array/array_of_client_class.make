CC = g++
LIB_DIR = ../client
CFLAGS = 
PROGRAM = array_of_client_class
OBJS = array_of_client_class.o $(LIB_DIR)/client_class.o

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


