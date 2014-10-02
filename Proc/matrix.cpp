#include "matrix.h"
#include <cassert>
#include <cstdlib>
#include <sys/timeb.h>
#include <iostream>

Matrix::Matrix (short n)
{
	data = new short * [n];

	if (data)
	{
		for (int i = 0; i < n; i++)
		{
			data[i] = new short[n];
			assert(data[i]);
		}
	}

	dimensions = n;
}

Matrix::~Matrix()
{
    //delete * data;
}

Matrix::Matrix (const Matrix& source)
{
    data = new short * [source.length()];
    dimensions = source.length();
    
    for (int i = 0; i < length(); i++)
    {
        data[i] = new short [source.length()];
        for (int j = 0; j < length(); j++)
        {
            data[i][j] = source.getElement(i, j);
        }
    }
}

void Matrix::operator= (const Matrix& source)
{
    if (dimensions != source.length())
    {
        for (int i = 0; i < dimensions; i++)
        {
            delete data[i];
        }
        delete * data;
        
        dimensions = source.length();
        
        data = new short * [source.length()];
        
        for (int i = 0; i < length(); i++)
        {
            for (int j = 0; j < length(); j++)
            {
                data[i] = new short [source.length()];
            }
        }
    }
    
    for (int i = 0; i < length(); i++)
    {
        for (int j = 0; j < length(); j++)
        {
            data[i][j] = source.getElement(i, j);
        }
    }
}

Matrix operator+ (const Matrix a, const Matrix b)
{
    short length = a.length();
    Matrix c = Matrix(length);
    
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            c.setElement(i, j, a.getElement(i, j) + b.getElement(i, j));
        }
    }
    
    return c;
}

Matrix operator- (const Matrix a, const Matrix b)
{
    short length = a.length();
    Matrix c = Matrix(length);
    
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            c.setElement(i, j, a.getElement(i, j) - b.getElement(i, j));
        }
    }
    
    return c;
}

Matrix operator* (const Matrix a, const Matrix b)
{
    short length = a.length();
    Matrix c = Matrix(length);
    
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            c.setElement(i, j, a.getElement(i, j) * b.getElement(i, j));
        }
    }
    
    return c;
}

short Matrix::length () const
{
	return dimensions;
}

void Matrix::fillRandom ()
{
    struct timeb time;
    ftime(&time);
    
    srand(time.millitm);

	assert(data);
	for (int i = 0; i < dimensions; i++)
	{
		assert(data[i]);

		for (int j = 0; j < dimensions; j++)
		{
            int r = rand() % 10 + 1;
			data[i][j] = r;
		}
	}
}

Matrix Matrix::subset(short p, short q, short r, short s) const
{
    int t, u;
    
    assert (q - p == s - r);
    
    Matrix m = Matrix(q - p + 1);
    short n = m.length();
    
    t %= n;
    u %= n;
    
    for (int i = p; i <= q; i++)
    {
        for (int j = r; j <= s; j++)
        {
            m.setElement(u, t, data[i-1][j-1]);
        }
    }
    
    m.printMatrix();
    
    return m;
}

void Matrix::printMatrix()
{
    std::cout << "Matrix dimensions: " << dimensions << " by " << dimensions << std::endl;
    std::cout << "Matrix:" << std::endl;
    
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            std::cout << data[i][j] << "    ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

void Matrix::setSubset(short p, short q, short r, short s, const Matrix& source)
{
    short n = source.length();

    for (int i = p; i <= q; i++)
    {
        for (int j = r; j <= s; j++)
        {
            data[i-1][j-1] = source.getElement((i - 1) % n, (j - 1) % n);
        }
    }
}

void Matrix::setElement(short i, short j, short newVal)
{
    data[i][j] = newVal;
}

short Matrix::getElement(short i, short j) const
{
    return data[i][j];
}