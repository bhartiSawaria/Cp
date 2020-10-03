#include <bits/stdc++.h> 


#define MAX 100

using namespace std;


class minPriorityQueue
{
	pair<int,int> a[MAX];
	int size;
	
	public:
	minPriorityQueue()
	{
		size=0;
	}
	bool empty()
	{
		if (size==0)
			return true;
		return false;
	}
	int isPresent(int x)
	{
		for (int i=1; i<=size; i++)
			if (a[i].first==x)
				return i;
		return 0;
	}
	int getKey(int x)
	{
		for (int i=1; i<=size; i++)
			if (a[i].first==x)
				return a[i].second;
		return -1;
	}
	void add(int x, int k)
	{
		size++;
		a[size].first = x;
		a[size].second = INT_MAX;
		decreaseKey(size, k);
		
	}
	int max()
	{
		return a[1].first;
	}
	
	int extractMin(int *x)
	{
		int max = a[1].first;
		(*x) = a[1].second;
		a[1].first = a[size].first;
		a[1].second = a[size].second;
		size--;
		minHeapify(1);
		
		return max;
	}
	
	void minHeapify(int i)
	{
		if (i<=size/2)
		{
			int index = 2*i;
			if (2*i+1<=size && a[2*i+1].second<a[2*i].second)
				index = 2*i+1;
				
			if (a[index].second<a[i].second)
			{
				int t=a[i].first;
				a[i].first=a[index].first;
				a[index].first=t;
				
				t=a[i].second;
				a[i].second=a[index].second;
				a[index].second=t;
				
				minHeapify(index);
			}
		}
	}
	
	void decreaseKey(int x, int newKey)
	{
		int i=isPresent(x);
		a[i].second = newKey;
		while (i>1 && a[i/2].second > newKey)
		{
			int t=a[i].first;
			a[i].first=a[i/2].first;
			a[i/2].first=t;
			
			t=a[i].second;
			a[i].second=a[i/2].second;
			a[i/2].second=t;
			
			i = i/2;
		}
	}
	
	void display()
	{
		for (int i=1; i<=size; i++)
			cout << a[i].first << " ";
		cout << endl;
	}
};

class Graph
{
	int V;
	vector< pair<int,int> > *adj;
	
	
	public:
	Graph(int V)
	{
		this->V = V;
		adj = new vector< pair<int,int> > [V];
	
	}
	
	void addEdge(int a, int b, int w)
	{
		adj[a].push_back(make_pair(b,w));
		adj[b].push_back(make_pair(a,w));
	}
	
	Graph primMST()
	{
		Graph g(V);
		
		int parent[V];
		minPriorityQueue q;
			
		fill_n(parent, V, -1);
		
		for (int i=0; i<V; i++)
			q.add(i,INT_MAX);
		//q.display();
		
		q.decreaseKey(0,0);
		//cout << "key of zero decreased " << endl;
		//q.display();
		
		while (!q.empty())
		{
			int x;
			int u = q.extractMin(&x);
			
			if (parent[u]!=-1)
				g.addEdge(u,parent[u],x);
			
			for (vector< pair<int,int> > :: iterator itr=adj[u].begin(); itr!=adj[u].end(); itr++)
			{
				pair<int,int> v=(*itr);
				if (q.isPresent(v.first) && (v.second)<q.getKey(v.first))
				{
					parent[v.first] = u;
					q.decreaseKey(v.first, v.second);
				}
			}
		}
		
		
		return g;
	}
	
	void display ()
	{
		cout <<"The edges are : " << endl;
		for (int i=0; i<V; i++)
		{	
			cout << i << " : ";
			for (vector< pair<int,int> > :: iterator itr=adj[i].begin(); itr!=adj[i].end(); itr++)
			{
				cout << "(" << (*itr).first << " , " << (*itr).second << ")\t";
			}
			cout << endl;
		}
	}
	
		
};

int main()
{
	// Test case 1
	Graph g1(4);
	g1.addEdge(0,3,6);
	g1.addEdge(2,3,7);
	g1.addEdge(0,1,4);
	g1.addEdge(1,2,5);
	Graph g2= g1.primMST();
	g2.display();
	
	// Test case 2
	Graph g3(9);
	g3.addEdge(0,1,4);
	g3.addEdge(0,7,8);
	g3.addEdge(1,2,8);
	g3.addEdge(1,7,11);
	g3.addEdge(2,3,7);
	g3.addEdge(2,8,2);
	g3.addEdge(2,5,4);
	g3.addEdge(3,4,9);
	g3.addEdge(3,5,14);
	g3.addEdge(4,5,10);
	g3.addEdge(5,6,2);
	g3.addEdge(6,7,1);
	g3.addEdge(6,8,6);
	g3.addEdge(7,8,7);
	Graph g4= g3.primMST();
	g4.display();
	
	
	return 0;
}
