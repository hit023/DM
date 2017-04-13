#ifndef FPTREE_HPP
#define FPTREE_HPP

#include <bits/stdc++.h>

using namespace std;

class FPNode
{
public:
	int att;
	FPNode * next[17];
	int sup_count;
	FPNode * parent;
	FPNode(int a, FPNode * p): sup_count(0), att(a)
	{
		parent = p;
		for(int i=0;i<17;i++)
		{
			next[i] = NULL;
		}
	}
};

class FPTree
{
public:
	FPNode * root;
	FPTree()
	{
		root = new FPNode(INT_MAX,NULL);
	}

	bool emptyTree() const
	{
		for(int i=0;i<17;i++)
		{
			if(!root->next[i])
			{
				return false;
			}
		}
		return true;
	}

	void createTree(int transactions[500][17], int sz)
	{
		FPNode * t = root;
		for(int i=0;i<sz;i++)
		{
			FPNode * d = root;
			vector<int> v(17,0);
			copy(transactions[i], transactions[i]+16, v.begin());
			for(int j=0;j<17;j++)
			{
				if(v[j]!=0)
				{
					if(t->next[j]==NULL)
					{
						t->next[j] = new FPNode(j,t);
					}
					t = t->next[j];
					++(t->sup_count);
				}
			}
			t = root;
		}
		createLinks(root);
	}

	void FPGrowth(FPNode * root, int msc)
	{
		//finds itemsets ending with a given suffix(looped over all possible attributes).
		for(int i=0;i<17;i++)
		{
			if(k[i].size()>=msc)
			{
				FPNode * cfp_root = conditionalFP(i,msc);
				cfp_root = root;
			}
		}
	}

private:
	vector<pair<FPNode *,FPNode *> > k[17];

	FPNode * conditionalFP(int att, int msc)
	{

	}

	void createLinks(FPNode * t)
	{
		if(t!=NULL)
		{
			FPNode * p = t->parent;
			while(p->parent!=root)
			{
				p=p->parent;
			}
			k[t->att].push_back(pair<FPNode *,FPNode *>(p,t));
			for(int i=0;i<17;i++)
			{
				if(t->next[i]!=NULL)
				{
					createLinks(t->next[i]);
				}
			}
		}
	}
};
#endif
