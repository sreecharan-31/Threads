#include<bits/stdc++.h>

using namespace std;
vector<int> a;

struct data{
  int l,r;
};
void swap(int* a, int* b);
int partition (int low, int high);
void *quickSort(void *p);

int main()
{
  int n;
  cin>>n;
  for(int i=0;i<n;i++){
    int temp;
    cin>>temp;
    a.push_back(temp);
  }
  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  struct data *d2=new data;
  d2->l=0;
  d2->r=a.size()-1;
  pthread_create(&tid,&attr,quickSort,d2);
  pthread_join(tid,NULL);

  for(int i=0;i<a.size();i++){
    cout<<a[i]<<" ";
  }
  cout<<endl;
}

void swap(int* a, int* b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int partition (int low, int high)
{
    int pivot = a[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return (i + 1);
}

void *quickSort(void *p){
    struct data *d=(struct data *)p;
    int low=d->l;
    int high=d->r;
    if (low < high)
    {
        int pi = partition(low, high);
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        struct data d1;
        d1.l=low;
        d1.r=pi-1;
        pthread_create(&tid,&attr,quickSort,(void *)&d1);
        pthread_join(tid,NULL);
        struct data d2;
        d2.l=pi+1;
        d2.r=high;
        pthread_attr_init(&attr);
        pthread_create(&tid,&attr,quickSort,(void *)&d2);
        pthread_join(tid,NULL);
    }
}
