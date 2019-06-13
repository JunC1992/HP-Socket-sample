CXX = g++
CFLAGS = -Wall -O2 -g
SRCS = $(wildcard *.cpp */*.cpp */*/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGET = libhxnet.so

$(TARGET) : $(OBJS)
	$(CXX) -shared -o $(TARGET) $^ $(CFLAGS)

%.o : %.cpp
	$(CXX) -fPIC -c $< -o $@ -g

clean:
	rm $(TARGET) $(OBJS) -rf
