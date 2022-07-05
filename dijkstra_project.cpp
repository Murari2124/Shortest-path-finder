/* Name: Vadde Manjula Murari
   Roll no.:19CE30024
   Shortest route finder between two cities(self project) using Dijkstra algorithm*/
#include<bits/stdc++.h>
using namespace std;
class Graph
{
    //used for adjacency list
	unordered_map<string,vector<pair<string,int>>> g;
	//for storing price for total journey
	int p=0;
    public:
    void addEdge(string start,string end,int wt);
    int ShortestPath(string dep,string des,unordered_map<string,vector<string>>*ans);
    void Display();
    int Price();
};
void Graph::addEdge(string start,string end,int w)
{   
	g[start].push_back(make_pair(end,w));
	
	g[end].push_back(make_pair(start,w));
}
class myComparator
{
public:
    int operator() (pair<int,string> &p1,pair<int,string> &p2)
    {
        return p1.first > p2.first;
    }
};
int Graph::ShortestPath(string dep,string des,unordered_map<string,vector<string>>*ans)
{
		string s=dep;
		
		unordered_map<string,int>distance;
		
		for(auto x:g)
		distance[x.first]=INT_MAX;
		
		unordered_map<string,bool> visited;
		
		for(auto x:g)
		visited[x.first]=false;
		
		distance[s]=0;
		
		priority_queue<pair<int,string>> q;
		
		q.push({0,s});
		
		while(!q.empty())
		{
			
			string a=q.top().second;
			
			q.pop();
			
			if(visited[a])
			continue;
			
			visited[a]=true;
			
			for(auto u:g[a])
			{
				string b=u.first;
				int w=u.second;
				
				if(distance[a]+w<distance[b])
				{
					distance[b]=distance[a]+w;
					q.push({-1*distance[b],b});  //make sure we want minheap
                    (*ans)[b].clear();
					for(auto x:(*ans)[a])
                    (*ans)[b].push_back(x);
                    (*ans)[b].push_back(a);
				}
			}
			
		}
		
		return p=distance[des];
}
void Graph::Display()
{
	for(auto x:g)
	cout<<x.first<<'\n';
}

int Graph::Price()
{
	return (p/14)*120;                         //approximate diesal cost for entire journey
}
int main()
{
    Graph g;
    cout<<"Please enter the data as shown below."<<endl;
    cout<<"City1  City2  Distance between 2 cities(in km): "<<endl;
	
	cout<<"Enter 0 to finish"<<endl;
    string city1,city2;
    int w;
    while(1)
    {
        cin>>city1;
		if(city1=="0")
		break;
		cin>>city2>>w;	
		g.addEdge(city1,city2,w);
    }
    int flag = 0;
    while(flag==0)
    {
        unordered_map<string,vector<string>>ans;
        cout<<"List of all cities is here:"<<endl;
        g.Display();
        cout<<"Please enter the departure city(please note that input is case sensitive): ";
        string dep;
        cin>>dep;
        cout<<endl;
        cout<<"Please enter the destination city: ";
        string desti;
        cin>>desti;
        cout<<"\nMinimum distance between "<<dep<<" and "<<desti<<" :";
	    cout<<g.ShortestPath(dep,desti,&ans)<<"km"<<'\n';
        cout<<"-> The shortest path is below: "<<endl;
        for(auto x:ans[desti])                                      //shows the shortest path
        {
            cout<<x<<" "<<"->"<<" ";
        }
        cout<<desti<<endl;
        cout<<"\nCost of travelling : "<<g.Price()<<'\n';
	
	    cout<<"\nEnter 1 to for another question and 0 to exit the program : ";
	
	    cin>>flag;
    }
}
