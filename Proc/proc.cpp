#include <iostream>
#include <chrono>
#include <cassert>
#include <vector>
#include "matrix.h"

long long timer (short n);
void proc (
	const Matrix& a,
	const Matrix& b,
	Matrix& c);

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
	const Matrix& a,
	const Matrix& b,
	Matrix& c)
{
    short n = a.length();
    short mid = n/2;
    
    std::vector<Matrix> p;
    
    for (int i = 0; i < 7; i++)
    {
        p.push_back(Matrix(n/2));
    }

    assert(n == b.length() && n == c.length()); // A,B,C are of size n x n
    assert(n >= 1); // n >= 1
    assert(!(n & (n - 1))); // n is an integer power of 2
    
    if (n == 1)
    {
        c = a * b;
    }
    else
    {
        proc(a.subset(1, mid, 1, mid) +
             a.subset(mid+1, n, mid+1, n),
             b.subset(1, mid, 1, mid) +
             b.subset(mid+1, n, mid+1, n),
             p[0]);
        proc(a.subset(mid+1, n, 1, mid) +
             a.subset(mid+1, n, mid+1, n),
             b.subset(1, mid, 1, mid),
             p[1]);
        proc(a.subset(1, mid, 1, mid),
             b.subset(1, mid, mid+1, n) -
             b.subset(mid+1, n, mid+1, n),
             p[2]);
        proc(a.subset(mid+1, n, mid+1, n),
             b.subset(mid+1, n, 1, mid) -
             b.subset(1, mid, 1, mid),
             p[3]);
        proc(a.subset(1, mid, 1, mid) +
             a.subset(1, mid, mid+1, n),
             b.subset(mid+1, n, mid+1, n),
             p[4]);
        proc(a.subset(mid+1, n, 1, mid) -
             a.subset(1, mid, 1, mid),
             b.subset(1, mid, 1, mid) +
             b.subset(1, mid, mid+1, n),
             p[5]);
        proc(a.subset(1, mid, mid+1, n) -
             a.subset(mid+1, n, mid+1, n),
             b.subset(mid+1, n, 1, mid) +
             b.subset(mid+1, n, mid+1, n),
             p[6]);
        c.setSubset(1, mid, 1, mid, p[0] + p[3] - p[4] + p[6]);
        c.setSubset(mid+1, n, 1, mid, p[1] + p[3]);
        c.setSubset(1, mid, mid+1, n, p[2] + p[4]);
        c.setSubset(mid+1, n, mid+1, n, p[0] + p[2] - p[1] + p[5]);
    }
    
    
    p.clear();
}