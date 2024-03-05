#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int min(int a,int b,int c){      //function to find minimum of three integers
    return min(min(a,b),c);
}

class EDD{
    private:    
    string s1;
    string s2;
    int **matrix;
    int flag1=0;                    //flag1 to check if assign is done
    int flag2=0;                    //flag2 to check if matrix is created
    int len1;                       //lenght of string1
    int len2;                       //length of string2
    int distance;                   //number of edits to make strings equal
    public:
    void assign(string,string);
    void compdist();
    int dist();
    void table();
    void des();
};

void EDD::des(){
    
    delete[] matrix;
}


void EDD::assign(string a,string b){
    s1 = a;                         //assigning strings to s1 and s2 and getting their length//
    s2 = b;
    len1 = s1.size();
    len2 = s2.size();
    flag1 = 1;
    flag2=0;
}

void EDD::compdist(){
    if(flag1==0){                   //if not assigned throwing error message
        throw "strings not found!";
    }
    matrix = new int*[len1+1];      //allocating memory for matrix 2d array
    for(int i=0;i<len1+1;i++){
        matrix[i] = new int[len2+1];
    }
    
    for(int i=0;i<=len1;i++){
        for(int j=0;j<=len2;j++){
            if(j==0){
                matrix[i][j] = i;
            }
            else if(i==0){
                matrix[i][j] = j;
            }
            else if(s1[i-1]==s2[j-1]){
                matrix[i][j] = matrix[i-1][j-1];
            }
            else{
                matrix[i][j] = 1 + min(matrix[i][j-1],matrix[i-1][j],matrix[i-1][j-1]);
            }
        }
    }
    flag2++;
}

int EDD::dist(){
    if(flag2==0){           //if matrix not created using compdist() function
        compdist();
    }
    distance = matrix[len1][len2];
    int ans = distance;
    return ans;
}

void EDD::table(){
    if(flag2==0){
        compdist();
    }
    for(int i=1;i<len1+1;i++){          //printing matrix
        for(int j=1;j<len2+1;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int que;
    string a,b,s;
    cin>>que;
    EDD E;
    
    for(int i=0;i<que;i++){
        cin>>s;
        if(s=="assign"){
            cin>>a;
            cin>>b;
            E.assign(a,b);
        }
        if(s=="compdist"){
            try{
                E.compdist();
            }
            
            catch(string message){
                cerr<<message<<endl;
            }
        }
        if(s=="dist"){
            try{
            int ans = E.dist();
            cout<<ans<<endl;
            }
            
            catch(string message){
                cerr<<message<<endl;
            }
        }
        if(s=="table"){
            try{
            E.table();
            }
             catch(string message){
                cerr<<message<<endl;
            }
        }
    }
    
    E.des();
    
    return 0;
}
