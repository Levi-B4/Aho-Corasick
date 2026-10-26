#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include <string>
#include <vector>

using std::vector, std::string, std::istream;

class AhoCorasick
{
    private:
        struct IteratorPair{
            string::const_iterator begin;
            string::const_iterator end;
            IteratorPair(){}
            IteratorPair(string::const_iterator begin, string::const_iterator end) : begin(begin), end(end){}
        };

        class Node{
        public:
            vector<Node*> children;
            int numBranches = 0;
            Node* failLink = nullptr;
            bool isWord = false;

            char data;

            /**
             * @brief Aho_CNode - default constructor
             */
            Node();

            /**
             * @brief Aho_CNode - constructor
             * @param data - value to set as this node's data
             */
            Node(char data);

            void addStrings(vector<string> strings);

            void addStrings(vector<IteratorPair>::iterator first, vector<IteratorPair>::iterator last);

            void addString(string str);

            void addString(IteratorPair str);

            vector<string> getAll();

            void getAll(vector<string>& output, const string& current);

            Node& operator=(char data);

            bool operator==(char data);

            /**
             * @brief Aho_CNode - default destructor
             */
            ~Node();
        };

        Node* root = nullptr;
    public:

        /**
         * @brief Aho_corasick - default constructor
         */
        AhoCorasick();

        /**
         * @brief Aho_corasick - constructor which builds the data structure from given string array
         * @param strings - strings to create data structure
         */
        AhoCorasick(vector<string> strings);

        void addString(string data);

        void addStrings(vector<string> strings);

        /**
         * @brief processText - processes text and outputs a vector of lines where the query appeared
         * @param data
         * @return
         */
        vector<int> processText(const string &data) const;

        /**
         * @brief processText - processes text and outputs a vector of lines where the query appeared
         * @param data
         * @return
         */
        vector<int> processText(istream &data) const;

        vector<string> getAll() const;

        /**
         * @brief ~Aho_corasick - default destructor
         */
        ~AhoCorasick();
};

#endif // AHOCORASICK_H
