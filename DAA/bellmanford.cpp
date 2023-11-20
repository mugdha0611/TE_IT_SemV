#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//struct for edge
struct Edge{
    int source, destination, weight;
};

//bellman ford function
void bellmanFord(vector<Edge> &edges, int n, int source){
    vector <int> dist(n,INT_MAX);
    dist[source] = 0;
    for(int i = 0; i<n-1;i++){
        for(auto it : edges){
            if(dist[it.source] != INT_MAX && dist[it.source]+ it.weight < dist[it.destination]){
                dist[it.destination] = dist[it.source]+ it.weight ;
            }
        }
    }

    //checking for negative weight cycle
    for(const Edge &edge : edges){
        if(dist[edge.source] != INT_MAX && dist[edge.source]+ edge.weight < dist[edge.destination]){
            cout<<"\ngraph contains -ve egde cycle. doesnt work";
            return;
        }
    }

    //printing shortest dist:
    cout<<"\n shortest dist from source "<<source<<"\nto other is:";
    for(int i =0; i<n; i++){
        cout<<"Vertex"<<i<<":"<<dist[i]<<endl;
    }
}

int main(){
    int numV, numE;
    cout<<"\nEnter the number of vertices and edges:"<<endl;
    cin>>numV>>numE;

    vector <Edge> edges(numE);
    cout<<"\nenter source, dest and weight for each :"<<endl;
    for(int i = 0; i<numE; i++){
        cin>>edges[i].source>>edges[i].destination>>edges[i].weight;
    }

    int source;
    cout<<"\nEnter source vertex:"<<endl;
    cin>>source;
    bellmanFord(edges, numV, source);
    return 0;
}