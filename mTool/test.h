#pragma once
class test
{
public:
	test(){}
	test(int n) : num(n) {

	}
	int num = 0;

	bool operator==(test& t) {
		return num == t.num;
	}
	bool operator<(test& t) {
		return num < t.num;
	}

};

