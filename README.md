# MPI Array Sorting Solution with Bitonic Sort
This project presents a parallel solution to Array sorting using MPI. To run the main part of the code you will need to run the following commands in a terminal.
1. git clone https://github.com/NicKylis/MpiSort.git
   This will clone the components of the repository to your local directory
2. make
   This acitvates the Makefile which will produce the executable file main
3. mpicc -np <p> ./main <q> <p>
   Runs the code with p processes and q elements for each process
NOTE that p needs to be a power of 2. For more information you can also type:
make help
