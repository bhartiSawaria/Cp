#include <iostream>
#include <vector>
#define MAX 100

using namespace std;

typedef pair<int,int> pii;

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
	vector<pii> *adj;
	int *d, *parent;
	minPriorityQueue q;
	
	public:
	Graph(int v)
	{
		V = v;
		adj= new vector<pii>[V];
		d = new int[V];
		parent = new int[V];
	}
	void addEdge(int u, int v, int w)
	{
		adj[u].push_back(make_pair(v,w));
	}
	
	Graph dijkstra(int s)
	{
		Graph g(V);
		
		initializeSingleSource(s);
		
		vector<bool> visited(V, false);
		
		for (int i=0; i<V; i++)
			q.add(i, INT_MAX);
		
		q.decreaseKey(s,0);
			
		while (!q.empty())
		{
			int k;
			int u = q.extractMin(&k);
		
			visited[u] = true;
			
			if (parent[u]!=-1)
				g.addEdge(parent[u],u, k);
			
			for (vector<pii>::iterator v=adj[u].begin(); v!=adj[u].end(); v++)
			{
				int x = (*v).first;
				if (!visited[x])
					relax(u, x,  (*v).second);
			}
			
		}
	
		return g;
	}
	
	void initializeSingleSource (int s)
	{
		for (int i=0; i<V; i++)
		{
			d[i] = INT_MAX;
			parent[i]=-1;		
		}
		d[s]=0;
	}
	
	void relax(int u, int v, int w)
	{
		int sum = INT_MAX;
		if (d[u]!=INT_MAX)
			sum = d[u]+w;
			
		if (d[v]>sum)
		{
			d[v]=sum;
			parent[v] = u;
			q.decreaseKey(v, sum);
		}
		
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
	Graph g(5);
	g.addEdge(0,1,10);
	g.addEdge(0,3,5);
	g.addEdge(1,2,1);
	g.addEdge(1,3,2);
	g.addEdge(2,4,4);
	g.addEdge(3,1,3);
	g.addEdge(3,2,9);
	g.addEdge(3,4,2);
	g.addEdge(4,0,7);
	g.addEdge(4,2,6);
	Graph g2 = g.dijkstra(0);
	g2.display();
	
	return 0;
}
