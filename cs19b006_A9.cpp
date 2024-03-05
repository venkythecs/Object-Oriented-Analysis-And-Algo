#include <cmath>
#include <cstdio>
#include <climits>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

class Convert{
    private:
    int **T;            //This graph shows which of the colours are adjacent
    float **G;          //adjacency matrix of the exchange rates
    int *nc;            //This array stores currency colour of the nth country
    int N;              //Number of currencies
    int C;              //Number of colours
    public:
    void makenullT(int);
    void makenullG(int);
    void createT(int);
    void createG();
    void printT();
    void printG();
    void longest(int,int,int);
    void des();
};

void Convert::makenullT(int a){
    C = a;
    
    T = new int*[C];            //allocating memory for adjacency matrix T and initializing diagonal elements to 1//
    for(int i=0;i<C;i++){
        T[i] = new int[C]();
        T[i][i] = 1;
    }
    
}
void Convert::makenullG(int a){
    N = a;
    nc = new int[N];            //allocating memory for adjacency matrix of G and array nc
    G = new float*[N];
    for(int i=0;i<N;i++){
        G[i] = new float[N]();
    }
}

void Convert::des(){
    delete[] nc;
    delete[] T;
    delete[] G;
}

void Convert::createT(int m){
    int u,v;
    for(int i=0;i<m;i++){      //storing the input values in adj matrix of T
        cin>>u>>v;
        T[u][v]=1;
        T[v][u]=1;
    }
}

void Convert::createG(){
    int col;
    for(int i=0;i<N;i++){     //Storing colours of corresponding currency in nc
        cin>>col;
        nc[i] = col;
    }
    float a;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>a;             //Storing the input values as negative logarithm//
            G[i][j]=a;          //as we need the longest path and multiply required edges. keeping negative we find the
            G[i][j]=-log10(G[i][j]);//shortest path and the intermediate additions will turn into multiply because of                                           log        
        }
    }
}

void Convert::longest(int s,int t,int amount){
    vector<float> distances;
    int flag = 0;                           //Using BELLMAN-FORD algorithm//
    for(int i=0;i<N;i++){
        distances.push_back(INT_MAX);      //initializing all the distances from source as infinity
    }
    float result = 0;
    distances.at(s) = 0;        //distance from source to itself is zero
    
     for (int i=0; i<N-1; i++) {
        for (int j=0; j<N; j++) {                   
            int k=0;                        //These for loops for finding shortest paths without cycles//
            while(k<N){                         
                if (T[nc[j]][nc[k]]!=0) {
                    float adddist = distances.at(j)+((G[j][k]));
                    if (distances.at(j)!=INT_MAX && adddist<distances.at(k)) {
                        distances.at(k)=distances.at(j)+((G[j][k]));
                    }
                }
                k++;
            }
        }
    }
    result = distances.at(t);
    
    for(int j=0;j<N;j++){
        int k=0;
        while(k<N){                 //checking if there is any other shorter path
            if(T[nc[j]][nc[k]]!=0){
                float adddist = distances.at(j)+((G[j][k]));
                if (distances.at(j)!=INT_MAX && adddist<distances.at(k)){
                    distances.at(k) = distances.at(j)+G[j][k];
                }
            }
            k++;
        }
    }
    
    if(result>distances.at(t)){
        flag++;         //if there is shorter path that means there is a increasing cycle so flag is incremented//
    }
    
    if(flag!=0){
        cout<<"INF"<<endl;
        return;
    }
    
    else{
    if(result==INT_MAX){  
        cout<<-1<<endl; //if result is not updated then there is no path so print -1//
        return;
    }
   
    else{
        result = (-1)*result;
        result = pow(10,result);      //getting the actual value and multiplying with given amount// 
        result *= amount;
        cout<<fixed<<setprecision(3)<<result<<endl;
    }
    }
    
    return;
    
}

void Convert::printT(){
    for(int i=0;i<C;i++){
        for(int j=0;j<C;j++){
            cout<<T[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void Convert::printG(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main() {
    Convert A;
    int C,m,n,Q;
    cin>>C>>m;
    A.makenullT(C);
    A.createT(m);
    cin>>n;
    A.makenullG(n);
    A.createG();
    //A.printT();
    //A.printG();
    cin>>Q;
    for(int i=0;i<Q;i++){
        int u,v,w;
        cin>>u>>v>>w;
        A.longest(u,v,w);
    }
    A.des();
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}