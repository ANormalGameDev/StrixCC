builddir = output
objects = $(builddir)/main.o $(builddir)/Magics.o $(builddir)/BoardsAndThreads.o $(builddir)/Moves.o $(builddir)/Bitboards.o

strixcc: $(objects)
		g++ -pg -o strixcc.out $(objects)
		make clean

$(builddir)/main.o: src/main.cc src/engine.hh src/Chess/Magics.hh src/Chess/BoardsAndThreads.hh src/Chess/Moves.hh
		g++ -o$(builddir)/main.o -c src/main.cc

$(builddir)/BoardsAndThreads.o: src/Chess/BoardsAndThreads.cc src/Chess/Utils.hh src/Chess/Magics.hh src/Chess/BoardsAndThreads.hh
		g++ -o$(builddir)/BoardsAndThreads.o -c src/Chess/BoardsAndThreads.cc

$(builddir)/Moves.o: src/Chess/Moves.cc src/Chess/Moves.hh src/Chess/Utils.hh src/Chess/Magics.hh src/Chess/BoardsAndThreads.hh src/engine.hh
		g++ -o$(builddir)/Moves.o -c src/Chess/Moves.cc

$(builddir)/Magics.o: src/Chess/Magics.cc src/engine.hh src/Chess/Magics.hh src/Chess/BoardsAndThreads.hh src/Chess/PrestoredMagics.hh
		g++ -o$(builddir)/Magics.o -c src/Chess/Magics.cc

$(builddir)/Bitboards.o: src/Chess/Bitboards.cc src/Chess/Moves.hh src/Chess/Utils.hh src/Chess/Magics.hh src/Chess/BoardsAndThreads.hh src/engine.hh
		g++ -o$(builddir)/Bitboards.o -c src/Chess/Bitboards.cc

clean:
	rm $(objects)