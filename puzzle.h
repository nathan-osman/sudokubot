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

#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>

#include "square.h"

/**
 * Individual sudoku puzzle
 **/
class Puzzle
{
public:

    Puzzle();
    ~Puzzle();

    /// Retrieve the value of the specified square
    int get(int row, int col) const;

    /// Set the value of the specified square
    void set(int row, int col, int num);

    /// Attempt to solve the puzzle
    bool solve();

private:

    /// Calculate the array offset for the specified row and column
    int rowColOffset(int row, int col) const {
        return row * 9 + col;
    }

    /// Calculate the array offset for the specified section and index
    int secOffset(int sec, int ind) const {
        return rowColOffset((sec / 3) * 3 + ind / 3, (sec % 3) * 3 + ind % 3);
    }

    /// Eliminate numbers from squares wherever possible
    void eliminateNumbers(std::vector<Square*> &vec);

    /// Attempt to deduce the location of remaining numbers in an area
    void deduceNumbers(std::vector<Square*> &vec);

    /// Determine if a number is valid in the specified location
    bool isValid(std::vector<Square*> &vec, Square *square, int num) const;

    /// Determine if the puzzle is solved
    bool isSolved() const;

    // The first item is in the upper-left corner and the next item
    // is the one immediately to the right (left-to-right-then-down)
    std::vector<Square*> mSquares;

    // These vectors allow us to use algorithms directly on rows, columns, and sections
    std::vector<Square*> mRows[9];
    std::vector<Square*> mColumns[9];
    std::vector<Square*> mSections[9];
};

#endif // PUZZLE_H
