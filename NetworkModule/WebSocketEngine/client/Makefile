CC=g++
LIBS=-lhpsocket -lpthread -ljsoncpp
CPPS= test.cpp \
      ./WSClientEngine.cpp \
      ./WSClient.cxx
#OPTI= -O2

TARGET=wsclient

all:
	$(CC) $(CPPS) $(LIBS) $(OPTI) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
