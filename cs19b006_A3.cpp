#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node{
    struct Node* next;
    int data;
};

class Stack{
    private:
    struct Node* tos;
    public:
    void Push(int x);
    int Pop();
    int Top();
    int IsEmpty();
    void dest();
    void Makenull();
};

void Stack::Makenull(){             //Initializing top of stack to null//
    tos = NULL;
}
int Stack::IsEmpty(){               //if tos is null then stack is empty//
    if(tos == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void Stack::Push(int x){
    struct Node* temp;          //creating new temp node and pushing it onto stack and making it top//
    temp = new struct Node;
    temp->data = x;
    temp->next = tos;
    tos = temp;
}

int Stack::Pop(){
    struct Node* temp;          //removing and returning the value of the top of stack//
    if(IsEmpty()==1){
        return -1;
    }
    else{
        temp = tos;
        tos = tos->next;
        temp->next = NULL;
        return temp->data;
    }
}

int Stack::Top(){               //returning the top of stack//
    if(IsEmpty()==1){
        return -1;
    }
    else{
        return tos->data;
    }
}

void Stack::dest(){             //destructor function//
    tos = NULL;
}
//---------------------------------------------------------------------------------------------//

class Graph{
    private:
    int n;
    int **adj;
    public:
    void Construct(int n);
    void operator+=(pair<int, int> addEdge);
    void operator-=(pair<int, int> delEdge);
    int Cyclehelper(int ,int ,int* );
    int detectCycle();
    int Components();
    int reach(int, int);
    void DFS(int a,int arr[]);
};

void Graph::Construct(int m){           //creating an adjacency matrix with all 0//
    n = m;
    adj = new int*[n];
    for(int i = 0;i < n;i++){
          adj[i] = new int[n];
        for(int j = 0;j < n;j++){
            adj[i][j] = 0;
        }
    }
}

void Graph::operator += (pair<int,int>p){
    int u = p.first;
    int v = p.second;                 //adding an edge between u and v//
    if(adj[u][v]!=1){
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
}

void Graph::operator -= (pair<int,int>p){
    int u = p.first;                 //removing the edge btw u and v//
    int v = p.second;
    if(adj[u][v]==1){
        adj[u][v]=0;
        adj[v][u]=0;
    }
}

int Graph::Cyclehelper(int current,int parent,int* visited){
    visited[current] = 1;
    for(int i=0;i<n;i++){
        if(adj[current][i]==1&&i!=parent){
            if(visited[i]==1){
                return 1;
                break;
            }
            else{
               Cyclehelper(i,current,visited);
            }
        }
    }
    return 0;
}

int Graph::detectCycle(){
    int *visited = new int[n];
    for(int i=0;i<n;i++){
        visited[i]=0;
    }
    for(int j=0;j<n;j++){
        if(visited[j]==0){
            if(Cyclehelper(j,-1,visited)==1){
                return 1;
            }
        }
    }
    return 0;
}

void Graph::DFS(int a,int visited[]){
    Stack R;
    R.Makenull();
    R.Push(a);
    while(R.IsEmpty()==0){                      
        int k=R.Top();                              //performing DFS using stack//
        visited[k] = 1;
        int flag = 0;
        int i=0;
        while(i<n){
            if(adj[i][k]==1 && visited[i]==0){
                R.Push(i);
                flag++;
            }
            i++;
        }
        if(flag==0) R.Pop();
                                                     //if flag is 0 then there are no more points which are adjacent
    }                                                //and not visited so we pop and backtrack//   
}

int Graph::reach(int u,int v){
    int *visited = new int[n];          //Applying DFS for u if v is reachable then visited[v] shoild be 1//
    for(int i=0;i<n;i++){
        visited[i] = 0;
    }
    DFS(u,visited);
    return visited[v];
}

int Graph::Components(){
    int *visited = new int[n];
    for(int i=0;i<n;i++){
        visited[i] = 0;
    }
    int num = 0;
    for(int i=0;i<n;i++){
        if(visited[i]==0){
            DFS(i,visited);         //Finding the number of components using DFS//
            num++;
        }
    }
    return num;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    Stack S;
    S.Makenull();
    Graph G;
    string req;
    int x,Q,n,m;
    int u,v;
    pair<int,int>p;
    cin>>Q;
    for(int i=0;i<Q;i++){
        cin>>req;
        if(req == "push"){
            cin>>x;
            S.Push(x);
        }
        else if(req == "top"){
            cout<<S.Top()<<endl;
        }
        else if(req == "pop"){
            cout<<S.Pop()<<endl;;
        }
        else if(req == "empty"){
            cout<<S.IsEmpty()<<endl;
        }
    }
    cin>>n;
    cin>>m;
    G.Construct(n);
    for(int i=0;i<m;i++){
        cin>>req;
        if(req == "add"){
            cin>>p.first>>p.second;
            G+=p;
        }
        if(req == "del"){
            cin>>p.first>>p.second;
            G-=p;
        }
        if(req == "cycle"){
            cout<<G.detectCycle()<<endl;
        }
        if(req == "reach"){
            cin>>u>>v;
            cout<<G.reach(u,v)<<endl;
        }
        if(req == "components"){
            cout<<G.Components()<<endl;
        }
    }
    return 0;
}
