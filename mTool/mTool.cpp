#include <iostream>
#include "mStack.h"
#include "mQueue.h"
#include "test.h"
#include <map>
#include "mMap.h"
#include <fstream>
#include <string>
#include "mList.h"

using namespace std;

vector<int> random(int count) {
    srand(int(time(0)));
    vector<int> result;

    for (int i = 0; i < count; i++) {
        result.push_back(rand());
    }

    return result;
}

void printMap(mMap<test, int>& m) {
    int index = 0;
    for (auto it = m.begin(); it != m.end();it++){
        cout << index++ << " " << it.first().num << " " << it.second() << endl;
    }
}

void randomdelete(vector<int>& nums,mMap<test,int>& m) {

    for (int i = 0; i < 100; i++) {
        auto tmpn = nums;
        random_shuffle(tmpn.begin(), tmpn.end());
        auto tmpm = m;
        for (int j = 0; j < nums.size(); j++) {
            tmpm.erase(test(tmpn[j]));
            if (!tmpm.isBalance()) {
                cout << "不平衡！！！" << endl;
                return;
            }
        }
    }

    cout << "测试通过！！！" << endl;

}

void write(vector<int>& nums) {

    ofstream ofs;
    ofs.open("test.txt",ios::out);

    for (int i = 0; i < nums.size(); i++) {
        ofs << nums[i] << endl;
    }

    ofs.close();

}


vector<int> read() {

    ifstream ifs;
    ifs.open("test.txt", ios::in);

    if (!ifs.is_open()) {
        cout << "文件打开失败" << endl;
    }

    vector<int> result;

    string str;
    while (getline(ifs, str)) {
        result.push_back(atoi(str.c_str()));
    }
    return result;
}

void testmap() {
    mMap<test, int> m;

    auto v = random(100);

    for (int i = 0; i < v.size(); i++) {
        m.insert(make_pair(test(v[i]), 1));
    }



    printMap(m);
    randomdelete(v, m);

    auto m1(m);
    printMap(m1);
    auto m2 = m1;
    printMap(m2);

    cout << m.size() << endl;
    cout << m.empty() << endl;
    cout << m.notempty() << endl;
}

void printList(mList<int>& m) {
    
    for (auto it = m.begin(); it != m.end(); it++) {
        cout << it.value() << endl;
    }

}

void testList() {

    mList<int> m;

    auto v = random(8);
    for (int i = 0; i < v.size(); i++) {
        m.pushback(v[i]);
    }

    printList(m);

    cout << endl;

    /*m.insert(3, 12, 3);

    printList(m);*/

    /*m.popback();
    m.popfront();*/

    /*m.pushback(3);
    m.pushfront(5);*/

   /* m.erase(0, 3);
    m.erase(1, 2);*/

    /*m.pushfront(3);
    m.insert(2, 3, 2);
    m.pushback(3);
    
    printList(m);

    m.remove(3);

    cout << endl;*/

    /*cout << m.front() << endl;
    cout << m.back() << endl << endl;

    m.front() = 5;*/

    //m.reverse();

    m.sort();

    printList(m);

    cout << endl;

    m.sort(true);

    printList(m);

}

int main()
{
    
    testList();

}

