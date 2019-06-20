CC=g++
LIBS=-lhpsocket -ljsoncpp -lpthread -llog4cxx
CPPS=./WSServerEngine.cpp \
     ./WSServer.cpp \
     ../WebSocketHandle/WSHandle.cpp \
     ../WebSocketHandle/EchoHandle/echoHandle.cpp \
     test.cxx
OPTI= -O2

TARGET=wsserv

all:
	$(CC) $(CPPS) $(LIBS) $(OPTI) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
