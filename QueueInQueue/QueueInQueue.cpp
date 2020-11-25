// hw2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <queue>

using namespace std;

queue<queue<int>> createQueue()
{
	int number = 10;
	queue<queue<int>> mainQueue;
	cout << "type 0 to start a new queue\n";
	while (true) {

		queue<int> intQueue;

		while (true) {
			cin >> number;
			if (number == 0 || number == -1 || (!intQueue.empty() && number < intQueue.back())) {
				break;
			}
			else {
				intQueue.push(number);
			}
			
		}
		mainQueue.push(intQueue);
		
		if (number == -1) {
			break;
		}	
	}
	return mainQueue;
}


void printMainQueue(const queue<queue<int>> & que)
{
	queue<queue<int>> q = que;
	while (!q.empty()) {
		while (!q.front().empty()) {
			cout << q.front().front() << " ";
			q.front().pop();
		}
		q.pop();
		cout << "\n";
	}
}

int sizeOfOuterQueue(const queue<queue<int>> & q)
{

	int size = 0;
	queue<queue<int>> temp = q;
	
	while (!temp.empty()) {
		size += temp.front().size();
		temp.pop();
	}
	return size;
}

void insertionSort(int * array, int size)
{
	for (int i = 0; i < size; i++) {
		int j = i;
		while (j > 0 && array[j - 1] > array[j]) {
			swap(array[j], array[j - 1]);
			j--;
		}
	}
}

void printArray(const int * array, int size)
{
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << "\n";
}

int main()
{
	queue<queue<int>> q = createQueue();
	printMainQueue(q);
	
	//cout << sizeOfOuterQueue(q) << "\n";

	cout << "\n";

	int size = sizeOfOuterQueue(q);
	int * container = new int[size];

	int i = 0;
	while (!q.empty()) {
		while (!q.front().empty()) {
			container[i] = q.front().front();
			q.front().pop();
			i++;
		}
		q.pop();
	}
	
	for (int i = 0; i < size; i++) {
		cout << container[i] << " ";
	}
	
	cout << "\n";

	insertionSort(container, size);

	printArray(container, size);

	delete[] container;
	container = nullptr;

    return 0;
}

