CC=g++
LIBS=-lhpsocket -ljsoncpp -lpthread
CPPS=./HttpServerEngine.cpp \
     ./HttpServer.cpp \
     ../HttpHandle/HttpHandle.cpp \
     ../HttpHandle/EchoHandle/echoHandle.cpp \
     test.cpp
OPTI= -O2

TARGET=httpserv

all:
	$(CC) $(CPPS) $(LIBS) $(OPTI) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
