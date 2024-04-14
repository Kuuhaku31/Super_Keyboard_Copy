
#include <stdio.h>
#include <math.h>
#define For(i,n) for(ll i = 0; i<n; i++)
#define For_(i,n) for(ll i = 1; i<=n; i++)
#define ll long long

using namespace std;

ll const INF = 0x3f3f3f3f3f3f3f3f;

int inum[100] = { 0 };
ll lnum[100] = { 0 };
double dnum[100] = { 0 };

int
main()
{
	For_(i, 4) scanf_s("%f", &dnum[i]);



	printf("%f", dnum[5]);

	return 0;
}
