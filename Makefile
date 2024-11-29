CC=clang++
CFLAGS=-c -pedantic-errors -gdwarf-4 -std=c++17
LDFLAGS=
SOURCES=exception.cpp datetime.cpp trip.cpp database.cpp aviasales.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=aviasales

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)