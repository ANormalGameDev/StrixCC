builddir = output
objects = $(builddir)/main.o

strixc: $(objects)
		g++ -o strixc $(objects)
		make clean

$(builddir)/main.o: src/main.cc
		g++ -o$(builddir)/main.o -c src/main.cc

clean:
	rm $(objects)