#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;

void *runner(void * param);

int main(int argc,char * argv[]){
  int n=atoi(argv[1]);
  for(int i=2;i<n;i++){
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid,&attr,runner,&i);
    pthread_join(tid,NULL);
  }
  cout<<endl;
}

void *runner(void * param){
  int flag=0;
  int n=*((int *)param);
  for(int i=2;i<=sqrt(n);i++){
    if(n!=i && n!=1)
      if(n%i==0)
        flag=1;
  }
  if(flag==0)
    cout<<n<<" ";
}
