#include "ahoCorasick.h"
#include <algorithm>

AhoCorasick::Node::Node(){}

AhoCorasick::Node::Node(char data): data(data){}

void AhoCorasick::Node::addStrings(vector<string> strings)
{
    std::sort(strings.begin(), strings.end());

    // create vector of iterators
    vector<IteratorPair> stringIterators(0);
    stringIterators.reserve(strings.size());
    for(const string &str : strings){
        if(str == ""){
            continue;
        }

        stringIterators.emplace_back(IteratorPair(str.begin(), str.end()));
    }

    addStrings(stringIterators.begin(), stringIterators.end());
}

void AhoCorasick::Node::addStrings(vector<IteratorPair>::iterator first, vector<IteratorPair>::iterator last)
{
    while(first != last && first->begin == first->end){
        isWord = true;
        ++first;
    }

    while(first != last){
        char toAdd = *first->begin;

        vector<IteratorPair>::iterator i = first;
        while(i != last && i->begin != i->end && *i->begin == toAdd){
            i->begin++;
            i++;
        }

        int charIndex = getCharIndex(toAdd);
        if(charIndex < 0){
            first = i;
            continue;
        }

        Node*& child = children[charIndex];
        if(child == nullptr){
            child = new Node(toAdd);
        }

        child->addStrings(first, i);
        first = i;
    }
}

void AhoCorasick::Node::addString(const string &str)
{
    IteratorPair strIt(str.begin(), str.end());
    addString(strIt);
}

void AhoCorasick::Node::addString(IteratorPair &str)
{
    if(str.begin == str.end){
        isWord = true;
        return;
    }

    int charIndex = getCharIndex(*str.begin);
    Node* child = children[charIndex];
    if(child == nullptr){
        child = new Node(*str.begin);
        children[charIndex] = child;
    }

    str.begin++;
    child->addString(str);
}

vector<string> AhoCorasick::Node::getAll(){
    vector<string> output;

    getAll(output, "");

    return output;
}

void AhoCorasick::Node::getAll(vector<string> &output, const string &current){
    if(isWord){
        output.emplace_back(current);
    }

    for(Node* child : children){
        if(child == nullptr) continue;
        child->getAll(output, current + child->data);
    }
}



int AhoCorasick::Node::getCharIndex(char c)
{
    if(c >= 'a' && c <= 'z'){
        return c - 'a';
    } else if(c >= '0' && c <= '9'){
        return (c - '0') + 26;
    } else if(c == '.'){
        return 36;
    } else if(c == '_'){
        return 37;
    } else {
        return -1;
    }
}

AhoCorasick::AhoCorasick() {

}

AhoCorasick::AhoCorasick(vector<string> strings){
    root = new Node();
    root->addStrings(strings);
}


/**
 * @brief AhoCorasick::getAll
 * @return a vector containing all strings in the trie
 */
vector<string> AhoCorasick::getAll() const
{
    return root->getAll();
}


AhoCorasick::~AhoCorasick(){}

