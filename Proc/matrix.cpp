#include "matrix.h"
#include <cassert>
#include <cstdlib>
#include <time.h>
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
            c.setElement(i, j, a.getElement(i, j) + b.getElement(i, j));
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
            c.setElement(i, j, a.getElement(i, j) - b.getElement(i, j));
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
	srand(time_t(NULL));

	assert(data);
	for (int i = 0; i < dimensions; i++)
	{
		assert(data[i]);

		for (int j = 0; j < dimensions; j++)
		{
			data[i][j] = rand() % 10 + 1;
		}
	}
}

Matrix Matrix::subset(short p, short q, short r, short s) const
{
    assert (q - p == s - r);
    
    Matrix m = Matrix(q - p);
    
    for (int i = p - 1; i < q - 1; i++)
    {
        for (int j = r - 1; j < s - 1; j++)
        {
            m.setElement(i, j, data[i][j]);
        }
    }
    
    return m;
}

void Matrix::setSubset(short p, short q, short r, short s, const Matrix& source)
{
    short n = source.length();
    
    for (int i = p - 1; i < q - 1; i++)
    {
        for (int j = r - 1; j < s - 1; j++)
        {
            data[i][j] = source.getElement(i % n, j % n);
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