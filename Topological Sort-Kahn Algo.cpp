#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
	int V;
	vector<int> *adj;
	vector<int> sortedList;
	
	public:
	Graph(int v)
	{
		V = v;
		adj = new vector<int>[V];
	}	
	
	void addEdge(int u, int v)
	{
		adj[u].push_back(v);
	}
	
	bool topologicalSort()
	{
		vector<int> inDegree(V,0);
		for (int u=0; u<V; u++)
			for (vector<int>::iterator v=adj[u].begin(); v!=adj[u].end(); v++)
				inDegree[*v]++;
			
		queue<int> q;
		for (int i=0; i<V; i++)
			if (inDegree[i]==0)
				q.push(i);
				
		int count=0;
		while(!q.empty())
		{
			int u = q.front();
			q.pop();
			sortedList.push_back(u);
			count++;
			
			for (vector<int>::iterator v=adj[u].begin(); v!=adj[u].end(); v++)
				if (--inDegree[*v] == 0)
					q.push(*v);
		}
		if (count!=V)
			return false;
		return true;
	}
	
	void display()
	{
		for (int i=0; i<V; i++)
		{
			cout << i<< " : ";
			for (vector<int>::iterator itr=adj[i].begin(); itr!=adj[i].end(); itr++)
				cout << *itr << "\t";
			cout << endl;
		}
	}
	
	void displaySortedList()
	{
		for(vector<int>::iterator itr=sortedList.begin(); itr!=sortedList.end(); itr++)
			cout << *itr << " ";
		cout << endl;
	}
};

int main()
{
	Graph g(6);
	g.addEdge(2,3);
	g.addEdge(3,1);
	g.addEdge(4,0);
	g.addEdge(4,1);
	g.addEdge(5,0);
	g.addEdge(5,2);
	g.topologicalSort();
	g.displaySortedList();
	return 0;
}
