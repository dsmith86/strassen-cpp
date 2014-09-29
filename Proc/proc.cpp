#include <iostream>
#include <chrono>
#include <cassert>
#include <vector>
#include "matrix.h"

long long timer (short n);
void proc (
	const Matrix a,
	const Matrix b,
	Matrix c);

int main()
{
	short n;

	std::cout << "n: ";
	std::cin >> n;
    long long microseconds = timer(n);
	std::cout << "Elapsed time for " << n << ": " << microseconds << std::endl;

	return EXIT_SUCCESS;
}

long long timer (short n)
{
	assert(n >= 1);

	Matrix a = Matrix(n);
	a.fillRandom();

	Matrix b = Matrix(n);
	b.fillRandom();

	Matrix c = Matrix(n);

	auto start = std::chrono::high_resolution_clock::now();

	proc (a, b, c);

	auto elapsed = std::chrono::high_resolution_clock::now() - start;

	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

	return microseconds;
}

void proc (
	const Matrix a,
	const Matrix b,
	Matrix c)
{
    short length = a.length();
    
    std::vector<Matrix> p;
    
    for (int i = 0; i < 7; i++)
    {
        p.push_back(Matrix(length/2));
    }

    assert(length == b.length() && length == c.length()); // A,B,C are of size n x n
    assert(length >= 1); // n >= 1
    assert(!(length & (length - 1))); // n is an integer power of 2
    
    if (length == 1)
    {
        c = a * b;
    }
    else
    {
        return;
    }
    
    
    p.clear();
}