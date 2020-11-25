#include <iostream>
#include "tree.h"

using namespace std;

int main()
{
    tree<int> tr;
    tr.create();

    llist<int> l = tr.getRange(4,37);
    l.print();
    llist<int> optimizedL = tr.optimizedRange(4,37);
    optimizedL.print();
    tr.ranger(4, 37);

    cout<<"\n";
    llist<int> newList;
    newList.insertInOrder(10);
    newList.insertInOrder(5);
    newList.insertInOrder(37);
    newList.insertInOrder(8);
    newList.insertInOrder(4);
    newList.insertInOrder(9);
    newList.insertInOrder(10);
    newList.insertInOrder(0);

    newList.print();
    //tr.print();

    //node_t<int> * q = tr.getNodeTo(3);
    //llist<int> l = tr.Range(4,37);
    //l.print();
    //cout<<tr.getHeightOfNode(37)<<"\n";
    //cout<<tr.hasChildren(37)<<"\n";
    //tr.getChildren(q, l);

    //l.print();

    //cout<<q->data<<" "<<q->left->data<<" "<<q->right->data<<"\n";
    return 0;
}
