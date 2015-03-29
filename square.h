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

/**
 * Track the possible numbers that could occupy a specific square
 **/
class Square
{
public:

    Square(int row, int col, int sec);

    /// Return the square's row
    int row() const {
        return mRow;
    }

    /// Return the square's column
    int col() const {
        return mCol;
    }

    /// Return the square's section
    int sec() const {
        return mSec;
    }

    /// Rule out a specific possibility
    void eliminate(int num);

    /// Determine if the number has been eliminated yet
    bool couldBe(int num) const;

    /// Retrieve the value of the square (0 if unsolved)
    operator int() const {
        return isSolved() ? mPossibilities.at(0) : 0;
    }

    /// Set the value of the square
    void operator=(int num);

    /// Determine if the square matches the specified number
    bool operator==(int num) const {
        return static_cast<int>(*this) == num;
    }

private:

    /// Determine if the square is solved or not
    bool isSolved() const {
        return mPossibilities.size() == 1;
    }

    int mRow;
    int mCol;
    int mSec;

    std::vector<int> mPossibilities;
};

#endif // SQUARE_H
