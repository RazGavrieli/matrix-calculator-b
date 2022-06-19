#pragma once
#include <vector>
#include <iostream>

//using namespace std; // must for student tests 3. 

namespace zich {
class Matrix
{
    std::vector<std::vector<double>> mat;
    unsigned int rows, cols;
 
    double at(unsigned int row, unsigned int col) const;
    
public:
    Matrix(std::vector<double> baseArr, int rows, int cols);
    Matrix(std::vector<std::vector<double>> mat, unsigned int rows, unsigned int cols);
    ~Matrix();
    
    Matrix operator + (Matrix const &other); 
    void operator += (Matrix const &other);
    Matrix operator + ();

    Matrix operator - (Matrix other);
    void operator -= (Matrix const &other);
    Matrix operator - ();

    bool operator > (Matrix const &other);
    bool operator >= (Matrix const &other);
    bool operator < (Matrix const &other);
    bool operator <= (Matrix const &other);
    bool operator == (Matrix const &other);
    friend bool operator == (Matrix const &lhs, Matrix const &rhs); // not correct but needed for student test 2
    bool operator != (Matrix const &other);
    friend bool operator != (Matrix const &lhs, Matrix const &rhs);
    //consider adding a friend !=

    Matrix& operator ++ (); // ++Prefix
    Matrix operator ++ (int); // Postfix++
    Matrix& operator -- (); // --Prefix
    Matrix operator -- (int); // Postfix--

    Matrix operator * (double const &scalar);
    friend Matrix operator * (double const &scalar, Matrix const &other);
    Matrix operator * (Matrix const &other);
    void operator *= (double const &scalar);
    void operator *= (Matrix const &other);


    friend std::ostream& operator << (std::ostream&, Matrix const &other);
    friend void operator >> (std::istream &, Matrix &);



};
}
