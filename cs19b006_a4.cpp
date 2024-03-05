#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

template <typename T> 
class Vector{
    private:
    size_t capacity;
    size_t currentsize;
    T* vec;
    public:
    Vector(size_t c);    
    Vector(size_t c,T x);
    Vector();
    void print();
    size_t Capacity();
    size_t size();
    void push(T x);
    void pop();
    T front();
    T back();
    T operator[](size_t i);
    void sort(size_t,size_t);
    void destructor();
    protected:
    int partition(size_t,size_t);
};

    template <typename T> 
    Vector<T>::Vector(size_t c){            //constructor functions depending on num of arguements//
        capacity = c;
        currentsize = 0;
        vec = new T[capacity];
    }
    
    template <typename T>
    Vector<T>::Vector(size_t c,T x){
        capacity = c;
        currentsize = 0;
        vec = new T[capacity];
        for(size_t i=0;i<capacity;i++){
            vec[i] = x;
            currentsize++;
        }
    }
    
    template <typename T>
    Vector<T>::Vector(){
        capacity = 1;
        currentsize=0;
        vec = new T[capacity];
    }
    template <typename T>
    size_t Vector<T>::Capacity(){       //This function returns the capacity of vector//
        return capacity;
    }
    
    template <typename T>
    size_t Vector<T>::size(){           //returns current size//
        return currentsize;
    }
    
    template <typename T>
    void Vector<T>::print(){
        for(size_t i=0;i<currentsize;i++){      
            cout<<vec[i]<<" ";
        }
    }
    template <typename T>
    void Vector<T>::push(T x){
        if(currentsize == capacity){            //if current size is eq to capacity vector is full//
        T* arr = new T[capacity];               //copy elements into temporary array//
        for(size_t i=0;i<currentsize;i++){      
            arr[i] = vec[i];
        }
        delete[] vec;                           //delete vector and create new vector with double capacity//
        capacity *= 2;
        vec = new T[capacity];
        for(size_t i=0;i<currentsize;i++){      //copy contents from temp array and then delete temp array//
            vec[i]=arr[i];
        }
            delete[] arr;
        }
        vec[currentsize]=x;                     //push new element and increase current size//
        currentsize++;
        
        
    }
    
    template <typename T>
    void Vector<T>::pop(){
        currentsize--;
    }
    
    template <typename T>
    T Vector<T>::front(){               //if vector is empty return -1 else return first element//
        if(currentsize==0){
            return -1;
        }
        else return vec[0];
    }
    
    template <typename T>
    T Vector<T>::back(){
        if(currentsize==0){             //similar to front() but returns last element//
            return -1;  
        }
        else return vec[currentsize-1];
    }

    template <typename T>
    T Vector<T>::operator[](size_t i){
        if(i>=currentsize){           
            return -1;
        }                              //returns ith elemennt if its not there returns -1//
        else return vec[i];
    }
    
    template <typename T>
    int Vector<T>::partition(size_t start,size_t end){       
        T pivot = vec[start];             
        T temp;
        size_t index = start;                 //parttion function this function returns the partition index using first                                                   element as pivot//
        
        for(size_t j=start+1;j<=end;j++){
            if(vec[j]<pivot){
                index++;
                temp = vec[index];
                vec[index]=vec[j];
                vec[j]=temp;
            }
        }
        temp=vec[index];
        vec[index]=vec[start];
        vec[start]=temp;
        return index;
        
    }

    template <typename T>
    void Vector<T>::sort(size_t start,size_t end){
        if(end>start){
            size_t pi = partition(start,end);
            if(pi!=0){
                sort(start,pi-1);
            }
            sort(pi+1,end);
        }
    }

     template <typename T>
    void Vector<T>::destructor(){
        delete[] vec;
    }
int main() {
    int Q;
    
    string s,r;
    Vector<int> v;
    getline(cin,s);
    int len = s.size();
    int k = 6;
    int num1=-1,num2=-1;
    
    while(k<len){                       //INPUT//
        if(s[k]==' '){
            k++;
            if(k>=len) break;
            num1=0;
            while(k<len && s[k]!=' '){
                num1 = num1*10 + s[k]-'0';
                k++;
            }
            if(k<len){
                k++;
                num2=0;
                while(k<len){
                    num2 = num2*10 + s[k]-'0';
                    k++;
                }
            }
        }
        k++;
    }
    
    if(num1==-1 && num2==-1){
        v = Vector<int>(); 
    }
    else if(num1!=-1 && num2==-1){
        v = Vector<int>(num1);
    }
    else{
        v = Vector<int>(num1,num2);
    }
    cin>>Q;
    for(int i=0;i<Q;i++){
        cin>>r;
        if(r=="push"){
            int x;
            cin>>x;
            v.push(x);
        }
        if(r=="pop"){
            v.pop();
        }
        if(r=="front"){
            cout<<v.front()<<endl;
        }
        if(r=="back"){
            cout<<v.back()<<endl;
        }
        if(r=="size"){
            cout<<v.size()<<endl;
        }
        if(r=="capacity"){
            cout<<v.Capacity()<<endl;
        }
        if(r=="sort"){
            v.sort(0,v.size()-1);
            v.print();
            cout<<endl;
        }
        if(r=="element"){
            size_t j;
            cin>>j;
            cout<<v[j]<<endl;
        }
    }
    
    v.destructor();
    
    
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
