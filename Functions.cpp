#include "stdafx.h"

#include<iostream>
#include<math.h>
#include<set>
#include<sstream>
#include"Functions.h"
#include"Classes.h"

bool IsWordTriangle(std::string sWord)
    {
    int nWordValue = 0;
    int ASCIIArray[26];
    for(size_t Index = 65; Index < 91; ++Index)
        {
        ASCIIArray[Index - 65] = Index;
        }
    //int ASCIIArray[26] = {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80}
    for(size_t Index = 0; Index < sWord.length(); ++Index)
        {
        for(size_t Index2 = 0; Index < 26; ++Index2)
            {
            if(sWord[Index] == ASCIIArray[Index2])
                {
                nWordValue += Index2 + 1;
                break;
                }
            }
        }
    return IsTriangle(nWordValue);
    }

bool IsTriangle(int nNumber)
    {
    //Triangle numbers are tn = ½n(n+1).
    int nTriangle = 0;
    int Index = 1;
    bool bTriangle = false;
    while(nTriangle <= nNumber)
        {
        nTriangle = (Index*(Index+1))/2;
        if(nTriangle == nNumber)
            {
            bTriangle = true;
            }
        ++Index;
        }
    return bTriangle;
    }

//This function returns the number of digits in its one int parameter.

int numberDigits(int n)
    {
    int j = 1;
    int count = 1;
    while (j < 1000000000)
        {
        if (n/j < 10)
            {
            return count;
            }
        j = j*10;
        count += 1;
        }
    std::cout << "Error";
    return 0;
    }

int nextPrime(int n)
    {
    for (int i = n; 1 > 0; i++)
        {
        if (isPrime(i) == 1)
            {
            return i;
            }
        }
    }

//Input is the integer denominator a.  Output is 1 if
//denominator results in a terminating fraction.
//Returns 0 if fraction is non-terminating.

//a <= 1000

int isTerminating(int a)
    {

    int c = 0;
    int uppern = 10;
    int upperm = 5;

    for	(int n = 0; n < uppern + 1; n++)
        {
        for	(int m = 0; m < upperm + 1; m++)
            {
            double dTWO = 2.0;
            double dFIVE = 5.0;
            if	(a == pow(dTWO,n)*pow(dFIVE,m))
                {
                c += 1;
                break;
                }

            }

        }

    if	(c == 1)
        {
        return 1;	
        } else {
            return 0;
        }

    }

//This function takes 10 parameters
//if each integer from 0 to 9 are present once and only once,
//the function returns 1.
//Else it returns 0.

int areAllDigits(int a,int b,int c,int d,int e,int f,int g,int h,int i,int j)
    {
    int array[10] = {a,b,c,d,e,f,g,h,i,j};
    for(int z = 0; z < 10; z++)
        {
        int x = 0;
        for (int y = 0; y < 10; y++)
            {
            if (array[y] == z)
                {
                x += 1;
                }
            }
        if(x != 1)
            {
            return 0;
            }
        }
    return 1;
    }

//This function returns true if n is prime.
//It returns false if n is not prime.

bool isPrime(int nNumber)
    {
    bool bPrime = true;
    int Index = 2;
    while(Index <= nNumber/2)
        {
        if(double(nNumber/Index) == double(nNumber)/double(Index))
            {
            bPrime = false;
            }
        ++Index;
        }
    if(nNumber == 2)
        {
        bPrime = true;
        }
    return bPrime;
    }

//Function returns 1 if n is a palindrome in base 2.
//Returns 0 if n is not a palindrome.
//
//Note that leading zeroes are not included as part
//of a palindrome.

int isPalindromeBaseTwo(int n)
    {
    int binary[21];
    for (int i = 20; i >= 0; i--)
        {
        if  (n >= power(2,i))
            {
            binary[20 - i - 1] = 1;
            n -= power(2,i);
            } else
            {
            binary[20 - i - 1] = 0;
                }
        }
    //find the location of the first nonzero binary value
    int loc;
    for (int i = 0; i < 20; i++)
        {
        if  (binary[i] == 1)
            {
            loc = i;
            break;
            }
        }

    //std::cout << std::endl;


    for (int i = loc, j = 19; i <= 19, j >= loc; i++, j--)
        {
        //std::cout << "i: " << i << "j: " << j << std:: endl;
        if  (binary[i] != binary[j])
            {
            return 0;
            }
        }
    std::cout << std::endl;

    for (int i = 0; i < 20; i++)
        {
        std::cout << binary[i] << " ";
        }
    return 1;
    }

int isPalindrome(int i)
    {
    int temp = i, digit;
    int reverse = 0;

    do
        {
        digit = temp%10;
        reverse = (reverse*10) + digit;
        temp = temp/10;
        }while (temp!=0);

        if (i == reverse)
            {
            return 1;
            }
        else
            {
            return 0;
            }
    }

//This function takes a parameter x and
//returns 1 if it is even and 0 if it is not.

bool isEven(int x)
    {
    if(x%2 == 0)
        {
        return 1;
        }
    return 0;
    }

int isAbundant(int n)
    {
    int sum = 0;
    for (int i = 1; i < n/2 + 1; i++)
        {
        if  (n % i == 0)
            {
            sum += i;
            }
        }
    if  (sum > n)
        {
        return 1;
        } else
        {
        return 0;
            }
    }

int factorial(int n)
    {
    if(n == 0)
        {
        return 1;
        }
    int answer = n;
    for(int i = n; i >= 1; i--)
        {
        answer = answer*i;
        }
    return answer;
    }

int concatinate(int a, int b)
    {
    //Calculating the number of digits a needs to be offset
    int offset = numberDigits(b);
    return a*power(10,offset) + b;
    }

int choose(int n, int r)
    {
    int denominator;
    int numerator;
    int facR = factorial(r);
    int NRfac = factorial(n-r);

    numerator = factorial(n);
    denominator = facR*NRfac;

    return numerator / denominator;
    }

char asciiToEnglish(int n)
    {
    //std::cout << "Using asciiToEnglish" << std::endl;
    char C;
    if (n == 33)
        {
        C = ' ';

        }
    if (n == 34)
        {
        C = '!';

        }
    if (n == 35)
        {
        C = '"';

        }
    if (n == 36)
        {
        C = '#';

        }
    if (n == 37)
        {
        C = '$';

        }
    if (n == 38)
        {
        C = '%';

        }
    if (n == 39)
        {
        C = '&';

        }
    if (n == 40)
        {
        //This character ignored > character constant too long for its type
        //C = ' SINGLE QUOTE MARK ';

        }
    if (n == 41)
        {
        //This character ignored > character constant too long for its type
        //C = ' OPEN PARENTHESIS ';

        }
    if (n == 42)
        {
        //This character ignored > character constant too long for its type
        //C = ' CLOSE PARENTHESIS ';

        }
    if (n == 43)
        {
        C = '*';

        }
    if (n == 44)
        {
        C = '+';

        }
    if (n == 45)
        {
        C = ',';

        }
    if (n == 46)
        {
        C = '-';

        }
    if (n == 47)
        {
        C = '.';

        }
    if (n == 48)
        {
        C = '/';

        }
    if (n == 49)
        {
        C = '0';

        }
    if (n == 50)
        {
        C = '1';

        }
    if (n == 51)
        {
        C = '2';

        }
    if (n == 52)
        {
        C = '3';

        }
    if (n == 53)
        {
        C = '4';

        }
    if (n == 54)
        {
        C = '5';

        }
    if (n == 55)
        {
        C = '6';

        }
    if (n == 56)
        {
        C = '7';

        }
    if (n == 57)
        {
        C = '8';

        }
    if (n == 58)
        {
        C = '9';

        }
    if (n == 59)
        {
        C = ':';

        }
    if (n == 60)
        {
        C = ';';

        }
    if (n == 61)
        {
        C = '<';

        }
    if (n == 62)
        {
        C = '=';

        }
    if (n == 63)
        {
        C = '>';

        }
    if (n == 64)
        {
        C = '?';

        }
    if (n == 65)
        {
        C = '@';

        }
    if (n == 66)
        {
        C = 'A';

        }
    if (n == 67)
        {
        C = 'B';

        }
    if (n == 68)
        {
        C = 'C';

        }
    if (n == 69)
        {
        C = 'D';

        }
    if (n == 70)
        {
        C = 'E';

        }
    if (n == 71)
        {
        C = 'F';

        }
    if (n == 72)
        {
        C = 'G';

        }
    if (n == 73)
        {
        C = 'H';

        }
    if (n == 74)
        {
        C = 'I';

        }
    if (n == 75)
        {
        C = 'J';

        }
    if (n == 76)
        {
        C = 'K';

        }
    if (n == 77)
        {
        C = 'L';

        }
    if (n == 78)
        {
        C = 'M';

        }
    if (n == 79)
        {
        C = 'N';

        }
    if (n == 80)
        {
        C = 'O';

        }
    if (n == 81)
        {
        C = 'P';

        }
    if (n == 82)
        {
        C = 'Q';

        }
    if (n == 83)
        {
        C = 'R';

        }
    if (n == 84)
        {
        C = 'S';

        }
    if (n == 85)
        {
        C = 'T';

        }
    if (n == 86)
        {
        C = 'U';

        }
    if (n == 87)
        {
        C = 'V';

        }
    if (n == 88)
        {
        C = 'W';

        }
    if (n == 89)
        {
        C = 'X';

        }
    if (n == 90)
        {
        C = 'Y';

        }
    if (n == 91)
        {
        C = 'Z';

        }
    if (n == 92)
        {
        C = '[';

        }
    if (n == 93)
        {
        //This character ignored > character constant too long for its type
        //C = ' FORWARD SLASH ';

        }
    if (n == 94)
        {
        C = ']';

        }
    if (n == 95)
        {
        C = '^';

        }
    if (n == 96)
        {
        C = '_';

        }
    if (n == 97)
        {
        C = '`';

        }
    if (n == 98)
        {
        C = 'a';

        }
    if (n == 99)
        {
        C = 'b';

        }
    if (n == 100)
        {
        C = 'c';

        }
    if (n == 101)
        {
        C = 'd';

        }
    if (n == 102)
        {
        C = 'e';

        }
    if (n == 103)
        {
        C = 'f';

        }
    if (n == 104)
        {
        C = 'g';

        }
    if (n == 105)
        {
        C = 'h';

        }
    if (n == 106)
        {
        C = 'i';
        }
    if (n == 107)
        {
        C = 'j';

        }
    if (n == 108)
        {
        C = 'k';

        }
    if (n == 109)
        {
        C = 'l';

        }
    if (n == 110)
        {
        C = 'm';

        }
    if (n == 111)
        {
        C = 'n';

        }
    if (n == 112)
        {
        C = 'o';

        }
    if (n == 113)
        {
        C = 'p';

        }
    if (n == 114)
        {
        C = 'q';

        }
    if (n == 115)
        {
        C = 'r';

        }
    if (n == 116)
        {
        C = 's';

        }
    if (n == 117)
        {
        C = 't';

        }
    if (n == 118)
        {
        C = 'u';

        }
    if (n == 119)
        {
        C = 'v';

        }
    if (n == 120)
        {
        C = 'w';

        }
    if (n == 121)
        {
        C = 'x';

        }
    if (n == 122)
        {
        C = 'y';

        }
    if (n == 123)
        {
        C = 'z';

        }
    if (n == 124)
        {
        C = '{';

        }
    if (n == 125)
        {
        C = '|';

        }
    if (n == 126)
        {
        C = '}';

        }
    if (n == 127)
        {
        C = '~';

        }
    if (n == 128)
        {
        //This character ignored > character constant too long for its type
        //C = ' DELETE ';

        }

    return C;
    }

//In number theory, a branch of mathematics, two integers
//a and b are said to be coprime (also spelled co-prime)
//or relatively prime if the only positive integer that
//evenly divides both of them is 1.

int areCoprime(int a, int b)
    {
    int c = a;
    if  (c < b)
        {
        c = b;
        }
    for (int i = 2; i < c; i++)
        {
        if  (a % i == 0 && b % i == 0)
            {
            return 0;
            }
        }
    return 1;
    }

int Totient(int n)
    {
    int Index,nAnswer=1; // All numbers are considered coprime
                         // with 1.
    for(Index=2;Index<n;++Index)
        {
        if(areCoprime(n,Index))
            {
            ++nAnswer;
            }
        }
    return nAnswer;
    }

//this function takes an integer and reterns an integer which has the digit order reversed.
//For example if the function took 1224, the function would return 4221.

int reverse(int i)
    {
    int temp = i, digit;
    int reverse = 0;

    do
        {
        digit = temp%10;
        reverse = (reverse*10) + digit;
        temp = temp/10;
        }while (temp!=0);

        return reverse;
    }

//This function takes a composite integer n and returns the lowest prime factor

int primeFactorization(int n)
    {
    //std::cout << "n=" << n << std::endl;
    int factor;
    for(int i = 2; i > 0; i++)
        {
        //Tracking code
        //std::cout << "Code 11" << std::endl;
        //if i is a factor of n and i is prime
        if(n % i == 0 && isPrime(i) == 1)
            {
            factor = i;
            break;
            }
        //Tracking code
        //std::cout << "Code 12" << std::endl;
        }
    //std::cout << "Returning: " << factor << std::endl;
    return factor;
    }


int power(int a, int b)
    {
    if  (b == 0)
        {
        return 1;
        }
    int i = a;
    for (int j = 1; j <= b - 1; j++)
        {
        i = i*a;
        }
    return i;
    }

//This function takes 4 integer parameters and returns
//1 if each integer has 4 distinct prime factors.
//These factors must be distince accross parameters too.
//Note that squares of prime factors ARE considered
//distinct factors.  (Ex. 2^2 is considered distinct from 2)

//Also note that the upper limit on a,b,c,d is ~10^20

int numDistinctPrimeFactors(int a, int b, int c, int d)
    {
    int input[4] = {a,b,c,d};
    int k,n;
    //Create a stable array primeFactors
    int primeFactors[80];
    for (int u = 0; u < 80; u++)
        {
        primeFactors[u] = 0;
        }
    //std::cout << "Step 1 ";
    for (int v = 0; v < 4; v++)
        {
        //std::cout << "Step 2 ";
        n = input[v];
        //For the set of positive integers i
        for (int i = 1; i < n/2 + 1; i++)
            {
            //Check if they are prime
            //If they are, check if i is a factor of n.
            if  (isPrime(i) == 1 && n % i == 0)
                {
                //std::cout << "Step 3 ";
                //If i is, store n as n/i and store i in the next available space in primeFactors.
                n = n/i;
                for (k = 0; k < 80; k++)
                    {
                    if  (primeFactors[k] == 0)
                        {
                        primeFactors[k] = i;
                        break;
                        }
                    }
                //std::cout << "Step 4 ";
                //If n is prime, store in the next space in primeFactors and break
                if  (isPrime(n) == 1)
                    {
                    for (k = 0; k < 80; k++)
                        {
                        if  (primeFactors[k] == 0)
                            {
                            primeFactors [k] = n;
                            break;
                            }
                        }
                    break;
                    }
                }
            }
        //std::cout << "Step 5 ";
        //Search for duplicates/triplicates/etc in primeFactors
        //Store the number of replicates as count.
        //Ex.  if there are two, count would be two..
        for (int t = 0; t < 80; t++)
            {
            int b = primeFactors[t];
            for (int s = t + 1; s < 80; s++)
                {
                if  (b == primeFactors[s])
                    {
                    primeFactors[t] = primeFactors[t]*primeFactors[s];
                    primeFactors[s] = 0;
                    }
                }
            }
        //std::cout << "Step 6 ";
        //count the number of distinct factors in primeFactors
        //if count != 4*(v+1) return 0.
        int count = 0;
        for (int w = 0; w < 80; w++)
            {
            int y = 0;
            for (int q = w + 1; q < 80; q++)
                {
                if (primeFactors[w] == primeFactors[q])
                    {
                    y += 1;
                    }
                }
            if (y == 0)
                {
                //primeFactors[w] is distinct
                count += 1;
                }
            }
        //std::cout << "Step 7 ";
        if  (count != 4*(v + 1))
            {
            return 0;
            }
        }
    //std::cout << "Step  ";
    return 1;
    for (int e = 0; e < 80; e++)
        {
        std::cout << primeFactors[e] << std::endl;
        }
    }

//Takes an int nNumber and returns nNumber(3nNumber-1)/2
//which is the pentagonal number of index nNumber.
int pentagonal(int nNumber)
    {
    return nNumber*(3*nNumber-1)/2;
    }

//Takes an int nNumber and returns true if nNumber is
//a pentagonal number of the form n(3n-1)/2.
bool isPentagonal(int nNumber, int nStartPentIndex)
    {
    //Pentagonal numbers are pn = n(3n-1)/2.
    int nPentagonal = 0;
    int Index = nStartPentIndex;
    bool bPentagonal = false;
    while(nPentagonal <= nNumber)
        {
        nPentagonal = Index*(3*Index-1)/2;
        if(nPentagonal == nNumber)
            {
            bPentagonal = true;
            }
        ++Index;
        }
    return bPentagonal;
    }

bool isHexagonal(int nNumber, int nStartHexIndex)
    {
    //Pentagonal numbers are hn = n(2n−1).
    int nHexagonal = 0;
    int Index = nStartHexIndex;
    bool bHexagonal = false;
    while(nHexagonal <= nNumber)
        {
        nHexagonal = Index*(2*Index-1);
        if(nHexagonal == nNumber)
            {
            bHexagonal = true;
            }
        ++Index;
        }
    return bHexagonal;
    }

bool dividesEvenly(int nNumerator, int nDenominator)
    {
    return double(nNumerator/nDenominator) == double(nNumerator)/double(nDenominator);
    }

int nDistinctPrimeFactors(int nNumber)
    {
    int nTemp = nNumber;
    std::set<int> sFactors;
    bool bExit = false;
    while(!bExit)
        {
        for(int Index = 2; Index <= nTemp; ++Index)
            {
            if(Index != nTemp)
                {
                //If Index divides nTemp evenly.
                if(floor(double(nTemp/Index)) == double(nTemp)/double(Index))
                    {
                    nTemp /= Index;
                    sFactors.insert(Index);
                    break;
                    }
                }
            else
                {
                sFactors.insert(Index);
                bExit = true;
                break;
                }
            }
        }
    sFactors.insert(nTemp);
    return sFactors.size();
    }

bool bSetChangeInsert(std::set<int> &sSet,int const nNumber)
    {
    int nSetSize = sSet.size();
    sSet.insert(nNumber);
    if(sSet.size() == nSetSize)
        {
        return false;
        }
    else
        {
        return true;
        }
    }

int nNumberCubedPermutations(int const nNumber)
    {
    bool bContinue = true;
    int nLargerNumber = nNumber+1;
    int nAnswer = 0;

    GND::StringInt siNumber(nNumber);
    while(bContinue)
        {
        GND::StringInt siLargerNumber(nLargerNumber);
        //Check to see that the cubes have the same number of digits.
        //If they don't they cannot be permutations of one another.
        GND::StringInt siNumberCubed(siNumber.power(3));
        GND::StringInt siLargerNumberCubed(siLargerNumber.power(3));
        if(siNumberCubed.nNumberOfDigits()!=siLargerNumberCubed.nNumberOfDigits())
            {
            break;
            }
        if(siNumber.bPermutedCubes(siLargerNumber))
            {
            ++nAnswer;
            }
        ++nLargerNumber;
        }
    return nAnswer;
    }

//Takes a string representation of an integer
//and returns the string representation of its cube.
std::string CubedString(std::string const sString)
    {
    GND::StringInt siNumber(sString);
    GND::StringInt siNumberSquared(siNumber.StringMultiply(sString));
    return siNumberSquared.StringMultiply(sString);
    }


void MuliplierTool(int nNumber,int &nRemainder,int &nFirstDigit)
    {
    nNumber+=nRemainder;
    std::stringstream into;
    into << nNumber;
    std::string sNumber = "";
    into >> sNumber;
    nFirstDigit=sNumber[sNumber.size()-1]-48;
    if(nNumber>9)
        {
        std::string sRemainder="";
        for(size_t Index = 0; Index<sNumber.size()-1;++Index)
            {
            sRemainder.push_back(sNumber[Index]);
            }
        std::stringstream into1;
        into1 << sRemainder;
        into1 >> nRemainder;
        }
    else
        {
        nRemainder=0;
        }
    }

std::string StringRemoveLeadingZeros(std::string const &sResult)
    {
    std::string sTemp = sResult;
    while(sTemp.substr(0,1) == "0")
        {
        sTemp=sTemp.substr(1,sTemp.size()-1);
        }
    return sTemp;
    }

bool IsSolutionToProblem51(int &nNumber)
    {
    // By replacing the 1st digit of the 2-digit number *3, it turns out that 
    // six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

    // By replacing the 3rd and 4th digits of 56**3 with the same digit, this 
    // 5-digit number is the first example having seven primes among the ten
    // generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663,
    // 56773, and 56993. Consequently 56003, being the first member of this family,
    // is the smallest prime with this property.

    // Find the smallest prime which, by replacing part of the number (not 
    // necessarily adjacent digits) with the same digit, is part of an eight
    // prime value family.

    int nPrimes=8;     // This is the number of required primes in the family.
                       // For the real answer, change this to 8.

    int nSubCandidate; // This is the digit value in nNumber currently being replaced.
                       // It cannot be greater than 2 to be sure that there are enough
                       // possibilities to produce 8 primes.

    GND::StringInt siNumber(nNumber);
    for(nSubCandidate=0;nSubCandidate<3;++nSubCandidate)
        {
        // Identify the indices of the candidate digits.
        std::set<size_t> sCandidateIndices;
        siNumber.IndicesOfMatchingDigits(nSubCandidate,sCandidateIndices);

        size_t nCount=0;
        if(sCandidateIndices.size())
            {
            int nSubValue=nSubCandidate; // This is the digit value of the current substitution.
            for(nSubValue=nSubCandidate;nSubValue<10;++nSubValue)
                {
                // Replace all the candidate digits with nSubValue.
                int nTestValue=siNumber.ReplacedDigits(nSubValue,sCandidateIndices);

                if(isPrime(nTestValue))
                    {
                    ++nCount;
                    }
                }
            }
        if(nCount==nPrimes)
            {
            return true;
            }
        }
    return false;
    }