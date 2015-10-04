CC					= g++
CFLAGS			= -Wall -g -O
INCLUDES	  =
LIBS				= 
OBJS 				= server.o 								\
							initiation_dispatcher.o \
							logging_acceptor.o 			\
							logging_handler.o				\
							net.o

SOURCE			=	$(OBJS:.o=.cpp)

TARGET 			= server.out client.out

all : $(TARGET)
.PHONY: all 

server.out : $(OBJS)
	$(CC) -o $@ $^
client.out : 
	gcc -o client.out client.c

#client.out : client.o
#	gcc -o client.out client.o

%.o : %.cc
		$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

%.d:%.cpp
		@set -e; rm -f $@; 	$(CC) -MM $(CFLAGS) $(INCLUDES) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;  \
		rm -f $@.$$$$ 


.PHONY: clean
.IGNORE:clean
clean :
	-rm $(OBJS) *.o *.d *.d.* $(TARGET) 

