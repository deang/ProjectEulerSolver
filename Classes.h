#include<iostream>
#include<set>
#include<list>
#include<vector>

namespace GND
{

class StringInt
    {
    public:

    StringInt(std::string sInitialValue); 
    StringInt(int nInitialValue);
    ~StringInt();

    void SetString(std::string const &sNew);
    std::string GetString() const;

    //Increments to n+1.
    void Increment();

    //This function takes a StringInt
    //and reads it's value into nNumber.  It will return
    //false if the number is too large to be stored as an int.
    void ToInt(int &nNumber) const;

    //This function will return true if m_StringInt and another have
    //the same digits (including a different order).
    bool bSameDigits(std::string const &sOtherString) const;

    //This function multiplies an integer represented by m_StringInt
    //by nMultiplier and returns a string result.
    std::string StringMultiply(int nMultiplier) const;

    //This function multiplies an integer represented by m_StringInt
    //by sMultiplier and returns a string result.
    std::string StringMultiply(std::string sMultiplier) const;

    //This function returns true if the digits of this,
    //StringIntA, and StringIntB have digits 1-9
    //once and only once taken together.
    bool StringIntPandigital(GND::StringInt const &StringIntA, 
                             GND::StringInt const &StringIntB) const;

    //This method compares the m_StringCubed of this and siOther
    //and returns true if they contain the same digits.
    bool bPermutedCubes(GND::StringInt const &siOther) const;

    //This method will take an integer exponent and return the
    //string representation of the cube of m_String.
    std::string power(int const nExponent) const;

    //This method will return the number of digits in m_String.
    int nNumberOfDigits() const;

    // This method returns the indices of the digits of m_String
    // which match nNumber.  Between 0 and 9 inclusive, nothing will
    // be returned.
    void IndicesOfMatchingDigits(int        const &nNumber,
                                 std::set<size_t> &sIndices) const;

    // This method returns m_String with its digits replaced with nNumber.
    // The digits replaced are indicated by sIndices.
    int ReplacedDigits(int              const &nNumber,
                       std::set<size_t> const &sIndices) const;

    // This method will replace the Index'th number of this
    // with nNumber.  If nNumber is not 0-9, nothing will be
    // done.
    void ReplaceDigit(int const &nNumber,size_t const &Index);

    // This method returns the digit sum of the integer.
    int DigitSum() const;

    private:

    std::string m_String;
    };

class SudokuGrid
    {
    public:
        SudokuGrid(int aanGrid[9][9]); 

        // Attempts to solve the puzzle.
        // If it cannot, it will return false.
        bool Solve();

        // Prints the grid to the screen.
        void Print() const;

        // Returns the number in the upper
        // left of the grid.
        int TopThree() const;

    private:

        // A constructor using raw data.
        SudokuGrid(int aanGrid[9][9],bool aaabPossibilities[9][9][9]);

        // Attempts to solve the puzzle in a deterministic fashion.
        // If the algorithm cannot, it will
        // return false.
        bool DeterministicSolve();

        // Increments the grid in a deterministic way.
        // If not possible, the method will return false.
        bool Increment();

        bool FindOnlyChoice(int &nAnswer,int &nXCoordinate,int &nYCoordinate) const;

        bool FindTwoOutOfThree(int &nAnswer,int &nXCoordinate,int &nYCoordinate) const;

        // Indicates whether the grid has been solved.
        // This should be used sparingly as it relies
        // on brute force checking.
        bool IsSolved() const;

        // The grid in its current state.
        // 0 indicates an unknown value.
        int m_aanGrid[9][9];

        // Cached possibilities.  Note:
        // any non-const method must
        // reset the cache.
        mutable bool m_aaabPossibilities[9][9][9];

        // Blind reset cache.
        void ResetCache() const;

        // Reset cache given a changed location in m_aanGrid.
        // This will be much faster than the blind method.

        // For performance, the method assumes the cache was
        // correct prior to the change.
        void ResetCache(int nXCoordinate, int nYCoordinate) const;
    };

#define SET_LEFT 0
#define SET_RIGHT 1

class SetData
    {
    public:
        SetData();

        // Inserts nValue into nDigit's nDirection set.
        // For example, one could add a 2 to 3's left
        // set by calling Insert(3,2,SET_LEFT);
        void Insert(int nDigit,int nValue,int nDirection);

        std::set<int> const &GetLeftSet(int nDigit);
        std::set<int> const &GetRightSet(int nDigit);

    private:
        // Left and Right sets for the digits 0-9.
        std::vector<std::pair<std::set<int>,std::set<int>> > m_Sets;

    };

class Passcode
    {
    public:
        Passcode(int nLogins[150]);

        // Solves the passcode and returns
        // the answer.
        int Solve();

    private:

        int ReturnAsInt();

        // A list of the ordered digits of the solution.
        std::vector<int> m_aSolution;

        // Data indicating left and right digits
        // of the digits 0-9.
        GND::SetData m_SetData;
    };

class PythagoreanTriple
    {
    public:
        PythagoreanTriple();

        // Increments the triple.
        // If this is not possible
        // the operator will return false.
        bool operator++();

        // Returns the triple.
        void ComputeTriple(int &nA,int &nB,int &nC);

    private:

        // These integers are the parameters of
        // Euclid's formula.

        // The triple is:
        
        // A=K(M2-N2)
        // B=K(2MN)
        // C=K(M2+N2)

        int m_nM;
        int m_nN;
        int m_nK;
        
    };

}