.PHONY:all
all:shmClient shmServer

shmClient:shmClient.cc
	g++ -o $@ $^ -std=c++11
shmServer:shmServer.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f shmClient shmServer
