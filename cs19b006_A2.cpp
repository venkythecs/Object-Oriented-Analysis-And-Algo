#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix{
    public:
    void MakeNull(int x,int y);
    void Create();
    void Print();
    int BinarySearch(int x,int k,int l,int r);
    void MatrixSearch(int x);
    protected:
    int **A;
    long int n;
    int m;
};
void Matrix::MakeNull(int x,int y){     //allocating space and initializing n and m//
    n=x;
    m=y;
    A = new int*[n];
    for(int i=0;i<n;i++){
        A[i] = new int[m];
    }
}

void Matrix::Create(){
    for(int i=0;i<n;i++){       //putting values in matrix A//
        for(int j=0;j<m;j++){
            cin>>A[i][j];
        }
    }
}

void Matrix::Print(){
    for(int i=0;i<n;i++){       //function for printing the matrix//
        for(int j=0;j<m;j++){
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }
}
int Matrix::BinarySearch(int val, int k,int left, int right){
        int mid=0;
        int min = A[k][0];
        if(val<min){    //if given value is less than minimum element we return -1//    
            return -1;
        }
        while(right>=left){     //iteration.//
             mid = (right+left)/2;       
            if(A[k][mid] <= val){       //if midlle elemnt is less than val we check the next element and proceed                                                   accordingly//
                if(A[k][mid+1]>val){
                    return mid;
                }
                else{
                    left= mid+1;
                }
            }
            else{
                right = mid-1;
            }
        }
        return mid;
}

void Matrix::MatrixSearch(int x){
    int flag = 0; //initializing helping variable flag to zero//
    for(int i=0;i<n;i++){
        if(flag!=0){
            break;
        }
        for(int j=0;j<m;j++){
            if(A[i][j]==x){             //if x is found we print and increment flag and break from loop// 
                cout<<i<<" "<<j<<endl;
                flag++;
                break;
            }
        }
    }
    if(flag==0){            //if flag is zero the val does not exist and print -1//
        cout<<-1<<" "<<-1<<endl;
    }
}
//--------------------------End of Matrix class-------------------------------//
class MatrixMedian : public Matrix{
    public:
   int UpperBound(int x,int k){
         int bs = BinarySearch(x,k,0,m-1);
        if(bs<m){
            return bs+1;    //we find binary search and add 1 to find upperbound//
        }
        else{
            return -1;
        }
    }
    
    int Median(){
        int min = A[0][0];
        int max= A[0][m-1];
        for(int i=1;i<n;i++){
            if(A[i][0]<min){
                min = A[i][0];
            }
            if(A[i][m-1]>max){
                max = A[i][m-1];
            }
            
        }
        
        int d = (n*m+1)/2;
        while(min<max){
            int mid = min + (max-min)/2;
            int sum =0;
            for(int i=0;i<n;i++){
                sum+=UpperBound(mid,i);   
            }
            if(sum<d){
                min = mid+1;
            }
            else{
                max = mid;
            }
        }
        return min;
    }
};
//-----------------------------End Of MATRIX MEDIAN Class-----------------------//

int main() {
   
    MatrixMedian M;
    int r,c;        //r and c are n and m respectively//
    int Q;
    string s;
    cin>>r>>c;
    M.MakeNull(r,c);
    M.Create();
    cin>>Q;
    for(int i=0;i<Q;i++){       //reading input as string and compare with corresponding strings//
        cin>>s;
        if(s=="BS"){
            int x,k;
            cin>>x>>k;
            cout<<M.BinarySearch(x,k,0,c-1)<<endl;
        }
        if(s=="MS"){
            int k;
            cin>>k;
            M.MatrixSearch(k);
        }
        if(s=="Median"){
            cout<<M.Median()<<endl;
        }
    }
    return 0;
}