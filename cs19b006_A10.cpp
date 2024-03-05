#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct node{
    int revealed;           //Each node has 3 parameters revealed=1 if the tile is already revealed,mine=1 if there is 
    int mine;               //mine in that tile, neighbours is how many mines are there in its neighbourhood//
    int neighbour;
};
class MSweep{
  private:
    node **Grid;
    int numrev;         //No. of tiles revealed so far//
    int size;
    int no_of_mines;
  public:
    void Putmines();
    void makenull(int,int);
    void Game();
    void des();
};
void MSweep::makenull(int n,int m){
    size = n;               
    no_of_mines = m;
    numrev = 0;
    
    Grid = new node*[n];
    for(int i=0;i<size;i++){                //allocating memory and initialising all nodes to 0//
        Grid[i] = new node[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            Grid[i][j].mine = 0;
            Grid[i][j].revealed=0;
            Grid[i][j].neighbour=0;
        }
    }
}

void MSweep::Putmines(){
    int pos;
    int row;
    int col;
    for(int i=0;i<no_of_mines;i++){
        cin>>pos;
        row = pos/size;                 //placing mine at given node//
        col = pos%size;
        Grid[row][col].mine=1;
        
        for(int i=max(0,row-1);i<=min(size-1,row+1);i++){
        for(int j=max(0,col-1);j<=min(size-1,col+1);j++){       //adding 1 to the node parameter (neighbour) of                                                                             neighbours//
            if(Grid[i][j].mine!=1){
                Grid[i][j].neighbour += 1;
            }
        }
    }
    }
    
}



void MSweep::Game(){                //starting the game//
    int row,col;
    int result = 0;
    while(result==0 && cin>>row>>col){      //reading until a result is acheived or input is done//
        
        //cin>>row>>col;
        if((Grid[row][col].mine)==1){
            result++;                       //if there is mine at given location printing lost and breaking//
            cout<<"Lost"<<endl;
            break;
        }
        
        if(Grid[row][col].revealed == 0){
            
        
        Grid[row][col].revealed = 1;
        numrev++;
        if(Grid[row][col].neighbour == 0){
            long long int pos = (row*size)+col;
            queue<long long int> Q;         //creating a queue and pushing the given position if there are no mines in                                                  neighbour//
            Q.push(pos);
        
            while(!Q.empty()){              //iterating until queue is empty//
                int a = Q.front();
                int p = a/size;
                int q = a%size;
            
                Q.pop();                
            
                for(int i=max(0,p-1);i<=min(size-1,p+1);i++){
                    for(int j=max(0,q-1);j<=min(size-1,q+1);j++){
                        if((Grid[i][j].mine==0) && (Grid[i][j].revealed==0)){
                            Grid[i][j].revealed = 1;            //checking neighbours and reveal and increment numrev//
                            numrev++;
                            
                            if((Grid[i][j].neighbour)==0){      //if the neighbour also has no mines arounf it push into
                                long long int num = i*size +j;  //queue//
                                Q.push(num);
                            }
                        }
                    
                    }
                }
            
            }
        }
        }
        if(numrev == size*size - no_of_mines){  //if all tiles revealed then print won and break//
            
            result++;
            cout<<"Won"<<endl;
            break;
            
        }
        else{
            cout<<numrev<<endl;         //printing num of tiles revealed upto now//
        }
    }
}

void MSweep::des(){
    for(int i=0;i<size;i++){
        delete[] Grid[i];
    }
    delete[] Grid;
}

int main() {
    int n,m;
    cin>>n>>m;
    MSweep A;
    A.makenull(n,m);
    A.Putmines();
    A.Game();
    A.des();
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
