# calls:
CC         = g++
CFLAGS     = -w -c -Wall -O3 -std=c++11
LDFLAGS    = 
EXECUTABLE = lines

SOURCES    = lines.cpp Util.cpp
OBJECTS    = $(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE) 
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o lines
