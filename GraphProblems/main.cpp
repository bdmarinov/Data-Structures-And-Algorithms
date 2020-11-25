#include <iostream>
#include <queue>
#include "graph.h"

using namespace std;

 //Checks if there is a way between start and end
template <typename T>
bool hasWay(graph<T> g, T start, T end, llist<T> &visited)
{
	visited.toEnd(start);

	if (start == end)
		return true;

	node_l<int> *p = g.point(start);
	p = p->next;

	while (p)
	{
		if (!visited.isMember(p->data) && hasWay(g, p->data, end, visited))
				return true;
		p = p->next;
	}

	return false;
}

//Gets all ways from a to b
template <typename T>
void allWays(graph<T> & g, const T & a, const T & b, llist<T> & visited)
{
    visited.toEnd(a);
    if(a == b){
        visited.print();
    }

    node_l<T> * p = g.point(a);
    p = p->next;

    while(p){
        if(!visited.isMember(p->data)){
            allWays(g, p->data, b, visited);
        }
        p = p->next;
    }
    visited.deleteLast();
}

//BFS on a graph
template <typename T> 
void BFS(graph<T> & g, const T & a)
{
    queue<T> q;
    llist<T> l;
    q.push(a);
    l.toEnd(a);

    while(!q.empty()){
        node_l<T> * p = g.point(q.front());
        q.pop();

        cout<<p->data<<" ";
        p = p->next;

        while(p){
            if(!l.isMember(p->data)){
                q.push(p->data);
                l.toEnd(p->data);
            }
            p = p->next;
        }
    }
}

//Checks if vertex has ways to all other vertices
template <typename T>
bool hasWayToAll(graph<T> & g, T vertex)
{
    llist<T> vertices = g.getVertices();
    vertices.iterStart();
    node_l<T> * p = vertices.iter();

    while(p){
        llist<T> helper;
        if(!hasWay(g, vertex, p->data, helper)){
            return false;
        }
        p = p->next;
    }
    return true;
}

//Gets all parents
template <typename T>
llist<T> getMotherVertex(graph<T> & g)
{
    llist<T> l = g.getVertices(), mothers;

    l.iterStart();
    node_l<T> * p = l.iter();

    while(p){
        if(hasWayToAll(g,p->data)){
            mothers.toEnd(p->data);
        }
        p = p->next;
    }
   return mothers;
}


template <typename T>
void hasCyclicWay(graph<T> & g, T vertex)
{
    llist<T> l = g.getVertices();

    l.iterStart();
    node_l<T> * p = l.iter();

    while(p){
        llist<T> helper;
        if(p->data != vertex && hasWay(g,p->data,vertex, helper)){
            helper.iterStart();
            node_l<T> * q = helper.iter();
            T first = q->data,last;
            while(q->next){
                q = q->next;
            }
            last = q->data;
                llist<T> h;
                if(g.hasEdge(first, last)){
                helper.print();
            }
        }
        p = p->next;
    }

}

template <typename T>
void cyclic(graph<T> & g, T start, T end, llist<T> & visited)
{
    visited.toEnd(start);

    if(start == end){
        visited.print();
        //return;
    }

    node_l<T> * p = g.point(start);
    p = p->next;

    while(p){
            if(visited.isMember(p->data)){
                visited.print();
            }
            if(!visited.isMember(p->data)){
                cyclic(g, p->data, end, visited);
            }
        p = p->next;
    }
    visited.deleteLast();
}

template <typename T>
void DFS(graph<T> & g, T a, llist<T> & visited, llist<T> & helper)
{
    visited.toEnd(a);

    node_l<T> * p = g.point(a);

    helper.toEnd(a);
    //cout<<p->data<<" ";

    p = p->next;
    while(p){
        if(!visited.isMember(p->data)){
            DFS(g, p->data, visited, helper);
        }
        p = p->next;
    }
}

template <typename T>
void DFSFromEach(graph<T> & g)
{
    llist<T> vertices = g.getVertices();
    vertices.iterStart();
    node_l<T> * p = vertices.iter();

    llist<T> helper;

    while(p){
        if(!helper.isMember(p->data)){
            llist<T> paths;
            DFS(g,p->data,paths, helper);
            paths.print();
            cout<<"\n";
        }
        p = p->next;
    }
}

template <typename T>
void someBFS(graph<T> & g, T start, llist<T> & visited)
{
    queue<T> q;
    llist<T> path;
    q.push(start);
    visited.toEnd(start);
    path.toEnd(start);

    while(!q.empty()){
        int size = q.size();

        while(size > 0){
            T current = q.front();
            cout<<current<<" ";
            q.pop();

            node_l<T> * p = g.point(current);
            p = p->next;

            while(p){

                if(!visited.isMember(p->data) || p->data == start){
                    //path.toEnd(current);
                    //visited.print();
                    q.push(p->data);
                    visited.toEnd(p->data);
                }
//                if(p->data == start){
//                        cout<<p->data;
//                    cout<<"cycle found\n";
//
//                    path.toEnd(start);
//                    path.print();
//                }
                p = p->next;
            }
            size--;
            }
        cout<<"\n";
    }
}

template <typename T>
llist<T> getListOfVertex(graph<T> & g, T target)
{
    llist<T> l;

    node_l<T> * p = g.point(target);
    while(p){
        l.toEnd(p->data);
        p = p->next;
    }
    return l;
}

template <typename T>
void transponseGraph(graph<T> & g)
{
    graph<T> copyG = g;
    llist<T> vertices = g.getVertices();
    llist<T> copyV = vertices;

    vertices.iterStart();
    node_l<T> * p = vertices.iter();

    while(p){
        copyV.iterStart();
        node_l<T> * q = copyV.iter();
        while(q){

            if(p->data != q->data && g.hasEdge(p->data, q->data) && (getListOfVertex(copyG, p->data).isMember(q->data))){
                cout<<p->data<<" "<<q->data<<"\n";
                g.deleteEdge(p->data, q->data);
                g.addEdge(q->data, p->data);
            }

            q = q->next;
        }
        cout<<"\n";
        p = p->next;
    }
}



int main()
{
    graph<int> g;
    g.enterGraph();
    llist<int> l;
//    g.print();
//    graph<int> g1 = g;
//    g1.print();
    //someBFS(g,0,l);
   // g.print();
    transponseGraph(g);

    g.print();
    //g.print();
//    DFSFromEach(g);
//    llist<int> l = g.getVertices();
//    l.print();
//    llist<int> l;
//    DFS(g,0,l);

//    l = getListOfVertex(g, 0);
    //l.print();
    return 0;
}




















/*

graph<int> g;
    g.enterGraph();
//    g.print();
    //llist<int> l,t,p,q,r;

//    cout<<hasWayToAll(g,0)<<"\n";
    llist<int> l,m;
    //hasWay(g,0,3,l);
   // l.print();
   cyclic(g,3,3,l);
   //DFS(g,1,l,m);
   // hasCyclicWay(g,0,0,l);
//hasCyclicWay(g,0);
//    cout<<hasWay(g, 0, 1, l)<<"\n";
//    cout<<l.length()<<"\n";
//    cout<<hasWay(g, 0, 1, t)<<"\n";
//    cout<<hasWay(g, 0, 2, p)<<"\n";
//    cout<<hasWay(g, 0, 3, q)<<"\n";
//    cout<<hasWay(g, 0, 1, r)<<"\n";
    //llist<int> mothers = getMotherVertex(g);
    //mothers.print();


*/
