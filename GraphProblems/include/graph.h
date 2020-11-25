#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "llist.h"

using namespace std;

template <typename T>
class graph
{
private:
	llist<llist<T> > g;
public:
	node_l<T>* point(const T&);
	void addVertex(const T&);
	void deleteVertex(const T&);
	bool hasVertex(const T&);
	void addEdge(const T&, const T&);
	void deleteEdge(const T&, const T&);
	bool hasEdge(const T&, const T&);

	void enterGraph();
	llist<T> getVertices();
	void print();
	bool isEmpty();
	void vertices(llist<T> & l);
};

template <typename T>
void graph<T>::vertices(llist<T> & l)
{
    g.iterStart();
    node_l<llist<T> > * p = g.iter();

    while(p){
        p->data.iterStart();
        node_l<T> * q = p->data.iter();
        l.toEnd(q->data);
        p = g.iter();
    }
}

template <typename T>
node_l<T> * graph<T>::point(const T & a)
{
    g.iterStart();
    node_l<llist<T>> * p;
    node_l<T> * q;

    do{
        p = g.iter();
        p->data.iterStart();
        q = p->data.iter();
    }while(p && q->data != a);

    if(q->data == a){
        return q;
    }
    return NULL;
}

template <typename T>
void graph<T>::addVertex(const T & a)
{
    llist<T> l;
    l.toEnd(a);

    g.toEnd(l);
}

template <typename T>
void graph<T>::enterGraph()
{
	char c;
	do
	{
		cout << "Enter graph vertex: ";
		int x; cin >> x;
		addVertex(x);
		cout << "Add another vertex (y/n)? "; cin >> c;
	} while (c == 'y');
	cout << "Edges:\n";
	do
	{
		cout << "Enter start vertex: ";
		int x; cin >> x;
		cout << "Enter end vertex: ";
		int y; cin >> y;
		addEdge(x, y);
		cout << "Add another edge (y/n)? "; cin >> c;
	} while (c == 'y');
}

template <typename T>
void graph<T>::deleteVertex(const T & a)
{
    g.iterStart();
    node_l<llist<T> >* p = g.iter(), *temp = NULL;

    while(p){
        p->data.iterStart();
        node_l<T> * q = p->data.iter();

        if(q->data == a){
            temp = p;
        }

        do{
            q = q->next;
        }while(q && q->data !=a);

        if(q->data == a){
            T x;
            p->data.deleteElem(q,x);
        }
        p = p->next;
    }
    if(temp){
        llist<T> l;
        g.deleteElem(p,l);
    }
}

template <typename T>
bool graph<T>::hasVertex(const T & a)
{
    node_l<T> * q = NULL;

    q = point(a);

    if(q){
        return true;
    }
}

template <typename T>
llist<T> graph<T>::getVertices()
{
	llist<T> l;
	g.iterStart();
	node_l<llist<T> > *p = g.iter();
	while (p)
	{
		p->data.iterStart();
		node_l<T> *q = p->data.iter();
		l.toEnd(q->data);
		p = p->next;
	}
	return l;
}

template <typename T>
void graph<T>::print()
{
    g.iterStart();
    node_l<llist<T> > * p = g.iter();

    while(p){
        p->data.print();
        p = p->next;
    }
}

template <typename T>
bool graph<T>::isEmpty()
{
    return (g.length() == 0);
}

template <typename T>
void graph<T>::addEdge(const T & a, const T & b)
{
    node_l<T> * p = point(a);
    while(p->next){
        p = p->next;
    }
    node_l<T> * q = new node_l<T>;
    q->data = b;
    q->next = NULL;

    p->next = q;
}

template <typename T>
void graph<T>::deleteEdge(const T & a, const T & b)
{
    g.iterStart();
    node_l<llist<T> > * p;
    node_l<T> * q;

    do{
        p = g.iter();
        p->data.iterStart();
        q = p->data.iter();
    }while(p && q->data != a);

    do{
        q = q->next;
    }while(q && q->data != b);

    if(q->data == b){
        T x;
        p->data.deleteElem(q,x);
    }
}

template <typename T>
bool graph<T>::hasEdge(const T & a, const T & b)
{
    node_l<T> * p = point(a);
    while(p){
        if(p->data == b){
            return true;
        }
        p = p->next;
    }
    return false;
}
#endif // GRAPH_H
