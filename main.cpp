/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 **/

#include <cstring>
#include <iostream>

#include "puzzle.h"

int main(int argc, char **argv)
{
    // Currently, input to the program is provided by way of a single command-
    // line argument containing the 81 digits for the puzzle in order from
    // left-to-right and then top-to-bottom

    // Ensure the correct input was provided
    if(argc != 2 || strlen(argv[1]) != 81) {
        std::cerr << "Error: argument be a list of 81 digits" << std::endl;
        return 1;
    }

    Puzzle puzzle;
    char *input = argv[1];

    // Whenever a digit between 1 and 9 (inclusive) is specified, set the
    // corresponding square in the puzzle - everything else is unknown
    for(int i = 0; i < 81; ++i) {
        if(input[i] >= '1' && input[i] <= '9') {
            puzzle.set(i % 9, i / 9, input[i] - '0');
        }
    }

    // Let the puzzle solver do all of the hard work
    bool solved = puzzle.solve();

    // Indicate the status to the user
    if(solved) {
        std::cout << std::endl << "Puzzle was solved. Solution below:" << std::endl;
    } else {
        std::cerr << std::endl << "Unable to solve puzzle. Attempt:" << std::endl;
    }

    // Display a grid of the solution (or the solver's attempt if unsolved)
    for(int y = 0; y < 9; ++y) {
        std::cout << "|";
        for(int x = 0; x < 9; ++x) {
            int num = puzzle.get(x, y);
            std::cout << (num ? static_cast<char>(num + '0') : ' ') << '|';
        }
        std::cout << std::endl;
    }

    // Return 0 (success) only if the puzzle was solved
    return solved ? 0 : 1;
}
