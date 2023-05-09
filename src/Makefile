OMP = /usr/local/opt/libomp/lib
CC = gcc

CPPFLAGS = -I/usr/local/opt/llvm/include -openmp
LDFLAGS = -L/usr/local/opt/llvm/lib

all: mc_p mc_s
mc_p:
	$(CC) -o mc_p mc_p.c $(CPPFLAGS) $(LDFLAGS) -lm

mc_s:
	gcc -o mc_s mc_s.c

compare:
	./penmp 1000000
	./mc_s  1000000


times_p:
	./penmp 1000
	./penmp 10000
	./penmp 100000
	./penmp 1000000
	./penmp 10000000

times_s:
	./mc_s 1000
	./mc_s 10000
	./mc_s 100000
	./mc_s 1000000
	./mc_s 10000000

clean:
	rm -f mc_p mc_s
