obj-m+=JavadChar.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) testJavadChar.c -o testJavadChar.out
	$(CC) testJavadChar2.c -o testJavadChar2.out -lpthread
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm -rf *.o *.ko *.out *.mod *.mod.c *.symvers *.order *~
