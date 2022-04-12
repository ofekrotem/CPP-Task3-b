#include "Matrix.hpp"
#include <stdexcept>

using namespace std;
using namespace zich;

//Constructor
Matrix::Matrix(const vector<double>& data_, const int rows_num, const int cols_num){
    //Checks if the rows and columns values are Non-negative
    if (rows_num <= 0 || cols_num <= 0){
        throw invalid_argument("Enter Non negative Rows_num and Cols_num!");
    }
    //Checks if the rows and columns values match the vector's size
    if (rows_num * cols_num != data_.size()){
        throw invalid_argument("(Rows x Columns) do not match the data size!");
    }
    this->data = vector<double>(data_);
    this->rows = (unsigned int)rows_num;
    this->cols = (unsigned int)cols_num;
}

//Calculates the sum of values
double zich::sum(const Matrix& matrix){
    double sum = 0;
    for (unsigned int i = 0; i < matrix.data.size(); i++){
        sum += matrix.data[i];
    }
    return sum;
}

//Checks if they are the same size
void Matrix::same_size(const Matrix& matrix) const{
    if ( cols != matrix.cols|| rows != matrix.rows ){
        throw invalid_argument("Matrices are not the same size!");
    }
}

//Unaric plus does nothing
Matrix Matrix::operator+() const{

    return *this;
}

//Unaric minus
Matrix Matrix::operator-() const{
    
    Matrix minus_mat = Matrix(*this);
    for (unsigned int i = 0; i < minus_mat.data.size(); i++){
        minus_mat.data[i] *= -1;
    }
    return minus_mat;
}

// ++Matrix
Matrix& Matrix::operator++(){
    *this += 1;
    return *this;
} 

// --Matrix
Matrix& Matrix::operator--(){
    *this -= 1;
    return *this;
}

// Matrix++
Matrix Matrix::operator++(int){
    Matrix ans = *this;
    *this += 1;
    return ans;
}

// Matrix--
Matrix Matrix::operator--(int){
    Matrix ans = *this;
    *this -= 1;
    return ans;
}

// Matrix + double
Matrix Matrix::operator+(const double num) const{
    Matrix ans = *this;
    for (unsigned int i = 0; i < ans.data.size(); i++){
        ans.data[i] += num;
    }
    return ans;
}

// Matrix - double
Matrix Matrix::operator-(const double num) const{
    Matrix ans = *this;
    for (unsigned int i = 0; i < ans.data.size(); i++){
        ans.data[i] -= num;
    }
    return ans;
}

// Matrix * double
Matrix Matrix::operator*(const double num) const{
    Matrix ans = *this;
    for (unsigned int i = 0; i < ans.data.size(); i++){
        ans.data[i] *= num;
    }
    return ans;
}

// Matrix + Matrix
Matrix Matrix::operator+(const Matrix& mat) const{
    same_size(mat); // Check if they are the same size - if not will throw exception
    Matrix ans = *this;
    for (unsigned int i = 0; i < ans.data.size(); i++){
        ans.data[i] += mat.data[i];
    }
    return ans;
}

// Matrix - Matrix
Matrix Matrix::operator-(const Matrix& mat) const{
    same_size(mat); // Check if they are the same size - if not will throw exception
    Matrix ans = *this;
    for (unsigned int i = 0; i < ans.data.size(); i++){
        ans.data[i] -= mat.data[i];
    }
    return ans;
}

// Matrix * Matrix
Matrix Matrix::operator*(const Matrix& mat) const{
    if (this->cols != mat.rows){ // Check if the cols of the first matrix equals the rows of the second - else throw exception
        throw invalid_argument("Mat1.cols != Mat2.rows");
    }
    unsigned int newRows = this->rows;
    unsigned int newCols = mat.cols;
    vector<double> vals(newRows * newCols, 0); //create new vector

    for (unsigned int i = 0; i < newRows; i++){ //run on rows
        for (unsigned int j = 0; j < newCols; j++){ //run on cols
            for (unsigned int k = 0; k < this->cols; k++){ //run on Mat1 cols
                vals[i * newCols + j] += (this->data[i * cols + k] * mat.data[k * mat.cols + j]);
            }
        }
    }

    return Matrix(vals,(int)newRows,(int)newCols); //return the new matrix
}

// Matrix += double
Matrix& Matrix::operator+=(const double num){
    *this = *this + num;
    return *this;
}

// Matrix -= double
Matrix& Matrix::operator-=(const double num){
    *this = *this - num;
    return *this;
}

// Matrix *= double
Matrix& Matrix::operator*=(const double num){
    *this = *this * num;
    return *this;
}

// Matrix += Matrix
Matrix& Matrix::operator+=(const Matrix& mat){
    *this = *this + mat;
    return *this;
}

// Matrix -= Matrix
Matrix& Matrix::operator-=(const Matrix& mat){
    *this = *this - mat;
    return *this;
}

// Matrix *= Matrix
Matrix& Matrix::operator*=(const Matrix& mat){
    *this = *this * mat;
    return *this;
}

// Matrix = Matrix (copy)
Matrix& Matrix::operator=(const Matrix& matrix){
    this->data = vector<double>(matrix.data);
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    return *this;
}

// Matrix == Matrix ? True : False
bool Matrix::operator==(const Matrix& mat) const{
    same_size(mat); // Check if they are the same size
    for (unsigned int i = 0; i < data.size(); i++){
        if (this->data[i] != mat.data[i]){
            return false;
        }
    }
    return true;
}

// Matrix != Matrix ? True : False
bool Matrix::operator!=(const Matrix& mat) const{
    return !(*this == mat);
}

// Matrix > Matrix (compare by sum) ? True : False
bool Matrix::operator>(const Matrix& mat) const{
    same_size(mat);
    return (sum(*this) > sum(mat));
}

// Matrix < Matrix (compare by sum) ? True : False
bool Matrix::operator<(const Matrix& mat) const{
    same_size(mat);
    return (sum(*this) < sum(mat));
}

// Matrix >= Matrix
bool Matrix::operator>=(const Matrix& mat) const{
    same_size(mat);
    return (*this>mat || *this == mat);
}

// Matrix <= Matrix
bool Matrix::operator<=(const Matrix& mat) const{
    same_size(mat);
    return (*this < mat || *this == mat);
}

// Matrix to string function
ostream& zich::operator<<(ostream& os, const Matrix& mat){
    for (unsigned int i = 0; i < mat.rows; i++){
        os << "["; // New row
        for (unsigned int j = 0; j < mat.cols; j++){
            os << mat.data[i * mat.cols + j];
            if (j + 1 < mat.cols){ // Add space after value
                os << " ";
            }
        }
        os << "]"; // End of row
        if (i + 1 < mat.rows){ // New line
            os << endl;
        }
    }
    return os;
}

istream& zich::operator>>(istream& is, Matrix& mat){
    string input;
    getline(is, input);
    unsigned int cols = 0;
    unsigned int rows = 0;
    unsigned int curCols = 0;
    bool flag = true;
    unsigned int i = 0;
    vector<double> vals = {};
    while (i < input.length() - 1)
    {
        // Must start with "["
        if (input[i] != '['){
            throw invalid_argument("Invalis Pattern");
        }
        while (input[i++] != ']')// Run on row
        {
            string val;
            while (input[i] != ' ' && input[i] != ']')
            {
                val += input.at(i++);
            }
            try{vals.push_back(stod(val));}
            catch (invalid_argument e){
                throw invalid_argument("Blank spaces and/or special characters");
            }
            cols++;
        }
        if (flag) // True if it's the first iteration
        { 
            curCols = cols;
            flag = false;
        } else if (cols != curCols){
            throw invalid_argument("Rows don't have the same number of values");
        }
        rows++;
        cols = 0;
        if (i < input.length() - 1) {
            if (input[i] != ',' || input[i+1] != ' '){throw invalid_argument("Invalid Pattern");}
            i += 2;
        }
    }
    mat = Matrix(vals, (int)rows, (int)curCols);
    return is;
}

// double + Matrix
Matrix zich::operator+(const double num, Matrix& mat){
    return mat + num;
}

// double - Matrix
Matrix zich::operator-(const double num, Matrix& mat){
    return -(mat - num);
}

// double * Matrix
Matrix zich::operator*(const double num, Matrix& mat){
    return mat * num;
}