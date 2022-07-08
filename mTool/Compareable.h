#pragma once

template<class K>
class Compareable
{

	int operator()(K k1, K k2) {
		if (k1 == k2)return 0;
		if (k1 < k2)return -1;
		return 1;
	}
};

