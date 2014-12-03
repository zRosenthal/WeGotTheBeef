#include<map>
using std::map;
#include<initializer_list>
using std::initializer_list;
#include<iostream>
using std::ostream; using std::cout; using std::cin; using std::endl;
#include<algorithm>
using std::find;
#include "class-09.h"
//Constructor 3 args
//creates a matrix
//sets dimension 
//iterates through list and adds values to the matrix
SparseMatrix::SparseMatrix(long x, long y, initializer_list<long> z_list) {
    dimension_ = {x,y};
    for(auto it = z_list.begin(); it != z_list.end(); it+=3) {
        matrix_map[{*it,*(it+1)}] = *(it+2);
    }
}
//set matrix as value
void SparseMatrix::set(long r, long c, long v) {
    matrix_map[{r,c}] = v;
} 
//overload () operator
//return value at location row,col in the matrix
long SparseMatrix::operator()(const long row, const long col) const {
    pair<long,long> p = {row,col};
    auto pointer = matrix_map.find(p);
    if(pointer != matrix_map.end()) {
        return pointer->second;
    }
    else if( row >= this -> get_rows()) {
        cout << "Error row-out-of-range: the row you have tried to access exceeds the row index of the matrix" << endl;
        return 0;
    }
    else if(col >= this -> get_cols()) {
        cout << "Error col-out-of-range: the col you have tried to access exceeds the column index of the matrix" << endl;
        return 0;
    }
    else {
        return 0;
    }
};

//overload + operator
//args: long
//add long to every spot in matrix;
SparseMatrix SparseMatrix::operator+(long rhs) {
    SparseMatrix temp(this -> get_rows(),this -> get_cols());
    for(auto it = matrix_map.begin(); it != matrix_map.end(); it++) {
        temp.set(it->first.first,it->first.second,it->second + rhs); 
    }
//    temp.default_value = rhs + default_value;
    return temp;
}

//overload + operator
//args a matrix
//check to make sure dimensions are equal
//instantiate a new matrix 'temp'
//iterate through all rows and colums adding 5 to every entry
SparseMatrix SparseMatrix::operator+(const SparseMatrix & rhs) {
    if(dimension_ == rhs.dimension_) {
        SparseMatrix temp(this -> get_rows(),this -> get_cols());
//        temp.default_value = default_value + rhs.default_value;
        for(auto it = matrix_map.begin(); it != matrix_map.end(); it++) {
            long r = it->first.first;
            long c = it->first.second;
            temp.set(r,c,it->second + rhs(r,c));
        }  
        for(auto it = rhs.matrix_map.begin(); it != rhs.matrix_map.end(); it++) {
            long r = it->first.first;
            long c = it->first.second;
            if(temp.matrix_map.find({r,c}) == temp.matrix_map.end()) {
            temp.set(r,c, it->second );
        }}
    return temp;
}
    else {
        cout << "Error +: to add matricies they must have the same dimensions" << endl;
        return SparseMatrix(0,0);
    }
}
//overload * operator
//args long
//multiply every value in the matrix  by the long 
SparseMatrix SparseMatrix::operator*(long rhs) {
    SparseMatrix temp(this -> get_rows(), this -> get_cols()); 
    //temp.default_value = default_value * rhs;
    for(auto it = matrix_map.begin(); it != matrix_map.end(); it++) {
        long r = it->first.first;
        long c = it->first.second;
        temp.set(r,c, it->second * rhs);       
    }
    return temp;
}

//overload * operator
//args  SparseMatrix
//multiply two SpwarseMatrix and return there product
SparseMatrix SparseMatrix::operator*(const SparseMatrix &rhs) {
    if(this->get_cols() == rhs.get_rows()) {
        SparseMatrix temp(this -> get_rows(), rhs.get_cols()); 
        for(long r = 0; r < temp.get_rows(); r ++) {
            for(long c = 0; c < temp.get_cols(); c++) {
                long sum = 0;
                for(long k = 0; k < rhs.get_rows(); k++) {
                    sum += (matrix_map[{r,k}]*rhs(k,c)); 
                }
                if(sum != 0) {temp.set(r,c,sum);}
            }
        }
        return temp;
    }
    else {
        cout << "Error *: the # of columns in the left-hand matrix must equal the # of rows in the righ-hand matrix" << endl;
        return SparseMatrix (0,0);
    }
}

//overload << operator
//iterates through all rows and cols in matrix and prints out ones that arnt 0
ostream &operator<<(ostream& out, const SparseMatrix& matrix) {
    for(long r = 0; r < matrix.get_rows(); r++) {
        for(long c = 0; c < matrix.get_cols(); c++) {
            if(matrix(r,c)) {
//    for(auto it = matrix.matrix_map.begin(); it != matrix.matrix_map.end(); it++) {
        out << "(" << r << "," << c << ") --> " 
            << matrix(r,c) << endl;
            }
            }}   
    return out;
}

//friend function - overload + operator
//Args : long , sparsematrix
SparseMatrix operator+(long lhs, const SparseMatrix & rhs) {
    SparseMatrix temp(rhs.get_rows(),rhs.get_cols());
    //temp.default_value = rhs.default_value + lhs;
    for(auto it = rhs.matrix_map.begin(); it != rhs.matrix_map.end(); it++) {
        temp.set(it->first.first,it->first.second, it->second + lhs);
    }
    return temp;
}

//friend function overload * operator
// perform scalar multiplication mulitplying every entry in rhs by lhs
//return the new matrix
SparseMatrix operator*(long lhs, const SparseMatrix & rhs) {
     SparseMatrix temp(rhs.get_rows(), rhs.get_cols()); 
   // temp.default_value = rhs.default_value * lhs;
    for(auto it = rhs.matrix_map.begin(); it != rhs.matrix_map.end(); it++) {
        long r = it->first.first;
        long c = it->first.second;
        temp.set(r,c, it->second * lhs);       
    }
    return temp;
}   

