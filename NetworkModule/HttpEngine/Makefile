CC=g++
LIBS=-lhpsocket
CPPS=./CHttpServerListenerImpl.cpp \
     ./HttpServer.cpp \
     test.cpp

TARGET=httpserv

all:
	$(CC) $(CPPS) $(LIBS) -o $(TARGET)
	
clean:
	rm $(TARGET) -f
