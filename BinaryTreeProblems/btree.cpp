// btree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
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
void printArray(T * array, int length)
{
	for (int i = 0; i < length; i++) {
		cout << array[i] << " ";
	}
	cout << "\n";
}

template <typename T>
class tree
{
private:
	node_t<T> *root;
	void copyTree(node_t<T> *&, node_t<T> * const&) const;
	void deleteTree(node_t<T> *&);
	void createTree(node_t<T> *&) const;

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


	//Main Operations With Trees
	void printIterInorder(node_t<T> *) const; //Inorder Traversal
	void printLevels(node_t <T> *) const; //Traversal Level by Level
	void printIterPreorder(node_t<T> *)const; //Iterative Preorder Traversal
	int heightOfTree(node_t<T> *) const; //Returns the Max Height
	bool tree<T>::equalTrees(node_t<T> * , node_t<T> *); //Checks if Two Trees Are Identical
	int positiveSum(node_t<T> *, int &); //Returns Sum Of Possitive Nodes
	void printLeaves(node_t<T> *) const; //Prints All Leaves
	void printLevelbyLevel(node_t<T> *) const; 
	void printSelectedLevel(node_t<T> *, int) const; //Prints All Nodes On The Selected Level
	void numberOfNodes(node_t<T> *, int &) const; //Gets The Number Of All Nodes In Tree
	int numberOfLeaves(node_t<T> *, int &) const; //Gets The Number Of All Leaves
	int getLevel(node_t<T> *, int) const; 
	bool checkSumNodes(node_t<T> *);
	bool printAncestors(node_t<T> *, int) const;
	bool hasPathSum(node_t<T> *, int)const;
	int sum(node_t<T> *) const;
	int isSumTree(node_t<T> *) const;
	void printAllPaths(node_t<T> *) const;
	void printPathsRecursively(node_t<T> *, T *, int) const;
	int DifferenceOddEven(node_t<T> *) const;
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
void tree<T>::printIterInorder(node_t<T> *p) const
{
	if (p)
	{
		stack<node_t<T> *> st;
		node_t<T> * current = p;
		while (true) {
			while (current != nullptr) {
				st.push(current);
				current = current->left;
			}
			if (current == nullptr && st.empty() == false) {
				node_t<T> * temp = st.top();
				cout << temp->data << " ";
				st.pop();
				current = temp->right;
			}
			if (current == nullptr && st.empty() == true) {
				break;
			}
		}
	}
}

template <typename T>
void tree<T>::printIterPreorder(node_t<T> * p) const
{
	stack<node_t<T> *> st;
	st.push(p);

	while (st.empty() == false) {
		node_t<T> * temp = st.top();
		cout << temp->data << " ";
		st.pop();
		
		if (temp->right != nullptr) {
			st.push(temp->right);
		}
		if (temp->left != nullptr) {
			st.push(temp->left);
		}
	}
}

template <typename T>
void tree<T>::printLevels(node_t<T> * p) const
{
	queue<node_t <T> *> q;
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
void tree<T>::print()
{
	/*
	cout << "Inorder with iteration: ";
	printIterInorder(root);
	cout << "\nLevel order: ";
	printLevels(root);
	cout << "\nPreorder with iteration: ";
	printIterPreorder(root);
	cout << "\nHeight of tree is: ";
	cout << heightOfTree(root) << "\n";
	int sum = 0;
	positiveSum(root, sum);
	cout << "sum is: " << sum << "\nLeaves are: ";
	printLeaves(root);
	cout<< "\nLevel by level printout is:\n";
	printLevelbyLevel(root);
	cout << "\nEnter a level to print: ";
	int level;
	cin >> level;
	cout << "\nPrintout on selected level is: ";
	printSelectedLevel(root, level);
	cout << "\nNumber of nodes in the tree is: ";
	int numOfNodes = 0, numOfLeaves = 0;
	numberOfNodes(root, numOfNodes);
	cout << numOfNodes << "\nNumber of leaves is: " << numberOfLeaves(root, numOfLeaves) << "\n";
	int value;
	cout << "Enter value to search for";
	cin >> value;
	cout << "\nNode with value " << value << " is on level: " << getLevel(root, value) << "\n";
	cout << "All paths in the tree are:\n";
	printAllPaths(root);
	*/
	//cout << "\nDifference between odd and even levels' sums: "<<DifferenceOddEven(root)<<"\n";
	cout << "\nLevel by level printout is:\n";
	printLevelbyLevel(root);
}

template <typename T>
bool tree<T>::checkSumNodes(node_t<T> * p)
{
	int left_sum = 0, right_sum = 0;
	if (p == nullptr || (p->left == nullptr && p->right == nullptr)) {
		return true;
	}
	esle{
		if (p->left != nullptr) {
			left_sum = p->left->data;
		}
		if (p->right != nullptr) {
			right_sum = p->right->data;
		}
		if ((p->data = left_sum + right_sum) && checkSumNodes(p->left) && checkSumNodes(p->right)) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool checkOdd(int value)
{
	if ((value % 2) == 0) {
		return true;
	}
	else
		return false;
}

template <typename T>
int tree<T>::DifferenceOddEven(node_t<T> * p) const
{
	int level_counter = 1;
	int height = heightOfTree(root);
	queue<node_t<T> *> q;
	q.push(p);
	int sum1 = 0, sum2 = 0;
	while (level_counter <= height) {
		int node_counter = q.size();
		if (node_counter == 0) {
			break;
		}
		while (node_counter > 0) {
			node_t<T> * node = q.front();
			if (checkOdd(level_counter)) {
				sum1 += node->data;
			}
			else {
				sum2 += node->data;
			}
			q.pop();

			if (node->left != nullptr) {
				q.push(node->left);
			}
			if (node->right != nullptr) {
				q.push(node->right);
			}
			node_counter--;
		}
		level_counter++;
	}
	return sum2 - sum1;
}


template <typename T>
int tree<T>::sum(node_t<T> * p) const
{
	if (p == nullptr) {
		return 0;
	}
	return p->data + sum(p->left) + sum(p->right);
}

template <typename T>
int tree<T>::isSumTree(node_t<T> * p) const
{
	if (p == nullptr || (p->left == nullptr && p->right == nullptr)) {
		return 0;
	}
	int l_sum = sum(p->left);
	int r_sum = sum(p->right);

	if ((p->data = l_sum + r_sum) && isSumTree(p->left) && isSumTree(p - right))
	{
		return 1;
	}
}

template <typename T>
bool tree<T>::hasPathSum(node_t<T> * p, int sum) const
{
	if (p == nullptr) {
		return (sum == 0);
	}
	else
	{
		bool flag = false;
		int subSum = sum - p->data;
		if (subSum == 0 && p->left == nullptr && p->right == nullptr) {
			return true;
		}

		if (p->left != nullptr) {
			flag = flag || hasPathSum(p->left, subSum);
		}
		if (p->right != nullptr) {
			flag = flag || hasPathSum(p->right, subSum);
		}
		return flag;
	}
}

template <typename T>
bool tree<T>::printAncestors(node_t<T> * p, int target) const
{
	if (p == nullptr) {
		return false;
	}
	if (p->data == target) {
		return true;
	}
	if (printAncestors(p->left, target) || printAncestors(p->right, target)) {
		cout << p->data << " ";
		return true;
	}
	return false;
}

template <typename T>
int tree<T>::numberOfLeaves(node_t<T> * p, int & number) const
{
	if (p) {
		numberOfLeaves(p->left, number);
		if (p->left == nullptr && p->right == nullptr) {
			number++;
		}
		numberOfLeaves(p->right, number);
	}
	return number;
}

template <typename T>
void tree<T>::numberOfNodes(node_t<T> * p, int & number) const
{
	if (p) {
		numberOfNodes(p->left,number);
		number++;
		numberOfNodes(p->right,number);
	}
}

template <typename T>
bool tree<T>::equalTrees(node_t<T> * root1, node_t<T> * root2)
{
	if (root1 == nullptr && root2 == nullptr) {
		return true;
	}
	if (root1 != nullptr && root2 != nullptr) {
		return (root1->data == root2->data &&
			equalTrees(root1->left, root2->left)&& 
			equalTrees(root1->right, root2->right)
			)
	}
	return false;
}

template <typename T>
int tree<T>::positiveSum(node_t<T> * p, int & total)
{
	if (p == nullptr) {
		return 0;
	}
		positiveSum(p->left, total);
		if (p->data >= 0) {
			total = total + p->data;
		}
		positiveSum(p->right, total);
}

template <typename T>
int tree<T>::getLevel(node_t<T> * p, int value) const
{
	queue<node_t<T> *> q;
	q.push(p);
	int height = heightOfTree(root);
	int	count = 1;
	while (count <= height) {
		int node_counter = q.size();
		if (node_counter == 0) {
			break;
		}
		while (node_counter > 0) {
			node_t<T> * temp = q.front();
			if (temp->data == value) {
				return count;
			}
			q.pop();
			if (temp->left != nullptr) {
				q.push(temp->left);
			}
			if (temp->right != nullptr) {
				q.push(temp->right);
			}
			node_counter--;
		}
		count++;
	}
}

template <typename T>
void tree<T>::printSelectedLevel(node_t<T> * p, int n) const
{
	queue<node_t<T> *> q;
	q.push(p);
	int height = heightOfTree(root);
		int count = 1;
	while (count <= height) {
		int node_counter = q.size();
		while (node_counter > 0) {
			node_t<T> * temp = q.front();
			if (count == n) {
				cout << temp->data << " ";
			}
			q.pop();
			if (temp->left != nullptr) {
				q.push(temp->left);
			}
			if (temp->right != nullptr) {
				q.push(temp->right);
			}
			node_counter--;
		}
		count++;
	}
}

template <typename T>
void tree<T>::printLevelbyLevel(node_t<T> * p) const
{
	queue<node_t<T> *> q;
	q.push(p);

	while (1) {
		int counter = q.size();
		if (counter == 0) {
			break;
		}
		while (counter > 0) {
			node_t<T> * temp = q.front();
			cout << temp->data << " ";
			q.pop();

			if (temp->left != nullptr) {
				q.push(temp->left);
			}
			if (temp->right != nullptr) {
				q.push(temp->right);
			}
			counter--;
		}
		cout << "\n";
	}

}

template <typename T>
void tree<T>::printLeaves(node_t<T> * p) const
{
	if (p) {
		printLeaves(p->left);
		if (p->left == nullptr && p->right == nullptr) {
			cout << p->data<<" ";
		}
		printLeaves(p->right);
	}
}

template<typename T>
int tree<T>::heightOfTree(node_t<T> * p) const
{
	if (p == nullptr) {
		return 0;
	}
	else {
		int lHeight = heightOfTree(p->left);
		int rHeight = heightOfTree(p->right);

		if (lHeight > rHeight) {
			return lHeight + 1;
		}
		else {
			return rHeight + 1;
		}
	}
}

template <typename T>
void tree<T>::printAllPaths(node_t<T> * p) const
{
	/*int maxNodes = 0;
	numberOfNodes(root, maxNodes);
	const int MAX = maxNodes + 1;
	int path[MAX];
	*/
	int path[1000];
	printPathsRecursively(p, path, 0);
}

template <typename T>
void tree<T>::printPathsRecursively(node_t<T> * p , T * array, int length) const
{
	array[length] = p->data;
	length++;

	if (p->left == nullptr && p->right == nullptr) {
		printArray(array, length);
	}
	else {
		printPathsRecursively(p->left, array, length);
		printPathsRecursively(p->right, array, length);
	}
}

int main()
{
	tree<int> tr;
	tr.create();
	tr.print();
    return 0;
}

