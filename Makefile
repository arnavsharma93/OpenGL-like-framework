CC = g++
CFLAGS = -Wall
PROG = out

SRCS = mainAssignment3.cpp
LIBS = -lglut -lGL -lGLU -larmadillo

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
