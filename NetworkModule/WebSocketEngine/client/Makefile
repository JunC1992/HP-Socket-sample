CC=g++
LIBS=-lhpsocket -lpthread
CPPS= test.cpp \
      ./WSClientEngine.cpp \
      ./WSClient.cpp
#OPTI= -O2

TARGET=wsclient

all:
	$(CC) $(CPPS) $(LIBS) $(OPTI) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
