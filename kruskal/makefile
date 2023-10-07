CC = g++
CFLAGS = -std=c++11

all: kruskal exec

kruskal: kruskal.cpp
	$(CC) $(CFLAGS) kruskal.cpp -o kruskal.bin
exec:
	./kruskal.bin
clean:
	rm -f kruskal.bin
