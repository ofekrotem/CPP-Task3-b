#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace zich{
    class Matrix{
        public:
            vector<double> data;
            unsigned int cols;
            unsigned int rows;

            Matrix(const vector<double>& data_, const int rows_num, const int cols_num);

            Matrix operator+() const; // +Matrix
            Matrix operator-() const; // -Matrix

            Matrix& operator++(); // ++Matrix
            Matrix& operator--(); // --Matrix

            Matrix operator++(int); // Matrix++
            Matrix operator--(int); // Matrix--

            Matrix operator+(const double) const; // Matrix + double
            Matrix operator-(const double) const; // Matrix - double
            Matrix operator*(const double) const; // Matrix * double

            Matrix operator+(const Matrix&) const; // Matrix + Matrix
            Matrix operator-(const Matrix&) const; // Matrix - Matrix
            Matrix operator*(const Matrix&) const; // Matrix * Matrix

            Matrix& operator+=(const double); // Matrix += double
            Matrix& operator-=(const double); // Matrix -= double
            Matrix& operator*=(const double); // Matrix *= double

            Matrix& operator+=(const Matrix&); // Matrix += Matrix
            Matrix& operator-=(const Matrix&); // Matrix -= Matrix
            Matrix& operator*=(const Matrix&); // Matrix *= Matrix

            Matrix& operator=(const Matrix&); // MatrixA = MatrixB (copy MatrixB into MatrixA)

            bool operator==(const Matrix&) const; // Matrix == Matrix ? True : False
            bool operator!=(const Matrix&) const; //Matrix != Matrix ? True : False
            bool operator>(const Matrix&) const; //Matrix > Matrix ? True : False
            bool operator<(const Matrix&) const; //Matrix < Matrix ? True : False
            bool operator>=(const Matrix&) const; //Matrix >= Matrix ? True : False
            bool operator<=(const Matrix&) const; //MAtrix <= Matrix ? True : False

            void same_size(const Matrix&) const; //simple inner function to check if 2 matrices are the same size
            //(throws an exception if otherwise)
            
            friend ostream& operator<<(ostream&, const Matrix&); //cout << Matrix
            friend istream& operator>>(istream&, Matrix&); //cin >> Matrix

            friend Matrix operator+(const double, Matrix&); //number + Matrix
            friend Matrix operator-(const double, Matrix&); //number - Matrix
            friend Matrix operator*(const double, Matrix&); //number * Matirx

            friend double sum(const Matrix&); // Calculates the sum of the Matrix's values
    };
}