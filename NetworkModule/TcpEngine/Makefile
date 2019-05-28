CC=g++
LIBS= -lhpsocket -lpthread -ljsoncpp
OPTI= -O2

ALL_CPPS= ./TcpServer.cpp \
	  ./TcpServerEngine.cpp \
	  ../TcpHandle/TcpHandle.cpp \
	  ../TcpHandle/EchoHandle/echoHandle.cpp \
	  ./test.cpp

TARGET=serv

$(TARGET):$(ALL_CPPS)
	$(CC) $(ALL_CPPS) $(LIBS) $(OPTI) -o $(TARGET)

clean:
	rm $(TARGET) -f
