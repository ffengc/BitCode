.PHONY:all
all: client server

client: CalClient.cc
	g++ -o  $@ $^ -lpthread -std=c++11
server: CalServer.cc
	g++ -o  $@ $^ -lpthread -std=c++11

.PHONY:clean
clean:
	rm -f server client