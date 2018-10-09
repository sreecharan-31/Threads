#include<bits/stdc++.h>
#define interval 1000

using namespace std;

void *runner(void * p);
double cp=0,sp=0;

int main(){
  pthread_t tid;
  srand(time(NULL));
  for(int i=0;i<interval*interval;i++){
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid,&attr,runner,NULL);
    pthread_join(tid,NULL);
  }
  double pi=double((cp/sp)*(4));
  cout<<"Value of Pi: "<<pi<<endl;
}

void *runner(void * p){
  double x=double((rand()%interval))/interval;
  double y=double((rand()%interval))/interval;
  double dist=(x*x)+(y*y);
  if(dist<=1)
    cp++;
  sp++;
}
