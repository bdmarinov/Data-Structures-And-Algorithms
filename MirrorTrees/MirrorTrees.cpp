// zadachakontrolno.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <queue>

using namespace std;

template <typename T>
struct node_t
{
	T data;
	node_t<T> *left, *right;

	node_t(T _data, node_t<T> * _left = NULL,
		node_t<T> *_right = NULL) :
		data(_data), left(_left), right(_right) {}
};

template <typename T>
class tree
{
private:
	node_t<T> *root;
	void copyTree(node_t<T> *&, node_t<T> * const&) const;
	void deleteTree(node_t<T> *&);
	void createTree(node_t<T> *&) const;
	void printTree(node_t<T> *p) const;
	int heightOfTree(node_t<T> *) const;
	void printLevels(node_t<T> *) const;
	void printLevelByLevel(node_t<T> *) const;
	void findMaxNode(node_t<T> *, int & ) const;
	bool checkEqualLevels(node_t<T> *, node_t<T> *) const;

public:
	tree();
	tree(tree<T> const&);
	tree<T>& operator=(tree<T> const &);
	~tree();
	bool isEmpty() const;
	T getRoot() const;
	tree<T> leftTree() const;
	tree<T> rightTree() const;
	void createRLF(T, tree<T> const&, tree<T> const&);
	void create();
	void print();
};

template <typename T>
tree<T>::tree()
{
	root = NULL;
}

template <typename T>
tree<T>::tree(tree<T> const &t)
{
	copyTree(root, t.root);
}

template <typename T>
tree<T>& tree<T>::operator=(tree<T> const &t)
{
	if (this != &t) {
		deleteTree(root);
		copyTree(root, t.root);
	}
	return *this;
}

template <typename T>
tree<T>::~tree()
{
	deleteTree(root);
}

template <typename T>
T tree<T>::getRoot() const
{
	return root->data;
}

template <typename T>
tree<T> tree<T>::leftTree() const
{
	tree<T> t;
	copyTree(t.root, root->left);
	return t;
}

template <typename T>
tree<T> tree<T>::rightTree() const
{
	tree<T> t;
	copyTree(t.root, root->right);
	return t;
}

template <typename T>
bool tree<T>::isEmpty() const
{
	return root == NULL;
}

template <typename T>
void tree<T>::createRLF(T x, tree<T> const& leftTree, tree<T> const& rightTree)
{
	root = new node_t<T>(x);
	copyTree(root->left, leftTree.root);
	copyTree(root->right, rightTree.root);
}

template <typename T>
void tree<T>::create()
{
	createTree(root);
}

template <typename T>
void tree<T>::createTree(node_t<T> *& pos) const
{
	T x; char c;
	cout << "root: ";
	cin >> x;

	pos = new node_t<T>(x);
	pos->left = NULL;
	pos->right = NULL;

	cout << "Add left tree of: " << x << ", y/n? ";
	cin >> c;
	if (c == 'y')
		createTree(pos->left);

	cout << "Add right tree of: " << x << ", y/n? ";
	cin >> c;
	if (c == 'y')
		createTree(pos->right);
}

template <typename T>
void tree<T>::print()
{
	printTree(root);
	cout << "\nLevel printout: ";
	printLevels(root);
	cout << "\nLevel by Level printout:\n";
	printLevelByLevel(root);
	cout << "\n";
	int max = root->data;
	findMaxNode(root, max);
	cout << "Max node value is: " << max << "\n";

}

template <typename T>
void tree<T>::copyTree(node_t<T>* &to, node_t<T>* const &from) const
{
	to = NULL;
	if (from)
	{
		to = new node_t<T>(from->data);
		copyTree(to->left, from->left);
		copyTree(to->right, from->right);
	}
}

template <typename T>
void tree<T>::deleteTree(node_t<T>* &r)
{
	if (r)
	{
		deleteTree(r->left);
		deleteTree(r->right);

		delete r;
	}
}

template <typename T>
void tree<T>::printTree(node_t<T> *p) const
{
	if (p)
	{
		printTree(p->left);
		cout << p->data << ' ';
		printTree(p->right);
	}
}

template <typename T>
int tree<T>::heightOfTree(node_t<T> * p) const
{
	if (p == nullptr) {
		return 0;
	}
	else {
		int lDepth = heightOfTree(p->left);
		int rDepth = heightOfTree(p->right);
		if (lDepth > rDepth) {
			return (lDepth + 1);
		}
		else {
			return (rDepth + 1);
		}
	}
}

template<typename T>
void tree<T>::printLevels(node_t<T> * p) const
{
	queue<node_t<T> *> q;
	q.push(p);

	while (q.empty() == false) {
		node_t<T> * node = q.front();
		cout << node->data << " ";
		q.pop();

		if (node->left != nullptr) {
			q.push(node->left);
		}
		if (node->right != nullptr) {
			q.push(node->right);
		}
	}
}

template <typename T>
void tree<T>::findMaxNode(node_t<T> * p, int & max) const
{
	if (p)
	{
		findMaxNode(p->left, max);
		(p->data > max) ? max = p->data : max = max;
		findMaxNode(p -> right, max);
	}
}

template <typename T>
bool tree<T>::checkEqualLevels(node_t<T> * root1, node_t<T> * root2) const
{
	queue<node_t<T> *> q1, q2;
	q1.push(root1);
	q2.push(root2);
	int MAX1 = root1->data, MAX2 = root2->data;
	findMaxNode(root1, MAX1);
	findMaxNode(root2, MAX2);

	if (MAX1 != MAX2) {
		return false;
	}
	else {
		int MAX = MAX1 + 1;
		int array1[MAX + 1], int array2[MAX + 1];
		for (int i = 0; i < MAX + 1; i++) {
			array1[i] = 0;
			array2[i] = 0;
		}

	int level_counter = 1, height = heightOfTree(root);
	while (level_counter <= height) {
		int node_counter = q.s 
		}
	}
}

template <typename T>
void tree<T>::printLevelByLevel(node_t<T> * p) const
{
	queue<node_t<T> *> q;
	q.push(p);

	int counter = 1;
	int height = heightOfTree(root);
	while (counter <= height) {
		int nodeCounter = q.size();
		if (nodeCounter == 0) {
			break;
		}
		while (nodeCounter > 0) {
			node_t<T> * node = q.front();
			cout << node->data << " ";
			q.pop();
			
			if (node->left != nullptr) {
				q.push(node->left);
			}
			if (node->right != nullptr) {
				q.push(node->right);
			}
			nodeCounter--;
		}
		counter++;
		cout << "\n";
	}
}

int main()
{
	tree<int> tr;
	tr.create();
	tr.print();
    return 0;
}

