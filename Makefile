src = src
csrc = $(src)/Engine
sources = $(src)/main.cc $(csrc)/Engine.cc $(csrc)/Board.cc $(csrc)/Utils.cc $(csrc)/Bitboards.cc $(csrc)/Moves.cc
execname = strixcc

use-clang:
	clang++ --version
	clang++ -Wall -O -o$(execname) $(sources)

use-gcc:
	g++ --version
	g++ -Wall -O -o$(execname) $(sources)