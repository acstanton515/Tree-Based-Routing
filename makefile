objects = sss.o node.o address.o packet.o

sss : $(objects)
	g++ -o bin/sss $(objects)

address.o : address.cc address.h
	g++ -c address.cc
sss.o : sss.cc sss.h
	g++ -c sss.cc
node.o : node.cc node.h
	g++ -c node.cc
packet.o : packet.cc packet.h
	g++ -c packet.cc
clean :
	rm $(objects) bin/sss
