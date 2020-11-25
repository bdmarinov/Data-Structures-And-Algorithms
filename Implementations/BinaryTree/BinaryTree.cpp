#include<iostream> 
#include <queue>
#include <stack>

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
	void levelByLevelPrint(node_t<T> * p) const;
	void getLeafNodes(node_t <T> *, stack<T> &);
	bool getRoad(node_t <T> *, T &, stack<T> &);
	
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
	void getLeaves(stack<T> &);
	void getPath(T &, stack<T> &);
	void commonAncestors(T &, T &);
	void LCA(T &, T &);

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
	//printTree(root);
	levelByLevelPrint(root);
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
void tree<T>::levelByLevelPrint(node_t<T> * p) const
{
	queue<node_t<T> *> q;
	q.push(p);
	
	while (q.empty() == false) {
		int node_counter = q.size();

		while (node_counter > 0) {
			node_t<T> * node = q.front();
			cout << node->data << " ";
			q.pop();
			
			if (node->left != nullptr) {
				q.push(node->left);
			}
			if (node->right != nullptr) {
				q.push(node->right);
			}
			node_counter--;
		}
		cout << "\n";
	}
}

template<typename T>
void tree<T>::getLeafNodes(node_t <T> * p, stack<T> & s)
{
	if (p)
	{
		getLeafNodes(p->left, s);
		if (p->left == nullptr && p->right == nullptr) {
			s.push(p->data);
		}
		getLeafNodes(p->right, s);
	}
}

template<typename T>
void tree<T>::getLeaves(stack<T> & s)
{
	getLeafNodes(root, s);
}

template <typename T>
bool tree<T>::getRoad(node_t <T> * p, T & target, stack<T> & s)
{
	if (p == nullptr) {
		return false;
	}
	if (p->data == target) {
		return true;
	}
	if (getRoad(p->left, target, s) || getRoad(p->right, target, s)) {
		s.push(p->data);
		return true;
	}
}

template <typename T>
void tree<T>::commonAncestors(T & a, T & b)
{
	stack<T> st1, st2;
	getPath(a, st1);
	getPath(b, st2);

	while (st1.empty() == false && st2.empty() == false) {
		if (st1.top() == st2.top()) {
			cout << st1.top()<<" ";
		}
		st1.pop();
		st2.pop();
	}
}

template <typename T>
void tree<T>::LCA(T & a, T & b)
{
	stack<T> st1, st2;
	getPath(a, st1);
	getPath(b, st2);
	T lowest_ancestor;

	while (st1.empty() == false && st2.empty() == false) {
		if(st1.top() == st2.top()) {
			lowest_ancestor = st1.top();
		}
		st1.pop();
		st2.pop();
	}
	cout << lowest_ancestor << "\n";
}


template <typename T> 
void tree<T>::getPath(T & target, stack<T> & s)
{
	s.push(target);
	getRoad(root, target, s);
}

int main()
{
    return 0;
}