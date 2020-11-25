#include <iostream>
#include "llist.h"
#include <stack>
#include <queue>
#include <cstring>

using namespace std;

void PairSum(const int & target, DList<int> & l)
{
    l.IterStart();
    l.IterEnd();

    bool flag = false;

    elem_link2<int> * start = l.IterNext();
    elem_link2<int> * end = l.IterPrev();

    while(start && end && start != end){
        if(start->inf + end->inf == target){
            cout<<"pair is: ("<<start->inf<<", "<<end->inf<<")"<<"\n";
            flag = true;
            start = l.IterNext();
            end = l.IterPrev();
        }
        else{
            if(start->inf + end->inf < target){
                start = l.IterNext();
            }else{
                end = l.IterPrev();
            }
        }
    }

    if(!flag){
        cout<<"No pairs were found\n";
    }
}

int findMin(DList<int> & l)
{
    l.IterStart();
    elem_link2<int> * p = l.IterNext();
    elem_link2<int> * q = NULL;

    if(p){
        int min = p->inf;
        q = p;

        p = l.IterNext();

        while(p){
            if(p->inf < min){
                min = p->inf;
                q = p;
            }
            p = l.IterNext();
        }
        int x;
        if(q){
            l.DeleteElem(q,x);
        }
        return min;
    }
}

void sortList(DList<int> & l)
{
    DList<int> helper;

    while(l.length() > 0){
        helper.ToEnd(findMin(l));
    }

    l = helper;
}

void removeDublicates(DList<int> & l)
{
    DList<int> helper;

    l.IterStart();
    elem_link2<int> * p = l.IterNext();

    if(p){
        helper.ToEnd(p->inf);
        p = l.IterNext();

        while(p){
            if(helper.isMember(p->inf)){
                int x;
                l.DeleteElem(p,x);
            }
            else{
                helper.ToEnd(p->inf);
            }
            p = l.IterNext();
        }
    }
}

void countEachDublicate(DList<int> & l)
{
    l.IterStart();
    elem_link2<int> * p = l.IterNext();
    queue<int> doubles, counter;

    while(p){
        elem_link2<int> * q = p->next;
        bool found = false;

        while(q){
            if(p->inf == q->inf){
                if(!found){
                    counter.push(1);
                    doubles.push(p->inf);
                }
                int x;
                l.DeleteElem(q,x);
                found = true;
                counter.back()++;
            }
            q = q->next;
        }
        l.print();
        p = p->next;
    }
    while(!doubles.empty() && !counter.empty()){
        cout<<doubles.front()<<"<=>"<<counter.front()<<"\n";
        doubles.pop();
        counter.pop();
    }
}

void reverseList(DList<int> & l)
{
    stack<int> st;

    l.IterStart();
    elem_link2<int> * p = l.IterNext();

    while(p){
        st.push(p->inf);
        int x;
        l.DeleteElem(p, x);

        p = l.IterNext();
    }

    while(!st.empty()){
        l.ToEnd(st.top());
        st.pop();
    }
}

void cutListByPieces(DList<int> & l, const int & piece)
{
    l.IterStart();
    elem_link2<int> * p = l.IterNext();

    DList<int> temp;

    while(p){

        int current = 0;
        DList<int> inner;
        while(p && current < piece){
            inner.ToEnd(p->inf);
            current++;
            p = p->next;
        }
        inner.print();
    }
}

template <typename T>
void listToList(DList<T> & a, DList<T> b)
{
    b.IterStart();
    elem_link2<T> * p = b.IterNext();

    while(p){
        a.ToEnd(p->inf);
        p = p->next;
    }
}

void ReverseListByPieces(DList<int> & l, const int & piece)
{
    l.IterStart();
    elem_link2<int> * p = l.IterNext();

    DList<int> temp;

    while(p){

        int current = 0;
        DList<int> inner;
        while(p && current < piece){
            inner.ToEnd(p->inf);
            current++;
            p = p->next;
        }
        //inner.print();
        reverseList(inner);
        listToList(temp,inner);
    }
    l = temp;
    //temp.print();
}

void insertAtPlace(DList<int> & l, const int & value)
{
    l.IterStart();
    elem_link2<int> * p = l.IterNext();

    if(value < p->inf){
        DList<int> temp;
        temp.ToEnd(value);
        listToList(temp,l);
        l = temp;
    }
    else{
        while(p && p->inf <= value){
            p = p->next;
        }
        DList<int> temp;
        while(p){
            temp.ToEnd(p->inf);
            int x;
            l.DeleteElem(p,x);
            p = p->next;
        }
        l.ToEnd(value);
        listToList(l,temp);
    }
}

void findMiddle(DList<int> & l)
{
    int middle = (l.length()/2);

    l.IterStart();
    elem_link2<int> * p = l.IterNext();

    if(p){
        while(p && middle > 0){
            p = p->next;
            middle--;
        }
        cout<<p->inf<<"\n";
    }
}

template <typename T>
bool checkEqualStacks(stack<T> & st1, stack<T> & st2)
{
    if(st1.size() != st2.size()){
        return false;
    }

    while(!st1.empty()){
        if(st1.top() != st2.top()){
            return false;
        }
        st1.pop();
        st2.pop();
    }
    return true;
}

template <typename T>
void listToStack(DList<T> l, stack<T> & st)
{
    l.IterStart();
    elem_link2<T> * p = l.IterNext();

    while(p){
        st.push(p->inf);
        p = p->next;
    }
}

bool hasWord(char * array, DList<char> l)
{
    int arrSize = strlen(array);

    l.IterStart();
    elem_link2<char> * p = l.IterNext();

    while(p){
        if(p->inf == array[0]){
            int tempSize = 0;
            bool inner_flag = true;

            while(p && tempSize < arrSize && p->inf == array[tempSize]){
                if(p->inf != array[tempSize]){
                    inner_flag = false;
                }

                tempSize++;
                if(p->next->inf == array[tempSize]){
                    p = p->next;
                }
            }

            if(inner_flag && tempSize == arrSize){
                return true;
            }
        }

        p = p->next;
    }
    return false;
}

template <typename T>
bool isPalindrome(DList<T> l)
{
    stack<T> st;
    listToStack(l,st);

    //l.print();
    l.IterStart();
    elem_link2<T> * p = l.IterNext();

    while(p){
        if(p->inf != st.top()){
            return false;
        }
        p = p->next;
        st.pop();
    }
    return true;
}

template <typename T>
int hasLoop(DList<T> & l)
{
    l.IterStart();


    elem_link2<T> * p = l.IterNext();
    elem_link2<T> * q = p;

    while(p && q && q->next){
        p = p->next;
        q = q->next->next;

        if(p == q){
            return 1;
        }
    }
    return 0;
}

int main()
{

    DList<int> l;

    /*
    l.ToEnd(1);
    l.ToEnd(12);
    l.ToEnd(8);
    l.ToEnd(-5);
    l.ToEnd(5);
    l.ToEnd(6);
    l.ToEnd(6);
    l.ToEnd(0);
    l.ToEnd(1);
    l.ToEnd(9);
    */

    l.ToEnd(1);
    l.ToEnd(1);

    l.ToEnd(7);
    l.ToEnd(6);

    l.ToEnd(1);
    l.ToEnd(4);

    l.ToEnd(8);
    l.ToEnd(8);

    l.ToEnd(8);
    l.ToEnd(7);

    l.ToEnd(4);
    l.ToEnd(1);

    l.ToEnd(8);


    //PairSum(7,l);

   // cout<<findMin(l)<<"\n";



    //sortList(l);
    //l.print();
    //removeDublicates(l);
    //l.print();

    //countEachDublicate(l);

    //countEachDublicate(l);


    /*
    l.print();

    removeDublicates(l);

    l.print();

    reverseList(l);

    l.print();
    */

    DList<int> ls;
    ls.ToEnd(1);
    ls.ToEnd(2);
    ls.ToEnd(3);
    ls.ToEnd(4);
    ls.ToEnd(5);
    //ls.ToEnd(6);
    //ls.ToEnd(7);
    //ls.ToEnd(8);


    //ls.print();
    //cutListByPieces(l,2);

    //ReverseListByPieces(ls,9);
    //insertAtPlace(ls,6);
    //insertAtPlace(ls,0);
    //insertAtPlace(ls,10);

    //ls.print();

   // findMiddle(ls);

    //cout<<"------------------\n";


    DList<char> lWord;
    char arrWord[] = "Bog dan";

    lWord.ToEnd('A');
    lWord.ToEnd('z');
    //lWord.ToEnd(' ');
    lWord.ToEnd('s');
    lWord.ToEnd('u');
    lWord.ToEnd('m');
    lWord.ToEnd('B');
    lWord.ToEnd('o');
    lWord.ToEnd('g');
    lWord.ToEnd(' ');
    lWord.ToEnd('d');
    lWord.ToEnd('a');
    lWord.ToEnd('n');

    lWord.ToEnd('B');
    lWord.ToEnd('o');
    lWord.ToEnd('g');
    lWord.ToEnd('d');
    lWord.ToEnd('a');
    lWord.ToEnd('n');
    //lWord.ToEnd(' ');
    lWord.ToEnd('M');
    lWord.ToEnd('a');
    lWord.ToEnd('r');
    lWord.ToEnd('i');
    lWord.ToEnd('n');
    lWord.ToEnd('o');
    lWord.ToEnd('v');
    lWord.ToEnd('.');

    //lWord.print();

    //cout<<canFindWord(arrWord,lWord)<<"\n";
    //cout<<hasWord(arrWord,lWord)<<"\n";

    DList<char> palindrome;
    palindrome.ToEnd('r');
    palindrome.ToEnd('a');

   // cout<<isPalindrome(palindrome)<<"\n";
    cout<<hasLoop(palindrome)<<"\n";

    return 0;
}
