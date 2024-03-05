#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <queue>
#include <climits>

using namespace std;

template<typename T>
class Graph{
    private:
    int V;
    vector<pair<T,int>> *Adj;       //considering adjacency list as an array of vectors// 
    public:
    //typedef T value_type;
    void makeNull(int );
    void AddV();
    void AddE(int,int,T);
    void DelE(int,int);
    void BFS(int);
    void SSP(int );
    void des();
    
};

template<typename T>
void Graph<T>::makeNull(int n){
    V = n;
    Adj = new vector<pair<T,int>> [V];      //allocating memory for the adjacency list//
}

template<typename T>
void Graph<T>::des(){
    delete [] Adj;
}

template<typename T>
void Graph<T>::AddE(int a,int b,T w){
    if(a>=V||b>=V||a<0||b<0){
        cerr<<"invalid arguements\n";
    }
    pair<T,int> e;
    e.second = b;
    e.first = w;
    int flag = 0;                   //flag for indicating if the edge is added//
    for(auto i=Adj[a].begin();i!=Adj[a].end();i++){
    if(i->first>e.first) {              //adding edge in sorted order with their respective weights//
    Adj[a].insert(i,e);                 //if new edge is less than weight then insert else keep linearly search//
    flag++;                             //once edge is added we break from the loop//
    break;
    }
    else if(i->first == e.first){       //if weight and new edge is equal then then we insert in order of vertex no.//
        if(i->second>e.second){         
            Adj[a].insert(i,e);
            flag++;
            break;
        }
    }
    }
    if(flag==0){
        Adj[a].push_back(e);//if flag is zero then we add the edge at the end of vector//
    }
    
    flag = 0;
    e.second = a;
                        //following similar procedure for second vector//
    for(auto i=Adj[b].begin();i!=Adj[b].end();i++){
    if(i->first >e.first) {   
    Adj[b].insert(i,e);
    flag++;
    break;
    }
    else if(i->first == e.first){
        if(i->second>e.second){
            Adj[b].insert(i,e);
            flag++;
            break;
        }
    }
    }
    if(flag==0){
        Adj[b].push_back(e);
    }
}

template<typename T>
void Graph<T>::AddV(){
    vector<pair<T,int>> *old = new  vector<pair<int,T>> [V];        //creating a duplicate adjacency list// 
    for(int i=0;i<V;i++){
        old[i] = Adj[i];
    }
    V++;
    delete[] Adj;
    Adj = new vector<pair<T,int>> [V];          //creating adjacency list by increasing number of vertices//
    for(int i=0;i<V-1;i++){
        Adj[i] = old[i];                //copying the previous values
    }
    delete[] old;                       //deallocating memory used for the duplicate adjlist//
}

template<typename T>
void Graph<T>::DelE(int a,int b){
    int flag = 0;
    for(auto i=Adj[a].begin();i!=Adj[a].end();i++){
        if(i->second == b){         
            Adj[a].erase(i);            //linearly iterating and if the vertex is found erase and break from the 
            flag++;                     //for loop 
            break;
        }
    }
    
    if(flag==0){
      cerr<<"No such vertex\n";     //if flag=0 then vertex is not found then we put error message i  stderr//
    }
    flag =0;
    
    for(auto i=Adj[b].begin();i!=Adj[a].end();i++){
        if(i->second == a){         
            Adj[b].erase(i);       //following similar procedure for second vertex of the edge// 
            flag++;
            break;
        }
    }
    if(flag==0){
      cerr<<"No such vertex\n";
    }
}

template<typename T>
void Graph<T>::BFS(int a){
    int *visited;
    
    visited = new int[V];       //creating a visited array and intialized to zero//
    for(int i=0;i<V;i++){
        visited[i] = 0;
    }
    queue<int> g;
    visited[a] = 1;            //marking the source as visited and pushing it into the queue//
    g.push(a);
    
    while(!g.empty()){
        int ver = g.front();  //the first element is taken and popped and all its adjacent,unvisited vertices are pushed                                    onto the queue// 
        g.pop();
        cout<<ver<<" ";       //the first element which is popped is printed
        for(auto i=Adj[ver].begin();i!=Adj[ver].end();i++){
            if(visited[i->second]==0){
                g.push(i->second);
                visited[i->second] = 1; //marking the adjacent vertex as visited after its pushed//
            }
        }
    }
   cout<<endl;
}

template<typename T>
void Graph<T>::SSP(int a){
    typedef pair<T,int> p;
    int *visited;           //creating a visited and distance array// //visited array is initialized to zero//
    int *disarr;            //disarr is initialized to int_max//
    disarr = new int[V];
    visited = new int[V];
    for(int i=0;i<V;i++){
        visited[i] = 0;
        disarr[i] = INT_MAX;
    }
    disarr[a] = 0;         //distance between the source and itself is zero//  
    priority_queue<p,vector<p>,greater<p>> g;   //creating a min oredered priority queue//
     p e;
     e.first = 0;
     e.second = a;
    g.push(e);      //pushing the first pair which has weight and source vertex//
    
    while(!g.empty()){
        p r = g.top();          //popping the first pair and marking its vertex as visited//
        int ver = r.second;
        visited[ver] = 1;
        g.pop();
        for(auto i=Adj[ver].begin();i!=Adj[ver].end();i++){
            int u = i->second;
            int wei = i->first;
            int distance = disarr[ver]+wei;
            if(visited[u]==0 && distance <disarr[u]){       //if distance between source to u via ver is less than 
                disarr[u] = distance;                       //direct ditance between source to u then update//
                p m;
                m.second = u;
                m.first = disarr[u];
                g.push(m);
            }
           
        }
    }
    for(int i=0;i<V;i++){
        cout<<disarr[i]<<" ";       //printing the distance array//
    }
    cout<<endl;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin>>n;
    Graph<int> G;
    G.makeNull(n);
    int Q;
    cin>>Q;
    int a,b,w;
    string s;
    for(int i=0;i<Q;i++){
        cin>>s;
        if(s=="ADDE"){
            cin>>a>>b>>w;
            G.AddE(a,b,w);
        }
        if(s=="ADDV"){
            G.AddV();
        }
        if(s=="DELE"){
            cin>>a>>b;
            G.DelE(a,b);
        }
        if(s=="BFS"){
            cin>>a;
            G.BFS(a);
        }
        if(s=="SSP"){
            cin>>a;
            G.SSP(a);
        }
    }
    for(int i=0;i<2;i++){
        cin>>s;
        if(s=="BFS"){
            cin>>a;
            G.BFS(a);
        }
        if(s=="SSP"){
            cin>>a;
            G.SSP(a);
        }
    }
    G.des();
    return 0;
}
