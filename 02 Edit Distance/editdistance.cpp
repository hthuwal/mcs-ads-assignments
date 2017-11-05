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

/**
 * Read strings and cost values from file
 * @param filename [name of file containing inputs]
 * @param del [character seperating the costs]
 */
void read(char del)
{
	/* Reading strings alphanumeric [a-zA-Z0-9] */
	getline(cin, x, '\n');
	getline(cin, y, '\n');

	/* Reading costs <copy>,<insert>,<replace>,<delete> seperated by del*/
	string temp;
	getline(cin, temp, del);
	cp_cost = atol(temp.c_str());

	getline(cin, temp, del);
	in_cost = atol(temp.c_str());

	getline(cin, temp, del);
	re_cost = atol(temp.c_str());

	getline(cin, temp, '\n');
	del_cost = atol(temp.c_str());
}

lli editdistance_dp()
{
	lli n = x.length();  /* Length of string x*/
	lli m = y.length();  /* Length of string y*/

	/*Dynamic Programming table*/
	lli dp[n+1][m+1];
	/*dp[i][j] denotes the minimum cost in transforming i characters of x (i.e x[0:i-1]) to j characters of y (i.e y[0:j-1])*/

	/*if x is an empty string then only option is to insert all the elements of y*/
	for(lli i=0;i<=m;i++)
		dp[0][i] = ((i%M)*(in_cost%M)%M);

	/*if y is an empty string then only option is to delete all the elements of x*/
	for(lli i=0;i<=n;i++)
		dp[i][0] = ((i%M)*(del_cost%M)%M);

	for(lli i = 1 ; i <= n ; i++)
	{
		for(lli j = 1 ; j <= m ; j++)
		{
			/* try insert */
			lli a = (in_cost % M + dp[i][j-1])%M;

			/* try replace */
			lli b = (re_cost % M + dp[i-1][j-1])%M;

			/* try del */
			lli c = (del_cost % M + dp[i-1][j])%M;

			dp[i][j] = a < b ? a : b;
			dp[i][j] = dp[i][j] < c ? dp[i][j] : c;

			/*try copy*/
			if(x[i-1]==y[j-1])
			{
				lli d = (cp_cost % M + dp[i-1][j-1])%M;
				dp[i][j] = dp[i][j] < d ? dp[i][j] : d;
			}
		}
	}
	return dp[n][m];
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
	string temp;
	getline(cin, temp, '\n');
	t = atol(temp.c_str());

	while(t--)
	{
		cout<<"t is "<<t<<endl;
		read(',');
		cout<<editdistance_dp()<<endl;
	}
}