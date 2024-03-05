#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;
int maxim(int a,int b,int c){
    int x;
    if(a>b){
        x=a;
    }
    else{x=b;}
    if(x>c){
        return x;
    }
    return c;
}
class BloomBrain{
  private:
    int *seraphic;
    int *empty;
    int capacity=0;
  public:
    void makenull(int n);
    void update(int arr[]);
    void join(int);
    void leave(int i);
    void play();
    int occupied();
    void print();
    void emparr();
    int maxsubarr(int,int);
    int cross(int,int,int);
    long long int ms(int*,int*,int,int);
    long long int merge(int*,int*,int,int,int);
    void des();
};
void BloomBrain::des(){
    delete[] seraphic;          //destructor function//
    delete[] empty;
}
void BloomBrain::emparr(){
    empty = new int[capacity];      //creating an array empty initialised all elements to 1//
    for(int i=0;i<capacity;i++){
        empty[i]=1;
    }
}
void BloomBrain::print(){
    for(int i=0;i<capacity;i++){    //used to print the elements of seraphic arr//
        cout<<seraphic[i]<<" ";
    }
}
void BloomBrain::makenull(int n){
    capacity = n;                   //allocating memory to seraphic arr//
    seraphic = new int[n];
}

void BloomBrain::leave(int i){
    seraphic[i]=0;                  //seraphic and empty of i will be set to 0//
    empty[i]=0;
}

int BloomBrain::occupied(){
    int sum=0;
    for(int i=0;i<capacity;i++){
        sum+=empty[i];              //returns the current number of occupied rooms using empty array//
    }
    return sum;
}

int BloomBrain::maxsubarr(int left,int right){
    if(left==right){
        return seraphic[right];
    }
    int mid;
    mid = (left+right)/2;                       //divide the array into two parts//
                                //return max of sum  in left,right,crossing sub arrays//
    return maxim(maxsubarr(left,mid),maxsubarr(mid+1,right),cross(left,mid,right));
}

int BloomBrain::cross(int left,int mid,int right){
    long long int sum = 0;
    long long int lsum = -100000000;
    long long int rsum = -100000000;
    for(int i=mid;i>=left;i--){
        sum+=seraphic[i];           //finding maximum sum in left array
        if(sum>lsum){
            lsum = sum;
        }
    }
    sum = 0;
    for(int i=mid+1;i<=right;i++){
        sum+=seraphic[i];
        if(sum>rsum){               //finding maximum sum in right array
            rsum = sum;
        }
    }
    return maxim(lsum+rsum,lsum,rsum);  //returns maximum sum including mid
}
void BloomBrain::update(int arr[]){
    //int qualtalk=0;
    for(int i=0;i<capacity;i++){
       seraphic[i] = arr[i];            //putting values in seraphic arr//
    }
    //print();
    int size=occupied();
    int temp[size];
    int dummy[size];
    int ind=0;
    for(int i=0;i<capacity;i++){
        if(empty[i]!=0){
        temp[ind]=seraphic[i];      //creating temp array without any empty rooms//
        ind++;
        }
    }
    long long int inv = ms(dummy,temp,0,size-1);
    
    cout<<inv<<endl;
}

void BloomBrain::join(int val){
    int index=-1;
    for(int i=capacity-1;i>=0;i--){
        if(empty[i]==0){            //putting given value in empty room and put empty as 1//
            index = i;
            break;
        }
    }
        empty[index]=1;
        seraphic[index]=val;
}

void BloomBrain::play(){
    long long int ans = maxsubarr(0,capacity-1);
    cout<<ans<<endl;
}

long long int BloomBrain::ms(int dummy[],int temp[],int left,int right){
    if(left>=right){
        return 0;
    }
    long long int inv = 0;
    int mid;
    mid = (left+right)/2;
    inv+=ms(dummy,temp,left,mid);
    inv+=ms(dummy,temp,mid+1,right);
    inv+=merge(dummy,temp,left,mid+1,right);    //sum of onversions in left part right part and merge//
    
    return inv;
}

long long int BloomBrain::merge(int dummy[],int temp[],int left,int mid,int right){
    int i=left;
    int j=mid;
    int k = left;           //merges two arrays and returns inv count of the arrays//
    long long int inv=0;
     while(i<mid && j<=right){
        if(temp[i]<=temp[j]){
            dummy[k] = temp[i];
            i++;
        }
        else {
            dummy[k] = temp[j];
            j++;            //if element in left with index i is greater than right subarr then there will be mid-i
            inv+=(mid-i);   //greater elements because the left arr is sorted//
        }
         k++;
        }
     if(i==mid){
        while(j<=right){
           dummy[k] = temp[j];          //this if-else for copying the remaining elements to dummy//
              j++;
              k++;
            }
        }
        else {
        while(i<mid){
            dummy[k] = temp[i];
            i++;
            k++;
            }
        }
    for(int i=left;i<=right;i++){
        temp[i]=dummy[i];           //copying merged elements to temp//
    }
    return inv;
}


int main() {
    int n,q;
    //char garb;
    BloomBrain B;
    string s;
    cin>>n;
    B.makenull(n);
    B.emparr();
    cin>>q;
    
    for(int i=0;i<q;i++){
        cin>>s;
        if(s=="update"){
            int *arr;
            arr = new int[n];
           for(int i=0;i<n;i++){
               cin>>arr[i];
           }
           B.update(arr);  
        }
        if(s=="play"){
            B.play();
        }
        if(s=="join"){
            int val;
            cin>>val;
            B.join(val);
        }
        if(s=="leave"){
            int idx;
            cin>>idx;
            B.leave(idx);
        }
        if(s=="occupied"){
            cout<<B.occupied()<<endl;
        }
    }
    B.des();        //for freeing memory// 
    //B.print();
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
