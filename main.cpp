#include "ahoCorasick.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> query{"dog", "cat", "dino", "dog1", "dog2", "ding_dong", "attack", "act"};

    AhoCorasick ac(query);

    vector<string> queryRetrieved = ac.getAll();

    for(string str : queryRetrieved){
        cout << str << "\n";
    }

    return 0;
}
