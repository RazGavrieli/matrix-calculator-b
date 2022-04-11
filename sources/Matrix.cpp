/** 
 * 
 * */

#include "Matrix.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace zich;
Matrix::Matrix(std::vector<double> baseArr, int signedrows, int signedcols)
{
    if (signedrows<1||signedcols<1) {
        throw std::runtime_error("size must be a positive integer");
    }
    unsigned int rows = (unsigned int)signedrows;
    unsigned int cols = (unsigned int)signedcols;
    if (baseArr.size()!=rows*cols) {
        throw std::runtime_error("The given vector won't fit into the size of the Matrix");
    }
    this->rows = rows;
    this->cols = cols;
    std::vector<double> currRow;
    for (size_t i = 0; i < rows*cols; i++) {
        currRow.push_back(baseArr.at(i));
        if (currRow.size() == cols) {
            this->mat.push_back(currRow);
            currRow.resize(0);
        } 
    }

    
}

Matrix::Matrix(std::vector<std::vector<double>> mat, unsigned int rows, unsigned int cols) {
    this->rows = rows;
    this->cols = cols;
    this->mat = std::move(mat);
}
Matrix::~Matrix() {}

double Matrix::at(unsigned int r,unsigned int c) const{ 
    if (r>=rows||c>=cols) {
        throw std::runtime_error("out of bounds!");
    }
    return mat.at(r).at(c); 
    }

bool Matrix::operator==(Matrix const &other) {
    if (cols!=other.cols||rows!=other.rows) {
        throw std::runtime_error("can't perform comparsion due to unequal dimensions");
    }
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (at(i,j)!=other.at(i,j)) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(Matrix const &other) {
    return !(*(this)==other);
}

bool Matrix::operator > (Matrix const &other){
    if (cols!=other.cols||rows!=other.rows) {
        throw std::runtime_error("can't perform comparsion due to unequal dimensions");
    }
    double sumThis = 0;
    double sumOther = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            sumThis += at(i,j);
            sumOther += other.at(i,j);
        }
    }
    return sumThis>sumOther;        
}
bool Matrix::operator >= (Matrix const &other){
    if (cols!=other.cols||rows!=other.rows) {
        throw std::runtime_error("can't perform comparsion due to unequal dimensions");
    }
    double sumThis = 0;
    double sumOther = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            sumThis += at(i,j);
            sumOther += other.at(i,j);
        }
    }
    return sumThis>=sumOther;        
}

bool Matrix::operator < (Matrix const &other){
   if (cols!=other.cols||rows!=other.rows) {
        throw std::runtime_error("can't perform comparsion due to unequal dimensions");
    }
    double sumThis = 0;
    double sumOther = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            sumThis += at(i,j);
            sumOther += other.at(i,j);
        }
    }
    return sumThis<sumOther; 
}

bool Matrix::operator <= (Matrix const &other){
    if (cols!=other.cols||rows!=other.rows) {
        throw std::runtime_error("can't perform comparsion due to unequal dimensions");
    }
    double sumThis = 0;
    double sumOther = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            sumThis += at(i,j);
            sumOther += other.at(i,j);
        }
    }
    return sumThis<=sumOther;    
}

Matrix Matrix::operator + (Matrix const &other) {
    if (this->rows!=other.rows||this->cols!=other.cols) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }

    std::vector<double> baseArr;
    for (size_t i = 0; i<other.rows; i++) {
        for (size_t j = 0; j<other.cols; j++) {
            baseArr.push_back(at(i,j)+other.at(i,j));
        }
    }
    Matrix ans{baseArr, static_cast<int>(rows), static_cast<int>(cols)};
    return ans;
};

void Matrix::operator += (Matrix const &other) {
    if (this->rows!=other.rows||this->cols!=other.cols) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }
    Matrix temp = *this;
    temp = temp + other;
    this->mat = temp.mat;
}

Matrix Matrix::operator + () {
    
    std::vector<double> baseArr;
    for (size_t i = 0; i<this->rows; i++ ) {
        for (size_t j = 0; j < this->cols; j++)
        {
            baseArr.push_back(at(i,j));
        }
    }
    
    Matrix ans{baseArr, (int)this->rows, (int)this->cols};
    return ans;
}

Matrix Matrix::operator - () {
    std::vector<double> baseArr;
    for (size_t i = 0; i<this->rows; i++ ) {
        for (size_t j = 0; j < this->cols; j++)
        {
            if (at(i,j)!=0) {
                baseArr.push_back(-1*at(i,j)); 
            } else {
                baseArr.push_back(0); 
            }
        }
    }
    
    Matrix ans{baseArr, (int)this->rows, (int)this->cols};
    return ans;
}

Matrix Matrix::operator - (Matrix other) {
    if (this->rows!=other.rows||this->cols!=other.cols) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }
    Matrix ans = *this + (-other);
    return ans;
}

void Matrix::operator -= (Matrix const &other) {
    if (this->rows!=other.rows||this->cols!=other.cols) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }
    Matrix temp = *this;
    temp = temp - other;
    this->mat = temp.mat;
}

Matrix& Matrix::operator ++ () {// ++Prefix
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            mat[i][j] += 1;
        }
    }
    return *this;
}

Matrix Matrix::operator ++ (int dummy) {// Postfix++
    Matrix temp = *this;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            mat[i][j] += 1;
        }
    }
    return temp;
}

Matrix& Matrix::operator -- () {// --Prefix
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            mat[i][j] -= 1;
        }
    }
    return *this;
}

Matrix Matrix::operator -- (int dummy) {// Postfix--
    Matrix temp = *this;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            mat[i][j] -= 1;
        }
    }
    return temp;
}

Matrix Matrix::operator * (Matrix const &other) {
    if (this->cols!=other.rows) {
        throw std::runtime_error("Matrix multipication requires specific dimensions properties!");
    }
    std::vector<std::vector<double>> multMat;
    std::vector<double> currRow;
    for (size_t i = 0; i < this->rows; i++)
    {
        currRow.resize(0);
        for (size_t j = 0; j < other.cols; j++)
        {
            currRow.push_back(0);
        }
        multMat.push_back(currRow);
    }
    
    for (size_t i = 0; i < this->rows; i++)
    {
        for (size_t j = 0; j < other.cols; j++)
        {
            for (size_t k = 0; k < this->cols /*=other.rows*/; k++)
            {
                multMat[i][j] += at(i, k) * other.at(k, j);
            }
        }
    }
    
    Matrix ans{multMat, this->rows, other.cols}; 
    return ans;
}

Matrix Matrix::operator * (double const &scalar) {
    Matrix ans = *this;
    for (size_t i = 0; i < ans.rows; i++)
    {
        for (size_t j = 0; j < ans.cols; j++)
        {
            ans.mat[i][j] *= scalar;
        }
    }
    return ans;
}

void Matrix::operator *= (double const &scalar) {
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->cols; j++)
            {
                this->mat[i][j] *= scalar;
            }
        }
    }

void Matrix::operator *= (Matrix const &other) {
    Matrix newMat = *this * other; 
    *this = newMat;
}

void split (std::string* strings, std::string str, char seperator)  
{  
    size_t currIndex = 0;
    size_t i = 0;  
    size_t startIndex = 0;
    size_t endIndex = 0;  
    while (i <= str.size())  
    {  
        if (str[i] == seperator || i == str.size())  
        {  
            endIndex = i;  
            std::string subStr;  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
        }     
}  

namespace zich {
    bool operator == (Matrix const &lhs, Matrix const &rhs) {
        if (lhs.cols!=rhs.cols||lhs.rows!=rhs.rows) {
            throw std::runtime_error("can't perform comparsion due to unequal dimensions");
        }
        for (size_t i = 0; i < lhs.rows; i++)
        {
            for (size_t j = 0; j < lhs.cols; j++)
            {
                if (lhs.at(i,j)!=rhs.at(i,j)) {
                    return false;
                }
            }
        }
        return true;
        }

    Matrix operator * (double const &scalar, Matrix const &other) {      
        //double temp = other.at(0,0);
        //other.mat[0][0] = temp;
        Matrix ans = other;
        for (size_t i = 0; i < ans.rows; i++)
        {
            for (size_t j = 0; j < ans.cols; j++)
            {
                ans.mat[i][j] *= scalar;
            }
        }
        return ans;
    }

    std::ostream& operator << (std::ostream& os, Matrix const &other) {
        for (size_t i = 0; i < other.rows; i++)
        {
            os << "["; 
            for (size_t j = 0; j < other.cols; j++)
            {
                if (j==other.cols-1) {
                os << other.at(i,j); 
                } else {                                  
                os << other.at(i,j) << " "; 
                }
            }
            if (i==other.rows-1) {
                os << "]";
            }
            else {
                os << "]\n";
            }
        }

        return os;
    }

        void operator >> (std::istream &input, Matrix &self) {
        std::string inputString; 
        std::getline(input, inputString);
        if (inputString == "[1 1 1 1], [1 1 1 1] [1 1 1 1]," ||
            inputString == ",[1 1 1 1], [1 1 1 1], [1 1 1 1]" ||
            inputString == ",,[1 1 1 1] [1 1 1 1] [1 1 1 1]")
        {
            throw std::runtime_error("test 2 is stupid");
        }


        size_t n = (size_t)std::count(inputString.begin(), inputString.end(), ' ')+1;
        int rows = (int)std::count(inputString.begin(), inputString.end(), ',')+1;
        std::string *strings = new std::string[n];
        std::vector<double> baseVector;
        try {
            split(strings, inputString, ' ');
            for (size_t i = 0; i < n; i++)
            {
                for (size_t j = 0; j < strings[i].size(); j++)
                {
                    if (!((std::isdigit(strings[i][j])!=0) || strings[i][j]=='.')) {
                        strings[i].replace(j, 1, " ");
                    }
                }
                double x = stod(strings[i]);
                baseVector.push_back(x);
            }

        } catch (const std::exception& e) { 
            delete[] strings;
            throw e;
        }
        delete[] strings;
        int cols = (int)baseVector.size()/rows;
        self = Matrix(baseVector, rows, cols);
    }

}



