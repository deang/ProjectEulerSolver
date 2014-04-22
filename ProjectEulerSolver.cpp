// ProjectEulerSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "IO.h"


int _tmain(int argc, _TCHAR* argv[])
{
    IOProgramHeader();
    int nCounter = 0;
    while(IORunProgram())
        {
        ++nCounter;
        if(nCounter>100)
            {
            break;
            }
        }
	return 0;
}

