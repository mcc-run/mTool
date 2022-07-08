#include <iostream>
#include "Compareable.h"

using namespace std;

template<class T>
class mList
{
private:
	int leng = 0;
	class mNode {
		friend class mList;
	public:
		mNode(){}
		mNode(T ele): value(ele){}

		T value;
		mNode* pre = nullptr;
		mNode* next = nullptr;
	};
	mNode* root = nullptr;
	mNode* tail = nullptr;

	void quickSort(T* keys, int begin, int end);

	mNode* get(int index) {
		mNode* pre = nullptr;
		if (leng - index > index) {
			pre = root;
			while (index--) {
				pre = pre->next;
			}
		}
		else {
			pre = tail;
			index = leng - index;
			while (index--)
			{
				pre = pre->pre;
			}
		}
		return pre;
	}

public:
	mList() {};
	mList(T& ele,int count=1);
	mList(mList<T>& m);
	~mList();

	mList& operator=(mList& m);

	int size();
	bool empty();
	bool notempty();



	bool pushback(T ele);
	bool popback();
	bool pushfront(T ele);
	bool popfront();
	bool insert(int index, T ele, int count = 1);

	void clear();
	bool erase(int index,int count = 1);
	void remove(T ele);
	
	T& front();
	T& back();

	void reverse();

	class iterator {
		friend class mList;
	private:
		mNode* now = nullptr;
	public:
		iterator() {}
		iterator(mNode* root) { now = root; }
		T& value() { return now->value; }

		iterator& operator++() {
			now = now->next;
			return *this;
		}
		iterator operator++(int) {
			iterator tmp = *this;
			now = now->next;
			return tmp;
		}
		bool operator==(mNode* node) { return now == node; }
		bool operator!=(mNode* node) { return now != node; }
	};


	void sort(bool desc = false) {
		if (!leng)return;

		//转换成数组，用于排序
		T* keys = new T[leng];
		mNode* node = root;
		for (int i = 0; i < leng; i++) {
			keys[i] = node->value;
			node = node->next;
		}

		quickSort(keys, 0, leng);
		node = root;
		if (desc) {
			for (int i = leng-1; i >= 0; i--) {
				node->value = keys[i];
				node = node->next;
			}
		}
		else {
			for (int i = 0; i < leng; i++) {
				node->value = keys[i];
				node = node->next;
			}
		}
		
	}

	iterator begin() { return iterator(root); }
	mNode* end() { return nullptr; }

};

template<class T>
inline void mList<T>::quickSort(T* keys, int begin, int end)
{
	if (begin >= end-1)return;
	T key = keys[begin];
	int left = begin;
	int right = end-1;
	while (left < right) {
		while (left < right && keys[right] > key)right--;
		if (left < right) {
			keys[left] = keys[right];
			left++;
		}
		while (left < right && keys[left] < key)left++;
		if (left < right) {
			keys[right] = keys[left];
			right--;
		}
	}
	keys[left] = key;
	quickSort(keys, begin, left);
	quickSort(keys, left + 1, end);
}

template<class T>
inline mList<T>::mList(T& ele, int count)
{
	root = new mNode(ele);
	mNode* now = root;
	leng++;
	count--;
	while (count--) {
		mNode* tmp = new mNode(ele);
		now->next = tmp;
		tmp->pre = now;
		now = tmp;
	}
}

template<class T>
inline mList<T>::mList(mList<T>& m)
{
	leng = m.leng;
	root = new mNode(m.root->value);
	tail = root;
	mNode* from = m.root->next;
	while (from) {
		mNode* node = new mNode(from->value);
		tail->next = node;
		node->pre = tail;
		tail = node;
		from = from->next;
	}
}

template<class T>
inline mList<T>::~mList()
{
	clear();
}

template<class T>
inline mList<T>& mList<T>::operator=(mList<T>& m)
{
	clear();
	leng = m.leng;
	root = new mNode(m.root->value);
	tail = root;
	mNode* from = m.root->next;
	while (from) {
		mNode* node = new mNode(from->value);
		tail->next = node;
		node->pre = tail;
		tail = node;
		from = from->next;
	}
}

template<class T>
inline int mList<T>::size()
{
	return leng;
}

template<class T>
inline bool mList<T>::empty()
{
	return leng == 0;
}

template<class T>
inline bool mList<T>::notempty()
{
	return leng != 0;
}



template<class T>
inline bool mList<T>::pushback(T ele)
{
	mNode* newnode = new mNode(ele);
	if (!newnode)return false;
	if (!leng) {
		tail = newnode;
		root = newnode;
	}
	else {
		tail->next = newnode;
		newnode->pre = tail;
		tail = newnode;
	}
	leng++;
	return true;
}

template<class T>
inline bool mList<T>::popback()
{
	if (!leng)return false;
	if (leng == 1) {
		delete root;
		root = nullptr;
		tail = nullptr;
		leng = 0;
		return true;
	}
	mNode* del = tail;
	tail = tail->pre;
	tail->next = nullptr;
	leng--;
	delete del;
	return true;
}

template<class T>
inline bool mList<T>::pushfront(T ele)
{
	mNode* newnode = new mNode(ele);
	if (!newnode)return false;
	if (!leng) {
		tail = newnode;
		root = newnode;
	}
	else {
		root->pre = newnode;
		newnode->next = root;
		root = newnode;
	}
	leng++;
	return true;
}

template<class T>
inline bool mList<T>::popfront()
{
	if (!leng)return false;
	if (leng == 1) {
		delete root;
		root = nullptr;
		tail = nullptr;
		leng = 0;
		return true;
	}
	mNode* del = root;
	root = root->next;
	root->pre = nullptr;
	leng--;
	delete del;
	return true;
}

template<class T>
inline bool mList<T>::insert(int index, T ele, int count)
{
	if (index < 0 || index > leng)return false;

	mNode* pre = get(index);
	leng += count;
	while (count--) {
		mNode* newnode = new mNode(ele);
		if (!newnode)return false;
		newnode->next = pre->next;
		if (pre->next)pre->next->pre = pre;
		pre->next = newnode;
		newnode->pre = pre;
		pre = newnode;
	}
	return true;
}

template<class T>
inline void mList<T>::clear()
{
	while (root) {
		mNode* del = root;
		root = root->next;
		delete del;
	}
	leng = 0;
	root = tail = nullptr;
}

template<class T>
inline bool mList<T>::erase(int index, int count)
{
	if (index < 0 || index + count >= leng)return false;
	leng -= count;
	if (index == 0) {
		while (count--)
		{
			mNode* del = root;
			if (del == tail)tail = nullptr;
			root = root->next;
			if (root)root->pre = nullptr;
			delete del;
		}
		return true;
	}
	mNode* pre = get(index-1);
	while (count--) {
		mNode* del = pre->next;
		if (del == tail)tail = pre;
		pre->next = del->next;
		if (del->next)del->next->pre = pre;
		delete del;
	}
	return true;
}

template<class T>
inline void mList<T>::remove(T ele)
{
	while (root && root->value == ele) {
		mNode* del = root;
		if (del == tail)tail = nullptr;
		root = root->next;
		if (root)root->pre = nullptr;
		leng--;
		delete del;
	}

	if (!root)tail = nullptr;

	mNode* pre = root;

	while (pre) {
		if (!pre->next)return;
		mNode* next = pre->next;
		if (next->value == ele) {
			pre->next = next->next;
			if (pre->next)pre->next->pre = pre;
			delete next;
			leng--;
		}
		else pre = pre->next;
	}
}

template<class T>
inline T& mList<T>::front()
{
	return root->value;
}

template<class T>
inline T& mList<T>::back()
{
	return tail->value;
}

template<class T>
inline void mList<T>::reverse()
{
	mNode* start = root, * end = tail;
	for (int i = 0; i < leng / 2; i++) {
		T tmp = start->value;
		start->value = end->value;
		end->value = tmp;
		start = start->next;
		end = end->pre;
	}
}
