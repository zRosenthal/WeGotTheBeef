#include<iostream>
using std::cout; using std::endl;
#include<initializer_list>
using std::initializer_list;
#include<stdexcept>
using std::runtime_error;
#include "class-09.h"

int main (){
    SparseMatrix mat(5,5);
    cout << "Default Val:"<< mat(2,2) << endl;
    // mat(2,2) = 10;
    mat.set(2,2,100);
    cout <<"Set val:"<< mat(2,2) << endl;
    auto p = mat.dimensions();
    cout << "Dimensions:"<<p.first<<" by "<<p.second<<", Non Zero Count:"<<mat.element_count()<<endl;
    
    SparseMatrix ident(5,5,{0,0,1,
			    1,1,1,
			    2,2,1,
			    3,3,1,
		            4,4,1});
    cout << "Ident(0,0): "<<ident(0,0) <<", Ident(4,4):"<< ident(4,4)<<", count:"
	 <<ident.element_count()<<endl;
    cout << "Ident "<<ident << endl;

    SparseMatrix temp(5,5);
    temp = ident + 5;
    cout << "ident + 5:"<<temp << endl;
    temp = 5 + ident;
    cout << "5 + ident:"<<temp << endl;
    cout << "mat: " << endl << mat << endl;
    cout << "ident: " << endl << ident << endl;
    temp = mat + ident;
 
    cout <<"mat + ident:"<< temp << endl;

    temp = ident * 5;
    cout << "ident * 5:"<<temp << endl;
    temp = 5 * ident;
    cout << "5 * ident:"<<temp << endl;
    temp = mat * ident;
    cout <<"mat * ident:"<< temp << endl;

    SparseMatrix bad(3,3);
    try{
	temp = bad + ident;
    }
    catch(runtime_error err){
	cout << "Bad add"<<endl;
	cout << err.what() << endl;
    }

    try{
	temp = bad * ident;
    }
    catch(runtime_error err){
	cout << "Bad multiply"<<endl;
	cout << err.what() << endl;
    }
}
