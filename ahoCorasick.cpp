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
        stringIterators.emplace_back(IteratorPair(str.begin(), str.end()));
    }

    addStrings(stringIterators.begin(), stringIterators.end());

    vector<string>::const_iterator query = strings.begin();
    for(int i = 0; i < strings.size(); i++){
        int j;
        for(j = i + 1; j < strings.size(); j++){
            if(strings[j][0] != strings[i][0]){
                break;
            }
        }

        i = j;
    }
}

void AhoCorasick::Node::addStrings(vector<IteratorPair>::iterator first, vector<IteratorPair>::iterator last)
{
    if(first == last){
        addString(*first);
        return;
    }

    for(vector<IteratorPair>::iterator i = first; i <= last; i++){
        char toAdd = *i->begin;
        i->begin++;

        vector<IteratorPair>::iterator j = i + 1;
        while(j <= last && *j->begin == toAdd){
            j->begin++;
            j++;
        }

        vector<Node*>::iterator childIt = std::find(children.begin(), children.end(), toAdd);
        Node* child;
        if(childIt == children.end()){
            child = new Node(toAdd);
            children.emplace_back(child);
        } else {
            child = *childIt;
        }

        child->addStrings(i, j - 1);
        i = j - 1;
    }
}

void AhoCorasick::Node::addString(string str)
{

}

void AhoCorasick::Node::addString(IteratorPair str)
{

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
        child->getAll(output, current + child->data);
    }
}



AhoCorasick::AhoCorasick() {

}


/**
 * @brief AhoCorasick::getAll
 * @return a vector containing all strings in the trie
 */
vector<string> AhoCorasick::getAll() const
{
    return root->getAll();
}


