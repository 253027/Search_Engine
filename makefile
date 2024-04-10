SRC:= server.cpp ./epoll/epoll.cpp ./eventloop/eventloop.cpp ./inetaddress/inetaddress.cpp \
	  ./socket/socket.cpp ./tcpcontroler/tcpcontroler.cpp ./utility/utility.cpp			   \
	  ./channel/channel.cpp ./tcpcontroler/abstractcontroler.cpp

OBJ:= $(patsubst %.cpp, %.o, $(SRC))

CFLAGS:= 
ifdef _DEBUG
	CFLAGS += -D _DEBUG -g -fsanitize=address
endif

server: $(OBJ)
	g++ $^ -o $@ $(CFLAGS)
%.o: %.cpp
	g++ -c $^ -o $@ $(CFLAGS) 

.PHONY: clean
clean:
	rm -f $(OBJ)