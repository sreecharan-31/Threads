#include<bits/stdc++.h>
#include<pthread.h>
#define N 10
using namespace std;

int si;

struct cofactor
{
	int A[N][N];
	int temp[N][N];
	int p,q,n;
};

void* getCofactor(void * para)
{
	struct cofactor * ptr=(struct cofactor *)para;
    int i = 0, j = 0;
    for (int row = 0; row < ptr->n; row++)
    {
        for (int col = 0; col < ptr->n; col++)
        {
            if (row != ptr->p && col != ptr->q)
            {
                ptr->temp[i][j++] = ptr->A[row][col];
                if (j == ptr->n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(int A[N][N], int n)
{
    int D = 0;
    if (n == 1)
        return A[0][0];
    int temp[N][N];
    int sign = 1;
    struct cofactor * ptr=new struct cofactor;
    for(int i=0;i<n;i++)
    	for(int j=0;j<n;j++)
    		ptr->A[i][j]=A[i][j];
    for (int f = 0; f < n; f++)
    {
    	ptr->q=f;
    	ptr->p=0;
    	ptr->n=n;
   			pthread_t tid;
				pthread_attr_t attr;
				pthread_attr_init(&attr);
				pthread_create(&tid,&attr,getCofactor,ptr);
      	pthread_join(tid,NULL);
        D += sign * A[0][f] * determinant(ptr->temp, n - 1);
        sign = -sign;
    }

    return D;
}

void adjoint(int A[N][N],int adj[N][N])
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }

    int sign = 1, temp[N][N];
  	struct cofactor * ptr=new struct cofactor;
    for(int i=0;i<si;i++)
    	for(int j=0;j<si;j++)
    		ptr->A[i][j]=A[i][j];
    for (int i=0; i<si; i++)
    {
        for (int j=0; j<si; j++)
        {
        		ptr->q=j;
    				ptr->p=i;
    				ptr->n=si;
						pthread_t tid;
						pthread_attr_t attr;
						pthread_attr_init(&attr);
						pthread_create(&tid,&attr,getCofactor,ptr);
						pthread_join(tid,NULL);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(ptr->temp,si-1));
        }
    }
}

void inverse(int A[N][N])
{
	float inverse[N][N];
    int det = determinant(A,si);
    int adj[N][N];
    adjoint(A, adj);
    cout<<"Inverse: "<<endl;
    for (int i=0; i<si; i++){
        for (int j=0; j<si; j++){
            inverse[i][j] = adj[i][j]/float(det);
        	cout<<inverse[i][j]<<" ";
        }
        cout<<endl;
     }
}


int main(){
	int a[N][N];
	cin>>si;
	for(int i=0;i<si;i++)
		for(int j=0;j<si;j++)
			cin>>a[i][j];
	inverse(a);
	return(0);
}
