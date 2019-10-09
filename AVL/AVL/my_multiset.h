#pragma once
#include "avl_tree.h"

static size_t rotation_count = 0;

template <typename Key>
class my_multiset
{
	avl_tree<Key> values;
	class iterator;

public:
	iterator insert(Key value) { return iterator(values.insert(value, rotation_count), &values); }
	size_t erase(const Key& key) { return values.erase(key, rotation_count); }
	iterator find(const Key& key) const { return iterator(values.find(key), &values); }

	iterator lower_bound(const Key& key) { return iterator(values.lower_bound(key), &values); }
	iterator upper_bound(const Key & key) { return iterator(values.upper_bound(key), &values); }

	size_t size() const { return values.size(); }
	bool empty() const { return values.empty(); }
	
	iterator begin() { return iterator(values.begin(), &values); }
	iterator end() { return iterator(values.end(), &values); }

	void print_set()
	{
		print_tree(values);
	}
	
private:
	class iterator
	{
		avl_tree_node<Key>* node;
		avl_tree<Key>* tree;
		int count;

	public:
		iterator(avl_tree_node<Key>* node_, avl_tree<Key>* tree_) :
			tree(tree_), count(node_->count) {
			node = node_ ? node_ : tree->end();			
		}

		iterator(avl_tree_node<Key>* node_, avl_tree<Key>* tree_, int count_) :
			tree(tree_), count(count_) {
			node = node_ ? node_ : tree->end();
		}

		Key& operator*() { return node->value; }

		iterator& operator++()
		{
			iterator temp(node, tree, count);		
			next();
			return temp;
		}

		iterator& operator++(int)
		{
			next();
			return this;
		}

		bool operator==(iterator& other)
		{
			return node == other.node;
		}

		bool operator!=(iterator& other)
		{
			return node != other.node;
		}	
	private:
		void next()
		{
			if (count == 1)
				node = tree->next(node);
			else
				count--;
		}
	};
};

template<typename T>
void write_set_to_file(string file_path, my_multiset<T>& set)
{
	size_t r_c;
	ofstream os(file_path);
	for (auto val : set)
	{
		os << val << " ";
	}
	os.close();
}

template<typename T>
my_multiset<T>& read_set_from_file(string file_path)
{
	size_t r_c;
	ifstream is(file_path);
	my_multiset<T> set;

	while (!is.eof())
	{
		int val;
		is >> val;
		set.insert(val);
	}
	return set;
}