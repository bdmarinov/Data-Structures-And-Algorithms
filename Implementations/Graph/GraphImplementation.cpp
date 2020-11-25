// GraphImplementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <queue>
#include "LinkedList.h"

using namespace std;

template <typename T>
class graph {
	
public:
	node_l<T> * point(const T & );
	void addVertex(const T & );
	void deleteVertex(const T&);
	bool hasVertex(const T&);
	void addEdge(const T&, const T&);
	void deleteEdge(const T&, const T&);
	bool hasEdge(const T&, const T&);

	void enterGraph();
	llist<T> getVertices() const;
	void print()const ;
	bool isEmpty() const;

private:
	llist<llist<T>> g;
};

template <typename T>
node_l<T> * graph<T>::point(const T & a)
{
	g.iterStart();
	node_l <llist<T>> * p;
	node_l <T> *q;

	do {
		p = g.iter();
		p->data.iterStart();
		q = p->data.iter();
	} while (p && q->data != a);

	return q;
}

template <typename T>
void graph<T>::addVertex(const T & a)
{
	llist<T> l;
	l.toEnd(a);

	g.toEnd(l);
}

template <typename T>
void graph<T>::deleteVertex(const T & a)
{
	g.iterStart();
	node_l <llist<T>> * p = g.iter(), temp;
	
	while (p) {
		p->data.iterStart();
		node_l <T> * q = p->data.iter();
		
		if (q->data == a) {
			temp = p;
		}

		do {
			q = q->next;
		} while (q && q->data != a);

		int x;
		p->data.deleteElem(q, x);
	}
	if (temp) {
		llist<T> list;
		g.deleteElem(temp, list);
	}
}

template <typename T>
bool graph<T>::hasVertex(const T & a)
{
	g.iterStart();
	node_l <llist<T>> * p = g.iter();
	node_l <T> * q;
	while (p) {
		p->data.iterStart();
		q = p->data.iter();
		if (q->data == a) {
			return true;
		}
	}
	return false;
}

template <typename T>
void graph<T>::addEdge(const T & a, const T & b)
{
	node_l <T> * q = point(a);

	while (q) {
		q = q->next;
	}
	node_l <T> * p = new node_l<T>;
	p->data = b;
	p->next = nullptr;
	q = p;
}

template <typename T>
bool graph<T>::hasEdge(const T & a, const T & b)
{
	g.iterStart();
	node_l <llist<T>> * p;
	node_l <T> * q;
	do {
		p = g.iter();
		p->data.iterStart();
		q = p->data.iter();
	} while (p && q->data != a);

	while (q) {
		if (q->data == b) {
			return true;
		}
		q = q->next;
	}
	return false;
}

template <typename T>
void graph<T>::deleteEdge(const T & a, const T & b)
{
	g.iterStart();
	node_l <llist<T>> * p;
	node_l <T> * q;

	do {
		p = g.iter();
		p->data.iterStart();
		q = p->data.iter();
	} while (p && q->data != a);

	while (q->data != b) {
		q = q->next;
	}
	T x;
	p->data.deleteElem(q, x);
}

template<typename T>
void graph<T>::print() const
{
	g.iterStart();
	node_l <llist<T>> * p = g.iter();
	while (p) {
		p->data.print();
		p = g.iter();
	}
	cout << "\n";
}

template <typename T>
llist<T> graph<T>::getVertices() const
{
	llist<T> list;
	g.iterStart();
	node <llist<T>> * p = g.iter();
	while (p) {
		p->data.iterStart();
		node_l <T> * q = p->data.iter();
		list.toEnd(q->data);
		p = g.iter();
	}
	return list;
}

template <typename T>
bool graph<T>::isEmpty() const
{
	return g.length() == 0;
}

template <typename T>
void graph<T>::enterGraph()
{
	char c;
	do {
		T value;
		cin >> value;
		addVertex(value);
		cout << "y for new vertex\n";
		cin >> c;
	} while (c == 'y');

	do {
		T value1, value2;
		cout << "enter start vertex\n";
		cin >> value1;
		cout << "enter end vertex\n";
		cin >> value2;
		addEdge(value1, value2);
		cout << "y for new edge\n";
		cin >> c;
	} while (c == 'y');
}

template <typename T>
bool hasWay(const graph<T> & g, T start, T end, llist<T> & visited)
{
	visited.toEnd(start);
	if (start == end) {
		return true;
	}

	node_l <T> * p = g.point(start);
	p = p->next;

	while (p) {
		if (!visited.isMember(p->data)) {
			if (hasWay(g, p->data, end, visited)) {
				return true;
			}
			visited.deleteLast();
		}
		p = p->next;
	}
}

template <typename T>
void printAllWays(const graph<T> & g, T start, T end, llist<T> & list, const llist<T> & members, const int n, int currentLength)
{
	list.toEnd(start);

	if (start == end && currentLength == n) {
		list.print();
		return;
	}

	node_l <T> * p = g.point(start);
	p = p->next;

	while (p) {
		if (currentLength < n && !members.isMember(p->data)) {
			printAllWays(g, p->data, end, list, members, n, currentLength + 1);
			list.deleteLast();
		}
		p = p->next;
	}
}

template <typename T>
void DFS(const graph<T> & g, T vertex, int * visited)
{
	visited[vertex] = true;

	cout << vertex << " ";

	node_l <T> * p = g.point(vertex);
	p = p->next;

	while (p) {
		if (!visited[p->data]) {
			DFS(g, p->data, visited);
		}
		p = p->next;
	}
}

template <typename T>
void BFS(const graph<T> & g, T vertex)
{
	queue<T> q;
	llist<T> list;

	q.push(vertex);
	list.toEnd(vertex);

	while (!q.empty()) {
		T current = q.front();
		q.pop();
		cout << current << " ";

		node_l <T> * p = g.point(current);
		p = p->next;

		while (p) {
			if (!list.isMember(p->data)) {
				q.push(p->data);
				list.toEnd(p->data);
			}
			p = p->next;
		}
	}
}



int main()
{

	llist<int> list;
	list.toEnd(5);
	list.toEnd(7);
	list.toEnd(12);
	list.toEnd(14);
	list.toEnd(18);
	list.toEnd(21);
	list.deleteLast();

	list.print();

    return 0;
}

