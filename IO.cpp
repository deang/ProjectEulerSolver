#include "stdafx.h"

#include <iostream>
#include "Problems.h"
#include "Test.h"
#include "Classes.h"
#include <math.h>

void IOLineBar()
    {
    std::cout << "\n----------------------------------------\n";
    std::cout << "----------------------------------------\n";
    }

void IOProgramHeader()
    {
    IOLineBar();
    std::cout << "\nProject Euler Problem Solver\n";
    std::cout << "Version 1.0\n";
    std::cout << "Gavin N. Dean\n\n";
    std::cout << "http://projecteuler.net/\n";
    IOLineBar();
    }

void IOTestOrProblem()
    {
    std::cout << "\nOption 1: Solve a specific problem." << std::endl;
    std::cout << "Option 2: Test known problems." << std::endl;
    std::cout << "Option 3: Solve a sudoku puzzle." << std::endl;
    std::cout << "Option 4: Exit program.\n" << std::endl;
    }

void IOProblemQuery()
    {
    std::cout << "\nEnter problem number." << std::endl;
    }

void IOCannotSolve()
    {
    std::cout << "Cannot solve this problem at this time." << std::endl;
    }

void IOSolutionHeader()
    {
    std::cout << "\nThe solution is: " << std::endl;
    }

void IOSudoku()
    {
    IOLineBar();
    std::cout << std::endl;

    int aanGrid[9][9];

    std::cout << "Enter the sudoku grid, entering 0 for unknown spaces." << std::endl;
    std::cout << std::endl;

    size_t Index;
    for(Index=0;Index<9;++Index)
        {
        double dEntry;
        std::cin >> dEntry;

        double dDigit=floor(dEntry/100000000);
        aanGrid[Index][0]=(int)dDigit;
        dEntry-=dDigit*100000000;

        dDigit=floor(dEntry/10000000);
        aanGrid[Index][1]=(int)dDigit;
        dEntry-=dDigit*10000000;

        dDigit=floor(dEntry/1000000);
        aanGrid[Index][2]=(int)dDigit;
        dEntry-=dDigit*1000000;

        dDigit=floor(dEntry/100000);
        aanGrid[Index][3]=(int)dDigit;
        dEntry-=dDigit*100000;

        dDigit=floor(dEntry/10000);
        aanGrid[Index][4]=(int)dDigit;
        dEntry-=dDigit*10000;

        dDigit=floor(dEntry/1000);
        aanGrid[Index][5]=(int)dDigit;
        dEntry-=dDigit*1000;

        dDigit=floor(dEntry/100);
        aanGrid[Index][6]=(int)dDigit;
        dEntry-=dDigit*100;

        dDigit=floor(dEntry/10);
        aanGrid[Index][7]=(int)dDigit;
        dEntry-=dDigit*10;

        dDigit=floor(dEntry/1);
        aanGrid[Index][8]=(int)dDigit;
        }

    GND::SudokuGrid TheSudokuGrid(aanGrid);

    std::cout << std::endl;
    std::cout << "Solving the sudoku..." << std::endl;
    std::cout << std::endl;

    if(!TheSudokuGrid.Solve())
        {
        std::cout << "Cannot solve this sudoku at this time." << std::endl;
        }
    else
        {
        IOSolutionHeader();
        TheSudokuGrid.Print();
        }
    IOLineBar();
    }

bool IORunProgram()
    {
    IOTestOrProblem();
    int nUserOption;
    std::cin >> nUserOption;
    if(nUserOption==1)
        {
        IOProblemQuery();
        int nProblemNumber = 0;
        std::cin >> nProblemNumber;

        IOSolutionHeader();
        if(nProblemNumber == 32)
            {
            std::cout << SolveProblem32() << std::endl;
            }
        else if(nProblemNumber == 42)
            {
            std::cout << SolveProblem42() << std::endl;
            }
        else if(nProblemNumber == 44)
            {
            std::cout << SolveProblem44() << std::endl;
            }
        else if(nProblemNumber == 45)
            {
            std::cout << SolveProblem45() << std::endl;
            }
        else if(nProblemNumber == 47)
            {
            std::cout << SolveProblem47() << std::endl;
            }
        else if(nProblemNumber == 51)
            {
            std::cout << SolveProblem51() << std::endl;
            }
        else if(nProblemNumber == 52)
            {
            std::cout << SolveProblem52() << std::endl;
            }
        else if(nProblemNumber == 56)
            {
            std::cout << SolveProblem56() << std::endl;
            }
        else if(nProblemNumber == 62)
            {
            std::cout << SolveProblem62() << std::endl;
            }
        else if(nProblemNumber == 69)
            {
            std::cout << SolveProblem69() << std::endl;
            }
        else if(nProblemNumber == 79)
            {
            std::cout << SolveProblem79() << std::endl;
            }
        else if(nProblemNumber == 94)
            {
            std::cout << SolveProblem94() << std::endl;
            }
        else if(nProblemNumber == 96)
            {
            std::cout << SolveProblem96() << std::endl;
            }
        else
            {
            IOCannotSolve();
            }
        IOLineBar();
        }
    else if(nUserOption==2)
        {
        Test();
        IOLineBar();
        }
    else if(nUserOption==3)
        {
        IOSudoku();
        }
    else if(nUserOption == 4)
        {
        return false;
        }
    return true;
    }

void IOMaxIntExceeded()
    {
    std::cout << "ERROR: Maximum value for data type int exceeded." << std::endl;
    }