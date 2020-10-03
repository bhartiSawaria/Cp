#include <iostream>
#include <algorithm>



using namespace std;

class Graph
{
	int V,E;
	typedef struct Edge
	{
		int u, v, wt;
	}Edge;
	Edge *edge;
	int k;
	
	public :
	Graph(int V,int E)
	{
		this->V = V;
		this->E = E;
		this->edge = new Edge[E];
		k=0;
	}
	
	void addEdge(int a, int b, int w)
	{
		edge[k].u=a;
		edge[k].v=b;
		edge[k++].wt=w;
	}
	
	static int myCmp(const void*a, const void *b)
	{
		Edge *a1 = (Edge*)a;
		Edge *a2 = (Edge*)b;
		if( a1->wt > a2->wt)
			return 1;
		else if ( a1->wt < a2->wt)
			return -1;
		return 0;
	}  
	
	int find(int parent[], int x)
	{
		if (parent[x]==-1)
			return x;
		return find(parent, parent[x]);
	}
	
	void Union(int parent[], int x, int y)
	{
		int xP = find(parent, x);
		int yP = find(parent, y);
		if (xP != yP)
			parent[xP]=yP;
	}
	
	Graph kruskalMst()
	{
		Graph g(V,V-1);
		
	
		qsort(edge, E-2, sizeof(edge[0]),myCmp );
		
		int e=0, i=0;
		int parent[V];
		fill_n(parent, V, -1);
		
		while (e<V-1 && i<E)
		{
			
				
			Edge nxt = edge[i++];
			
			int x = find(parent, nxt.u);
			int y = find(parent, nxt.v);
			 			
			if (x!=y ) 
			{
				g.addEdge(nxt.u, nxt.v, nxt.wt);
				e++;
				Union(parent, x, y);
			}
			
		}
		return g;
	}
	
	void display ()
	{
		cout <<"The edges are : " << endl;
		for (int i=0; i<E; i++)
			cout<< "From " << edge[i].u << " to " << edge[i].v << " with wt : " << edge[i].wt << endl;
	}
};



int main()
{
	// Test case 1
	Graph g1(4,4);
	g1.addEdge(0,1,4);
	g1.addEdge(1,2,5);
	g1.addEdge(2,3,7);
	g1.addEdge(0,3,6);
	Graph g2 = g1.kruskalMst();
	g2.display();
	
	cout << endl ;
	
	// Test case 2
	Graph g3(9,14);
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
	Graph g4= g3.kruskalMst();
	g4.display();
	return 0;
}
