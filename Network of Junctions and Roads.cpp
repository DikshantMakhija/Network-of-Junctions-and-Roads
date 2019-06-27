#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <limits.h>

using namespace std;
long int V,E;
struct node
{
	long int junction;
	long int build;
	long int traverse;
	long int traffic;
	node* right;
}; 

struct header
{
    long int junction;
    long int traffic;
    header* down;
    node* right;
};

struct Graph
{	
	header* head;
	
};
void print(Graph* graph){
	header* p = graph->head;
	while(p){
		cout<<"junction"<<p->junction<<" ";
		node* q = p->right;
		while(q){
			cout<<q->junction<<" ";
			q =q->right;
		}
		p = p->down;
		cout<<endl;
	}
}
struct Distance{
	long int junction;
	long int time;
	bool operator<(const Distance& rhs) const
    {
        return time >rhs.time;
    }
};
void add_juntion(long int junction,long int traffic, Graph* grapha){
	header* p = grapha->head;
	header* new_head = new header;
	new_head->junction = junction;
	new_head->traffic = traffic;
	new_head->down = NULL;
	new_head->right = NULL;
	long int flag = 0;
	//==cout<<" 1" <<endl;
	if(p == NULL){
		//cout<<" 2" <<endl;
		grapha->head = new_head;
	}
	else{
		do
		{	if(p->down ==NULL){
				flag = 1;
			}
			else{
			p=p->down;
			}
		} while (flag < 1);
		p->down = new_head;
	}
	
}

void add_road(long int i,long int j,long int build,long int traverse, Graph* graph){
	node* new_node = new node;
	new_node->junction = j;
	new_node->build = build;
	new_node->traverse = traverse;
	new_node->right = NULL;
	header* p = graph->head;
	while(p->down){
		if(p->junction == j){
			break;
		}
		p=p->down;
	}
	new_node->traffic = p->traffic;
	p = graph->head;
	long int flag = 0;
	while(p->down){
		if(p->junction == i){
			break;
		}
		p=p->down;
	}
	//cout<<p->junction<<endl;
	node* q = p->right;
	if(q == NULL){
		p->right = new_node;
	}
	else{
		do
		{	if(q->right ==NULL){
				flag = 1;
			}
			else{
			q = q->right;
			}
		} while (flag < 1);
		q->right = new_node;
	}


	new_node = new node;
	new_node->junction = i;
	new_node->build = build;
	new_node->traverse = traverse;
	new_node->right = NULL;
	p = graph->head;
	while(p->down){
		if(p->junction == i){
			break;
		}
		p=p->down;
	}
	new_node->traffic = p->traffic;
	p = graph->head;
	while(p->down){
		if(p->junction == j){
			break;
		}
		p=p->down;
	}
	flag = 0;
	q = p->right;
	if(q == NULL){
		p->right = new_node;
	}
	else{
		do
		{	if(q->right ==NULL){
				flag = 1;
			}
			else{
			q = q->right;
			}
		} while (flag < 1);
		q->right = new_node;
	}
}

void demolish_road(long int i,long int j, Graph* graph){
	header* p = graph->head;
	while(p->down){
		if(p->junction == i){
			break;
		}
		p=p->down;
	}
	
	node* q = p->right;
	node* r = p->right;
	if(q->junction == j)
	{
		p->right = q->right;
		//delete q;
    }
	else{
	
	q = q->right;
	while(q->right){	
		if(q->junction == j){
			break;
		}
		r = q;
		q = q->right;
	}
	r->right = q->right;
	//delete q;
	}
	p = graph->head;
	while(p->down){
		if(p->junction == j){
			break;
		}
		p=p->down;
	}
	q = p->right;
	if(q->junction == i)
	{
		p->right = q->right;
		//delete q; 
	}
	else{
	r = p->right;
	q = q->right;
	while(q->right){	
		if(q->junction == i){
			break;
		}
		r = q;
		q = q->right;
	}
	r->right = q->right;
	//delete q;
	}
}
long int no = 0;
void printPath(long int parent[],long int j)
{
     
    // Base Case : If j is source
    if (parent[j] == - 1)
        return;
 
    printPath(parent, parent[j]);
    //no = no + 1;
    cout<<" "<<j;
}
void counter(long int parent[],long int j){
     if (parent[j] == - 1)
        return;
    counter(parent, parent[j]);
    no = no + 1;
}
void shortestpath(long int src,long int dest, Graph* graph){
    if(V == 1 || E == 0 ){
        cout<<"-1"<<endl;
    }
    else{
    priority_queue<Distance> pq;
	long int dist[1000000],parent[1000000];
    parent[src] = -1;    
    for(long int i =0; i<1000000;i++){
        
     
     dist[i]=INT_MAX;
    }
        Distance d;
	d.junction = src;
	d.time = 0;
	pq.push(d);
	dist[src] = 0;
	//cout<<"boom"<<endl;
    while(!pq.empty()){
		Distance x;
		x = pq.top();
		long int u = x.junction;
        pq.pop();
		header* p = graph->head;
		while(p){
			//cout<<p->junction<<endl;
            if(p->junction == u){
				break;
			}
            else{
			p=p->down;
            }
		}
    
		//cout<<p->junction<<endl;
		node* q = p->right;
		long int min = INT_MAX,min_junction;
        while(q)
		{	if(p->junction == src){
            long int reach = (q->traverse);
            if(dist[q->junction]>reach){
				//cout<<u<<endl;
                parent[q->junction] =  u;
				dist[q->junction] = reach;
				Distance final;
				final.junction = q->junction;
				final.time = dist[q->junction];
				//cout<<q->junction<<" "<<dist[q->junction]<<endl;
                pq.push(final);		
			}    
        }
            else{
            long int t = p->traffic;
			long int d = dist[u];
            long int reach;
            if(d%t == 0){
                reach = d +q->traverse; 
            }
                else{
                reach = (d+ t - (d%t)) + (q->traverse);
                }
                    if(dist[q->junction]>reach){
				parent[q->junction] =  u;
				dist[q->junction] = reach;
				Distance final;
				final.junction = q->junction;
				final.time = dist[q->junction];
				//cout<<q->junction<<" "<<dist[q->junction]<<endl;
                pq.push(final);		
			}
            }
		q = q->right;
		}
        
    
    }
    /*cout<<"resutl"<<endl;
    for (int i = 0; i<100;i++){
        if(dist[i]<INT_MAX){
        cout<<i<<" "<<dist[i]<<endl;
        
        }
    }*/
    if(dist[dest]<INT_MAX){
    counter(parent,dest);
    cout<<dist[dest]<<" "<<no+1<<" "<<src;
    printPath(parent,dest);
    no = 0;
    }
    else{
        cout<<"-1"<<endl;
    }
	no = 0;
    cout<<endl;
    }
}
struct Edge
{   long int pos;
    long int src;
    long int dest;
    long int build;
    long int traverse;
    bool operator<(const Edge& rhs) const
    {
        return build >rhs.build;
    }
};
struct Ans{
	long int src;
	long int dest;
    bool operator<(const Ans& rhs) const
    {
        if(src == rhs.src){
        	return dest>rhs.dest;	
		}
		else{
			return src > rhs.src;
		}
		
    }
};
struct junction{
    long int junction;
    long int traverse;
};
junction junctions[1000000];
 
struct subset
{
    long int parent;
    long int rank;
    long int org;
};
 
int find(struct subset subsets[], int i)
{	long int k;
    for (int j = 0; j<V;j++){
        if(subsets[j].org ==i){
          k = j; 
            break;
        }
    }
    i = k;
    if (subsets[i].parent != subsets[i].org)
        {	//cout<<"parent"<<subsets[i].parent<<endl;
			subsets[i].parent = find(subsets, subsets[i].parent);
		}
    return subsets[i].parent;
}
 
void Union(struct subset subsets[],long int x,long int y)
{
    long int xroot = find(subsets, x);
    long int yroot = find(subsets, y);
    
    long int xindex=-1;
    for(long int a=0; a<V; a++){
        if(subsets[a].org==xroot){
            xindex=a;
            break;
        }
    }
    long int yindex=-1;
    for(long int a=0; a<V; a++){
        if(subsets[a].org==yroot){
            yindex=a;
            break;
        }
    }
    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xindex].rank < subsets[yindex].rank)
        subsets[xindex].parent = yroot;
    else if (subsets[xindex].rank > subsets[yindex].rank)
        subsets[yindex].parent = xroot;
    
    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[yindex].parent = xroot;
        subsets[xindex].rank++;
    }
}

    
void KruskalMST(priority_queue<Edge> pq,junction junctions[])
{   if( V ==1 || E==0){
    cout<<"-1"<<endl;
    }
    else{
    priority_queue<Ans> MST;  // Tnis will store the resultant MST
    subset *subsets = new subset[V];
    
    for (long int i =0; i<V; i++)
    {
        subsets[i].parent =junctions[i].junction;
        subsets[i].org = junctions[i].junction;
        subsets[i].rank = 0;
    }
    long int e = 0;  // An index variable, used for result[]
    long int flag = 0;
    long int weight = 0; // An index variable, used for sorted edges
 	while (e < V - 1)
    {
        if(pq.empty()){
            cout<<"-1"<<endl;
            flag = 1;
            break;
        }
        Edge next_edge = pq.top();
        pq.pop();
        
        
        //cout<<"nx"<<next_edge.src<<endl;
        
		long int x = find(subsets, next_edge.src);

		long int y = find(subsets, next_edge.dest); 
        if (x != y)
        {   Ans ans;
            ans.src = next_edge.src;
            ans.dest = next_edge.dest;
            weight = weight + next_edge.build;
            if(ans.src>ans.dest){
            	long int temp = ans.dest;
            	ans.dest = ans.src;
            	ans.src = temp;
			}
			MST.push(ans);
            e++;
			Union(subsets, x, y);
        }
        //cout<<"1"<<endl;
    }
    if(flag == 0){
        cout<<e<<" "<<weight;
        for (int i = 0; i < e; i++){
            Ans ans1 = MST.top();
            //cout<<"1"<<endl;
		    MST.pop();
            cout<<" "<<ans1.src<<" "<<ans1.dest;
        }
   
    cout<<endl;    
    }
    }
    return;
}

int main(){
	priority_queue<Edge> q, tempQ;
    
    Graph* graph = new Graph;
	cin>>V>>E;
	graph->head =NULL;
	
	for(long int i = 0;i < V; i++){
		long int x,y,z,a ;
        cin>>x>>y;
		add_juntion(x, y, graph);
        junctions[i].junction = x;
        junctions[i].traverse = y;//cout<<graph->head->junction;
	}
        Edge edge;

	for(long int i = 0; i<E; i++){
		long int x,y,z,a ;
        cin>>x>>y>>z>>a;
		add_road(x,y,z,a, graph);
        edge.src = x;
        edge.dest = y;
        edge.build = z;
        edge.traverse = a;
        q.push(edge);
	}
    	 priority_queue<Edge> temp;

	long int total,operation;
    cin>>total;
     for (long int abc=0; abc<total; abc++){
        cin>>operation;
        switch(operation){
            case 1 : {
                long int x,y,z,a ;
                cin>>x>>y;
           		add_juntion(x, y, graph);
                junctions[V].junction = x;
                junctions[V].traverse = y;//cout<<graph->head->junction
                V=V+1;
                break;                                
                }
            case 2 : {
                long int x,y,z,a ;
                cin>>x>>y>>z>>a;
                add_road(x,y,z,a, graph);
                Edge e;
                e.src= x;
                e.dest=y;
                e.build =z;
                e.traverse = a;
                q.push(e);
                E = E+1;
                break;
            }
            case 3 : {
                long int x,y,z,a ;
                cin>>x>>y;
                demolish_road(x,y,graph);
                for(long int i=0; i<E; i++){
                    Edge e=q.top();
                    if(!((e.src==x && e.dest==y)||(e.src==y && e.dest==x))){
                        temp.push(q.top());   
                    }
                    q.pop();
                }
                q=temp;
                while(!temp.empty()){
                    temp.pop();
                }
                E = E-1;
                break;
            }
            case 4 : {
                long int x,y,z,a ;
                priority_queue<Edge> tempQ;//cin>>x;
                tempQ = q;
                KruskalMST(tempQ, junctions);
                break;    
            }
            case 5 : {
                long int x,y,z,a ;
            	cin>>x>>y;
                shortestpath(x,y,graph);
            	break;
            }
            default : 
                break;
            }
        }
}