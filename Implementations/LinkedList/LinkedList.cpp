#include <iostream>

using namespace std;

template <typename T>
struct node_l
{
	T data;
	node_l<T> *next;
};

template <typename T>
class llist {
private:
	node_l<T> *start;
	node_l<T> *end;
	node_l<T> *current;

	void deleteList()
	{
		node_l<T> *p = start;
		while (start)
		{
			p = start;
			start = start->next;
			delete p;
		}
	}

	void copyList(llist<T> const &l)
	{
		start = end = NULL;
		if (l.start)
		{
			node_l<T> *p = l.start;
			while (p)
			{
				toEnd(p->data);
				p = p->next;
			}
		}
	}

public:
	llist()
	{
		start = NULL;
		end = NULL;
	}

	llist(llist const &l)
	{
		copyList(l);
	}

	llist<T>& operator= (llist<T> const &l)
	{
		if (this != &l)
		{
			deleteList();
			copyList(l);
		}

		return *this;
	}

	~llist()
	{
		deleteList();
	}

	void iterStart(node_l<T> *p = NULL)
	{
		if (p == NULL)
			current = start;
		else
			current = p;
	}

	void deleteLast()
	{
		iterStart();
		node_l <T> * p = iter();
		while (p->next) {
			p = iter();
		}
		int x;
		deleteElem(p, x);
	}

	node_l<T>* iter()
	{
		node_l<T> *result = current;

		if (current)
			current = current->next;

		return result;
	}

	void toEnd(T const & x)
	{
		node_l<T> *temp = new node_l<T>;
		temp->data = x;
		temp->next = NULL;

		if (start == NULL)
			start = temp;
		else
			end->next = temp;

		end = temp;
	}

	void insertAfter(node_l<T>* p, T const &x)
	{
		node_l<T>* temp = new node_l<T>;
		temp->data = x;
		temp->next = p->next;

		if (p == end)
			end = temp;

		p->next = temp;
	}

	void insertBefore(node_l<T>* p, T const &x)
	{
		node_l<T> *temp = new node_l<T>;
		*temp = *p; // or q->data = p->data; q->next = p->next;

		if (temp == end)
			end = temp;

		p->data = x;
		p->next = temp;
	}

	bool deleteAfter(node_l<T>* p, T &x)
	{
		if (p->next)
		{
			node_l<T> *temp = p->next;
			x = p->data;
			p->next = temp->next;

			if (temp == end)
				end = p;

			delete temp;
			return true;
		}

		return false;
	}

	void deleteElem(node_l<T>* p, T &x)
	{
		if (p != start)
		{
			node_l<T> *temp = start;
			while (temp->next != p)
				temp = temp->next;
			deleteAfter(temp, x);
		}
		else
		{
			x = p->data;

			if (start == end)
			{
				start = NULL;
				end = NULL;
			}
			else
				start = start->next;

			delete p;
		}
	}

	bool deleteBefore(node_l<T>* p, T &x)
	{
		if (p != start)
		{
			node_l<T> *q = start;
			while (q->next != p)
				q = q->next;
			deleteElem(q, x);

			return true;
		}

		return false;
	}

	void print()
	{
		node_l<T> *p = start;
		while (p)
		{
			cout << p->data << ' ';
			p = p->next;
		}

		cout << endl;
	}

	int length()
	{
		int result = 0;
		node_l<T> *p = start;
		while (p)
		{
			result++;
			p = p->next;
		}

		return result;
	}

	bool isMember(T const &x)
	{
		iterStart();
		node_l<T> *p = iter();

		while (p)
		{
			if (p->data == x)
				return true;
			p = iter();
		}

		return false;
	}
};

int main()
{
    return 0;
}