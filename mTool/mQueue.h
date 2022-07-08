#pragma once
#include <iostream>

using namespace std;

template<class T>
class mQueue
{
public:
	mQueue();
	mQueue(mQueue& que);
	~mQueue();
	mQueue& operator=(mQueue& que);
	void push(T ele);
	void pop();
	T& back();
	T& front();
	bool empty();
	bool Noempty();
	int size();
private:
	T* queue = nullptr;
	int capacity = 0;
	int head = 0;
	int tail = 0;
	int leng = 0;
	void resize();
};

template<class T>
inline mQueue<T>::mQueue()
{
	capacity = 12;
	queue = new T[capacity];
}

template<class T>
inline mQueue<T>::mQueue(mQueue& que)
{
	capacity = 12;
	while (capacity < que.capacity)capacity <<= 1;
	queue = new T[capacity];
	int index = que.head;
	while (index != que.tail) {
		queue[tail++] = que.queue[index];
		index = (index + 1) % que.capacity;
		leng++;
	}
}

template<class T>
inline mQueue<T>::~mQueue()
{
	delete[] queue;
}

template<class T>
inline mQueue<T>& mQueue<T>::operator=(mQueue<T>& que)
{
	delete[] queue;
	capacity = 12;
	head = 0;
	tail = 0;
	leng = 0;
	while (capacity < que.capacity)capacity <<= 1;
	queue = new T[capacity];
	int index = que.head;
	while (index != que.tail) {
		queue[tail++] = que.queue[index];
		index = (index + 1) % que.capacity;
		leng++;
	}
}

template<class T>
inline void mQueue<T>::push(T ele)
{
	if ((tail + 1) % capacity == head)resize();
	queue[tail] = ele;
	leng++;
	tail = (tail + 1) % capacity;
}

template<class T>
inline void mQueue<T>::pop()
{
	head = (head + 1) % capacity;
	leng--;
}

template<class T>
inline T& mQueue<T>::back()
{
	if (tail == 0)return queue[capacity - 1];
	return queue[tail - 1];
}

template<class T>
inline T& mQueue<T>::front()
{
	return queue[head];
}

template<class T>
inline bool mQueue<T>::empty()
{
	return leng == 0;
}

template<class T>
inline bool mQueue<T>::Noempty()
{
	return leng != 0;
}

template<class T>
inline int mQueue<T>::size()
{
	return leng;
}

template<class T>
inline void mQueue<T>::resize()
{
	T* temp = new T[capacity<<1];
	int index = 0;
	while (head != tail) {
		temp[index++] = queue[head];
		head = (head + 1) % capacity;
	}
	capacity <<= 1;
	delete[] queue;
	queue = temp;
	head = 0;
	tail = index;
}
