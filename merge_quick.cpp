#include<bits/stdc++.h>

using namespace std;
vector<int> a={1,6,4,7,8,2};
struct data{
  int l,r;
};
void swap(int* a, int* b);
int partition (int arr[], int low, int high);
void merge(int a[], int l, int m, int r);
void *mergeSort(void *p);
void *quickSort(void *p);
int main()
{
  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  struct data *d1=new data;
  d1->l=0;
  d1->r=a.size()-1;
  pthread_create(&tid,&attr,mergeSort,d1);
  pthread_join(tid,NULL);
  pthread_attr_init(&attr);
  struct data *d2=new data;
  d2->l=0;
  d2->r=a.size()-1;
  pthread_create(&tid,&attr,quickSort,d2);
  pthread_join(tid,NULL);
}

void swap(int* a, int* b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void merge(int a[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void *mergeSort(void *p)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void *quickSort(void *p){
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
