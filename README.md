## sudokubot

The goal of this program is to provide a simple application that can be used to solve sudoku puzzles of varying difficulty in a timely and accurate manner.

### About the Application

sudokubot is written in C++11 and uses nothing more than the standard template library (STL). As such, it should compile with any modern compiler. The application uses CMake for building the sudokubot binary.

### Building the Application

The commands for building the application are very simple:

    mkdir build
    cd build
    cmake ..

### Using the Application

The application expects the 9x9 grid to be supplied via a single 81-digit command-line argument. Any square that is not solved should use a non-numeric digit instead (such as '?' or '*'). An example is given below:

    $ ./sudokubot ??13?2?65??7??????653?1??243????1?7????235????1?4????353??8?297??????5??98?7?41??

sudokubot will logically deduce the values of the unsolved squares and display the results.
