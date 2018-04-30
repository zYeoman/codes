#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile that compiles and runs the digitrec program
#
# @desc: 1. "make" or "make sw" runs software execution by default
# 		 2. "make clean" cleans up the directory


all: sw

sw: digitrec.cpp host.cpp
	@echo "Compiling & executing digitrec on local host ... "
	g++ digitrec.cpp host.cpp -o host.o
	./host.o

clean:
		@echo "Clean up output files"
		rm -rf *.o

