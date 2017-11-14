#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <istream>
#include <string>

#define lli long long int
#define M 1000000007

using namespace std;

string x,y;
lli cp_cost, in_cost, re_cost, del_cost;

lli editdistance_dp_space_optimized()
{
	lli n = x.length();  /* Length of string x*/
	lli m = y.length();  /* Length of string y*/

	/*Dynamic Programming table*/
	lli dp[2][m+1];

	/*if x is an empty string then only option is to insert all the elements of y*/
	for(lli i=0;i<=m;i++)
		dp[0][i] = ((i%M)*(in_cost%M)%M);

	for(lli i = 1 ; i <= n ; i++)
	{
		/*if y is an empty string then only option is to delete all the elements of x*/
		dp[1][0] = ((i%M)*(del_cost%M)%M);

		for(lli j = 1 ; j <= m ; j++)
		{
			/* try insert */
			lli a = (in_cost % M + dp[1][j-1])%M;

			/* try replace */
			lli b = (re_cost % M + dp[0][j-1])%M;

			/* try del */
			lli c = (del_cost % M + dp[0][j])%M;

			dp[1][j] = a < b ? a : b;
			dp[1][j] = dp[1][j] < c ? dp[1][j] : c;

			/*try copy*/
			if(x[i-1]==y[j-1])
			{
				lli d = (cp_cost % M + dp[0][j-1])%M;
				dp[1][j] = dp[1][j] < d ? dp[1][j] : d;
			}
		}

		for(lli j=0 ;j<=m; j++)
			dp[0][j] = dp[1][j];
	}
	return dp[0][m];
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout<<"Program expects one command line argument : The path to input file. None given!\n";
		exit(0);
	}
	
	if(freopen(argv[1], "r", stdin)==NULL)
	{
		printf("Cannot open input file. Please ensure that the path \"%s\" is correct!\n", argv[1]);
		exit(0);
	}

	lli t;
	cin>>t;

	while(t--)
	{
		cin>>x>>y>>cp_cost>>in_cost>>re_cost>>del_cost;
		cout<<editdistance_dp_space_optimized()<<endl;
	}
}