CC = g++
CFLAGS  = -g
ODIR = build

default: clean preBuild build

preBuild: 
	mkdir $(ODIR)

build:  main.o
	$(CC) $(CFLAGS) -o resistor $(ODIR)/main.o -lcurses

main.o:  main.cpp 
	$(CC) $(CFLAGS) -c main.cpp -o $(ODIR)/main.o

clean: 
	$(RM) -r $(ODIR) *~ resistor

