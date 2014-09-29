#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
	Matrix (short n);
    ~Matrix ();
    Matrix (const Matrix& source);
    friend Matrix operator+ (const Matrix a, const Matrix b);
    friend Matrix operator- (const Matrix a, const Matrix b);
    friend Matrix operator* (const Matrix a, const Matrix b);
    void operator= (const Matrix& source);
    
	short length () const;
	void fillRandom ();
    Matrix subset(short p, short q, short r, short s) const;
    void setSubset(short p, short q, short r, short s, const Matrix& source);
private:
    void setElement(short i, short j, short newVal);
    short getElement(short i, short j) const;
    
	short ** data;
	short dimensions;
};

#endif