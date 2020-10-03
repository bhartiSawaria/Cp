#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int,int> pii;

class Graph
{
	int V;
	vector<pii> *adj;
	int *d, *parent;
	
	public:
	Graph(int V)
	{
		this->V = V;
		adj= new vector<pii> [V];
		d = new int[V];
		parent = new int[V];
	}
	void addEdge(int u, int v, int w)
	{
		adj[u].push_back(make_pair(v,w));
	}
	
	void initializeSingleSource(int s)
	{
		for (int i=0; i<V; i++)
		{
			d[i]=INT_MAX;
			parent[i]=-1;
		}
		d[s] = 0;
	}
	
	void relax (int u, int v, int w)
	{
		int sum;
		if (d[u]==INT_MAX)
			sum = INT_MAX;
		else
			sum = d[u]+w;
			
		if (d[v]>sum)
		{
			d[v] = sum;
			parent[v] = u;
		}
	}
	
	bool bellmanFord(int s)
	{
		initializeSingleSource(s);
		for (int i=1; i<=V-1; i++)
			for (int u=0; u<V;u++)
				for (vector<pii>::iterator v=adj[u].begin(); v!=adj[u].end(); v++)
					relax(u,(*v).first, (*v).second);
					
		// now a check
		for (int u=0; u<V;u++)
			for (vector<pii>::iterator v=adj[u].begin(); v!=adj[u].end(); v++)
				if (d[(*v).first]>d[u] + (*v).second)
					return false;
		return true;
	}
	void displayShortestPath()
	{
		cout << "The shortest path" << endl;
		for(int i=0; i<V; i++)
			cout << i<< " : " << "From " << parent[i]<< " with dis " << d[i] <<  endl;
	}
	void display()
	{
		cout << "The edges are" << endl;
		for (int i=0; i<V; i++)
		{
			cout << i << " : ";
			for (vector<pii>::iterator itr=adj[i].begin(); itr!=adj[i].end(); itr++)
				cout<< (*itr).first << "(" << (*itr).second << ")\t";
			cout << endl;
		}
			
	}
};

int main()
{
	// Test case 1
	Graph g(5);
	g.addEdge(0,1,6);
	g.addEdge(0,3,7);
	g.addEdge(1,3,8);
	g.addEdge(1,4,-4);
	g.addEdge(1,2,5);
	g.addEdge(2,1,-2);
	g.addEdge(3,2,-3);
	g.addEdge(3,4,9);
	g.addEdge(4,2,7);
	g.addEdge(4,0,2);
	g.bellmanFord(0);
	g.displayShortestPath();
	
	return 0;
}
