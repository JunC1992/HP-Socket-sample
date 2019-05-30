CC=g++
LIBS=-lhpsocket -ljsoncpp -lpthread
CPPS=./WSServerEngine.cpp \
     ./WSServer.cpp \
     ../WebSocketHandle/WSHandle.cpp \
     ../WebSocketHandle/EchoHandle/echoHandle.cpp \
     test.cpp
#OPTI= -O2

TARGET=wsserv

all:
	$(CC) $(CPPS) $(LIBS) $(OPTI) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
