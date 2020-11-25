#ifndef TREE_H
#define TREE_H
#include <queue>
#include "llist.h"

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
	void getNodeTo(node_t<T> *, T, node_t<T> * & );
	bool hasWay(node_t<T> * , T, llist<T> & );
	void range(node_t<T> *, llist<T> &, T ,T );
public:
    llist<T> getRange(T, T);
    int getHeightOfNode(T) const;
    int getHeight() const;
    bool hasChildren(T value);
    llist<T> Range(T, T);
    bool hasWay(T, llist<T> &);
    void getChildren(node_t<T> *, llist<T> &);
    node_t<T> * getNodeTo(T);
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
	void getNodesWithinRangeToLevel(int, llist<T> & , T, T);
	llist<T> optimizedRange(T, T);
	void ranger(T, T);
};

template <typename T>
void tree<T>::ranger(T start, T end)
{
    llist<T> l;
    range(root, l, start, end);
    l.print();
}

template <typename T>
void tree<T>::range(node_t<T> * p, llist<T> & way, T start ,T end)
{
    if(p){
        range(p->left, way, start, end);
        if(p->data >= start && p->data <= end){
            way.toEnd(p->data);
        }
        range(p->right, way, start, end);
    }
}

template <typename T>
llist<T> tree<T>::optimizedRange(T start, T end)
{
    llist<T> values;
    node_t<T> * p = root;
    if(p){
        queue<node_t<T> *> q;
        q.push(p);
        bool one = false, two = false;

        while(!q.empty()){
            int count = q.size();

            while(count > 0){
                node_t<T> * current = q.front();
                if(current->data >= start && current->data <= end && !values.isMember(current->data)){
                    values.toEnd(current->data);
                }

                if(current->data == start){
                    one = true;
                }

                if(current->data == end){
                    two = true;
                }

                q.pop();

                if(current->left){
                    q.push(current->left);
                }
                if(current->right){
                    q.push(current->right);
                }
                count--;
            }
            if(one && two){
                return values;
            }
        }
    }
    return values;
}

template <typename T>
void tree<T>::getNodesWithinRangeToLevel(int level, llist<T> & nodes, T start, T end)
{
    node_t<T> * p = root;
    if(p)
    {
        int height = -1;
        queue<node_t<T> *> q;
        q.push(p);

        while(!q.empty()){
            int count = q.size();

            while(count > 0){
                node_t<T> * current = q.front();
                if(current->data >= start && current->data <= end && !nodes.isMember(current->data)){
                    nodes.toEnd(current->data);
                }
                q.pop();

                if(current->left){
                    q.push(current->left);
                }
                if(current->right){
                    q.push(current->right);
                }
                count--;
            }
            height++;
        }
        if(height == level){
            return;
        }
    }
}

template <typename T>
llist<T> tree<T>::getRange(T start, T end)
{
    int h1 = getHeightOfNode(start), h2 = getHeightOfNode(end);
    llist<T> values;
    if(h1 >= h2){
       getNodesWithinRangeToLevel(h1,values, start, end);
    }
    else
    {
        getNodesWithinRangeToLevel(h2, values, start, end);
    }
    //values.print();
    return values;
}

template <typename T>
int tree<T>::getHeightOfNode(T target) const
{
    node_t<T> * p = root;
    if(p)
    {
        int height = -1;
        queue<node_t<T> *> q;
        q.push(p);

        while(!q.empty()){
            int count = q.size();

            while(count > 0){
                node_t<T> * current = q.front();
                q.pop();

                if(current->data == target){
                    return (height + 1);
                }

                if(current->left){
                    q.push(current->left);
                }
                if(current->right){
                    q.push(current->right);
                }
                count--;
            }
            height++;
        }
    }
    return -1;
}

template <typename T>
int tree<T>::getHeight() const
{
    node_t<T> * p = root;
    if(p)
    {
        int height = -1;
        queue<node_t<T> *> q;
        q.push(p);

        while(!q.empty()){
            int count = q.size();

            while(count > 0){
                node_t<T> * current = q.front();
                q.pop();

                if(current->left){
                    q.push(current->left);
                }
                if(current->right){
                    q.push(current->right);
                }
                count--;
            }
            height++;
        }
        return height;
    }
    return -1;
}

template <typename T>
bool tree<T>::hasChildren(T value)
{
    node_t<T> * q = getNodeTo(value);
    if(q->left || q->right){
        return true;
    }
    return false;
}

template <typename T>
llist<T> tree<T>::Range(T start, T end)
{
    llist<T> a, b,values;
    hasWay(start,a);
    hasWay(end,b);

    a.iterStart();
    b.iterStart();
    a.print();

    node_l<T> * p = a.iter();

    while(p)
    {
        if(hasChildren(p->data) && (p->data >= start && p->data <= end)){
            cout<<p->data<<"\n";
            node_t<T> * q = this->getNodeTo(p->data);
            llist<T> children;
            getChildren(q,children);
            children.print();
        }
        p = p->next;
    }


    return values;
}

template<typename T>
bool tree<T>::hasWay(T target, llist<T> & way)
{
    return hasWay(root, target, way);
}

template <typename T>
bool tree<T>::hasWay(node_t<T> * p, T target, llist<T> & way)
{
    if(!p){
        return false;
        }
    way.toEnd(p->data);
    if(p->data == target){
        return true;
        }
    if(hasWay(p->left, target, way)||hasWay(p->right, target, way)){
        return true;
        }

    way.deleteLast();
    return false;
}

template <typename T>
void tree<T>::getChildren(node_t<T> * p, llist<T> & children)
{
    if(p)
    {
        getChildren(p->left, children);
        children.toEnd(p->data);
        getChildren(p->right, children);
    }
}

template <typename T>
node_t<T> * tree<T>::getNodeTo(T value)
{
    node_t<T> * q = NULL;
    getNodeTo(root, value, q);
    return q;
}

template <typename T>
void tree<T>::getNodeTo(node_t<T> *p, T value, node_t<T> * & q)
{
    if(p)
    {
        getNodeTo(p->left, value, q);
        if(p->data == value){
            q = p;
            return;
        }
        getNodeTo(p->right, value, q);
    }
}

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
#endif // TREE_H



/*

while(p)
    {
        if(!values.isMember(p->data) && (p->data >= start && p->data <= end)){
            values.toEnd(p->data);
        }
        p = p->next;
    }

    p = b.iter();

    while(p)
    {
        if(!values.isMember(p->data) && (p->data >= start && p->data <= end)){
            values.toEnd(p->data);
        }
        p = p->next;
    }



*/
