SRC:= server.cpp ./epoll/epoll.cpp ./eventloop/eventloop.cpp ./inetaddress/inetaddress.cpp \
	  ./socket/socket.cpp ./networkcontroler/tcpcontroler.cpp ./utility/utility.cpp			   \
	  ./channel/channel.cpp ./networkcontroler/abstractcontroler.cpp 

OBJ:= $(patsubst %.cpp, %.o, $(SRC))

CFLAGS:= 
ifdef _DEBUG
	CFLAGS += -D _DEBUG -g -fsanitize=address
endif

server: $(OBJ)
	g++ $^ $(CFLAGS) -o $@ 
%.o: %.cpp
	g++ -c $^ $(CFLAGS)  -o $@ 

.PHONY: clean
clean:
	rm -f $(OBJ)