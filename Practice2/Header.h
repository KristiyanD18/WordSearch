#pragma once
int getDigitsCount(long n)
{
	int i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}

	return i;
}

int getDigitAtPosition(long N, unsigned int pos, int digitsCount)
{
	int timesToDivide = digitsCount - pos;

	for (size_t i = 0; i < timesToDivide; i++)
	{
		N /= 10;
	}

	return N - ((N / 10) * 10);
}

int timesTen(int count)
{
	int result = 1;
	for (size_t i = 0; i < count; i++)
	{
		result *= 10;
	}

	return result;
}

int checkNum(long N, unsigned int m, unsigned int l)
{
	int digitsCount = getDigitsCount(N);
	if (digitsCount >= 9 || m > digitsCount || l > digitsCount || m < 1 || l < 1) // validation
	{
		return -1;
	}
	int timesToDivideM = digitsCount - m;
	int timesToDivideL = digitsCount - l;
	int posM = getDigitAtPosition(N, m, digitsCount);
	int posL = getDigitAtPosition(N, l, digitsCount);

	N = N - posM * timesTen(timesToDivideM) + posL * timesTen(timesToDivideM);
	N = N - posL * timesTen(timesToDivideL) + posM * timesTen(timesToDivideL);

	if (N == (N / 4) * 4)
	{
		return 1;
	}

	return 0;
}
