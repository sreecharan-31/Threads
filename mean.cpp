#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;

struct data{
  int n;
  int a[100];
};
double mean,median;

void *runner1(void * para);
void *runner2(void * para);
void *runner3(void * para);

int main(){
  int n;
  cin>>n;
  struct data d;
  d.n=n;
  for(int i=0;i<n;i++){
    cin>>d.a[i];
  }
  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tid,&attr,runner1,&d);
  pthread_join(tid,NULL);

  pthread_create(&tid,&attr,runner2,&d);
  pthread_join(tid,NULL);

  pthread_create(&tid,&attr,runner3,&d);
  pthread_join(tid,NULL);
}

void *runner1(void * para){
  struct data *d=(struct data *)para;
  int sum=0;
  for(int i=0;i<d->n;i++){
    sum+=d->a[i];
  }
  mean=(double)((double)sum/d->n);
  cout<<"Mean: "<<mean<<endl;
}


void *runner2(void * para){
  struct data *d=(struct data *)para;
  sort(d->a,d->a+d->n);
  median=d->a[d->n/2];
  cout<<"Median: "<<median<<endl;
}


void *runner3(void * para){
  struct data *d=(struct data *)para;
  std::map<int, int> map;
  for(int i=0;i<d->n;i++){
    map[d->a[i]]++;
  }
  int max=map[d->a[0]];
  int max_pos=0;
  for(int i=0;i<d->n;i++){
    if(map[d->a[i]]>max){
      max_pos=i;
      max=map[d->a[i]];
    }
  }
  cout<<"Mode: "<<d->a[max_pos]<<endl;
}
