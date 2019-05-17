CC=g++
LIBS= -lhpsocket -lpthread

SERV=serv
CLI=client
CLI4C=client4c

all:
	$(CC) serv.cpp $(LIBS) -o $(SERV)
	$(CC) client.cpp $(LIBS) -o $(CLI)
	$(CC) sock_cli.c -o $(CLI4C)
	
$(SERV): serv.cpp
	$(CC) serv.cpp $(LIBS) -o $(SERV)

$(CLI): client.cpp
	$(CC) client.cpp $(LIBS) -o $(CLI)

$(CLI4C): sock_cli.c
	$(CC) sock_cli.cpp -o $(CLI4C)


clean:
	rm $(SERV) $(CLI) $(CLI4C)
