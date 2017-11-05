#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <istream>
#include <string>
using namespace std;

string x,y;
int cp_cost, in_cost, re_cost, del_cost;

/**
 * Read strings and cost values from file
 * @param filename [name of file containing inputs]
 * @param del [character seperating the costs]
 */
void read(char *filename, char del)
{
	if(freopen(filename, "r", stdin)==NULL)
	{
		printf("Cannot open input file. Please ensure that the path \"%s\" is correct!\n", filename);
		exit(0);
	}
	/* Reading strings alphanumeric [a-zA-Z0-9] */
	cin>>x;
	cin>>y;

	/* Reading costs seperated by del*/
	string temp;
	getline(cin, temp, del);
	cp_cost = atoi(temp.c_str());

	getline(cin, temp, del);
	in_cost = atoi(temp.c_str());

	getline(cin, temp, del);
	re_cost = atoi(temp.c_str());

	getline(cin, temp, del);
	del_cost = atoi(temp.c_str());
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout<<"Program expects one command line argument : The path to input file. None given!\n";
		exit(0);
	}
	read(argv[1], ',');

}