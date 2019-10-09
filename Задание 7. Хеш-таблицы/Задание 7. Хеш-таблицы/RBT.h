#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <iterator>
#include <stack>
#include <string>
#include <queue>

typedef enum { BLACK, RED } Color;

template<typename T>
class RBT
{
private:
    struct node
    {
        T data;
        node* parent;
        node* left;
        node* right;
        Color color;
        
        node(T d, node* p, node* l, node* r) : data(d), parent(p), left(l), right(r), color(BLACK) {}
        node(T d) : data(d), parent(nullptr), left(nullptr), right(nullptr), color(BLACK) {}
	public:
        node* next()
        {
            node* x = this;
            if (x->right)
                return minnode(x->right);
            node* y = x->parent;
            while (y && (x == y->right))
            {
                x = y;
                y = y->parent;
            }
            return y;
        }

		bool nextIsNull()
		{
			node* x = this;
			if (x->right)
				return false;
			node* y = x->parent;
			while (!y->right)
			{
				if(!y->parent) return true;
				y = y->parent;
			}
			return false;
		}

		node* prev()
		{
			node* x = this;
			if (x->left)
				return maxnode(x->left);
			node* y = x->parent;
			while (y && (x == y->left))
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		bool prevIsNull()
		{
			node* x = this;
			if (x->left)
				return false;
			if (!x->parent) return true;
			node* y = x->parent;
			while (!y->left)
			{
				if (!y->parent) return true;
				y = y->parent;
			}
			return false;
		}
    };
    
    // Поля класса дерева
    node* root;
    node* q = nullptr;
    size_t count_rotation = 0;

    // Операция ЛЕВОГО поворота
    void rotate_left(node* x)
    {
        ++count_rotation;
        node* y = x->right;
        
        x->right = y->left;
        
        if (y->left != nullptr)
            y->left->parent = x;
        
        if (y != nullptr)
            y->parent = x->parent;
        
        if (x->parent)
        {
            if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
        }
        else
            root = y;
        
        y->left = x;
        
        if (x != nullptr)
            x->parent = y;
    }
    
    // Операция ПРАВОГО поворота
    void rotate_right(node *x)
    {
        ++count_rotation;
        node *y = x->left;
        
        x->left = y->right;
        
        if (y->right != nullptr)
            y->right->parent = x;
        
        if (y != nullptr)
            y->parent = x->parent;
        
        if (x->parent)
        {
            if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
        }
        else
            root = y;
        
        y->right = x;
        
        if (x != nullptr)
            x->parent = y;
    }
    
    node* successor(node* p)
    {
        node* y = nullptr;
        if (p->left != nullptr)
        {
            y = p->left;
            while (y->right != nullptr)
                y = y->right;
        }
        else
        {
            y = p->right;
            while (y->left != nullptr)
                y = y->left;
        }
        return y;
    }
    
    // Процедура перекрашивания узлов и выполнения поворотов после вставки
    // с целью сохранения свойств красно-чёрного дерева
    void insert_Fixup(node* x)
    {
        while (x != root && x->parent->color == RED)
        {
            if (x->parent == x->parent->parent->left)
            {
                node* y = x->parent->parent->right;
                if (y->color == RED)
                {
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }
                else
                {
                    if (x == x->parent->right)
                    {
                        x = x->parent;
                        rotate_left(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    rotate_right(x->parent->parent);
                }
            }
            else
            {
                node* y = x->parent->parent->left;
                if (y->color == RED)
                {
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }
                else
                {
                    if (x == x->parent->left)
                    {
                        x = x->parent;
                        rotate_right(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    rotate_left(x->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    // Процедура перекрашивания узлов и выполнения поворотов после удаления
    // с целью сохранения свойств красно-чёрного дерева
    void remove_Fixup(node* x)
    {
        while (x && x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                node* w = x->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotate_left(x->parent);
                    w = x->parent->right;
                }
                if (w->left != nullptr && w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotate_right(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotate_left(x->parent);
                    x = root;
                }
            }
            else
            {
                node* w = x->parent->left;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotate_right(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotate_left(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotate_right(x->parent);
                    x = root;
                }
            }
            x->color = BLACK;
        }
        
    }
    
    void PrintHelp(node* root)
    {
        if (root != nullptr)
        {
            PrintHelp(root->left);
            std::cout << root->data << " ";
            PrintHelp(root->right);
        }
    }
    
    static node* minnode(node* p)
    {
        if (!p)
            return p;
        while (p->left)
            p = p->left;
        return p;
    }
    
    static node* maxnode(node* p)
    {
        if (!p)
            return p;
        while (p->right)
            p = p->right;
        return p;
    }
    
	
    
    void help_output(std::ofstream & out, node* root)
    {
        if (root)
        {
            help_output(out, root->left);
            out << root->data << " ";
            help_output(out, root->right);
        }
    }
public:
		size_t rotations() const
		{
			return count_rotation;
		};
    
    class TreeIterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
        node* rootIter;
		bool end_node = false;

    public:
        TreeIterator() : rootIter(nullptr) {}
        
        TreeIterator(node* tree, bool end = false) : rootIter(tree), end_node(end) {}
        
        T operator *()
        {
            return rootIter->data;
        }
        
        explicit TreeIterator(T data)
        {
            rootIter = new node(data);
        }
        
        //TreeIterator(const TreeIterator& other) : rootIter(other.rootIter) {}
        
        friend bool operator==(const TreeIterator& other1, const TreeIterator& other2)
        {
            return (other1.rootIter == other2.rootIter  && other1.end_node == other2.end_node);
            
        }
        
        friend bool operator!=(const TreeIterator& other1, const TreeIterator& other2)
        {
            return !(other1 == other2);
        }
        
       /* TreeIterator& operator=(const TreeIterator& other)
        {
            this->rootIter = other.rootIter;
            return *this;
        }
        
        TreeIterator& operator=(TreeIterator&& other)
        {
            this->rootIter = other.rootIter;
            other.rootIter = nullptr;
            return *this;
        }*/
        
        TreeIterator & operator++()
        {
            node * nextPtr = rootIter->next();
			
			if (nextPtr == nullptr && !end_node) end_node = true;
			else rootIter = nextPtr;

            return *this;
        }
        
        /*TreeIterator operator++(T)
        {
            TreeIterator cur(*this);
            operator++(); 
            return cur;
        }*/
        
        ~TreeIterator() = default;
    };
    
public:
    
    using iterator = TreeIterator;
    
    RBT() : root(nullptr) {}
    
    iterator end()
    {
        node* cur = root;
        
        /*if (cur == nullptr)
         return iterator(new node(0));*/
        
        while (cur->right != nullptr)
            cur = cur->right;
        return iterator(cur, true);
    }
    
    iterator begin()
    {
        node * cur = root;
        while (cur->left != nullptr)
            cur = cur->left;
        return iterator(cur);
    }
    
    iterator min()
    {
        return iterator(minnode(root));
    }
    
    iterator max()
    {
        return iterator(maxnode(root));
    }
    
    // Вставка 
    void insert(T data)
    {
        count_rotation = 0;
        node* cur = root;
        node* parent = nullptr;
        
        while (cur != nullptr)
        {
            if ((data == cur->data))
                return;
            parent = cur;
            if (data < cur->data)
                cur = cur->left;
            else cur = cur->right;
        }
        
        node* x = new node(data);
        x->parent = parent;
        x->color = RED;
        if (parent == nullptr)
            root = x;
        else {
            if ((data < parent->data))
                parent->left = x;
            else
                parent->right = x;
            
            while (x != root && x->parent->color == RED)
            {
                if (x->parent == x->parent->parent->left)
                {
                    node* uncle = x->parent->parent->right;
                    if (uncle == nullptr || uncle->color == BLACK)
                    {
                        
                        if (x == x->parent->right)
                        {
                            x = x->parent;
                            rotate_left(x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        rotate_right(x->parent->parent);
                    }
                    else
                    {
                        x->parent->color = BLACK;
                        uncle->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    }
                }
                else
                {
                    
                    node* uncle = x->parent->parent->left;
                    if (uncle == nullptr || uncle->color == BLACK)
                    {
                        if (x == x->parent->left)
                        {
                            x = x->parent;
                            rotate_right(x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        rotate_left(x->parent->parent);
                    }
                    else
                    {
                        x->parent->color = BLACK;
                        uncle->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    }
                    
                }
            }
        }
        root->color = BLACK;
    }
    
    // Удаление
    void remove(T x)
    {
        count_rotation = 0;
        if (root == nullptr)
            return;
        node* p = root;
        node* y = nullptr;
        int found = 0;
        while (p != nullptr && found == 0)
        {
            if (p->data == x)
                found = 1;
            if (found == 0)
            {
                if (p->data < x)
                    p = p->right;
                else
                    p = p->left;
            }
        }
        if (found == 0)
            return;
        else
        {
            if (p->left == nullptr || p->right == nullptr)
                y = p;
            else
                y = successor(p);
            if (y->left != nullptr)
                q = y->left;
            else
            {
                if (y->right != nullptr)
                    q = y->right;
                else
                    q = nullptr;
            }
            if (q != nullptr)
                q->parent = y->parent;
            if (y->parent == nullptr)
                root = q;
            else
            {
                if (y == y->parent->left)
                    y->parent->left = q;
                else
                    y->parent->right = q;
            }
            if (y != p)
            {
                p->color = y->color;
                p->data = y->data;
            }
            if (y->color == BLACK)
                remove_Fixup(q);
        }
    }

	iterator lower_bound_help(node* root, T x)
	{
		node* cur = root;
		bool goingLess = false;
		while (true)
		{
			if (cur->data == x)
				return iterator(cur);
			else if (cur->data > x)
			{
				if (cur->prev() == nullptr)
				{
					return iterator(cur);
				}
				else
				{
					goingLess = true;
					cur = cur->prev();
				}
			}
			else
				if (cur->next() == nullptr)
					return end();
				else
				{
					if (goingLess) return iterator(cur);
					goingLess = false;
					cur = cur->next();
				}
		}
	}


	iterator upper_bound_help(node* root, T x)
	{
		node* cur = root;
		bool goingMore = false;
		while (true)
		{
			if (cur->data == x)
				return iterator(cur);
			else if (cur->data > x)
			{
				if (cur->prev() == nullptr)
					return end();
				else
				{
					if (goingMore) return iterator(cur);
					goingMore = false;
					cur = cur->prev();
				}
			}
			else
				if (cur->next() == nullptr)
				{
					return iterator(cur);
				}
				else
				{
					goingMore = true;
					cur = cur->next();
				}

		}
	}
    
    // Находит позицию первого элемента в упорядоченном диапазоне, который имеет значение большее или эквивалентное указанному значению.
    // Если такового нет, то возвращает итератор на last
    iterator lower_bound(T x)
    {
        return lower_bound_help(root, x);
    }
    
    // Находит позицию первого элемента в упорядоченном диапазоне, который имеет значение меньшее или эквивалентное указанному значению.
    // Если такового нет, то возвращает итератор на last
    iterator upper_bound(T x)
    {
		return upper_bound_help(root, x);
    }
    
    void print_infix()
    {
        PrintHelp(root);
    }
     
    // Поиск элемента дерева по его значению, в случае неудачи возврат итератора end()
    iterator find(T x)
    {
        if (root == nullptr)
            return this->end();

        node* cur = root;
        while (cur != nullptr)
        {
            if (x < cur->data)
                cur = cur->left;
            else if (x > cur->data)
                cur = cur->right;
            else return iterator(cur);
        }
        return this->end();
    }
    
    void output_file(std::string name)
    {
        std::ofstream out(name);
        help_output(out, root);
        out.close();
    }
    
    void input_file(std::string name)
    {
        T data;
        std::ifstream in(name);
        while (!in.eof())
        {
            in >> data;
            insert(data);
        }
    }
};