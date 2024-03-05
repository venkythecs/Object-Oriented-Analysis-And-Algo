#include <cmath>
#include <cstdio>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int,int> p;

class Graph{
    protected:
    int V;
    vector<pair<int,int>> *Adj; //considering adjacency list as an array of vectors// 
    public:
    //typedef T value_type;
    void makeNull(int );
    void AddV();
    void AddE(int,int,int);
    void DelE(int,int);
    void des();
    int uptodate=0;
};


void Graph::makeNull(int n){
    V = n;
    Adj = new vector<pair<int,int>> [V];//allocating memory for the adjacency list//
    uptodate=0;
}


void Graph::des(){
    delete [] Adj;
}


void Graph::AddE(int a,int b,int w){
    if(a>=V||b>=V||a<0||b<0){
        cerr<<"invalid arguements\n";
    }
    else{
        uptodate = 1;
    }
    pair<int,int> e;
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


void Graph::AddV(){
    uptodate = 1;
    vector<pair<int,int>> *old = new  vector<pair<int,int>> [V];        //creating a duplicate adjacency list// 
    for(int i=0;i<V;i++){
        old[i] = Adj[i];
    }
    V++;
    delete[] Adj;
    Adj = new vector<pair<int,int>> [V];          //creating adjacency list by increasing number of vertices//
    for(int i=0;i<V-1;i++){
        Adj[i] = old[i];                //copying the previous values
    }
    delete[] old;                       //deallocating memory used for the duplicate adjlist//
}


void Graph::DelE(int a,int b){
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
    else{
        uptodate = 1;
    }
}


class MST : public Graph{
    private:
     priority_queue<p,vector<p>,greater<p>> *sptree;
     int Vtr;
    public:
     void construct(int);
     long long int Prims(int);
     long long int Kruskal();
     int checkcycle(int,int);
     void Display();
     void Treeuptodate();
};

void MST::construct(int v){
    makeNull(v);
    sptree = new priority_queue<p,vector<p>,greater<p>>[v];
    Vtr = v;
}
void MST::Treeuptodate(){
    if(uptodate==0){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
}

int MST::checkcycle(int u,int v){
    vector<int> visited(V,0);
    vector<int> queue;
    visited.at(u) = 1;
    queue.push_back(u);
    while(!queue.empty()){
    auto x = *queue.begin();
    queue.erase(queue.begin());
    
    auto a = sptree[x];
    
    while(!a.empty()){
        auto b = a.top();
        a.pop();
        int ver = b.second;
        
        if(visited[ver]==0){
            visited[ver] =1;
            queue.push_back(ver);
            if(ver == v){
                return 1;
            }
        }
    }
    }
    return 0;
}

long long int MST::Kruskal(){
    Vtr = V;
    sptree = new priority_queue<p,vector<p>,greater<p>>[V];
    long long int mstcost = 0;
    vector<int>visited(V,0); 
    
    priority_queue<pair<int,p>,vector<pair<int,p>>,greater<pair<int,p>>> E;
    for(int i=0;i<V;i++){
        for(auto j=Adj[i].begin();j!=Adj[i].end();j++){
            if(j->second > i){
                p p1;
                p1.first = i;
                p1.second = j->second;
                pair<int,p> p2;
                p2.second = p1;
                p2.first = j->first;
                E.push(p2);
            }
        }
    }
    int flag = 0;
    while(flag<V-1 &&!E.empty()){
        auto a = E.top();
        E.pop();
        int u = a.second.first;
        int v = a.second.second;
        int wei = a.first;
        
        if(checkcycle(u,v)==0){
            p p1,p2;
            p1.first = wei;
            p1.second = u;
            sptree[v].push(p1);
            p2.first = wei;
            p2.second = v;
            sptree[u].push(p2);
            visited.at(u) = 1;
            visited.at(v) = 1;
            mstcost+=wei;
            flag++;
        }
    }
    
    uptodate = 0;
    return mstcost;
    
}


long long int MST::Prims(int source){
    if(source<0||source>V){
        cerr<<"Invalid arguements"<<endl;
    }
    //typedef pair<int,int> p;
    Vtr = V;
    sptree = new priority_queue<p,vector<p>,greater<p>>[V];
    
    long long int mstcost=0;
    priority_queue<p,vector<p>,greater<p>> g;
    
    vector<int> weiarr(V,INT_MAX);
    vector<int> inmst(V,0);
    vector<int> parent(V,-1);
    
    weiarr[source] = 0;
    inmst[source] = 1;
    parent[source] = source;
    
    p e;
    e.first = 0;
    e.second = source;
    g.push(e);
    
    while(!g.empty()){
        p r = g.top();
        int u = r.second;
        g.pop();
        
        inmst[u] = 1;
        
        for(auto i = Adj[u].begin();i!=Adj[u].end();i++){
            int wei = i->first;
            int ver = i->second;
            if(inmst.at(ver)==0 && weiarr.at(ver)>wei){
                weiarr.at(ver)=wei;
                parent[ver] = u;
                p p1;
                p1.first = wei;
                p1.second = ver;
                g.push(p1);
            }
        }
    }
    
    for(auto i = 0;i<V;i++){
        mstcost+=weiarr.at(i);
    }
    
    for(int i=0;i<V;i++){
        int u = i;
        int v = parent[u];
        int wei = weiarr[u];
        p p1,p2;
        p1.first = wei;
        p1.second = u;
        p2.first = wei;
        p2.second = v;
        sptree[v].push(p1);
        sptree[u].push(p2);
    }
    uptodate = 0;
    return mstcost;
}

void MST::Display(){
   priority_queue<pair<int,p>,vector<pair<int,p>>,greater<pair<int,p>>> E; 
   
    for(int i=0;i<Vtr;i++){
        auto a = sptree[i];
        pair<int,p> p1;
        while(!a.empty()){
            auto b = a.top();
            a.pop();
            int j = b.second;
            if(j>i){
                p1.first = b.first;
                //p1.second = b;
                p r ;
                r.first = i;
                r.second = j;
                p1.second =r;
                E.push(p1);
            }
        }
    }
    while(!E.empty()){
        auto a = E.top();
        E.pop();
        p x;
        x = a.second;
        cout<<x.first<<" "<<x.second<<" "<<a.first<<endl;
    }
    
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    MST A;
    int n,Q;
    string s;
    cin>>n>>Q;
    int a,b,w;
    A.construct(n);
    for(int i=0;i<Q;i++){
        cin>>s;
        if(s == "ADDE"){
            cin>>a>>b>>w;
            A.AddE(a,b,w);
        }
        if(s=="ADDV"){
            A.AddV();
        }
        if(s=="DELE"){
            cin>>a>>b;
            A.DelE(a,b);
        }
        if(s=="Prims"){
            cin>>a;
            cout<<A.Prims(a)<<endl;
        }
        if(s=="TreeUptodate"){
            A.Treeuptodate();
        }
        if(s=="DisplayTree"){
            A.Display();
        }
        if(s=="Kruskal"){
            cout<<A.Kruskal()<<endl;
        }
        
    }
    return 0;
}
