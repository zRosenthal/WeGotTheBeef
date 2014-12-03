#ifndef BISTACK_H
#define BISTACK_H
#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<string>
using std::string; using std::to_string;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream;
#include<algorithm>
using std::transform; using std::copy; using std::fill;
using std::swap;
#include<stdexcept>
using std::runtime_error;
template <typename T>
class BiStack;
template <typename T>
class BiStack {
    private:
        T *bistack_;
        size_t sz_;
        size_t maxsz_;
        size_t top1_;
        size_t top2_;

        void grow_and_copy();
    
    public:
        BiStack(size_t maxsz = 32,size_t sz = 4);
        BiStack(const BiStack &s);
        ~BiStack();
        BiStack& operator=(BiStack);

        T top1();
        T top2();
        
        void pop1();
        void pop2();
        void push1(T);
        void push2(T); 
        
        bool full();
        bool empty1(); 
        bool empty2();
        
        friend ostream& operator<< (ostream &out, const BiStack<T> &s) {
            out << "(end of left stack)";
            copy(s.bistack_, (s.bistack_ + s.top1_), ostream_iterator<T>(out,","));
            out << "(top of left stack)" << endl;
            out << "(top of right stack)";
copy((s.bistack_ + s.top2_+1),(s.bistack_ + s.sz_), ostream_iterator<T>(out,","));
            out << "(end of right stack)" << endl;
            return out;
        }    
};
//Constructor
//args: sz and maxsz
//initialize a new array of size sz
//set sz_ equal to sz and maxsz_ equal to maxsz
//initialize top1 to 0 and top2 to the the size of the deck minus 1
template <typename T>
BiStack<T>::BiStack(size_t sz , size_t maxsz) {
    bistack_ = new T[sz];
    sz_ = sz;
    maxsz_ = maxsz;
    top1_  = 0;
    top2_ = sz -1; 
}
//destructor
//delete bistack
template <typename T>
BiStack<T>::~BiStack() {
    delete []bistack_;
}

//copy
//initialize all private vars to match that of s
//create a new arrary the same size of s
//copy all elements in s into the new bistack
template <typename T>
BiStack<T>::BiStack(const BiStack<T> &s) {
    if (this != &s){ 
        sz_ = s.sz_;
        top1_ = s.top1_;
        top2_ = s.top2_; 
        maxsz_ = s.maxsz_;
        bistack_ = new T[s.sz_];
        copy(s.bistack_, s.bistack_ + s.sz_, bistack_);
    }
}

//overloaded = operator
//args Bistack
//return Bistack
//swap all member variables from s with the ones pointed to by 'this'
template <typename T>
BiStack<T> & BiStack<T>::operator=(BiStack <T> s) {
    swap(sz_, s.sz_);
    swap(top1_, s.top1_);
    swap(top2_, s.top2_);
    swap(maxsz_, s.maxsz_);
    swap(bistack_, s.bistack_);
    return *this;
}

//full
//checks to see if the bistack is full by comparing the top values
//reutnrs true or false
template <typename T> 
bool BiStack<T>::full() {
    return (top1_ > top2_) ? true : false;
} 

template <typename T>
void BiStack<T>::grow_and_copy() {
    if(sz_ < maxsz_) {
        size_t newsz = (2* sz_ <= maxsz_) ? 2*sz_ : maxsz_;
        T* temp = new T[newsz];
        copy(bistack_, bistack_ + top1_ +1, temp);
        copy(bistack_ + top2_ ,bistack_ +  sz_,  temp +newsz - sz_ + top2_);
        swap(bistack_, temp);
        top2_ = top2_ + newsz - sz_;
        sz_ = newsz;
        delete []temp;
    cout << "grow" << endl;    
    }
    else {
        throw runtime_error("Bistack has reached capacity");    
    }
}



//Push1
//arg: elm ( a single element of type T)
//check to see if stack is full
//if it is ot full it pushes a element to the top of the left stack
//if the bistack is full it calls the grow and copy function then pushes the elm
template <typename T>
void BiStack<T>::push1(T elm) {
    if(!(this -> full())) {
            bistack_[top1_++] = elm; 
    }
    else {
        cout << "isfull" << endl;
        this->grow_and_copy();
        bistack_[top1_++] = elm;
    }
}

//Push2
//arg: elm ( a single element of type T)
//check to see if stack is full
//if it is ot full it pushes a element to the top of the right stack
//if the bistack is full it calls the grow and copy function then pushes the elm
template <typename T>
void BiStack<T>::push2(T elm) {
    if(!(this -> full())) {
    bistack_[top2_--] = elm;
    }
    else {

        cout << "isfulL" << endl;
        this->grow_and_copy();
        bistack_[top2_--] = elm;
    }
}

//top1
//return the top of the left side of the bistack
template <typename T>
T BiStack<T>::top1() {
    return bistack_[top1_ - 1];
}


//top2
//return the top of the right side of the bistack
template <typename T>
T BiStack<T>::top2() {
    return bistack_[top2_ +1];
}


template <typename T>
bool BiStack<T>::empty1() {
   return (top1_ == 0) ? true : false; 
}

template <typename T>
bool BiStack<T>::empty2() {
   return (top2_ == sz_ - 1) ? true : false; 
}


template <typename T>
void BiStack<T>::pop1() {
    if(!(this->empty1())) {
        top1_--;
    }  
    else {
        throw runtime_error("Cannot 'pop' from an empty stack");
    } 
}


template <typename T>
void BiStack<T>::pop2() {
    if(!(this->empty2())) {
        top2_++;
    }
    else {
        throw runtime_error("Cannot 'pop' from an empty stack");
    }
}
#endif
