#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#define T 435
#define max_leaf_itemsets 2
using namespace std;

class Node
{
public:
    vector<Node*> children;
    int sz;//sz marks how many items have already been accomodated in this Node as a leaf.
    //for now, assume max. of sz to be 2.
    vector<vector<int> > leaf_itemsets;
    bool isLeaf() const
    {
        for(int i=0;i<5;i++)
        {
            if(children[i]!=NULL)
            {
                return false;
            }
        }
        return true;
    }
    Node() : children(5), sz(0)
    {
        for(int i=0;i<5;i++)
        {
            children[i]=NULL;
        }
    }
};

vector<vector<int> > makeSubsets(,int k)
{
    vector<vector<int> > subsets;
    for(int i=0;i<T;i++)
    {

    }
}

void reOrganize(Node * t, int ht)
{
    int item1 = t->leaf_itemsets[0][ht];
    t->children[item1] = new Node();
    t->children[item1]->leaf_itemsets.push_back(t->leaf_itemsets[0]);

    int item2 = t->leaf_itemsets[1][ht];
    t->children[item2] = new Node();
    t->children[item2]->leaf_itemsets.push_back(t->leaf_itemsets[1]);
}

void insertIntoTree(const vector<int> & itemset, Node * t, int ht,int k)
{
    int p = itemset[ht];
    while(!t->isLeaf() && t->children[p]!=NULL)
    {
        t = t->children[p];
        if(t->sz == max_leaf_itemsets && t->isLeaf() && ht<k)
        {
            ++ht;
            reOrganize(t,ht);
            insertIntoTree(itemset,t,ht,k);
        }
        else if(t->sz > max_leaf_itemsets && t->isLeaf() && ht>=k)
        {
            t->leaf_itemsets.push_back(itemset);
            return;
        }
        ++ht;
        p = itemset[ht];
    }
    t->children[p] = new Node();
    t->children[p]->leaf_itemsets.push_back(itemset);
}

Node * makeHashTree(vector<vector<vector<int> > > & v,int k)
{
    //k mod 5
    //k is the number of items in each itemset belonging to the set of candidate frequent-itemsets.
    Node * root = new Node();
    //assume that each leaf node can only accomodate 2 itemsets.
    //Node * t = root;
    for(int i=0;i<v[1].size();i++)
    {
        insertIntoTree(v[1][i], root,0,k);
    }
    return root;
}

void merge(vector<vector<vector<int> > > & v,int k)
{
    for(int i=0;i<v[0].size();i++)
    {
        for(int j=i+1;j<v[0].size();j++)
        {
            int flag=0;
            for(int p=0;p<=k-2;p++)
            {
                if(v[0][i][p]!=v[0][j][p])
                {
                    flag=1;
                    break;
                }
            }
            if(!flag)
            {
                vector<int> d(k-1);
                d=v[0][i];
                d.push_back(v[0][j][k-1]);
                v[1].push_back(d);
            }
        }
    }
}

void prune_sets(vector<vector<vector<int> > > & v,vector<int> & sup_count,double sup)
{
    for(int i=1;i<v[0].size();i++)
    {
        if((double)sup_count[i]/T<sup)
        {
            cout<<"sup: "<<(double)sup_count[i]/T<<'\n';
            v[0].erase(v[0].begin()+i);
            sup_count.erase(sup_count.begin()+i);
        }
    }
}

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
    double sup,conf;
    cout<<"Enter support: "<<'\n';
    cin>>sup;
    cout<<"Enter confidence: "<<'\n';
    cin>>conf;

    vector<vector<vector<int> > > v(2);
    //finding the support of 1-frequent items.

    v[0].resize(17);
    for(int i=0;i<17;i++)
    {
        v[0][i].resize(1,i);
    }
    vector<int> sup_count(17,0);

    for(int i=0;i<17;i++)
    {
        for(int j=0;j<t;j++)
        {
            if(transactions[j][i])
            {
                ++sup_count[i];
            }
        }
    }
    prune_sets(v,sup_count,sup);
    int k=1;
    while(!v[0].empty())
    {
        merge(v,k);
        ++k;
        makeHashTree(v,k);
        makeSubsets(transactions,k);
    }

    return 0;
}
