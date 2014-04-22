#include "stdafx.h"

#include<iostream>
#include "Problems.h"
#include "Test.h"

void Test()
    {
    TestTool(32,SolveProblem32(),45228);
    TestTool(42,SolveProblem42(),162);
    TestTool(44,SolveProblem44(),5482660);
    TestTool(47,SolveProblem47(),134043);
    TestTool(51,SolveProblem51(),121313);
    TestTool(52,SolveProblem52(),142857);
    }

void TestTool(int nProblemNumber,int nCalculatedAnswer,int nExpectedAnswer)
    {
    if(nCalculatedAnswer==nExpectedAnswer)
        {
        std::cout << "Problem " << nProblemNumber << " passed." << std::endl;
        }
    else
        {
        std::cout << "Problem " << nProblemNumber << " FAILED." << std::endl;
        }
    }