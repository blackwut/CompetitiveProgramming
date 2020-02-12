#pragma once

#include <vector>

template <typename T>
class BSTArray {
public:
    BSTArray();
    ~BSTArray();

    void insert(T key);
    size_t search(T key);
    size_t search(T key, size_t index);

    T findMin();
    T findMin(size_t index);
    T findMax();
    T findMax(size_t index);

    T predecessor(size_t index);
    T successor(size_t index);

    int remove(T key);
    int remove(T key, size_t index);

    void destroy_tree();
    void destroy_tree(size_t index);

    void visit_preorder(const std::function<void (T & val)> & f);
    void visit_preorder(const std::function<void (T & val)> & f, size_t index);

    void visit_inorder(const std::function<void (T & val)> & f);
    void visit_inorder(const std::function<void (T & val)> & f, size_t index);

    void visit_postorder(const std::function<void (T & val)> & f);
    void visit_postorder(const std::function<void (T & val)> & f, size_t index);

    void visit_euler(const std::function<void (T & val)> & before,
                     const std::function<void (T & val)> & after);
    void visit_euler(const std::function<void (T & val)> & before,
                     const std::function<void (T & val)> & after,
                     size_t index);

    void visit_BFS(const std::function<void (T & val)> & f);
    void visit_BFS(const std::function<void (T & val)> & f, size_t index);


private:
    std::vector x;

    void insert(T key, size_t index);
};

template <typename T>
BSTArray<T>::BSTArray()
{
    
}

template <typename T>
BSTArray<T>::~BSTArray()
{
    destroy_tree();
}