// Lab4.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Lab4.h"


// This is an example of an exported variable
LAB4_API int nLab4=0;

// This is an example of an exported function.
LAB4_API int fnLab4(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see Lab4.h for the class definition
CLab4::CLab4()
{
	return;
}
