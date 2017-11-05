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
	}
}