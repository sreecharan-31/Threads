#include<bits/stdc++.h>

using namespace std;

vector<int> a={1,10,210,10,11,11,510};
double Q2,Q1,Q3,l,r;

void *findlq(void *p){
    int *num=(int *)p;
    int n=*num;
    int mid=(n-1)/2;
    {
      Q1=a[mid];
    }
}

void *findrq(void *p){
    int *num=(int *)p;
    int n=*num;
    int mid=(a.size()+n)/2;
    {
      Q3=a[mid];
    }
}

int main(){
  sort(a.begin(),a.end());
  int mid=(a.size()-1)/2;
  if(a.size()%2==0){
    Q2=double(a[mid]+a[mid+1])/2;
  }

  else{
    Q2=a[mid];
  }
  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tid,&attr,findlq,&mid);
  pthread_join(tid,NULL);

  pthread_attr_init(&attr);
  pthread_create(&tid,&attr,findrq,&mid);
  pthread_join(tid,NULL);

  double I=Q3-Q1;
  l=Q1-(1.5*I);
  r=Q3+(1.5*I);
  cout<<Q1<<" "<<Q2<<" "<<Q3<<" "<<l<<" "<<r<<endl;
  cout<<"The outliers are: "<<endl;
  for(int i=0;i<a.size();i++){
    if(a[i]<l || a[i]>r){
      cout<<a[i]<<" ";
    }
  }
  cout<<endl;
}
