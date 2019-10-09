#pragma once

#include <iostream>
#include <fstream>
#include "avl_tree_node.h"

using namespace std;

template <typename Key>
class avl_tree
{
	avl_tree_node<Key>* root;
	avl_tree_node<Key>* null_elem;

	size_t size_c;		

public:	
    avl_tree() : root(nullptr), size_c(0)
	{
		null_elem = new avl_tree_node<Key>(NULL);
	}

	bool check() { return check_(root); }
	bool check_(avl_tree_node<Key>* node)
	{
		if (!node)
			return true;
		if (node->right && node->right->parent != node ||
			node->left && node->left->parent != node)
		{
			throw "lol";
			return false;
		}
		return check_(node->right) && check_(node->left);
	}

	avl_tree_node<Key>* insert(Key key, size_t& rotation_count) 
	{
		size_c++;
		if (!root)
			return insert_root(key);
		avl_tree_node<Key>* new_node = nullptr;		
		bst_insert(key, root, nullptr, new_node);
		null_elem_insert_reassign(new_node);		
		rotation_count = traverse_balancing(new_node->parent);		
		return new_node;
	}

	size_t erase(const Key& key, size_t& rotation_count)
    {
		size_t count;
		auto node = bst_erase(key, count);
		rotation_count = traverse_balancing(node);
		size_c -= count;
		return count;
    }

	avl_tree_node<Key>* find(const Key& key)
	{
		auto cur = root;
		while (cur && cur != null_elem)
		{
			if (cur->value == key)
				return cur;
			if (key > cur->value)
				cur = cur->right;
			else
				cur = cur->left;
		}
		return nullptr;
	}

	avl_tree_node<Key>* lower_bound(const Key& key)
    {
        auto current = root;
        avl_tree_node<Key>* next = nullptr;
        while (current && current != null_elem)
        {
            if (current->value >= key)
            {
                next = current;
                current = current->left;
            }
            else
                current = current->right;
        }
        return next;
    }

	avl_tree_node<Key>* upper_bound(const Key& key)
    {
        auto current = root;
        avl_tree_node<Key>* next = nullptr;
        while (current && current != null_elem)
        {
            if (current->value <= key)
            {
                next = current;
                current = current->right;
            }
            else
                current = current->left;
        }
        return next;
    }

	size_t size() const { return size_c; }
	bool empty() const { return size_c == 0; }

	avl_tree_node<Key>* next(avl_tree_node<Key>* node)
	{
		if (auto temp = node->right)
		{
			if (temp == null_elem)
				return temp;

			while (temp->left)
				temp = temp->left;

			return temp;
		}

		auto temp = node;
		while (!temp->is_left())
			temp = temp->parent;

		return temp->parent;
	}

	avl_tree_node<Key>* begin() { return null_elem->left; }
	avl_tree_node<Key>* end() { return null_elem; }
	
private:
	avl_tree_node<Key>* insert_root(Key key)
	{
		root = new avl_tree_node<Key>(key);
		null_elem->left = root;		
		null_elem->right = root;
		root->right = null_elem;
		return root;
	}

	avl_tree_node<Key>* bst_insert(Key key, avl_tree_node<Key>* node, avl_tree_node<Key>* parent, avl_tree_node<Key>*& new_node)
	{		
		if (!node || node == null_elem)
		{
			new_node = new avl_tree_node<Key>(key, parent, nullptr, nullptr);			
			return new_node;
		}
		if (node->value == key)
		{
			new_node = node;
			new_node->count++;
		}
			
		if (key > node->value)
			node->right = bst_insert(key, node->right, node, new_node);
		if (key < node->value)
			node->left = bst_insert(key, node->left, node, new_node);		
		return node;
	}

	avl_tree_node<Key>* bst_erase(Key key, size_t & count) // returns parrent of deleted node
	{
		auto node = find(key);		
		if (!node)
		{
			count = 0;
			return nullptr;
		}			
		count = node->count;
		if (node->left && node->right && node->right != null_elem)
		{
			auto temp = leftest_from(node->right); // temp can have only 1 right child (leaf or null_elem)
			node->value = temp->value;
			node = temp->parent;
			if (temp->right)
			{
				if (temp->right == null_elem) // if child is null_elem then reassign n_el and delete temp
				{
					null_elem->right = node;
					node->right = null_elem;
				}
				else // if child is a leaf then delete leaf
				{
					temp->value = temp->right->value;
					temp = temp->right;
				}
			}
			delete temp;
		}
		else if (node->right == null_elem)
		{
			if (auto temp = node->left)
			{
				node->value = temp->value;
				delete temp;
			}
			else // 
			{
				temp = node;
				node = node->parent;
				null_elem->right = node;
				if (node)
					node->right = null_elem;
				else
					root = nullptr;
				delete temp;
			}
		}		
		else if (node->right)
		{
			auto temp = node->right;
			node->value = temp->value;
			node->height = 1;
			node = node->parent;
			delete temp;
		}
		else if (node->left)
		{
			auto temp = node->left;
			if (null_elem->left == temp)
				null_elem->left = node;
			node->value = temp->value;
			node->height = 1;
			node = node->parent;
			delete temp;
		}
		else
		{
			auto temp = node;
			node = node->parent;
			delete temp;
		}

		return node;
	}	

	void null_elem_insert_reassign(avl_tree_node<Key>* node)
	{
		if (!node)
			return;
		if (null_elem->left->left == node) // Added new minimum
			null_elem->left = node;
		if (null_elem->right->right == node) // Added new maximum
		{
			null_elem->right = node;
			node->right = null_elem;
		}
	}

    avl_tree_node<Key>* rotate_left(avl_tree_node<Key>* node)
    {
        auto r_node = node->right;
        node->right = r_node->left;
		if (r_node->left)
			r_node->left->parent = node;
		if (!node->parent)		
			root = r_node;
		else
		{
			if (node->is_left())
				node->parent->left = r_node;
			else
				node->parent->right = r_node;
		}
		r_node->parent = node->parent;
		r_node->left = node;
		node->parent = r_node;

        restore_height(node);
        restore_height(r_node);

        return r_node;
    }

    avl_tree_node<Key>* rotate_right(avl_tree_node<Key>* node)
    {
        auto l_node = node->left;
        node->left = l_node->right;
		if (l_node->right)
			l_node->right->parent = node;
		if (!node->parent)
			root = l_node;
		else
		{
			if (node->is_left())
				node->parent->left = l_node;
			else
				node->parent->right = l_node;
		}
		l_node->parent = node->parent;
		l_node->right = node;
		node->parent = l_node;

        restore_height(node);
        restore_height(l_node);

        return l_node;
    }

    avl_tree_node<Key>* leftest_from(avl_tree_node<Key>* node) const
    {
        auto temp = node;
        while (temp->left)
            temp = temp->left;
        return temp;
    }

	void restore_height(avl_tree_node<Key>* node)
    {		
		auto left = node->left ? node->left->height : 0;
		auto right = node->right ? node->right->height : 0;
	    node->height = (left > right ? left : right) + 1;
    }

	size_t traverse_balancing(avl_tree_node<Key>* node)
	{
		size_t rotation_count = 0;
		while (node)
		{			
			restore_height(node);
			switch (get_balance(node))
			{
			case 1: break;
			case -1: break;
			case 0: return rotation_count;
			default: rotation_count += balancing(node);
				if (get_balance(node) == 0) return rotation_count;
				break;
			}
			node = node->parent;
		}
		return rotation_count;
	}

	size_t balancing(avl_tree_node<Key>* node)
    {       
		size_t rotation_count = 1;
        if (get_balance(node) == 2)
        {
			if (get_balance(node->left) < 0)
			{
				rotation_count++;
				node->left = rotate_left(node->left);
			}
            rotate_right(node);
        }
        if (get_balance(node) == -2)
        {
			if (get_balance(node->right) > 0)
			{
				rotation_count++;
				node->right = rotate_right(node->right);
			}
            rotate_left(node);
        }		
        return rotation_count;
    }

	size_t height(avl_tree_node<Key>* node) const
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

	int get_balance(avl_tree_node<Key>* node) const
    {
		if (!node)
			return 0;
        return height(node->left) - height(node->right);
    }

	template<typename T>
	friend void print_tree(const avl_tree<T>& tree);
};

template<typename T>
void print_tree(const avl_tree<T>& tree)
{
	auto root = tree.root;
	print_node(root, tree.null_elem);
}

template<typename T>
void print_node(const avl_tree_node<T>* node, const avl_tree_node<T>* null_elem, int space = 0, int tab = 4)
{
	if (node == nullptr || node == null_elem)
		return;
	print_node(node->right, null_elem, space + tab);
	for (int i = 0; i < space; i++)
		std::cout << " ";
	std::cout << node->value << std::endl;
	print_node(node->left, null_elem, space + tab);
}