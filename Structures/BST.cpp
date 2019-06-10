/**
    Author:  Alberto Ottimo
    BST struct based
*/

#include <iostream>
#include <queue>
using namespace std;

template <typename T>
struct node {
    T key;
    node * left;
    node * right;
    node * parent;

    node(T key) :
    key(key),
    left(NULL),
    right(NULL),
    parent(NULL)
    {}

    node(T key, node<T> * parent) :
    key(key),
    left(NULL),
    right(NULL),
    parent(parent)
    {}
};

template <typename T>
class BST {
public:
    BST();
    ~BST();

    void insert(T key);
    node<T> * search(T key);
    node<T> * search(T key, node<T> * n);

    node<T> * findMin();
    node<T> * findMin(node<T> * n);
    node<T> * findMax();
    node<T> * findMax(node<T> * n);

    node<T> * predecessor(node<T> * n);
    node<T> * successor(node<T> * n);

    node<T> * remove(T key);
    node<T> * remove(T key, node<T> * n);

    void destroy_tree();
    void destroy_tree(node<T> * n);

    void visit_preorder(const std::function<void (node<T> *)> & f);
    void visit_preorder(const std::function<void (node<T> *)> & f, node<T> * n);

    void visit_inorder(const std::function<void (node<T> *)> & f);
    void visit_inorder(const std::function<void (node<T> *)> & f, node<T> * n);

    void visit_postorder(const std::function<void (node<T> *)> & f);
    void visit_postorder(const std::function<void (node<T> *)> & f, node<T> * n);

    void visit_euler(const std::function<void (node<T> *)> & before,
                     const std::function<void (node<T> *)> & after);
    void visit_euler(const std::function<void (node<T> *)> & before,
                     const std::function<void (node<T> *)> & after,
                     node<T> * n);

    void visit_BFS(const std::function<void (node<T> *)> & f);
    void visit_BFS(const std::function<void (node<T> *)> & f, node<T> * n);


private:
    node<T> * root;

    void insert(T key, node<T> * n);
};

template <typename T>
BST<T>::BST()
{
    root = NULL;
}

template <typename T>
BST<T>::~BST()
{
    destroy_tree();
}

template <typename T>
void BST<T>::insert(T key)
{
    if (root == NULL) {
        root = new node<T>(key);
    } else {
        insert(key, root);
    }
}

template <typename T>
void BST<T>::insert(T key, node<T> * n)
{
    if (key < n->key) {
        if(n->left == NULL){
            n->left = new node<T>(key, n);
        } else {
            insert(key, n->left);
        }
    } else {
        if(n->right == NULL) {
            n->right = new node<T>(key, n);
        } else {
            insert(key, n->right);
        }
    }
}


template <typename T>
node<T> * BST<T>::search(T key)
{
    return search(key, root);
}

template <typename T>
node<T> * BST<T>::search(T key, node<T> * n)
{
    if (n == NULL) {
        return NULL;
    }
    
    if(key == n->key){
        return n;
    }

    if (key < n->key){
        return search(key, n->left);
    }

    return search(key, n->right);
}


template <typename T>
node<T> * BST<T>::findMin()
{
    return findMin(root);
}

template <typename T>
node<T> * BST<T>::findMin(node<T> * n)
{
    if (n == NULL) {
        return NULL;
    }

    if (n->left == NULL) {
        return n;
    }

    return findMin(n->left);
}


template <typename T>
node<T> * BST<T>::findMax()
{
    return findMax(root);
}

template <typename T>
node<T> * BST<T>::findMax(node<T> * n)
{
    if (n == NULL) {
        return NULL;
    }

    if (n->right == NULL) {
        return n;
    }

    return findMax(n->right);
}


template <typename T>
node<T> * BST<T>::predecessor(node<T> * n)
{
    if (n == NULL) {
        return NULL;
    }

    if (n->left != NULL) {
        return findMax(n->left);
    }

    node<T> * tmp = n->parent;
    while ((tmp != NULL) && (n == tmp->left)) {
        n = tmp;
        tmp = tmp->parent;
    }
    return tmp;
}


template <typename T>
node<T> * BST<T>::successor(node<T> * n)
{
    if (n == NULL) {
        return NULL;
    }

    if (n->right != NULL) {
        return findMin(n->right);
    }

    node<T> * tmp = n->parent;
    while ((tmp != NULL) && (n == tmp->right)) {
        n = tmp;
        tmp = tmp->parent;
    }
    return tmp;
}

template <typename T>
node<T> * BST<T>::remove(T key)
{
    return remove(key, root);
}

template <typename T>
node<T> * BST<T>::remove(T key, node<T> * n)
{
    if (n == NULL) {
        return n;
    }

    if (key < n->key) {
        n->left = remove(key, n->left);
    } else if (key > n->key) {
        n->right = remove(key, n->right);
    } else {

        if (n->left == NULL) {
            node<T> * tmp = n->right;
            if (tmp != NULL) {
                tmp->parent = n->parent;
            }
            delete n;
            return tmp;
        }
        if (n->right == NULL) {
            node<T> * tmp = n->left;
            if (tmp != NULL) {
                tmp->parent = n->parent;
            }
            delete n;
            return tmp;
        }

        node<T> * tmp = findMin(n->right);
        n->key = tmp->key;
        n->right = remove(tmp->key, n->right);
    }

    return n;
}


template <typename T>
void BST<T>::destroy_tree()
{
    destroy_tree(root);
}

template <typename T>
void BST<T>::destroy_tree(node<T> * n)
{
    if (n != NULL){
        destroy_tree(n->left);
        destroy_tree(n->right);
        delete n;
    }
}


template <typename T>
void BST<T>::visit_preorder(const std::function<void (node<T> *)> & f)
{
    visit_preorder(f, root);
}

template <typename T>
void BST<T>::visit_preorder(const std::function<void (node<T> *)> & f, node<T> * n)
{
    if (n != NULL) {
        f(n);
        visit_preorder(f, n->left);
        visit_preorder(f, n->right);
    }
}


template <typename T>
void BST<T>::visit_inorder(const std::function<void (node<T> *)> & f)
{
    visit_inorder(f, root);
}

template <typename T>
void BST<T>::visit_inorder(const std::function<void (node<T> *)> & f, node<T> * n)
{
    if (n != NULL) {
        visit_inorder(f, n->left);
        f(n);
        visit_inorder(f, n->right);
    }
}


template <typename T>
void BST<T>::visit_postorder(const std::function<void (node<T> *)> & f)
{
    visit_postorder(f, root);
}

template <typename T>
void BST<T>::visit_postorder(const std::function<void (node<T> *)> & f, node<T> * n)
{
    if (n != NULL) {
        visit_postorder(f, n->left);
        visit_postorder(f, n->right);
        f(n);
    }
}


template <typename T>
void BST<T>::visit_euler(const std::function<void (node<T> *)> & before,
                         const std::function<void (node<T> *)> & after)
{
    visit_euler(before, after, root);
}

template <typename T>
void BST<T>::visit_euler(const std::function<void (node<T> *)> & before,
                         const std::function<void (node<T> *)> & after,
                         node<T> * n)
{
    if (n != NULL) {
        before(n);
        visit_euler(before, after, n->left);
        visit_euler(before, after, n->right);
        after(n);
    }
}


template <typename T>
void BST<T>::visit_BFS(const std::function<void (node<T> *)> & f)
{
    visit_BFS(f, root);
}

template <typename T>
void BST<T>::visit_BFS(const std::function<void (node<T> *)> & f, node<T> * n)
{
    if (n != NULL) {
        queue<node<T> *> q;
        q.push(n);

        while (!q.empty()) {
            node<T> * tmp = q.front();
            q.pop();
            f(tmp);
            if (tmp->left != NULL) {
                q.push(tmp->left);
            }
            if (tmp->right != NULL) {
                q.push(tmp->right);
            }
        }
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto printNode = [](node<int> * n){cout << n->key << " ";};

    BST<int> * tree = new BST<int>();

    tree->insert(3);
    tree->insert(1);
    tree->insert(5);
    tree->insert(0);
    tree->insert(2);
    tree->insert(4);
    tree->insert(6);

    // tree->remove(1);

    cout << " preorder: ";
    tree->visit_preorder(printNode);
    cout << endl;
    
    cout << "  inorder: ";
    tree->visit_inorder(printNode);
    cout << endl;

    cout << "postorder: ";
    tree->visit_postorder(printNode);
    cout << endl;

    cout << "    euler: ";
    tree->visit_euler(printNode, printNode);
    cout << endl;

    cout << "      BFS: ";
    tree->visit_BFS(printNode);
    cout << endl;

    cout << "predecessors:" << endl;
    tree->visit_inorder([&tree](node<int> * n) {
        node<int> * p = tree->predecessor(n);
        if (p != NULL) {
            cout << n->key << "<-" << p->key << endl;
        }
    });
    cout << endl;

    cout << "successors:" << endl;
    tree->visit_inorder([&tree](node<int> * n) {
        node<int> * s = tree->successor(n);
        if (s != NULL) {
            cout << n->key << "->" << s->key << endl;
        }
    });
    cout << endl;

    cout << "parents:" << endl;
    tree->visit_inorder([](node<int> * n) {
        node<int> * p = n->parent;
        if (p != NULL) {
            cout << n->key << "<-" << p->key << endl;
        }
    });
    cout << endl;

    delete tree;

    return 0;
}
