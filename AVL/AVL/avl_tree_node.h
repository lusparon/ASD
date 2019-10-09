#pragma once

template <typename T>
struct avl_tree_node
{
    T value;

    avl_tree_node<T>* parent;
    avl_tree_node<T>* left;
    avl_tree_node<T>* right;

	size_t count;
    int height;

    avl_tree_node(T value_, avl_tree_node<T>* parent_ = nullptr,
                  avl_tree_node<T>* left_ = nullptr, avl_tree_node<T>* right_ = nullptr) :
            value(value_), parent(parent_), left(left_), right(right_),
            height(1), count(1) {}

    ~avl_tree_node()
    {
        if (parent)
        {
            if (is_left())
                parent->left = nullptr;
            else
                parent->right = nullptr;
            parent = nullptr;
        }
        left = nullptr;
        right = nullptr;
    }

    bool is_left()
    {
        return parent && this == parent->left;
    }
};