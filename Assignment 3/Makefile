all: tdQ

tdQ:  Queue.h Event.o EmptyDataCollectionException.o
	g++ -o tdQ -Wall  Event.o EmptyDataCollectionException.o
	

	
Event.o: Event.cpp Event.h
	g++ -c -Wall Event.cpp

EmptyDataCollectionException.o: EmptyDataCollectionException.cpp EmptyDataCollectionException.h 
	g++ -c -Wall EmptyDataCollectionException.cpp

clean:	
	rm -f tdQ *.o
