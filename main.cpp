
#include "BPlusTree.h"

void BPTree::insert(int x) {
    if (root == NULL) {
        root = new Node;
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
        root->parent = NULL;
    } else {
        Node *cursor = root;
        Node *parent;

        while (cursor->IS_LEAF == false) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }

                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        if (cursor->size < MAX) {
            insertVal(x,cursor);
            cursor->parent = parent;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        } else split(x, parent, cursor);
    }
}
int BPTree::insertVal(int x, Node *cursor) {
    int i = 0;
    while (x > cursor->key[i] && i < cursor->size) i++;
    for (int j = cursor->size; j > i; j--) cursor->key[j] = cursor->key[j - 1];
    cursor->key[i] = x;
    cursor->size++;
    return i;
}
void BPTree::split(int x, Node * parent, Node *cursor) {
    Node* LLeaf=new Node;
    Node* RLeaf=new Node;
    insertVal(x,cursor);
    LLeaf->IS_LEAF=RLeaf->IS_LEAF=true;
    LLeaf->size=(MAX+1)/2;
    RLeaf->size=(MAX+1)-(MAX+1)/2;
    for(int i=0;i<MAX+1;i++)LLeaf->ptr[i]=cursor->ptr[i];
    LLeaf->ptr[LLeaf->size]= RLeaf;
    RLeaf->ptr[RLeaf->size]= LLeaf->ptr[MAX];
    LLeaf->ptr[MAX] = NULL;
    for (int i = 0;i < LLeaf->size; i++) {
        LLeaf->key[i]= cursor->key[i];
    }
    for (int i = 0,j=LLeaf->size;i < RLeaf->size; i++,j++) {
        RLeaf->key[i]= cursor->key[j];
    }
    if(cursor==root){
        Node* newRoot=new Node;
        newRoot->key[0] = RLeaf->key[0];
        newRoot->ptr[0] = LLeaf;
        newRoot->ptr[1] = RLeaf;
        newRoot->IS_LEAF = false;
        newRoot->size = 1;
        root = newRoot;
        LLeaf->parent=RLeaf->parent=newRoot;
    }
    else {insertInternal(RLeaf->key[0],parent,LLeaf,RLeaf);}

}
void BPTree::insertInternal(int x,Node* cursor,Node* LLeaf,Node* RRLeaf)
{

    if (cursor->size < MAX) {
       auto i=insertVal(x,cursor);
        for (int j = cursor->size;j > i + 1; j--) {
            cursor->ptr[j]= cursor->ptr[j - 1];
            }
        cursor->ptr[i]=LLeaf;
        cursor->ptr[i + 1] = RRLeaf;
    }

    else {

        Node* newLchild = new Node;
        Node* newRchild = new Node;
        Node* virtualPtr[MAX + 2];
        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i=insertVal(x,cursor);
        for (int j = MAX + 2;j > i + 1; j--) {
            virtualPtr[j]= virtualPtr[j - 1];
        }
        virtualPtr[i]=LLeaf;
        virtualPtr[i + 1] = RRLeaf;
        newLchild->IS_LEAF=newRchild->IS_LEAF = false;
        newLchild->size= (MAX + 1) / 2;
        newRchild->size= MAX - (MAX + 1) /2;
        for (int i = 0;i < newLchild->size;i++) {

            newLchild->key[i]= cursor->key[i];
        }
        for (int i = 0, j = newLchild->size+1;i < newRchild->size;i++, j++) {

            newRchild->key[i]= cursor->key[j];
        }
        for (int i = 0;i < LLeaf->size + 1;i++) {
            newLchild->ptr[i]= virtualPtr[i];
        }
        for (int i = 0, j = LLeaf->size + 1;i < RRLeaf->size + 1;i++, j++) {
            newRchild->ptr[i]= virtualPtr[j];
        }
        if (cursor == root) {
            Node* newRoot = new Node;
            newRoot->key[0]= cursor->key[newLchild->size];
            newRoot->ptr[0] = newLchild;
            newRoot->ptr[1] = newRchild;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
            newLchild->parent=newRchild->parent=newRoot;
        }
        else {
            insertInternal(cursor->key[newLchild->size],cursor->parent,newLchild,newRchild);
        }
    }
}


void BPTree::display() {
    queue<Node*>q;
    q.push(root);
    while(!q.empty()){

        int size_t=q.size();
        while(size_t--){
            auto t=q.front();
            for(int i=0;i<t->size+1;i++){
                if(!t->IS_LEAF){
                    q.push(t->ptr[i]);
                }
            }
            for(int i=0;i<t->size;i++){
                cout<<t->key[i]<<",";
            }
            cout<<"  ";
            q.pop();
        }
        cout<<endl;

    }

}
// Driver Code
int main()
{
    BPTree node;
    node.insert(5);
    node.insert(8);
    node.insert(10);
    node.insert(15);
    node.insert(16);
    node.insert(20);
    node.insert(19);
    node.display();
    return 0;
}