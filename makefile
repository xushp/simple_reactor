server.out client.out : server.o initiation_dispatcher.o logging_acceptor.o logging_handler.o net.o
	g++ -o server.out server.o initiation_dispatcher.o logging_acceptor.o logging_handler.o net.o
	gcc -o client.out client.c

#client.out : client.o
#	gcc -o client.out client.o

client.o : client.c
	gcc -c client.c

server.o : server.cc initiation_dispatcher.h net.h event_handler.h logging_acceptor.h log.h
	g++ -c server.cc

initiation_dispatcher.o : initiation_dispatcher.cc initiation_dispatcher.h 
	g++ -c initiation_dispatcher.cc

logging_acceptor.o : logging_acceptor.cc logging_acceptor.h 
	g++ -c logging_acceptor.cc

logging_handler.o : logging_handler.cc logging_handler.h 
	g++ -c logging_handler.cc

net.o : net.cc net.h
	g++ -c net.cc

clean :
	rm server.out client.out server.o initiation_dispatcher.o logging_acceptor.o logging_handler.o net.o

