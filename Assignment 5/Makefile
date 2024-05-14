# Define the default target
all: hftd

# Compile the application
hftd: hashFunctionTestDriver.o Dictionary.o Profile.o EmptyDataCollectionException.o ElementAlreadyExistsException.o UnableToInsertException.o ElementDoesNotExistException.o
	g++ -Wall -o hftd hashFunctionTestDriver.o Dictionary.o Profile.o EmptyDataCollectionException.o ElementAlreadyExistsException.o UnableToInsertException.o ElementDoesNotExistException.o

# Compile hashFunctionTestDriver
hashFunctionTestDriver.o: hashFunctionTestDriver.cpp
	g++ -Wall -c hashFunctionTestDriver.cpp  

# Compile Dictionary
Dictionary.o: Dictionary.h Dictionary.cpp Profile.h
	g++ -Wall -c Dictionary.cpp

# Compile Profile
Profile.o: Profile.h Profile.cpp
	g++ -Wall -c Profile.cpp
	
# Compile EmptyDataCollectionException
EmptyDataCollectionException.o: EmptyDataCollectionException.h EmptyDataCollectionException.cpp
	g++ -Wall -c EmptyDataCollectionException.cpp

# Compile ElementAlreadyExistsException
ElementAlreadyExistsException.o: ElementAlreadyExistsException.h ElementAlreadyExistsException.cpp
	g++ -Wall -c ElementAlreadyExistsException.cpp

# Compile UnableToInsertException
UnableToInsertException.o: UnableToInsertException.h UnableToInsertException.cpp
	g++ -Wall -c UnableToInsertException.cpp

# Compile ElementDoesNotExistException
ElementDoesNotExistException.o: ElementDoesNotExistException.h ElementDoesNotExistException.cpp
	g++ -Wall -c ElementDoesNotExistException.cpp

# Clean up generated files
clean:
	rm -f hftd *.o

