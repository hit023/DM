#include <bits/stdc++.h>
#include "fptree.hpp"

using namespace std;

int main()
{
	ifstream infile("vote.arff");
    string line;

    int transactions[500][17]; //2: democrat, 3:republican
    int t=0;
    while(getline(infile,line))
    {
        int n = line.length();
        int i=0,j=0;
        while(j<n)
        {
            if(line[j]=='n')
            {
                transactions[t][i] = 0;
                ++i;
            }
            else if(line[j]=='y')
            {
                transactions[t][i] = 1;
                ++i;
            }
            else if(line[j]=='?')
            {
                transactions[t][i] = 1;
                ++i;
            }
            else if(line[j]=='d')
            {
                transactions[t][i] = 2;
                ++i;
                ++t;
                break;
            }
            else if(line[j]=='r')
            {
                transactions[t][i] = 3;
                ++i;
                ++t;
                break;
            }
            ++j;
        }
    }
	FPTree * tree = new FPTree();
	tree->createTree(transactions, t);

	int min_sup_count;
	cout<<"\n min. support count: "<<'\n';
	cin>>min_sup_count;

	tree->FPGrowth(min_sup_count);
	return 0;
}
