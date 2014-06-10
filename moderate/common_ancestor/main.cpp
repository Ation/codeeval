#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <map>
#include <set>

using namespace std;

bool getUnsignedInteger(const string &line, size_t &position, unsigned int &number) {
    unsigned int result = 0;
    char temp;

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            break;
        }
    }

    if (position >= line.length()) {
        return false;
    }

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            position ++;
            break;
        }
    }

    number = result;
    return true;
}

typedef struct _node {
    struct _node *parent;
    struct _node *left;
    struct _node *right;

    unsigned int value;
}Node;

class Tree {
public:
    Tree(){}

    void addRoot(unsigned int value) {
        m_root = new Node();

        m_root->parent = m_root->left = m_root->right = nullptr;
        m_root->value = value;

        saveNode(m_root);
    }

    void addLeft(unsigned int parentValue, unsigned int nodeValue) {
        auto parent = getNode(parentValue);
        auto node = createChild(parent, nodeValue);

        parent->left = node;
    }

    void addRight( unsigned int parentValue, unsigned int nodeValue) {
        auto parent = getNode(parentValue);
        auto node = createChild(parent, nodeValue);

        parent->right = node;
    }

    unsigned int getAncestor(unsigned int one, unsigned int two) {
        set<unsigned int> ancestors;

        auto node = getNode(one);

        while (node != nullptr) {
            ancestors.insert(node->value);
            node = node->parent;
        }

        node = getNode(two);

        while (node != nullptr) {
            auto it = ancestors.find(node->value);
            if (it != ancestors.end()) {
                return (*it);
            }
            node = node->parent;
        }

        return 0;
    }

private:
    map<unsigned int, Node *> m_nodeMap;
    Node  *m_root;

    void saveNode(Node *node) {
        m_nodeMap.insert( pair<unsigned int, Node*>(node->value, node));
    }

    Node* getNode(unsigned int value) {
        return m_nodeMap[value];
    }

    Node* createChild(Node *parentNode, unsigned int nodeValue) {
        auto node = new Node();
        node->left = node->right = nullptr;
        node->parent = parentNode;

        node->value = nodeValue;

        saveNode(node);

        return node;
    }
};

unsigned int getLowestAncestor(const string &line, Tree &tree) {
    unsigned int one;
    unsigned int two;

    size_t position = 0;

    getUnsignedInteger(line, position, one);
    getUnsignedInteger(line, position, two);

    return tree.getAncestor(one, two);
}

int main(int argc, char *argv[]) {
    Tree tree;

    tree.addRoot(30);
    tree.addLeft(30, 8);
    tree.addRight(30, 52);

    tree.addLeft(8, 3);
    tree.addRight(8, 20);

    tree.addLeft(20, 10);
    tree.addRight(20, 29);

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        cout << getLowestAncestor(inputLine, tree) << endl;
    }

    return 0;
}

