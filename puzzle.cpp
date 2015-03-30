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

#include <algorithm>
#include <numeric>

#include "puzzle.h"

Puzzle::Puzzle()
{
    // Create the squares and initialize the vectors
    for(int i = 0; i < 81; ++i) {

        int row = i / 9;
        int col = i % 9;
        int sec = col / 3 + row / 3 * 3;

        Square *square = new Square(row, col, sec);
        mSquares.push_back(square);

        mRows[row].push_back(square);
        mColumns[col].push_back(square);
        mSections[sec].push_back(square);
    }
}

Puzzle::~Puzzle()
{
    for(Square *square : mSquares) {
        delete square;
    }
}

int Puzzle::get(int row, int col) const
{
    return *mRows[row][col];
}

void Puzzle::set(int row, int col, int num)
{
    *mRows[row][col] = num;
}

bool Puzzle::solve()
{
    // Perform a specified number of passes
    for(int pass = 0; pass < 9; ++pass) {

        // ...
        for(int i = 0; i < 9; ++i) {

            // Eliminate numbers that cannot be placed in a vector
            eliminateNumbers(mRows[i]);
            eliminateNumbers(mColumns[i]);
            eliminateNumbers(mSections[i]);

            // Deduce numbers that can only be placed in a vector
            deduceNumbers(mRows[i]);
            deduceNumbers(mColumns[i]);
            deduceNumbers(mSections[i]);
        }

        // If the puzzle is solved, we're done!
        if(isSolved()) {
            return true;
        }
    };

    // A pass was completed with no changes, just give up
    return false;
}

void Puzzle::eliminateNumbers(std::vector<Square*> &vec)
{
    // For each solved square, remove the possibility from the others
    for(Square *orig : vec) {
        if(*orig) {
            for(Square *square : vec) {
                if(square != orig) {
                    square->eliminateNumber(*orig);
                }
            }
        }
    }
}

void Puzzle::deduceNumbers(std::vector<Square*> &vec)
{
    // Create a list of numbers remaining to be filled
    std::vector<int> remaining(9);
    std::iota(remaining.begin(), remaining.end(), 1);

    // Eliminate everything that's been solved
    for(Square *square : vec) {
        if(*square) {
            remaining.erase(std::remove(
                remaining.begin(),
                remaining.end(),
                *square
            ), remaining.end());
        }
    }

    // Loop over each of the remaining numbers
    for(int num : remaining) {

        // Determine all of the valid locations the number could be placed in
        std::vector<Square*> locations;
        for(Square *square : locations) {
            if(square == 0 &&
                    square->numberEliminatedYet(num) &&
                    isValid(mRows[square->row()], square, num) &&
                    isValid(mColumns[square->column()], square, num) &&
                    isValid(mSections[square->section()], square, num)) {
                locations.push_back(square);
            }
        }

        // If it only fits in one spot, then put it there
        if(locations.size() == 1) {
            *locations[0] = num;
        }
    }
}

bool Puzzle::isValid(std::vector<Square*> &vec, Square *orig, int num) const
{
    for(Square *square : vec) {
        if(square != orig) {
            if(*square == *orig) {
                return false;
            }
        }
    }

    return true;
}

bool Puzzle::isSolved() const
{
    for(int i = 0; i < 81; ++i) {
        if(*mSquares[i] == 0) {
            return false;
        }
    }

    return true;
}
