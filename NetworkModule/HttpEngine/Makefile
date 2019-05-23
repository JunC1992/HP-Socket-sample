CC=g++
LIBS=-lhpsocket -ljsoncpp -lpthread
CPPS=./HttpServerEngine.cpp \
     ./HttpServer.cpp \
     ../HttpHandle/HttpHandle.cpp \
     ../HttpHandle/EchoHandle/echoHandle.cpp \
     test.cpp

TARGET=httpserv

all:
	$(CC) $(CPPS) $(LIBS) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
