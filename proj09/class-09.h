#ifndef SPARSE_MATRIX
#define SPARSE_MATRIX
#include<vector>
using std::vector;
#include<map>
using std::map;
using std::pair;
#include<string>
using std::string;
#include<iostream>
using std::ostream;
#include<initializer_list>
using std::initializer_list;
class SparseMatrix{
    private:
        pair<long,long> dimension_ = {0,0};
        map<pair<long,long>,long> matrix_map;
    //    long default_value = 0;

    public:
        //constructors
        SparseMatrix(long x, long y) {dimension_ = {x,y};};
        SparseMatrix(long x,long y,initializer_list<long> z_list);
   
        //getters
        long get_rows() const {return dimension_.first; };
        long get_cols() const {return dimension_.second;};
        pair<long,long> get_size() const {return dimension_;};
       
        //setters
        void set(long r, long c, long v);
        
        //members
        long operator()(const long row, const long col) const; 
        long element_count() {return matrix_map.size();}; 
        pair<long,long> dimensions() {return dimension_;};
        SparseMatrix operator+(long rhs);
        SparseMatrix operator+(const SparseMatrix & rhs);
        SparseMatrix operator*(long rhs);
        SparseMatrix operator*(const SparseMatrix & rhs);
        //friends
        friend ostream &operator<<(ostream& out, const SparseMatrix& matrix);        
        friend SparseMatrix operator+(long lhs, const SparseMatrix & rhs);
        friend SparseMatrix operator*(long lhs, const SparseMatrix & rhs);
};

ostream &operator<<(ostream& out, const SparseMatrix& matrix);
SparseMatrix operator+(long lhs, const SparseMatrix & rhs);
SparseMatrix operator*(long lhs, const SparseMatrix & rhs);
#endif
