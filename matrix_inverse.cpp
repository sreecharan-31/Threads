#include<bits/stdc++.h>
#include<pthread.h>
#include<signal.h>

#define N 10
using namespace std;

int si;

struct cofactor
{
	int A[N][N];
	int temp[N][N];
	int p,q,n;
};

void response(int signo){
	cout<<"FPE Encountered"<<endl;
}

void getCofactorone(int A[N][N],int temp[N][N],int p,int q,int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

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
        //getCofactor(ptr);
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
  	// struct cofactor * ptr=new struct cofactor;
   //  for(int i=0;i<si;i++)
   //  	for(int j=0;j<si;j++)
   //  		ptr->A[i][j]=A[i][j];
    for (int i=0; i<si; i++)
    {
        for (int j=0; j<si; j++)
        {
      //   	ptr->q=j;
    		// ptr->p=i;
    		// ptr->n=si;
      //       getCofactor(ptr);
      		getCofactorone(A, temp, i, j, si);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp,si-1));
        }
    }
}

void inverse(int A[N][N])
{
		signal(SIGFPE,response);
		float inverse[N][N];
    int det = determinant(A,si);
    cout<<"determinant is"<<det<<endl;
    int adj[N][N];
    adjoint(A, adj);
    cout<<"The inverse is"<<endl;
    for (int i=0; i<si; i++){
        for (int j=0; j<si; j++){
						raise(SIGFPE);
            inverse[i][j] = adj[i][j]/float(det);
        	cout<<inverse[i][j]<<" ";
        }
        cout<<endl;
     }
}


int main(){
	int a[N][N];
	cout<<"Enter the matrix size"<<endl;
	cin>>si;
	cout<<"Enter the matrix"<<endl;
	for(int i=0;i<si;i++)
		for(int j=0;j<si;j++)
			cin>>a[i][j];
	inverse(a);
	return(0);
}
