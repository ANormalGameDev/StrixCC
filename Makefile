builddir = output
objects = $(builddir)/main.o $(builddir)/uci.o

strixc: $(objects)
		g++ -o strixc $(objects)
		make clean

$(builddir)/main.o: src/main.cc src/uci.hh
		g++ -o$(builddir)/main.o -c src/main.cc

$(builddir)/uci.o: src/uci.cc src/uci.hh
		g++ -o$(builddir)/uci.o -c src/uci.cc

clean:
	rm $(objects)