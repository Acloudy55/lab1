TARGET=program
CC=gcc
# FLAGS= -MMD -Wno-error=incompatible-function-pointer-types -Wno-incompatible-function-pointer-types -Wno-visibility -Wno-incompatible-pointer-types -g -O0

$(TARGET):  fullclean error.o int.o double.o float.o coef.o complex.o polynomial.o test.o main.o
	$(CC) error.o int.o double.o float.o coef.o complex.o polynomial.o test.o main.o -o $(TARGET)

main.o:
	$(CC) -c main.c $(FLAGS) -o main.o
test.o:
	$(CC) -c test.c $(FLAGS) -o test.o
cli.o:
	$(CC) -c cli.c $(FLAGS) -o cli.o
polynomial.o:
	$(CC) -c polynomial.c $(FLAGS) -o polynomial.o
error.o:
	$(CC) -c error.c $(FLAGS) -o error.o
complex.o:
	$(CC) -c types/complex.c $(FLAGS) -o complex.o
float.o:
	$(CC) -c types/float.c $(FLAGS) -o float.o
double.o:
	$(CC) -c types/double.c $(FLAGS) -o double.o
int.o:
	$(CC) -c types/int.c $(FLAGS) -o int.o
coef.o:
	$(CC) -c coef.c $(FLAGS) -o coef.o
.PHONY: clean fullclean test

clean:
	rm -f *.o
	rm -f *.d

fullclean: clean
	rm -f $(TARGET)

test: $(TARGET)
	./run_tests.sh
