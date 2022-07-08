#include <iostream>

using namespace std;

template<class T>
class mArray
{
public:
	mArray();
	mArray(mArray& arr);
	mArray(int n,T& ele);
	~mArray();
	mArray<T>& operator=(const mArray<T>& arr);

	bool empty();
	bool Noempty();
	int capacity();
	int size();
	void resize(int n);
	void resize(int n,T& ele);

	void push_back(T& ele);
	void pop_back();
	bool insert(int pos, T& ele);
	bool insert(int pos, int count, T& ele);
	bool erase(int pos, int leng);
	void clear();

	T& operator[](int index);
	T& front();
	T& back();


	void reserve(int len);
private:
	T* array = nullptr;
	int leng=0;
	int maxCap = 0;
	void exCapacity(int min = -1);
};

template<class T>
inline mArray<T>::mArray()
{
	array = new T[12];
	maxCap = 12;
}

template<class T>
inline mArray<T>::mArray(mArray& arr)
{
	maxCap = arr.maxCap;
	array = new T[maxCap];
	for (int i = 0; i < arr.leng; i++)array[i] = arr.array[i];
	leng = arr.leng;
}

template<class T>
inline mArray<T>::mArray(int n, T& ele)
{
	maxCap = 12;
	while (maxCap <= n)maxCap <<= 1;
	array = new T[maxCap];
	for (int i = 0; i < n; i++)array[i] = ele;
}

template<class T>
inline mArray<T>::~mArray()
{
	delete[] array;
}

template<class T>
inline mArray<T>& mArray<T>::operator=(const mArray<T>& arr)
{
	delete[] array;
	maxCap = arr.maxCap;
	leng = arr.leng;
	array = new T[maxCap];
	for (int i = 0; i < leng; i++)array[i] = arr.array[i];
}

template<class T>
inline bool mArray<T>::empty()
{	
	return leng == 0;
}

template<class T>
inline bool mArray<T>::Noempty()
{
	return leng != 0;
}

template<class T>
inline int mArray<T>::capacity()
{
	return maxCap;
}

template<class T>
inline int mArray<T>::size()
{
	return leng;
}

template<class T>
inline void mArray<T>::resize(int n)
{
	T* temp = new T[n];
	for (int i = 0; i < leng && i < n; i++) {
		temp[i] = array[i];
	}
	delete[] array;
	array = temp;
	leng = n > leng ? leng : n;
	maxCap = n;
}

template<class T>
inline void mArray<T>::resize(int n, T& ele)
{
	T* temp = new T[n];
	for (int i = 0; i < leng && i < n; i++) {
		temp[i] = array[i];
	}
	for (int i = leng; i < n; i++)temp[i] = ele;
	delete[] array;
	array = temp;
	leng = n > leng ? leng : n;
	maxCap = n;
}

template<class T>
inline void mArray<T>::push_back(T& ele)
{
	if (leng == maxCap)exCapacity();
	array[leng++] = ele;
}

template<class T>
inline void mArray<T>::pop_back()
{
	leng--;
}

template<class T>
inline bool mArray<T>::insert(int pos, T& ele)
{
	if (pos < 0 && pos > leng)return false;
	if (leng == maxCap)exCapacity();
	for (int i = leng - 1; i >= pos; i--) {
		array[i + 1] = array[i];
	}
	array[pos] = ele;
	return true;
}

template<class T>
inline bool mArray<T>::insert(int pos, int count, T& ele)
{
	if (count <= 0)return false;
	if (pos < 0 && pos > leng)return false;
	if (leng+count >= maxCap)exCapacity(leng+count);
	for (int i = leng - 1; i >= pos; i--) {
		array[i + count] = array[i];
	}
	for (int i = 0; i < count; i++) {
		array[pos + i] = ele;
	}
	return true;
}

template<class T>
inline bool mArray<T>::erase(int pos, int leng)
{
	if (pos < 0 || pos >= leng)return false;
	if (pos == leng - 1)return true;
	for (int i = pos; i < leng-1; i++) {
		array[i] = array[i + 1];
	}
	leng--;
	return true;
}

template<class T>
inline void mArray<T>::clear()
{
	delete[] array;
	array = new T[12];
	maxCap = 12;
	leng = 0;
}

template<class T>
inline T& mArray<T>::operator[](int index)
{
	if (index < 0 || index >= leng)cout << "下标超出范围！！！" << endl;
	return array[index];
}

template<class T>
inline T& mArray<T>::front()
{
	if (leng == 0)cout << "当前数组没有元素！！！" << endl;
	return array[-1];
}

template<class T>
inline T& mArray<T>::back()
{
	if (leng == 0)cout << "当前数组没有元素！！！" << endl;
	return array[leng - 1];
}

template<class T>
inline void mArray<T>::reserve(int len)
{
	T* temp = new T[leng + len];
	for (int i = 0; i < leng; i++)temp[i] = array[i];
	maxCap = leng + len;
}

template<class T>
inline void mArray<T>::exCapacity(int min)
{
	maxCap <<= 1;
	if (min != -1)while (maxCap <= min)maxCap <<= 1;
	T* temp = new T[maxCap];
	for (int i = 0; i < leng; i++)temp[i] = array[i];
	delete[] array;
	array = temp;
}
