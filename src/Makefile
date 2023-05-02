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
	./mc_s 1000000

clean:
	rm -f mc_p mc_s
