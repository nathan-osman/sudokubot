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

#ifndef SQUARE_H
#define SQUARE_H

#include <vector>

// Track the possible numbers that could occupy a specific square
class Square
{
public:

    Square(int row, int column, int section);

    // Each square needs to keep track of its row / column / section so that
    // later when the validity of potential numbers is investigated, the area
    // can be checked for existing numbers

    int row() const { return mRow; }
    int column() const { return mColumn; }
    int section() const { return mSection; }

    void eliminateNumber(int number);
    bool numberEliminatedYet(int number) const;

    // Retrieve the value of the square (0 if unsolved)
    operator int() const {
        return (mPossibilities.size() == 1) ? mPossibilities.at(0) : 0;
    }

    // Set the value of the square
    void operator=(int number);

    // If the square is solved, determine if it matches the number
    bool operator==(int number) const {
        return static_cast<int>(*this) == number;
    }

private:

    int mRow;
    int mColumn;
    int mSection;

    std::vector<int> mPossibilities;
};

#endif // SQUARE_H
