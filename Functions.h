#include <set>

//This function takes a string of capital letters and returns if it is a
//triangle word (tn = ½n(n+1)).  For example "A" would have a word value of 1 and would
//be a triangle word.
bool IsWordTriangle(std::string sWord);

//This function returns true if nNumber is a triangle number
//of the form tn = ½n(n+1).
bool IsTriangle(int nNumber);

//This function returns the number of digits in its one int parameter.
int numberDigits(int n);

int nextPrime(int n);

//Input is the integer denominator a.  Output is 1 if
//denominator results in a terminating fraction.
//Returns 0 if fraction is non-terminating.

//a <= 1000
int isTerminating(int a);

//This function takes 10 parameters
//if each integer from 0 to 9 are present once and only once,
//the function returns 1.
//Else it returns 0.
int areAllDigits(int a,int b,int c,int d,int e,int f,int g,int h,int i,int j);

//This function returns true if n is prime.
//It returns false if n is not prime.
bool isPrime(int nNumber);

//Function returns 1 if n is a palindrome in base 2.
//Returns 0 if n is not a palindrome.
//
//Note that leading zeroes are not included as part
//of a palindrome.
int isPalindromeBaseTwo(int n);

int isPalindrome(int i);

//This function takes a parameter x and
//returns 1 if it is even and 0 if it is not.
bool isEven(int x);

int isAbundant(int n);

int factorial(int n);

int concatinate(int a, int b);

//n choose r.
int choose(int n, int r);

char asciiToEnglish(int n);

//In number theory, a branch of mathematics, two integers
//a and b are said to be coprime (also spelled co-prime)
//or relatively prime if the only positive integer that
//evenly divides both of them is 1.

int areCoprime(int a, int b);

//This function computes the Totient of n.
int Totient(int n);

//this function takes an integer and reterns an integer which has the digit order reversed.
//For example if the function took 1224, the function would return 4221.
int reverse(int i);

//Returns a^b.
int power(int a, int b);

//Takes an int nNumber and returns nNumber(3nNumber-1)/2
//which is the pentagonal number of index nNumber.
int pentagonal(int nNumber);

//Takes an int nNumber and returns true if nNumber is
//a pentagonal number of the form n(3n-1)/2.
//nStart is the starting n.
bool isPentagonal(int nNumber, int nStartPentIndex = 0);

//Takes an int nNumber and returns true if nNumber is
//a hexagonal number of the form n(2n−1).
bool isHexagonal(int nNumber, int nStartHexIndex = 0);

//This function takes an int nNumber and returns the number
//of distinct prime factors of nNumber.
//For example nNumber = 6 would return 2 because 6 has two
//distinct prime factors (2 and 3).
int nDistinctPrimeFactors(int nNumber);

//This function will return true if nNumerator divides
//nDenominator without remainder.
bool dividesEvenly(int nNumerator, int nDenominator);

//This function attempts to add nNumber to sSet.  If
//this is successful the function returns true.
bool bSetChangeInsert(std::set<int> &sSet,int const nNumber);

//Finds the number of digit permutations of nNumber^3
//which are also cubed integers > nNumber.
int nNumberCubedPermutations(int const nNumber);

//Takes a string representation of an integer
//and returns the string representation of its cube.
std::string CubedString(std::string const sString);

void MuliplierTool(int const nNumber,int &nRemainder,int &nFirstDigit);

std::string StringRemoveLeadingZeros(std::string const &sResult);

bool IsSolutionToProblem51(int &nNumber);
