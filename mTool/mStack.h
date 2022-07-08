#include <iostream>

using namespace std;

template<class T>
class mStack
{
public:
	mStack();
	mStack(mStack& stk);
	~mStack();
	mStack<T>& operator=(mStack<T>& stk);
	void push(T ele);
	T& top();
	void pop();
	bool empty();
	bool Noempty();
	int size();
private:
	T* stack;
	int capacity = 0;
	int index = -1;
	void resize();
};

template<class T>
inline mStack<T>::mStack()
{
	capacity = 12;
	stack = new T[capacity];
}

template<class T>
inline mStack<T>::mStack(mStack& stk)
{
	int temp = stk.size();
	capacity = 12;
	while (capacity <= temp)capacity << 1;
	stack = new T[capacity];
	for (int i = 0; i < stk.size(); i++) {
		T ele = stk.stack[i];
		stack[i] = ele;
	}
	index = stk.size() - 1;
}

template<class T>
inline mStack<T>::~mStack()
{
	delete[] stack;
}

template<class T>
inline mStack<T>& mStack<T>::operator=(mStack<T>& stk)
{
	int temp = stk.size();
	capacity = 12;
	while (capacity <= temp)capacity << 1;
	stack = new T[capacity];
	for (int i = 0; i < stk.size(); i++) {
		stack[i] = stk.stack[i];
	}
	index = stk.size() - 1;
	return *this;
}

template<class T>
inline void mStack<T>::push(T ele)
{
	if (index == capacity) {
		resize();
	}
	stack[++index]  = ele;
}

template<class T>
inline T& mStack<T>::top()
{
	// TODO: 在此处插入 return 语句
	if (index == -1) {
		cout << "当前栈为空！！！！";
	}
	return stack[index];
}

template<class T>
inline void mStack<T>::pop()
{
	if (index == -1) {
		cout << "当前栈为空";
		return;
	}
	index--;
}

template<class T>
inline bool mStack<T>::empty()
{
	return index == -1;
}

template<class T>
inline bool mStack<T>::Noempty()
{
	return index != -1;
}

template<class T>
inline int mStack<T>::size()
{
	return index+1;
}

template<class T>
inline void mStack<T>::resize()
{
	capacity <<= 1;
	T* temp = new T[capacity];
	for (int i = 0; i <= index; i++) {
		temp[i] = stack[i];
	}
	delete[] stack;
	stack = temp;
}



