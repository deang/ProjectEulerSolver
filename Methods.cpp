#include "stdafx.h"

#include <string>
#include <sstream>

#include "Classes.h"
#include "Functions.h"
#include "IO.h"

GND::StringInt::StringInt(std::string sInitialValue)
    {
    m_String = sInitialValue;
    }

GND::StringInt::StringInt(int nInitialValue)
    {
    std::stringstream into;
    into << nInitialValue;
    into >> m_String;
    }

GND::StringInt::~StringInt()
    {
    }

void GND::StringInt::Increment()
    {
    //For each character in m_String.
    int nRemainder = 1;
    for(int Index = int(m_String.size()) - 1; Index > -1; --Index)
        {
        if(nRemainder == 0)
            {
            break;
            }
        else
            {
            m_String[Index] += nRemainder;
            nRemainder = 0;
            if(m_String[Index] == 58)
                {
                m_String[Index] = 48;
                nRemainder = 1;
                if(Index == 0)
                    {
                    m_String.insert(0,"1");
                    nRemainder = 0;
                    }
                }
            }
        }
    }

void GND::StringInt::ToInt(int &nNumber) const
    {
    if(m_String.size() > 9)
        {
        //The number is too large.
        std::cout << "Warning: Answer too large!" << std::endl;
        nNumber = 0;
        }
    int nPowerOfTen = 1;
    nNumber = 0;
    for(int Index = int(m_String.size()) - 1; Index > -1; --Index)
        {
        int nDigit = m_String[Index] - 48; //Converting from ASCII to an int.
        nNumber += nDigit*nPowerOfTen;
        nPowerOfTen *= 10;
        }
    }

bool GND::StringInt::bSameDigits(std::string const &sOtherString) const
    {
    int NumberDigitsA[10] = {0,0,0,0,0,0,0,0,0,0};
    int NumberDigitsB[10] = {0,0,0,0,0,0,0,0,0,0};
    //Count the # of 1's, 2's etc in StringA
    for(size_t Index = 0; Index < m_String.size(); ++Index)
        {
        NumberDigitsA[m_String[Index] - 48] += 1;
        }
    //Count the # of 1's, 2's etc in StringB
    for(size_t Index = 0; Index < sOtherString.size(); ++Index)
        {
        NumberDigitsB[sOtherString[Index] - 48] += 1;
        }
    //Determine if StringA and StringB have the same
    //digits.
    bool bEquivalent = true;
    for(int Index = 0; Index < 10; ++Index)
        {
        if(NumberDigitsA[Index] != NumberDigitsB[Index])
            {
            bEquivalent = false;
            }
        }
    return bEquivalent;
    }

std::string GND::StringInt::StringMultiply(int nMultiplier) const
    {
    std::string sAnswer;
    //For each digit starting on the right.
    int nRemainder = 0;
    for(int Index = int(m_String.size()) - 1; Index > -1; --Index)
        {
        //Multiply that digit by nMultiplier.
        //-48 converts ASCII to int for 0-9.
        int nProduct = nMultiplier*(m_String[Index]-48);
        nProduct += nRemainder;
        nRemainder = 0;
        if(nProduct < 10)
            {
            std::string sNewDigit = "";
            sNewDigit = nProduct+48;
            sAnswer.insert(0,sNewDigit);
            }
        else
            {
            //Take the ones digit of nProduct and 
            //push it onto sAnswer.
            //Store the other digit as nRemainder.
            std::string sProduct;
            std::ostringstream convert;
            convert << nProduct;
            sProduct = convert.str();
    
            nRemainder = sProduct[0] - 48;
            std::string sNewDigit = "";
            sNewDigit = sProduct[1];
            sAnswer.insert(0,sNewDigit);
            }
        }
    return sAnswer;
    }

#define GND_ARRAY_SIZE 100

//This function multiplies an integer represented by m_String
//by sMultiplier and returns a string result.
std::string GND::StringInt::StringMultiply(std::string sMultiplier) const
    {
    int IntArray[GND_ARRAY_SIZE][GND_ARRAY_SIZE];
    for(int Index1 = 0; Index1 < GND_ARRAY_SIZE; ++Index1)
        {
        for(int Index2 = 0; Index2 < GND_ARRAY_SIZE; ++Index2)
            {
            IntArray[Index1][Index2] = 0;
            }
        }
    int nOffset = 0;
    int nRow = 0;
    //for(size_t Index1 = 0; Index1 < sMultiplier.size();++Index1)
    for(size_t Index1 = sMultiplier.size(); Index1 >= 1;--Index1)
        {
        int nMultDigit = sMultiplier[Index1-1] - 48;
        int nInnerOffset=0;
        int nRemainder=0;
        //for(size_t Index2 = 0; Index2 < m_String.size();++Index2)
        for(size_t Index2 = m_String.size(); Index2 >= 1;--Index2)
            {
            int nTopDigit = m_String[Index2-1] - 48;
            int nFirstDigit=0;
            MuliplierTool(nMultDigit*nTopDigit,nRemainder,nFirstDigit);
            IntArray[nRow++][nInnerOffset+nOffset]=nFirstDigit;
            nInnerOffset++;
            }
        IntArray[nRow++][nInnerOffset+nOffset]=nRemainder;
        ++nOffset;
        }
    //IntArray[0][nRow++]=nRemainder;

    //Sum each column in the 2DArray.
    std::string sResult="";
    int nRemainder = 0;
    int nMaxCol = sMultiplier.size()+ m_String.size();
    for(int Index1 = 0; Index1 < nMaxCol; ++Index1)
        {
        int nColumnSum = 0;
        for(int Index2 = 0; Index2 < 100; ++Index2)
            {
            nColumnSum += IntArray[Index2][Index1];
            }
        int nFirstDigit = 0;
        MuliplierTool(nColumnSum,nRemainder,nFirstDigit);
        std::stringstream into;
        into << nFirstDigit;
        std::string sFirstDigit;
        into >> sFirstDigit;
        sResult.insert(0,sFirstDigit);
        }
    if(nRemainder!=0)
        {
        std::stringstream into;
        into << nRemainder;
        std::string sRemainder;
        into >> sRemainder;
        sResult.insert(0,sRemainder);
        }
    if(sResult[0]==48)
        {
        sResult=sResult.substr();
        }
    sResult=StringRemoveLeadingZeros(sResult);
    return sResult;
    }

bool GND::StringInt::StringIntPandigital(GND::StringInt const &StringIntA, 
                                         GND::StringInt const &StringIntB) const
    {
    int NumberDigits[10] = {0,0,0,0,0,0,0,0,0,0};
    ////Count the # of 1's, 2's etc in this StringInt.
    for(size_t Index = 0; Index < m_String.size(); ++Index)
        {
        NumberDigits[m_String[Index] - 48] += 1;
        }
    //Count the # of 1's, 2's etc in StringIntA
    std::string sString = StringIntA.GetString();
    for(size_t Index = 0; Index < sString.size(); ++Index)
        {
        NumberDigits[sString[Index] - 48] += 1;
        }
    //Count the # of 1's, 2's etc in StringIntB
    sString = StringIntB.GetString();
    for(size_t Index = 0; Index < sString.size(); ++Index)
        {
        NumberDigits[sString[Index] - 48] += 1;
        }
    //Determine if they are pandigital 1-9.
    bool bPandigital = true;
    for(int Index = 1; Index < 10; ++Index)
        {
        if(NumberDigits[Index] != 1)
            {
            bPandigital = false;
            }
        }
    return bPandigital;
    }

bool GND::StringInt::bPermutedCubes(GND::StringInt const &siOther) const
    {
    //Calculate the cubed strings.
    std::string sThisCubed=CubedString(this->GetString());
    std::string sOtherCubed=CubedString(siOther.GetString());

    //See if they have the same digits.
    GND::StringInt siTemp(sThisCubed);
    return siTemp.bSameDigits(sOtherCubed);
    }

std::string GND::StringInt::power(int const nExponent) const
    {
    GND::StringInt siTemp(this->GetString());
    for(int Index = 0; Index < nExponent-1; ++Index)
        {
        siTemp.SetString(siTemp.StringMultiply(this->GetString()));
        }
    return siTemp.GetString();
    }

int GND::StringInt::nNumberOfDigits() const
    {
    return m_String.size();
    }

void GND::StringInt::IndicesOfMatchingDigits(int        const &nNumber,
                                             std::set<size_t> &sIndices) const
    {
    if(nNumber<0||nNumber>9)
        {
        return;
        }

    int nASCIINumber=nNumber+48;

    size_t Index;
    for(Index=0;Index<m_String.size();++Index)
        {
        int nASCIIDigit=m_String[Index];
        if(nASCIIDigit==nASCIINumber)
            {
            sIndices.insert(Index);
            }
        }
    }

int GND::StringInt::ReplacedDigits(int              const &nNumber,
                                   std::set<size_t> const &sIndices) const
    {
    if(nNumber<0||nNumber>9)
        {
        return 0;
        }

    int nASCIINumber=nNumber+48;
    GND::StringInt siTemp(m_String);

    std::set<size_t>::const_iterator iter=sIndices.begin();
    while(iter!=sIndices.end())
        {
        size_t Index=(*iter);
        siTemp.ReplaceDigit(nNumber,Index);

        ++iter;
        }

    int nAnswer;
    siTemp.ToInt(nAnswer);
    return nAnswer;
    }

void GND::StringInt::ReplaceDigit(int const &nNumber,size_t const &Index)
    {
    if(nNumber<0||nNumber>9)
        {
        return;
        }
    m_String[Index]=nNumber+48;
    }

int GND::StringInt::DigitSum() const
    {
    int nAnswer=0;
    size_t Index;
    for(Index=0;Index<m_String.size();++Index)
        {
        int nDigit=m_String[Index]-48;
        nAnswer+=nDigit;
        }
    return nAnswer;
    }

void GND::StringInt::SetString(std::string const &sNew)
    {
    m_String = sNew;
    }

std::string GND::StringInt::GetString() const 
    {
    return m_String;
    }

//////////////////////////////////////////////////////////////////////////
//
//
//  GND::SudokuGrid methods.
//
//
//////////////////////////////////////////////////////////////////////////

GND::SudokuGrid::SudokuGrid(int aanGrid[9][9])
    {
    //m_aanGrid=aanGrid;
    std::copy(&aanGrid[0][0],&aanGrid[0][0]+81,&m_aanGrid[0][0]);
    ResetCache();
    }

GND::SudokuGrid::SudokuGrid(int aanGrid[9][9],bool aaabPossibilities[9][9][9])
    {
    //m_aanGrid=aanGrid;
    std::copy(&aanGrid[0][0],&aanGrid[0][0]+81,&m_aanGrid[0][0]);
    //m_aaabPossibilities=aaabPossibilities;
    std::copy(&aaabPossibilities[0][0][0],
              &aaabPossibilities[0][0][0]+729/*9^3*/,
              &m_aaabPossibilities[0][0][0]);
    }

bool GND::SudokuGrid::Solve()
    {
    if(DeterministicSolve())
        {
        return true;
        }
    else
        {
        // Find the grid position with the minimal number of possibilities.

        int nXMin=0;
        int nYMin=0;
        int nMinPoss=10;

        int nX,nY,nZ;
        for(nX=0;nX<9;++nX)
            {
            for(nY=0;nY<9;++nY)
                {
                int nCount=0;
                for(nZ=0;nZ<9;++nZ)
                    {
                    if(m_aaabPossibilities[nX][nY][nZ])
                        {
                        ++nCount;
                        }
                    }
                if(nCount<nMinPoss&&nCount!=0)
                    {
                    nMinPoss=nCount;
                    nXMin=nX;
                    nYMin=nY;
                    }
                }
            }

        for(nZ=0;nZ<9;++nZ)
            {
            if(m_aaabPossibilities[nXMin][nYMin][nZ])
                {
                // Narrow it down and try again.

                bool aaabPossibilities[9][9][9];
                //aaabPossibilities=m_aaabPossibilities;
                std::copy(&m_aaabPossibilities[0][0][0],
                          &m_aaabPossibilities[0][0][0]+729/*9^3*/,
                          &aaabPossibilities[0][0][0]);


                int nZCoord;
                for(nZCoord=0;nZCoord<9;++nZCoord)
                    {
                    aaabPossibilities[nXMin][nYMin][nZCoord]=false;
                    }
                aaabPossibilities[nXMin][nYMin][nZ]=true;

                SudokuGrid SecondaryGrid(m_aanGrid,aaabPossibilities);

                if(SecondaryGrid.Solve())
                    {
                    // We're done.
                    // Copy the data and return.

                    //m_aanGrid=SecondaryGrid.m_aanGrid;
                    std::copy(&SecondaryGrid.m_aanGrid[0][0],
                        &SecondaryGrid.m_aanGrid[0][0]+81,
                        &m_aanGrid[0][0]);

                    //m_aaabPossibilities=SecondaryGrid.m_aaabPossibilities;
                    std::copy(&SecondaryGrid.m_aaabPossibilities[0][0][0],
                        &SecondaryGrid.m_aaabPossibilities[0][0][0]+729/*9^3*/,
                        &m_aaabPossibilities[0][0][0]);

                    return true;
                    }
                }
            }
        return false;
        }
    }

bool GND::SudokuGrid::DeterministicSolve()
    {
    bool bSuccess=true;
    while(bSuccess)
        {
        bSuccess=Increment();
        }
    bool bAnswer=true;
    if(!IsSolved())
        {
        bAnswer=false;
        }
    return bAnswer;
    }

bool GND::SudokuGrid::Increment()
    {
    int nAnswer,nXCoordinate,nYCoordinate;
    if(FindOnlyChoice(nAnswer,nXCoordinate,nYCoordinate))
        {
        m_aanGrid[nXCoordinate][nYCoordinate]=nAnswer;
        ResetCache(nXCoordinate,nYCoordinate);
        return true;
        }
    else if(FindTwoOutOfThree(nAnswer,nXCoordinate,nYCoordinate))
        {
        m_aanGrid[nXCoordinate][nYCoordinate]=nAnswer;
        ResetCache(nXCoordinate,nYCoordinate);
        return true;
        }
    return false;
    }

bool GND::SudokuGrid::FindTwoOutOfThree(int &nAnswer,int &nXCoordinate,int &nYCoordinate) const
    {
    nAnswer=0;

    int nX,nY,nZ;
    for(nX=0;nX<9;++nX)
        {
        for(nY=0;nY<9;++nY)
            {
            int nValue=m_aanGrid[nX][nY];
            if(nValue==0)
                {
                for(nZ=0;nZ<9;++nZ)
                    {
                    if(m_aaabPossibilities[nX][nY][nZ])
                        {
                        bool bAnswer=true;

                        // Look at the rows and columns.
                        int Index;
                        for(Index=0;Index<9;++Index)
                            {
                            if(Index!=nX&&m_aaabPossibilities[Index][nY][nZ])
                                {
                                bAnswer=false;
                                break;
                                }
                            if(Index!=nY&&m_aaabPossibilities[nX][Index][nZ])
                                {
                                bAnswer=false;
                                break;
                                }
                            }

                        // Look at the region.
                        if(bAnswer)
                            {
                            if(nX<3)          // X=0,1,2
                                {
                                if(nY<3)      // Y=0,1,2
                                    {
                                    if(m_aaabPossibilities[0][0][nZ]||
                                       m_aaabPossibilities[0][1][nZ]||
                                       m_aaabPossibilities[0][2][nZ]||
                                       m_aaabPossibilities[1][0][nZ]||
                                       m_aaabPossibilities[1][1][nZ]||
                                       m_aaabPossibilities[1][2][nZ]||
                                       m_aaabPossibilities[2][0][nZ]||
                                       m_aaabPossibilities[2][1][nZ]||
                                       m_aaabPossibilities[2][2][nZ])
                                        {
                                        bAnswer=false;
                                        }
                                    }
                                else if(nY<6) // Y=3,4,5
                                    {
                                    if(m_aaabPossibilities[0][3][nZ]||
                                       m_aaabPossibilities[0][4][nZ]||
                                       m_aaabPossibilities[0][5][nZ]||
                                       m_aaabPossibilities[1][3][nZ]||
                                       m_aaabPossibilities[1][4][nZ]||
                                       m_aaabPossibilities[1][5][nZ]||
                                       m_aaabPossibilities[2][3][nZ]||
                                       m_aaabPossibilities[2][4][nZ]||
                                       m_aaabPossibilities[2][5][nZ])
                                        {
                                        bAnswer=false;
                                        }
                                    }
                                else          // Y=6,7,8
                                    {
                                    if(m_aaabPossibilities[0][6][nZ]||
                                       m_aaabPossibilities[0][7][nZ]||
                                       m_aaabPossibilities[0][8][nZ]||
                                       m_aaabPossibilities[1][6][nZ]||
                                       m_aaabPossibilities[1][7][nZ]||
                                       m_aaabPossibilities[1][8][nZ]||
                                       m_aaabPossibilities[2][6][nZ]||
                                       m_aaabPossibilities[2][7][nZ]||
                                       m_aaabPossibilities[2][8][nZ])
                                        {
                                        bAnswer=false;
                                        }
                                    }
                                }
                            else if(nX<6)     // X=3,4,5
                                {
                                if(nY<3)      // Y=0,1,2
                                    {
                                    if(m_aaabPossibilities[3][0][nZ]||
                                       m_aaabPossibilities[3][1][nZ]||
                                       m_aaabPossibilities[3][2][nZ]||
                                       m_aaabPossibilities[4][0][nZ]||
                                       m_aaabPossibilities[4][1][nZ]||
                                       m_aaabPossibilities[4][2][nZ]||
                                       m_aaabPossibilities[5][0][nZ]||
                                       m_aaabPossibilities[5][1][nZ]||
                                       m_aaabPossibilities[5][2][nZ])
                                        {
                                        bAnswer=false;
                                        }
                                    }
                                else if(nY<6) // Y=3,4,5
                                    {
                                    if(m_aaabPossibilities[3][3][nZ]||
                                       m_aaabPossibilities[3][4][nZ]||
                                       m_aaabPossibilities[3][5][nZ]||
                                       m_aaabPossibilities[4][3][nZ]||
                                       m_aaabPossibilities[4][4][nZ]||
                                       m_aaabPossibilities[4][5][nZ]||
                                       m_aaabPossibilities[5][3][nZ]||
                                       m_aaabPossibilities[5][4][nZ]||
                                       m_aaabPossibilities[5][5][nZ])
                                        {
                                        bAnswer=false;
                                        }
                                    }
                                else          // Y=6,7,8
                                    {
                                    if(m_aaabPossibilities[3][6][nZ]||
                                       m_aaabPossibilities[3][7][nZ]||
                                       m_aaabPossibilities[3][8][nZ]||
                                       m_aaabPossibilities[4][6][nZ]||
                                       m_aaabPossibilities[4][7][nZ]||
                                       m_aaabPossibilities[4][8][nZ]||
                                       m_aaabPossibilities[5][6][nZ]||
                                       m_aaabPossibilities[5][7][nZ]||
                                       m_aaabPossibilities[5][8][nZ])
                                        {
                                        bAnswer=false;
                                        }
                                    }
                                }
                            else              // X=6,7,8
                                {
                                if(nY<3)      // Y=0,1,2
                                    {
                                    if(m_aaabPossibilities[6][0][nZ]||
                                       m_aaabPossibilities[6][1][nZ]||
                                       m_aaabPossibilities[6][2][nZ]||
                                       m_aaabPossibilities[7][0][nZ]||
                                       m_aaabPossibilities[7][1][nZ]||
                                       m_aaabPossibilities[7][2][nZ]||
                                       m_aaabPossibilities[8][0][nZ]||
                                       m_aaabPossibilities[8][1][nZ]||
                                       m_aaabPossibilities[8][2][nZ])
                                        {
                                        bAnswer=false;
                                        }
                                    }
                                else if(nY<6) // Y=3,4,5
                                    {
                                    if(m_aaabPossibilities[6][3][nZ]||
                                       m_aaabPossibilities[6][4][nZ]||
                                       m_aaabPossibilities[6][5][nZ]||
                                       m_aaabPossibilities[7][3][nZ]||
                                       m_aaabPossibilities[7][4][nZ]||
                                       m_aaabPossibilities[7][5][nZ]||
                                       m_aaabPossibilities[8][3][nZ]||
                                       m_aaabPossibilities[8][4][nZ]||
                                       m_aaabPossibilities[8][5][nZ])
                                        {
                                        bAnswer=false;
                                        }
                                    }
                                else          // Y=6,7,8
                                    {
                                    if(m_aaabPossibilities[6][6][nZ]||
                                       m_aaabPossibilities[6][7][nZ]||
                                       m_aaabPossibilities[6][8][nZ]||
                                       m_aaabPossibilities[7][6][nZ]||
                                       m_aaabPossibilities[7][7][nZ]||
                                       m_aaabPossibilities[7][8][nZ]||
                                       m_aaabPossibilities[8][6][nZ]||
                                       m_aaabPossibilities[8][7][nZ]||
                                       m_aaabPossibilities[8][8][nZ])
                                        {
                                        bAnswer=false;
                                        }
                                    }
                                }
                            }

                        if(bAnswer)
                            {
                            // We're done.
                            // Record the results and return.
                            nAnswer=nZ+1;
                            nXCoordinate=nX;
                            nYCoordinate=nY;

                            return true;
                            }
                        }
                    }
                }
            }
        }
    return false;
    }

bool GND::SudokuGrid::FindOnlyChoice(int &nAnswer,int &nXCoordinate,int &nYCoordinate) const
    {
    bool bAnswer=false;

    int nX,nY,nZ;
    for(nX=0;nX<9;++nX)
        {
        for(nY=0;nY<9;++nY)
            {
            if(m_aanGrid[nX][nY]==0) // Only check unsolved grid points.
                {
                int nCount=0,nAnsTemp=0;
                for(nZ=0;nZ<9;++nZ)
                    {
                    if(m_aaabPossibilities[nX][nY][nZ])
                        {
                        ++nCount;
                        nAnsTemp=nZ+1;
                        }
                    }
                if(nCount==1)
                    {
                    // We're done.
                    // Record the results and return.
                    nAnswer=nAnsTemp;
                    nXCoordinate=nX;
                    nYCoordinate=nY;
                    return true;
                    }
                }
            }
        }
    return false;
    }

bool GND::SudokuGrid::IsSolved() const
    {
    int nIndex;

    // Check the rows.
    int nX,nY;
    for(nX=0;nX<9;++nX)
        {
        bool abDigits[9]={false,false,false,false,false,false,false,false,false};
        for(nY=0;nY<9;++nY)
            {
            int nValue=m_aanGrid[nX][nY];
            if(nValue<1)
                {
                return false;
                }
            abDigits[nValue-1]=true;
            }

        for(nIndex=0;nIndex<9;++nIndex)
            {
            if(!abDigits[nIndex])
                {
                return false;
                }
            }
        }

    // Check the columns.
    for(nY=0;nY<9;++nY)
        {
        bool abDigits[9]={false,false,false,false,false,false,false,false,false};
        for(nX=0;nX<9;++nX)
            {
            int nValue=m_aanGrid[nX][nY];
            abDigits[nValue-1]=true;
            }

        for(nIndex=0;nIndex<9;++nIndex)
            {
            if(!abDigits[nIndex])
                {
                return false;
                }
            }
        }

    // Check the regions.
    bool abDigits1[9]={false,false,false,false,false,false,false,false,false};
    abDigits1[m_aanGrid[0][0]-1]=true;
    abDigits1[m_aanGrid[0][1]-1]=true;
    abDigits1[m_aanGrid[0][2]-1]=true;
    abDigits1[m_aanGrid[1][0]-1]=true;
    abDigits1[m_aanGrid[1][1]-1]=true;
    abDigits1[m_aanGrid[1][2]-1]=true;
    abDigits1[m_aanGrid[2][0]-1]=true;
    abDigits1[m_aanGrid[2][1]-1]=true;
    abDigits1[m_aanGrid[2][2]-1]=true;

    for(nIndex=0;nIndex<9;++nIndex)
        {
        if(!abDigits1[nIndex])
            {
            return false;
            }
        }

    bool abDigits2[9]={false,false,false,false,false,false,false,false,false};
    abDigits2[m_aanGrid[0][3]-1]=true;
    abDigits2[m_aanGrid[0][4]-1]=true;
    abDigits2[m_aanGrid[0][5]-1]=true;
    abDigits2[m_aanGrid[1][3]-1]=true;
    abDigits2[m_aanGrid[1][4]-1]=true;
    abDigits2[m_aanGrid[1][5]-1]=true;
    abDigits2[m_aanGrid[2][3]-1]=true;
    abDigits2[m_aanGrid[2][4]-1]=true;
    abDigits2[m_aanGrid[2][5]-1]=true;

    for(nIndex=0;nIndex<9;++nIndex)
        {
        if(!abDigits2[nIndex])
            {
            return false;
            }
        }

    bool abDigits3[9]={false,false,false,false,false,false,false,false,false};
    abDigits3[m_aanGrid[0][6]-1]=true;
    abDigits3[m_aanGrid[0][7]-1]=true;
    abDigits3[m_aanGrid[0][8]-1]=true;
    abDigits3[m_aanGrid[1][6]-1]=true;
    abDigits3[m_aanGrid[1][7]-1]=true;
    abDigits3[m_aanGrid[1][8]-1]=true;
    abDigits3[m_aanGrid[2][6]-1]=true;
    abDigits3[m_aanGrid[2][7]-1]=true;
    abDigits3[m_aanGrid[2][8]-1]=true;

    for(nIndex=0;nIndex<9;++nIndex)
        {
        if(!abDigits3[nIndex])
            {
            return false;
            }
        }

    bool abDigits4[9]={false,false,false,false,false,false,false,false,false};
    abDigits4[m_aanGrid[3][0]-1]=true;
    abDigits4[m_aanGrid[3][1]-1]=true;
    abDigits4[m_aanGrid[3][2]-1]=true;
    abDigits4[m_aanGrid[4][0]-1]=true;
    abDigits4[m_aanGrid[4][1]-1]=true;
    abDigits4[m_aanGrid[4][2]-1]=true;
    abDigits4[m_aanGrid[5][0]-1]=true;
    abDigits4[m_aanGrid[5][1]-1]=true;
    abDigits4[m_aanGrid[5][2]-1]=true;

    for(nIndex=0;nIndex<9;++nIndex)
        {
        if(!abDigits4[nIndex])
            {
            return false;
            }
        }

    bool abDigits5[9]={false,false,false,false,false,false,false,false,false};
    abDigits5[m_aanGrid[3][3]-1]=true;
    abDigits5[m_aanGrid[3][4]-1]=true;
    abDigits5[m_aanGrid[3][5]-1]=true;
    abDigits5[m_aanGrid[4][3]-1]=true;
    abDigits5[m_aanGrid[4][4]-1]=true;
    abDigits5[m_aanGrid[4][5]-1]=true;
    abDigits5[m_aanGrid[5][3]-1]=true;
    abDigits5[m_aanGrid[5][4]-1]=true;
    abDigits5[m_aanGrid[5][5]-1]=true;

    for(nIndex=0;nIndex<9;++nIndex)
        {
        if(!abDigits5[nIndex])
            {
            return false;
            }
        }

    bool abDigits6[9]={false,false,false,false,false,false,false,false,false};
    abDigits6[m_aanGrid[3][6]-1]=true;
    abDigits6[m_aanGrid[3][7]-1]=true;
    abDigits6[m_aanGrid[3][8]-1]=true;
    abDigits6[m_aanGrid[4][6]-1]=true;
    abDigits6[m_aanGrid[4][7]-1]=true;
    abDigits6[m_aanGrid[4][8]-1]=true;
    abDigits6[m_aanGrid[5][6]-1]=true;
    abDigits6[m_aanGrid[5][7]-1]=true;
    abDigits6[m_aanGrid[5][8]-1]=true;

    for(nIndex=0;nIndex<9;++nIndex)
        {
        if(!abDigits6[nIndex])
            {
            return false;
            }
        }

    bool abDigits7[9]={false,false,false,false,false,false,false,false,false};
    abDigits7[m_aanGrid[6][0]-1]=true;
    abDigits7[m_aanGrid[6][1]-1]=true;
    abDigits7[m_aanGrid[6][2]-1]=true;
    abDigits7[m_aanGrid[7][0]-1]=true;
    abDigits7[m_aanGrid[7][1]-1]=true;
    abDigits7[m_aanGrid[7][2]-1]=true;
    abDigits7[m_aanGrid[8][0]-1]=true;
    abDigits7[m_aanGrid[8][1]-1]=true;
    abDigits7[m_aanGrid[8][2]-1]=true;

    for(nIndex=0;nIndex<9;++nIndex)
        {
        if(!abDigits7[nIndex])
            {
            return false;
            }
        }

    bool abDigits8[9]={false,false,false,false,false,false,false,false,false};
    abDigits8[m_aanGrid[6][3]-1]=true;
    abDigits8[m_aanGrid[6][4]-1]=true;
    abDigits8[m_aanGrid[6][5]-1]=true;
    abDigits8[m_aanGrid[7][3]-1]=true;
    abDigits8[m_aanGrid[7][4]-1]=true;
    abDigits8[m_aanGrid[7][5]-1]=true;
    abDigits8[m_aanGrid[8][3]-1]=true;
    abDigits8[m_aanGrid[8][4]-1]=true;
    abDigits8[m_aanGrid[8][5]-1]=true;

    for(nIndex=0;nIndex<9;++nIndex)
        {
        if(!abDigits8[nIndex])
            {
            return false;
            }
        }

    bool abDigits9[9]={false,false,false,false,false,false,false,false,false};
    abDigits9[m_aanGrid[6][6]-1]=true;
    abDigits9[m_aanGrid[6][7]-1]=true;
    abDigits9[m_aanGrid[6][8]-1]=true;
    abDigits9[m_aanGrid[7][6]-1]=true;
    abDigits9[m_aanGrid[7][7]-1]=true;
    abDigits9[m_aanGrid[7][8]-1]=true;
    abDigits9[m_aanGrid[8][6]-1]=true;
    abDigits9[m_aanGrid[8][7]-1]=true;
    abDigits9[m_aanGrid[8][8]-1]=true;

    for(nIndex=0;nIndex<9;++nIndex)
        {
        if(!abDigits9[nIndex])
            {
            return false;
            }
        }

    return true;
    }

void GND::SudokuGrid::Print() const
    {
    std::cout << m_aanGrid[0][0] << " " << m_aanGrid[0][1] << " " << m_aanGrid[0][2];
    std::cout << "   "; 
    std::cout << m_aanGrid[0][3] << " " << m_aanGrid[0][4] << " " << m_aanGrid[0][5];
    std::cout << "   "; 
    std::cout << m_aanGrid[0][6] << " " << m_aanGrid[0][7] << " " << m_aanGrid[0][8];
    std::cout << std::endl;


    std::cout << m_aanGrid[1][0] << " " << m_aanGrid[1][1] << " " << m_aanGrid[1][2];
    std::cout << "   "; 
    std::cout << m_aanGrid[1][3] << " " << m_aanGrid[1][4] << " " << m_aanGrid[1][5];
    std::cout << "   "; 
    std::cout << m_aanGrid[1][6] << " " << m_aanGrid[1][7] << " " << m_aanGrid[1][8];
    std::cout << std::endl;



    std::cout << m_aanGrid[2][0] << " " << m_aanGrid[2][1] << " " << m_aanGrid[2][2];
    std::cout << "   "; 
    std::cout << m_aanGrid[2][3] << " " << m_aanGrid[2][4] << " " << m_aanGrid[2][5];
    std::cout << "   "; 
    std::cout << m_aanGrid[2][6] << " " << m_aanGrid[2][7] << " " << m_aanGrid[2][8];
    std::cout << std::endl;
    std::cout << std::endl;



    std::cout << m_aanGrid[3][0] << " " << m_aanGrid[3][1] << " " << m_aanGrid[3][2];
    std::cout << "   "; 
    std::cout << m_aanGrid[3][3] << " " << m_aanGrid[3][4] << " " << m_aanGrid[3][5];
    std::cout << "   "; 
    std::cout << m_aanGrid[3][6] << " " << m_aanGrid[3][7] << " " << m_aanGrid[3][8];
    std::cout << std::endl;



    std::cout << m_aanGrid[4][0] << " " << m_aanGrid[4][1] << " " << m_aanGrid[4][2];
    std::cout << "   "; 
    std::cout << m_aanGrid[4][3] << " " << m_aanGrid[4][4] << " " << m_aanGrid[4][5];
    std::cout << "   "; 
    std::cout << m_aanGrid[4][6] << " " << m_aanGrid[4][7] << " " << m_aanGrid[4][8];
    std::cout << std::endl;



    std::cout << m_aanGrid[5][0] << " " << m_aanGrid[5][1] << " " << m_aanGrid[5][2];
    std::cout << "   "; 
    std::cout << m_aanGrid[5][3] << " " << m_aanGrid[5][4] << " " << m_aanGrid[5][5];
    std::cout << "   "; 
    std::cout << m_aanGrid[5][6] << " " << m_aanGrid[5][7] << " " << m_aanGrid[5][8];
    std::cout << std::endl;
    std::cout << std::endl;



    std::cout << m_aanGrid[6][0] << " " << m_aanGrid[6][1] << " " << m_aanGrid[6][2];
    std::cout << "   "; 
    std::cout << m_aanGrid[6][3] << " " << m_aanGrid[6][4] << " " << m_aanGrid[6][5];
    std::cout << "   "; 
    std::cout << m_aanGrid[6][6] << " " << m_aanGrid[6][7] << " " << m_aanGrid[6][8];
    std::cout << std::endl;



    std::cout << m_aanGrid[7][0] << " " << m_aanGrid[7][1] << " " << m_aanGrid[7][2];
    std::cout << "   "; 
    std::cout << m_aanGrid[7][3] << " " << m_aanGrid[7][4] << " " << m_aanGrid[7][5];
    std::cout << "   "; 
    std::cout << m_aanGrid[7][6] << " " << m_aanGrid[7][7] << " " << m_aanGrid[7][8];
    std::cout << std::endl;



    std::cout << m_aanGrid[8][0] << " " << m_aanGrid[8][1] << " " << m_aanGrid[8][2];
    std::cout << "   "; 
    std::cout << m_aanGrid[8][3] << " " << m_aanGrid[8][4] << " " << m_aanGrid[8][5];
    std::cout << "   "; 
    std::cout << m_aanGrid[8][6] << " " << m_aanGrid[8][7] << " " << m_aanGrid[8][8];
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    }

void GND::SudokuGrid::ResetCache() const
    {
    // Very brute force, but there shouldn't be many
    // blind cache resets.

    int nX,nY,nZ;
    for(nX=0;nX<9;++nX)
        {
        for(nY=0;nY<9;++nY)
            {
            for(nZ=0;nZ<9;++nZ)
                {
                m_aaabPossibilities[nX][nY][nZ]=true;
                }
            }
        }

    for(nX=0;nX<9;++nX)
        {
        for(nY=0;nY<9;++nY)
            {
            ResetCache(nX,nY);
            }
        }
    }

void GND::SudokuGrid::ResetCache(int nXCoordinate, int nYCoordinate) const
    {
    // Find the value nValue in the grid.
    int nValue=m_aanGrid[nXCoordinate][nYCoordinate];

    if(nValue>0) // Only reset the cache for known values.
        {
        // nValue corresponds to a Z index of nValue-1.
        int nZIndex=nValue-1;

        // Set all possibilities at this position to false.
        int nCoord;
        for(nCoord=0;nCoord<9;++nCoord)
            {
            m_aaabPossibilities[nXCoordinate][nYCoordinate][nCoord]=false;
            }

        // Set positions in the same row to false.
        for(nCoord=0;nCoord<9;++nCoord)
            {
            if(nCoord!=nXCoordinate)
                {
                m_aaabPossibilities[nCoord][nYCoordinate][nZIndex]=false;
                }
            }

        // Set positions in the same column to false.
        for(nCoord=0;nCoord<9;++nCoord)
            {
            if(nCoord!=nYCoordinate)
                {
                m_aaabPossibilities[nXCoordinate][nCoord][nZIndex]=false;
                }
            } 

        // Set positions in the same region to false.

        //////////////////////////////////////////////////////////////////////////
        //
        // How to quickly identify the region?
        // Note: nArray[x][y] is really just nArray[x*y] so there is
        // potentially extra multiplication going on...
        //
        //////////////////////////////////////////////////////////////////////////

        if(nXCoordinate<3)          // X=0,1,2
            {
            if(nYCoordinate<3)      // Y=0,1,2
                {
                m_aaabPossibilities[0][0][nZIndex]=false;
                m_aaabPossibilities[0][1][nZIndex]=false;
                m_aaabPossibilities[0][2][nZIndex]=false;
                m_aaabPossibilities[1][0][nZIndex]=false;
                m_aaabPossibilities[1][1][nZIndex]=false;
                m_aaabPossibilities[1][2][nZIndex]=false;
                m_aaabPossibilities[2][0][nZIndex]=false;
                m_aaabPossibilities[2][1][nZIndex]=false;
                m_aaabPossibilities[2][2][nZIndex]=false;
                }
            else if(nYCoordinate<6) // Y=3,4,5
                {
                m_aaabPossibilities[0][3][nZIndex]=false;
                m_aaabPossibilities[0][4][nZIndex]=false;
                m_aaabPossibilities[0][5][nZIndex]=false;
                m_aaabPossibilities[1][3][nZIndex]=false;
                m_aaabPossibilities[1][4][nZIndex]=false;
                m_aaabPossibilities[1][5][nZIndex]=false;
                m_aaabPossibilities[2][3][nZIndex]=false;
                m_aaabPossibilities[2][4][nZIndex]=false;
                m_aaabPossibilities[2][5][nZIndex]=false;
                }
            else                    // Y=6,7,8
                {
                m_aaabPossibilities[0][6][nZIndex]=false;
                m_aaabPossibilities[0][7][nZIndex]=false;
                m_aaabPossibilities[0][8][nZIndex]=false;
                m_aaabPossibilities[1][6][nZIndex]=false;
                m_aaabPossibilities[1][7][nZIndex]=false;
                m_aaabPossibilities[1][8][nZIndex]=false;
                m_aaabPossibilities[2][6][nZIndex]=false;
                m_aaabPossibilities[2][7][nZIndex]=false;
                m_aaabPossibilities[2][8][nZIndex]=false;
                }
            }
        else if(nXCoordinate<6)     // X=3,4,5
            {
            if(nYCoordinate<3)      // Y=0,1,2
                {
                m_aaabPossibilities[3][0][nZIndex]=false;
                m_aaabPossibilities[3][1][nZIndex]=false;
                m_aaabPossibilities[3][2][nZIndex]=false;
                m_aaabPossibilities[4][0][nZIndex]=false;
                m_aaabPossibilities[4][1][nZIndex]=false;
                m_aaabPossibilities[4][2][nZIndex]=false;
                m_aaabPossibilities[5][0][nZIndex]=false;
                m_aaabPossibilities[5][1][nZIndex]=false;
                m_aaabPossibilities[5][2][nZIndex]=false;
                }
            else if(nYCoordinate<6) // Y=3,4,5
                {
                m_aaabPossibilities[3][3][nZIndex]=false;
                m_aaabPossibilities[3][4][nZIndex]=false;
                m_aaabPossibilities[3][5][nZIndex]=false;
                m_aaabPossibilities[4][3][nZIndex]=false;
                m_aaabPossibilities[4][4][nZIndex]=false;
                m_aaabPossibilities[4][5][nZIndex]=false;
                m_aaabPossibilities[5][3][nZIndex]=false;
                m_aaabPossibilities[5][4][nZIndex]=false;
                m_aaabPossibilities[5][5][nZIndex]=false;
                }
            else                    // Y=6,7,8
                {
                m_aaabPossibilities[3][6][nZIndex]=false;
                m_aaabPossibilities[3][7][nZIndex]=false;
                m_aaabPossibilities[3][8][nZIndex]=false;
                m_aaabPossibilities[4][6][nZIndex]=false;
                m_aaabPossibilities[4][7][nZIndex]=false;
                m_aaabPossibilities[4][8][nZIndex]=false;
                m_aaabPossibilities[5][6][nZIndex]=false;
                m_aaabPossibilities[5][7][nZIndex]=false;
                m_aaabPossibilities[5][8][nZIndex]=false;
                }
            }
        else                        // X=6,7,8
            {
            if(nYCoordinate<3)      // Y=0,1,2
                {
                m_aaabPossibilities[6][0][nZIndex]=false;
                m_aaabPossibilities[6][1][nZIndex]=false;
                m_aaabPossibilities[6][2][nZIndex]=false;
                m_aaabPossibilities[7][0][nZIndex]=false;
                m_aaabPossibilities[7][1][nZIndex]=false;
                m_aaabPossibilities[7][2][nZIndex]=false;
                m_aaabPossibilities[8][0][nZIndex]=false;
                m_aaabPossibilities[8][1][nZIndex]=false;
                m_aaabPossibilities[8][2][nZIndex]=false;
                }
            else if(nYCoordinate<6) // Y=3,4,5
                {
                m_aaabPossibilities[6][3][nZIndex]=false;
                m_aaabPossibilities[6][4][nZIndex]=false;
                m_aaabPossibilities[6][5][nZIndex]=false;
                m_aaabPossibilities[7][3][nZIndex]=false;
                m_aaabPossibilities[7][4][nZIndex]=false;
                m_aaabPossibilities[7][5][nZIndex]=false;
                m_aaabPossibilities[8][3][nZIndex]=false;
                m_aaabPossibilities[8][4][nZIndex]=false;
                m_aaabPossibilities[8][5][nZIndex]=false;
                }
            else                    // Y=6,7,8
                {
                m_aaabPossibilities[6][6][nZIndex]=false;
                m_aaabPossibilities[6][7][nZIndex]=false;
                m_aaabPossibilities[6][8][nZIndex]=false;
                m_aaabPossibilities[7][6][nZIndex]=false;
                m_aaabPossibilities[7][7][nZIndex]=false;
                m_aaabPossibilities[7][8][nZIndex]=false;
                m_aaabPossibilities[8][6][nZIndex]=false;
                m_aaabPossibilities[8][7][nZIndex]=false;
                m_aaabPossibilities[8][8][nZIndex]=false;
                }
            }
        }
    }

int GND::SudokuGrid::TopThree() const
    {
    int nAnswer=0;

    nAnswer+=m_aanGrid[0][0]*100;
    nAnswer+=m_aanGrid[0][1]*10;
    nAnswer+=m_aanGrid[0][2];

    return nAnswer;
    }

//////////////////////////////////////////////////////////////////////////
//
// GND::Passcode methods
//
//////////////////////////////////////////////////////////////////////////

GND::Passcode::Passcode(int nLogins[150])
    {
    // Initialize the sets.
    size_t Index;
    for(Index=0;Index<150;Index+=3)
        {
        int A=nLogins[Index],
            B=nLogins[Index+1],
            C=nLogins[Index+2];

        // There is a B and a C to the right of A.
        m_SetData.Insert(A,B,SET_RIGHT);
        m_SetData.Insert(A,C,SET_RIGHT);

        // There is an A to the left and a C to
        // the right of B.
        m_SetData.Insert(B,A,SET_LEFT);
        m_SetData.Insert(B,C,SET_RIGHT);

        // There is an A and a B to the left
        // of C.
        m_SetData.Insert(C,A,SET_LEFT);
        m_SetData.Insert(C,B,SET_LEFT);
        }
    }

int GND::Passcode::ReturnAsInt()
    {
    // Returns the passcode as an int.
    int nAnswer=0;

    int x=1;
    int Index,nSolution=(int)m_aSolution.size();
    for(Index=nSolution-1;Index>-1;--Index)
        {
        int n=m_aSolution[Index];
        nAnswer+=n*x;
        x*=10;
        }

    return nAnswer;
    }

int GND::Passcode::Solve()
    {
    // Find the singular numbers.
    std::vector<int> aSingularNumbers;
    size_t nTotalNumbers=0;

    size_t nDigit;
    for(nDigit=0;nDigit<10;++nDigit)
        {
        std::set<int> const &sLeft=m_SetData.GetLeftSet(nDigit);
        std::set<int> const &sRight=m_SetData.GetRightSet(nDigit);

        if(sLeft.size()||sRight.size())
            {
            // Digits that occur in their own sets
            // are not singular.
            if(sLeft.find(nDigit)==sLeft.end()&&
               sRight.find(nDigit)==sRight.end())
                {
                aSingularNumbers.push_back(nDigit);
                }
            ++nTotalNumbers;
            }
        }

    if(nTotalNumbers!=aSingularNumbers.size())
        {
        // This passcode has digits which occur
        // more than once in the passcode.
        // This case is currently not supported.
        assert(UnderConstruction);
        return 0;
        }

    // Order the numbers.
    std::set<int> sInList;

    size_t nSingular=aSingularNumbers.size();
    while(m_aSolution.size()!=nSingular)
        {
        int nNextDigit=-1;
        int Index1;
        for(Index1=0;Index1<(int)nSingular;++Index1)
            {
            int nDigit1=aSingularNumbers[Index1];

            if(sInList.find(nDigit1)==sInList.end())
                {
                std::set<int> const &sLeft=m_SetData.GetLeftSet(nDigit1);

                // Whether nDigit1 is the next digit
                // to be added to the solution.
                bool bNextDigit=true;

                std::set<int>::const_iterator iter=sLeft.begin();
                while(iter!=sLeft.end())
                    {
                    int n=*iter;
                    if(sInList.find(n)==sInList.end())
                        {
                        bNextDigit=false;
                        }
                    ++iter;
                    }

                if(bNextDigit)
                    {
                    nNextDigit=nDigit1;
                    break;
                    }
                }
            }

        // Add nNextDigit to the solution.
        sInList.insert(nNextDigit);
        m_aSolution.push_back(nNextDigit);
        }

    int nAnswer=ReturnAsInt();
    return nAnswer;
    }

//////////////////////////////////////////////////////////////////////////
//
// GND::SetData methods
//
//////////////////////////////////////////////////////////////////////////

GND::SetData::SetData()
    {
    size_t Index;
    for(Index=0;Index<10;++Index)
        {
        std::pair<std::set<int>,std::set<int>> ThisPair;
        m_Sets.push_back(ThisPair);
        }
    }

void GND::SetData::Insert(int nDigit,int nValue,int nDirection)
    {
    if(nDirection==SET_LEFT)
        {
        m_Sets[nDigit].first.insert(nValue);
        }
    else
        {
        m_Sets[nDigit].second.insert(nValue);
        }
    }

std::set<int> const &GND::SetData::GetLeftSet(int nDigit)
    {
    return m_Sets[nDigit].first;
    }

std::set<int> const &GND::SetData::GetRightSet(int nDigit)
    {
    return m_Sets[nDigit].second;
    }

//////////////////////////////////////////////////////////////////////////
//
// GND::PythagoreanTriple methods.
//
//////////////////////////////////////////////////////////////////////////

GND::PythagoreanTriple::PythagoreanTriple()
    {
    // Start with the smallest triple: 3,4,5
    // which corresponds to (2,1,1)
    m_nM=2;
    m_nN=1;
    m_nK=1;
    }

#define MAX_CIRCUMFRENCE 1000000000

bool GND::PythagoreanTriple::operator++()
    {
    // Leave bread crumbs.
    int nOrigN=m_nN;
    int nOrigM=m_nM;
    int nOrigK=m_nK;

    // Try to increment K.
    ++m_nK;

    int nATemp=0;
    int nBTemp=0;
    int nCTemp=0;
    ComputeTriple(nATemp,nBTemp,nCTemp);

    int nTempCircum=nATemp+nATemp+nCTemp+nCTemp;
    if(nTempCircum<MAX_CIRCUMFRENCE)
        {
        return true;
        }
    else
        {
        m_nK=1;

        // m > n
        // m-n must be odd
        // m,n must be coprime

        // Try to increment M.
        int nTempM=m_nM;

        bool bLooking=true;
        while(bLooking)
            {
            nTempM+=2;
            if(areCoprime(nTempM,m_nN))
                {
                bLooking=false;
                }
            }

        m_nM=nTempM;

        ComputeTriple(nATemp,nBTemp,nCTemp);
        nTempCircum=nATemp+nATemp+nCTemp+nCTemp;
        if(nTempCircum<MAX_CIRCUMFRENCE)
            {
            return true;
            }
        else
            {
            // Try to increment N.
            ++m_nN;
            m_nM=m_nN+1;

            // Find M.
            int nTempM=m_nM;

            bLooking=true;
            while(bLooking)
                {
                if(areCoprime(nTempM,m_nN))
                    {
                    bLooking=false;
                    }
                else
                    {
                    nTempM+=2;
                    }
                }

            m_nM=nTempM;

            ComputeTriple(nATemp,nBTemp,nCTemp);
            nTempCircum=nATemp+nATemp+nCTemp+nCTemp;
            if(nTempCircum<MAX_CIRCUMFRENCE)
                {
                return true;
                }
            }
        }

    int m_nN=nOrigN;
    int m_nM=nOrigM;
    int m_nK=nOrigK;

    return false;
    }

void GND::PythagoreanTriple::ComputeTriple(int &nA,
                                           int &nB,
                                           int &nC)
    {
    int dM2=m_nM*m_nM;
    int dN2=m_nN*m_nN;

    nA=m_nK*(dM2-dN2);
    nB=m_nK*(2*m_nM*m_nN);
    nC=m_nK*(dM2+dN2);
    }