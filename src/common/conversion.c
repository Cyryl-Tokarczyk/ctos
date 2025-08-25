#include "conversion.h"

char* intToString(int n, char* buffer)
{
	if (n == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';

		return buffer;
	}

	bool isNegative = n < 0 ? true : false;

	if (isNegative)
	{
		n *= -1;
	}

	size_t numOfDigits = 0;

	while (n > 0) {
		buffer[numOfDigits] = '0' + n % 10;
		n /= 10;

		numOfDigits++;
	}

	if (isNegative)
	{
		buffer[numOfDigits] = '-';

		numOfDigits++;
	}

	for (size_t i = 0; i < numOfDigits / 2; i++)
	{
		char temp = buffer[i];
		buffer[i] = buffer[numOfDigits - 1 - i];
		buffer[numOfDigits - 1 - i] = temp;
	}

	buffer[numOfDigits] = '\0';

	return buffer;
}