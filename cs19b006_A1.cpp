#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef int mat;
class Matrix{               //Constructing a Matrix class with the following functions//
public:
    void Construct(int a,int i,int j);
    void Display(int n);
    void SPSUM(int n);
    long long int MOD(int n);
    void MRS(int k,int n,mat m2[50][50]);
    void MADD(int x,int n,mat m2[50][50]);
    int M[50][50];
};

void Matrix::Construct(int a,int i,int j){  //inserts given integer at given place of matrix M//
    M[i][j] = a;    
}

void Matrix::Display(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Matrix::SPSUM(int n){
    int temp = 0;
    int tm[50][50];
    for(int i=0;i<n;i++){           //Duplicating matrix M into a temporary matrix tm//
        for(int j=0;j<n;j++){
            tm[i][j]= M[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){       //swapping i,jth term with j,ith term if i+j is odd//
            if((i+j)%2 !=0 ){
                temp=tm[i][j];
                tm[i][j]=tm[j][i];
                tm[j][i]=temp;
            }
        }
    }
    
    for(int i=0;i<n;i++){
        int sum=0;
        for(int j=0;j<n;j++){       //Calculating the sum of rows//
            sum+=tm[i][j];
        }
        cout<<sum;
        if(i==n-1){cout<<endl;}
        else{cout<<",";}
    }
}

long long int Matrix::MOD(int n){
    int result[50];                 //Creating an array for storing the result of each row//
    for(int i=0;i<n;i++){
        if(i%3 == 0){
            int max=-1000;
            for(int j=0;j<n;j++){   //Finding max element in a row if i is divisible by 3//    
                if(M[i][j]>max){
                    max = M[i][j];
                }
            }
            result[i] = max;
        }
        else if(i%3 == 1){
            int min = 1000; 
            for(int j=0;j<n;j++){   //Finding min elemnt of the row//           
                if(M[i][j]<min){
                    min = M[i][j];
                }
            }
            result[i]=min;
        }
        else{
            int sum=0;
            for(int j=0;j<n;j++){
                sum+=M[i][j];       //Finding sum and subsequently average and storing in result array//
            }
            int avg = sum/n;
            result[i]=avg;
        }
    }
    long long int ans=1;
    for(int i=0;i<n;i++){
        ans*=result[i];             //Computing product of all the element sin result array and returning//
    }
    return ans;
}
void Matrix::MADD(int x,int n,mat B[50][50]){
    int tm[50][50];//temporary matrix//
    int s[50][50];//sum matrix//
    if(x==1){
        for(int i=0;i<n;i++){ 
            for(int j=0;j<n;j++){       //if x=1 tm is transpose of first matrix then we get s by adding tm and B,
                tm[i][j]=M[j][i];       //similarly for x=2 transposing B and adding to get s//
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                s[i][j]=tm[i][j]+B[i][j];
                cout<<s[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    else{
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                tm[i][j]=B[j][i]; 
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                s[i][j]=tm[i][j]+M[i][j];
                cout<<s[i][j]<<" ";
            }
            cout<<endl;
        }
        
    }
}

void Matrix::MRS(int k,int n,mat B[50][50]){
    int C[50][50];//Shifted matrix of first matrix//
    int D[50][50];//Shifted matrix of second matrix//
    int s[50][50];//Sum matrix//
    int ni,nj;//these will be the new values of i and j//
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            nj = (j+k)%n;       //Finding new value of i and j//
            ni = (i+(j+k)/n)%n;
            C[ni][nj] = M[i][j];//Forming the matrices C and D//
            D[ni][nj] = B[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            s[i][j] = C[i][j]+D[i][j];//Adding the newly formed matrices//
            cout<<s[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int Q,n,k,x;
    string req;//string for reading the input//
    cin>>Q>>n;
    Matrix A;       //Placing first matrix in class and the other matrix will be sent as arguement for required                                 functions//
    mat B[50][50];
    for(int i=0;i<n;i++){   
        for(int j=0;j<n;j++){   //Constructing first matrix//
            int a;
            cin>>a;
            A.Construct(a,i,j);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){   //Constructing second matrix//    
            cin>>B[i][j];
        }
    }
    for(int i=0;i<Q;i++){   //Reading inputs and calling functions//
        cin>>req;
        if(req == "SPSUM"){
            A.SPSUM(n);
        }
        else if(req == "MOD"){
           cout<<A.MOD(n)<<endl;
        }
        else if(req == "MRS"){
            cin>>k;
            A.MRS(k,n,B);
        }
        else if(req == "MADD"){
            cin>>x;
            A.MADD(x,n,B);
        }
    }
    return 0;
}