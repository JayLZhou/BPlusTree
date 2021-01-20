#include <iostream>
#include <queue>
using namespace std;
 int MAX = 2;

// BP node
class Node {
    bool IS_LEAF;
    int *key, size;
    Node** ptr;
    Node* parent;
    friend class BPTree;

public:
    Node():key(new int[MAX+1]),ptr(new Node* [MAX+1]),parent(NULL){}
    ~Node();
};

// BP tree
class BPTree {
    Node* root;
    void insertInternal(int,Node*,Node*,Node*);
    void split(int ,Node *,Node *);
    int insertVal(int ,Node *);
public:
    BPTree():root(NULL){}
    void insert(int x);
    void display();
};
