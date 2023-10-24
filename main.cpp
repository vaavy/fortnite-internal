#include "yass.h"
#include <iostream>

bool testYASS(PatternScan::YASS scanner, char* buffer, int size)
{
	return scanner.Scan((uintptr_t)buffer, size);
}

int main()
{
}