CC = g++
LIB_DIR = ../lib
CFLAGS = 
PROGRAM = array_of_client_class
OBJS = array_of_client_class.o $(LIB_DIR)/client_class.o

$(PROGRAM): $(OBJS)
	$(CC) -o $@ $^
.c.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(PROGRAM) array_of_client_class.o
test:
	./$(PROGRAM) test_data.csv


