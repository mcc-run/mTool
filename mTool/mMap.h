#include <iostream>
#include <queue>

using namespace std;

template<class K, class V, class Compare =int>
class mMap
{
public:
	class iterator;
private:

	class mNode {
	public:
		//false：红	true：黑
		bool color = false;
		K key;
		V value;
		mNode* left = nullptr;
		mNode* right = nullptr;
		mNode* parent = nullptr;
		mNode* pre = nullptr;
		mNode* next = nullptr;
		mNode() {}
		mNode(K k) : key(k) {};
		mNode(K k, V v) : key(k), value(v) {};
		mNode(K k, V v, mNode* l, mNode* r) : key(k), value(v), left(l), right(r) {};
	};

	
	void rotateLeft(mNode* node);
	void rotateright(mNode* node);


	mNode* root = nullptr;
	mNode* start = nullptr;
	int leng = 0;


	//根据其他红黑树复制节点
	void copyroot(mNode* from, mNode* desc);
	//完成红黑树线索化
	mNode* thread = nullptr;
	void threadedTree(mNode* node);


	//寻找目标节点，若无法找到则返回父节点
	mNode* findNode(mNode* target, mNode* root) {
		if (!root)return nullptr;
		mNode* node = nullptr;
		if (compare(target, root) == 0)return root;
		else if (compare(target, root) < 0) {
			node = findNode(target, root->left);
		}
		else {
			node = findNode(target, root->right);
		}
		if (!node)return root;
		return node;
	}

	//修复红黑树
	void Fixinsert(mNode* child);
	void Fixdelete(mNode* child);

	//比较key值
	int compare(mNode* n1, mNode* n2);

	void exchangecolor(mNode* n1, mNode* n2);


public:
	mMap() {};
	mMap(mMap& m);
	mMap& operator=(mMap& m);
	~mMap();

	

	class iterator {
		friend class mMap;
	public:
		iterator(){}
		iterator(mNode* root) { now = root; }
		K first() { return now->key; }
		V& second() { return now->value; }

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
	private:
		mNode* now = nullptr;
	};

	int size();
	bool empty();
	bool notempty();

	void insert(pair<K, V> ele);
	void clear();
	void erase(K k);
	void erase(iterator& it);//

	

	iterator* find(K k) {
		mNode* target = findNode(new mNode(K), root);
		if (!target)return iterator();
		if (compare(target, new mNode(K)) == 0)return iterator(target);
		return iterator();
	}
	iterator* operator[](K k) {
		return find(k);
	}

	iterator begin() {
		while (start->pre)start = start->pre;
		return iterator(start);
	}

	mNode* end() { return nullptr; }
	
	void preOrder(mNode* root, int leng, vector<int>& test);

	bool isBalance();


};

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::rotateLeft(mNode* node)
{
	if (!node || !node->left)return;
	mNode* parent = node->parent, *child = node->left;
	//旋转
	node->left = child->right;
	if (child->right)child->right->parent = node;
	child->right = node;
	node->parent = child;
	child->parent = parent;
	if (parent) {
		if (parent->left == node) {
			parent->left = child;
		}
		else parent->right = child;
	}
	else {
		root = child;
	}
}

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::rotateright(mNode* node)
{
	if (!node || !node->right)return;
	mNode* parent = node->parent, *child = node->right;
	//旋转
	node->right = child->left;
	if (child->left)child->left->parent = node;
	child->left = node;
	node->parent = child;
	child->parent = parent;
	if (parent) {
		if (parent->left == node) {
			parent->left = child;
		}
		else parent->right = child;
	}
	else {
		root = child;
	}
}

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::copyroot(mNode* from, mNode* desc)
{
	if (!from)return;
	desc->color = from->color;
	desc->key = from->key;
	desc->value = from->value;
	if (from->left) {
		mNode* son = new mNode();
		desc->left = son;
		son->parent = desc;
		copyroot(from->left, son);
	}
	if (from->right) {
		mNode* son = new mNode();
		desc->right = son;
		son->parent = desc;
		copyroot(from->right, son);
	}
}

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::threadedTree(mNode* node)
{
	if (!node)return;
	threadedTree(node->left);
	if (!thread) {
		start = node;
		thread = node;
	}
	else {
		thread->next = node;
		node->pre = thread;
		thread = node;
	}
	threadedTree(node->right);
}




template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::Fixinsert(mNode* child)
{
	while (!child->color && child->parent && !child->parent->color) {
		mNode* parent = child->parent, *gparent = parent->parent;
		if (parent == gparent->left) {
			mNode* uncle = gparent->right;
			if (!uncle || uncle->color) {
					if (child == parent->right) {
						rotateright(parent);
						mNode* tmp = child;
						child = parent;
						parent = tmp;
					}
					rotateLeft(gparent);
					exchangecolor(parent, gparent);
				}
			else {
					parent->color = true;
					uncle->color = true;
					gparent->color = false;
					child = gparent;
				}
		}
		else {
			mNode* uncle = gparent->left;
			if (!uncle || uncle->color) {
				if (child == parent->left) {
					rotateLeft(parent);
					mNode* tmp = child;
					child = parent;
					parent = tmp;
				}
				rotateright(gparent);
				exchangecolor(parent, gparent);
			}
			else {
				parent->color = true;
				uncle->color = true;
				gparent->color = false;
				child = gparent;
			}
		}
	}
}

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::Fixdelete(mNode* child)
{
	if (!child)return;
	
	while (child->parent && child->color) {
		mNode* parent = child->parent;
		if (child == parent->left) {
			mNode* brother = parent->right;
			//右侄红
			if (brother->right && !brother->right->color) {
				brother->color = parent->color;
				brother->right->color = true;
				parent->color = true;
				rotateright(parent);
				break;
			}
			//左侄红
			else if (brother->left && !brother->left->color) {
				exchangecolor(brother, brother->left);
				rotateLeft(brother);
				brother = parent->right;
				brother->color = parent->color;
				brother->right->color = true;
				parent->color = true;
				rotateright(parent);
				break;
			}
			//双侄黑
			else if (brother->color) {
				brother->color = false;
				child = parent;
			}
			//红兄
			else {
				exchangecolor(parent, brother);
				rotateright(parent);
			}
		}
		else {
			mNode* brother = parent->left;
			//左侄黑
			if (brother->left && !brother->left->color) {
				brother->color = parent->color;
				parent->color = true;
				brother->left->color = true;
				rotateLeft(parent);
				break;
			}
			//右侄黑
			else if (brother->right && !brother->right->color) {
				exchangecolor(brother,brother->right);
				rotateright(brother);
				brother = parent->left;
				brother->color = parent->color;
				parent->color = true;
				brother->left->color = true;
				rotateLeft(parent);
				break;
			}
			//双侄黑
			else if (brother->color) {
				brother->color = false;
				child = parent;
			}
			//红兄
			else {
				exchangecolor(parent, brother);
				rotateLeft(parent);
			}
		}
	}

	root->color = true;
	child->color = true;

}

template<class K, class V, class Compare>
inline int mMap<K, V, Compare>::compare(mNode* n1, mNode* n2)
{
	if (n1->key == n2->key)return 0;
	if (n1->key < n2->key)return -1;
	return 1;
}

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::exchangecolor(mNode* n1, mNode* n2)
{
	bool tmp = n1->color;
	n1->color = n2->color;
	n2->color = tmp;
}


template<class K, class V, class Compare>
inline mMap<K, V, Compare>::mMap(mMap& m)
{
	leng = m.leng;
	if (leng) {
		root = new mNode();
		copyroot(m.root, root);
		threadedTree(root);
		thread = nullptr;
	}
}

template<class K, class V, class Compare>
inline mMap<K, V, Compare>& mMap<K, V, Compare>::operator=(mMap<K,V,Compare>& m)
{
	clear();
	leng = m.leng;
	if (leng) {
		root = new mNode();
		copyroot(m.root, root);
		threadedTree(root);
		thread = nullptr;
	}

	return *this;
}

template<class K, class V, class Compare>
inline mMap<K, V, Compare>::~mMap()
{
	clear();
}

template<class K, class V, class Compare>
inline int mMap<K, V, Compare>::size()
{
	return leng;
}

template<class K, class V, class Compare>
inline bool mMap<K, V, Compare>::empty()
{
	return leng == 0;
}

template<class K, class V, class Compare>
inline bool mMap<K, V, Compare>::notempty()
{
	return leng != 0;
}

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::insert(pair<K, V> ele)
{
	if (!leng) {
		root = new mNode(ele.first, ele.second);
		root->color = true;
		start = root;
		leng = 1;
		return;
	}
	mNode* newnode = new mNode(ele.first, ele.second);
	mNode* index = findNode(newnode, root);
	if (compare(index, newnode) == 0) {
		index->value = ele.second;
		return;
	}
	else if (compare(index, newnode) > 0) {
		index->left = newnode;
		newnode->pre = index->pre;
		if (newnode->pre)newnode->pre->next = newnode;
		newnode->next = index;
		index->pre = newnode;
	}
	else {
		index->right = newnode;
		newnode->next = index->next;
		if (newnode->next)newnode->next->pre = newnode;
		newnode->pre = index;
		index->next = newnode;
	}
	newnode->parent = index;
	leng++;
	if (!index->color)Fixinsert(newnode);
	root->color = true;
}

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::clear()
{
	leng = 0;
	thread = nullptr;
	start = nullptr;
	queue<mNode*> que;
	if(root)que.push(root);
	
	while (!que.empty())
	{
		mNode* node = que.front();
		que.pop();
		if (node->left)que.push(node->left);
		if (node->right)que.push(node->right);
		delete node;
	}

	root = nullptr;
}

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::erase(K k)
{
	mNode* target = findNode(new mNode(k), root);

	//若目标节点不存在则直接返回
	if (!target)return;
	if (compare(target, new mNode(k)) != 0)return;

	//保证删除节点最多只有一个子节点
	if (target->left && target->right) {
		mNode* tmp = target->next;
		target->key = tmp->key;
		target->value = tmp->value;
		target = tmp;
	}
	//寻找子节点
	mNode* child = nullptr;
	if (target->left) {
		child = target->left;
		child->next = target->next;
		if (child->next)child->next->pre = child;
	}
	else if (target->right) {
		child = target->right;
		child->pre = target->pre;
		if (child->pre)child->pre->next = child;
	}
	if (!child) {
		if (target->pre)target->pre->next = target->next;
		if (target->next)target->next->pre = target->pre;
		Fixdelete(target);
	}
	else {
		child->parent = target->parent;
	}
	
	
	if (target->parent) {
		//非根节点
		mNode* parent = target->parent;
		if (parent->left == target)parent->left = child;
		if (parent->right == target)parent->right = child;
	}
	else {
		if (!child) {
			clear();
			return;
		}
		root = child;
		start = child;
	}
	
	if (child && target->color) {
		if (!child->color)child->color = true;
		else Fixdelete(child);
	}
	if (root)root->color = true;
	delete target;
	leng--;
}

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::erase(iterator& it)
{
	mNode* target = it.now;
	it.now = target->next;
	erase(target->key);
}

template<class K, class V, class Compare>
inline void mMap<K, V, Compare>::preOrder(mNode* root, int leng, vector<int>& test)
{
	if (!root) {
		test.push_back(leng);
		return;
	}
	if (root->color)leng += 1;
	preOrder(root->left, leng, test);
	preOrder(root->right, leng, test);
}

template<class K, class V, class Compare>
inline bool mMap<K, V, Compare>::isBalance()
{
	vector<int> test;
	preOrder(root, 0, test);
	for (int i = 1; i < test.size(); i++) {
		if (test[i] != test[i - 1]) {
			return false;
		}
	}
	return true;
}

