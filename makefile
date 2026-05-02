OBJ = $(patsubst %.c ,%.o ,$(wildcard *.c))
APC.out : $(OBJ)
	gcc -o $@ $^
clean :
	rm *.exe *.o
