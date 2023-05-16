OMP = /usr/local/opt/libomp/lib
CC = gcc

CPPFLAGS = -I/usr/local/opt/llvm/include -openmp
LDFLAGS = -L/usr/local/opt/llvm/lib

all: win_p mc_s
mc_p:
	$(CC) -o mc_p mc_p.c $(CPPFLAGS) $(LDFLAGS)
win_p:
	$(CC) -o mc_p mc_p.c -fopenmp -std=c11

mc_s:
	gcc -std=c11 -o mc_s mc_s.c

compare:
	./mc_p 1000000
	./mc_s  1000000

scale:
	./mc_p 10000000 1
	./mc_p 10000000 2
	./mc_p 10000000 3
	./mc_p 10000000 4
	./mc_p 10000000 5
	./mc_p 10000000 6
	./mc_p 10000000 7
	./mc_p 10000000 8

times_p:
	./mc_p.exe 1000 8
	./mc_p.exe 10000 8
	./mc_p.exe 100000 8
	./mc_p.exe 1000000 8
	./mc_p.exe 10000000 8

times_s:
	./mc_s 1000
	./mc_s 10000
	./mc_s 100000
	./mc_s 1000000
	./mc_s 10000000

clean:
	rm -f mc_p mc_s
