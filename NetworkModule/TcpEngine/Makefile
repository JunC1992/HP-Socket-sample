CC=g++
LIBS= -lhpsocket -lpthread

ALL_CPPS= ./TcpServer.cpp \
	  ./TcpServerEngine.cpp \
	  ./test.cpp

TARGET=serv

$(TARGET):$(ALL_CPPS)
	$(CC) $(ALL_CPPS) $(LIBS) -o $(TARGET)

clean:
	rm $(TARGET) -f
