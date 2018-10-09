#include<bits/stdc++.h>

using namespace std;
vector<int> a;
struct data{
  int l,r,m;
};

void merge(int l, int m, int r);
void *mergeSort(void *p);

int main()
{
  int n;
  cin>>n;
  for(int i=0;i<n;i++){
    int temp;
    cin>>temp;
    a.push_back(temp);
  }
  struct data *d1=new data;
  d1->l=0;
  d1->r=a.size()-1;
  mergeSort((void *)d1);

  for(int i=0;i<a.size();i++){
    cout<<a[i]<<" ";
  }
  cout<<endl;
}

void merge(int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1+ j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
}

void *mergeSort(void *p)
{
  struct data *d=(struct data *)p;
    if (d->l < d->r)
    {
        int m = d->l+((d->r)-(d->l))/2;
        struct data d1;
        d1.l=d->l;
        d1.r=m;
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid,&attr,mergeSort,(void *)&d1);
        pthread_join(tid,NULL);
        struct data d2;
        d2.l=m+1;
        d2.r=d->r;
        pthread_attr_init(&attr);
        pthread_create(&tid,&attr,mergeSort,(void *)&d2);
        pthread_join(tid,NULL);
        merge(d->l, m, d->r);
    }
}
