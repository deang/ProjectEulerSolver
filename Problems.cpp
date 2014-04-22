#include "stdafx.h"

#include <cstdio> 
#include <iostream>
#include <fstream>
#include <string>

#include "Functions.h"
#include "Classes.h"
#include "IO.h"

#define GND_MAXINT 2000000000

int SolveProblem32()
    {
    int nSum = 0;
    std::set<int> sProducts;
    for(int nNumber = 1; nNumber < 10000; ++nNumber)
        {
        for(int nFactor1 = 1; nFactor1 <= nNumber/2; ++nFactor1)
            {
            if(nNumber%nFactor1 == 0)
                {
                int nFactor2 = nNumber/nFactor1;
                GND::StringInt siNumber(nNumber),
                               siFactor1(nFactor1),
                               siFactor2(nFactor2);
                if(siNumber.StringIntPandigital(siFactor1,siFactor2))
                    {
                    if(bSetChangeInsert(sProducts,nNumber))
                        {
                        nSum+=nNumber;
                        }
                    }
                }
            }
        }
    return nSum;
    }

int SolveProblem42()
    {
    //Read in the file.
    std::ifstream file("C:/Euler/words.txt");
    std::string sWords;
    std::getline(file, sWords);

    //Create a vector of strings with all of the words.
    std::string csWords = sWords.c_str();
    //For God's sake give me something without all the fucking parentheses.
    std::string csWordsCorrected = "";
    for(size_t Index = 0; Index < csWords.length(); ++Index)
        {
        //If it equals ".
        if (csWords[Index] == 34)
            {
            //
            }
        else
            {
            csWordsCorrected += csWords.substr(Index,1);
            }
        }
    //Calculate the word value for each word.
    //Determine how many of the word values are triangle numbers.
    std::string sTemp = "";
    std::string aWordStrings[3571];
    int nNumberTriangleWords = 0;
    for(size_t Index = 0; Index < csWordsCorrected.length(); ++Index)
        {
        if(csWordsCorrected[Index] == 44)
            {
            if(IsWordTriangle(sTemp))
                {
                ++nNumberTriangleWords;
                }
            sTemp.clear();
            }
        else
            {
            sTemp += csWordsCorrected.substr(Index,1);
            }
        }

/*    int nNumberTriangleWords = 0;
    for(size_t Index = 0; Index < aWordStrings->size(); ++Index)
        {
        if(IsWordTriangle(aWordStrings[Index]))
            {
            ++nNumberTriangleWords;
            }
        }*/ 
    return nNumberTriangleWords;
    }

int SolveProblem44()
    {
    int Index1 = 2,Index2 = 1;
    bool bExit = false;
    int nAnswer = 2147483647;  //Presumably the answer is less than this.
    while(!bExit)
        {
        Index2 = 1;
        int nPentagonal1 = pentagonal(Index1);
        while(Index2 < Index1)
            {
            int nPentagonal2 = pentagonal(Index2);
            int nSum=nPentagonal1+nPentagonal2;
            int nDiff=nPentagonal1-nPentagonal2;
            if(isPentagonal(nSum) && isPentagonal(nDiff) && nDiff < nAnswer)
                {
                nAnswer = nDiff;
                bExit = true;
                }
            ++Index2;
            }
        ++Index1;
        }
    return nAnswer;
    }

int SolveProblem45()
    {
    unsigned int nTriNumber = 0,nPentNumber = 0,nHexNumber = 0;
    int nTriIndex = 1,nPentIndex = 1,nHexIndex = 1;
    nTriNumber = nTriIndex*(nTriIndex+1)/2;
    nPentNumber = nPentIndex*(3*nPentIndex-1)/2;
    nHexNumber = nHexIndex*(2*nHexIndex-1);
    bool bSolved = false;
    while(!bSolved)
        {
        //If Tn = Tp = Th, exit the program.
        if(nTriNumber == nHexNumber && nTriNumber==nPentNumber && nTriIndex > 285)
            {
            bSolved = true;
            }
        else
            {
            //If Tn > Tp, calculate the next Tp
            if(nTriNumber>nPentNumber)
                {
                ++nPentIndex;
                nPentNumber = nPentIndex*(3*nPentIndex-1)/2;
                }
            //If Tn > Th, calculate the next Th
            if(nTriNumber>nHexNumber)
                {
                ++nHexIndex;
                nHexNumber = nHexIndex*(2*nHexIndex-1);
                }
            //Calculate the next Tp.
            ++nTriIndex;
            nTriNumber = nTriIndex*(nTriIndex+1)/2;
            }
        }
    return nTriNumber;
    }

int SolveProblem47()
    {
    //The problem wants the first 4 consecutive integers with 4 distinct prime
    //factors each.  This algorithm will find the first n consecutive integers
    //with n distinct prime factors.  Here n is nDistinct.
    int nDistinct = 4;
    int nNumber = 1;
    bool bSolved = false;
    while(!bSolved)
        {
        ++nNumber;
        int nCorrectCount = 0;
        for(int Index = 0; Index < nDistinct; ++Index)
            {
            if(nDistinctPrimeFactors(nNumber + Index) == nDistinct)
                {
                ++nCorrectCount;
                }
            }
        if(nCorrectCount==nDistinct)
            {
            bSolved = true;
            }
        }
    return nNumber;
    }

int SolveProblem52()
    {
    GND::StringInt siNumber("1");
    bool bSolved = false;
    int nAnswer = 0;
    while(!bSolved)
        {
        if(siNumber.bSameDigits(siNumber.StringMultiply(2)))
            {
            if(siNumber.bSameDigits(siNumber.StringMultiply(3)))
                {
                if(siNumber.bSameDigits(siNumber.StringMultiply(4)))
                    {
                    if(siNumber.bSameDigits(siNumber.StringMultiply(5)))
                        {
                        if(siNumber.bSameDigits(siNumber.StringMultiply(6)))
                            {
                            siNumber.ToInt(nAnswer);
                            bSolved = true;
                            }
                        }
                    }
                }
            }
        siNumber.Increment();
        }
    return nAnswer;
    }

int SolveProblem56()
    {
    // A googol (10^100) is a massive number: one followed by one-hundred
    // zeros; 100^100 is almost unimaginably large: one followed by two-
    // hundred zeros. Despite their size, the sum of the digits in each
    // number is only 1.

    // Considering natural numbers of the form, a^b, where a, b < 100,
    // what is the maximum digital sum?

    // 1.26.14
    // I have hit a dead end on this problem.  As of now I am unable
    // to think of an efficient solution.  The only thing I can think
    // of is to brute force the problem; to do the arithmetic using a 
    // big number library (such as GMP or MPIR, downloads available online).
    // the results would then be converted to string and the digit
    // sum computed.  However, GMP and MPIR are not well supported
    // on windows and would require ugly changes to visual studio.
    // One possibility would be to build on the mac side because
    // GMP is native to unix.  But this seems like a bit much in
    // lieu of a "real" solution.

    return 0;
    }

int SolveProblem62()
    {
    int nNumber=1;
    int nPermutations=5;
    int nCubedPerm=0;
    bool bSolved=false;
    while(!bSolved)
        {
        ++nNumber;
        //Find the number of digit permutations of nNumber^3
        //which are also cubed integers > nNumber nCubedPerm.

        nCubedPerm = nNumberCubedPermutations(nNumber);

        if(nCubedPerm==nPermutations-1)
            {
            bSolved=true;
            }
        if(nNumber>GND_MAXINT)
            {
            IOMaxIntExceeded();
            break;
            }
        }
    return nNumber;
    }

int SolveProblem51()
    {
    int nNumber=1;
    while(!IsSolutionToProblem51(nNumber))
        {
        if(nNumber>GND_MAXINT)
            {
            return 0;
            }
        ++nNumber;
        }
    return nNumber;
    }

int SolveProblem69()
    {
    int nAnswer=0,Index;
    double dMaxValue=0;

    for(Index=1;Index<1000001;++Index)
        {
        int nTotient=Totient(Index);

        //std::cout << Index << std::endl;

        double dValue=((double)Index)/((double)nTotient);
        if(dValue>dMaxValue)
            {
            dMaxValue=dValue;
            nAnswer=Index;
            }
        }
    return nAnswer;
    }

std::string get_file_contents()
    {
    std::FILE *pFile=std::fopen("c://Users//Gavin//Documents//Visual Studio 2008//Projects//Gavin's Project//Gavin's Project//sudoku.txt","rb");
    std::string contents;
    if(pFile)
        {
        std::fseek(pFile,0,SEEK_END);
        contents.resize(std::ftell(pFile));
        std::rewind(pFile);
        std::fread(&contents[0],1,contents.size(),pFile);
        std::fclose(pFile);
        }
    else
        {
        assert(UnderConstruction);
        }
    return contents;
    }

int SolveProblem79()
    {
    int nLogins[150]={3,1,9,
                      6,8,0,
                      1,8,0,
                      6,9,0,
                      1,2,9,
                      6,2,0,
                      7,6,2,
                      6,8,9,
                      7,6,2,
                      3,1,8,
                      3,6,8,
                      7,1,0,
                      7,2,0,
                      7,1,0,
                      6,2,9,
                      1,6,8,
                      1,6,0,
                      6,8,9,
                      7,1,6,
                      7,3,1,
                      7,3,6,
                      7,2,9,
                      3,1,6,
                      7,2,9,
                      7,2,9,
                      7,1,0,
                      7,6,9,
                      2,9,0,
                      7,1,9,
                      6,8,0,
                      3,1,8,
                      3,8,9,
                      1,6,2,
                      2,8,9,
                      1,6,2,
                      7,1,8,
                      7,2,9,
                      3,1,9,
                      7,9,0,
                      6,8,0,
                      8,9,0,
                      3,6,2,
                      3,1,9,
                      7,6,0,
                      3,1,6,
                      7,2,9,
                      3,8,0,
                      3,1,9,
                      7,2,8,
                      7,1,6};

    GND::Passcode ThePasscode(nLogins);
    int nAnswer=ThePasscode.Solve();
    return nAnswer;
    }

int SolveProblem94()
    {
    int nAnswer=0;

    GND::PythagoreanTriple Triple;

    bool bContinue=true;
    while(bContinue)
        {
        int nA=0,nB=0,nC=0;
        Triple.ComputeTriple(nA,nB,nC);

        // The complete triangle is a triangle
        // of interest if and only if either A or B
        // =(C+-1)/2 and C is odd.

        if(nC%2==1)
            {
            int nHighPoss=(nC+1)/2;
            int nLowPoss=(nC-1)/2;

            if(nA==nHighPoss/*||nB==nHighPoss*/)
                {
                nAnswer+=3*nC+1;

                std::cout << "C = " << nC << " A = " << nA << std::endl;
                }
            else if(nA==nLowPoss/*||nB==nLowPoss*/)
                {
                nAnswer+=3*nC-1;

                std::cout << "C = " << nC << " A = " << nA << std::endl;
                }
            }

        bContinue=++Triple;
        }

    return nAnswer;
    }

int SolveProblem96()
    {
    int nAnswer=0;

    std::string sData=get_file_contents();

    size_t nWhere=0;
    size_t Index;
    for(Index=0;Index<50;++Index)
        {
        // Skip the grid header.
        nWhere+=8;

        int aanGrid[9][9];
        size_t Index1,Index2;
        for(Index1=0;Index1<9;++Index1)
            {
            for(Index2=0;Index2<9;++Index2)
                {
                aanGrid[Index1][Index2]=sData[nWhere++]-48;
                }
            ++nWhere; // Returns.
            }

        GND::SudokuGrid TheGrid(aanGrid);
        if(!TheGrid.Solve())
            {
            assert(UnderConstruction);
            }
        nAnswer+=TheGrid.TopThree();
        }
    return nAnswer;
    }