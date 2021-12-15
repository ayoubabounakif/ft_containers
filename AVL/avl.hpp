/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:33:38 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/15 20:24:41 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"
# include "../iterator/iterator_traits/iterator_traits.hpp"
# include "../iterator/iterator/iterator.hpp"
# include "../iterator/iterator/reverse_iterator.hpp"
# include "../iterator/bidirectional_iterator/bidirectional_iterator.hpp"

# include <errno.h>

//! if Linux
// #define ptrdiff_t __gnu_cxx::ptrdiff_t

namespace ft {
    

    template < class T, class Compare = std::less<typename T::first_type> , class Alloc = std::allocator<T> >
    class AVL {

        struct Node;

        public:
            typedef T           value_type;
            typedef typename T::first_type key_type;
            typedef Node        node_type;
            typedef Compare     key_compare;
            typedef Alloc       allocator_type;
            typedef ptrdiff_t   difference_type;
            typedef size_t      size_type;
            typedef typename    allocator_type::template rebind<node_type>::other   rebind_allocator;
            typedef             bidirectional_iterator<value_type, node_type, AVL>             iterator;
            typedef             bidirectional_iterator<const value_type, const node_type, AVL> const_iterator;
            typedef             reverse_iterator<const_iterator>  const_reverse_iterator;
            typedef             reverse_iterator<iterator>  reverse_iterator;

        private:
            struct Node {
                value_type *    data;
                Node *          parent;
                Node *          left;
                Node *          right;
                int             height;
                int             balanceFactor;
            };
        
        private:
            node_type   *       __root;
            key_compare         __comp;
            allocator_type      __alloc;
            rebind_allocator    __rebindAlloc;
            size_type           __size;

            node_type * __initNode( const value_type& value ) {
                node_type * tmp = __rebindAlloc.allocate(1);
                tmp->data = __alloc.allocate(1);
                __alloc.construct(tmp->data, value);
                tmp->parent = nullptr;
                tmp->left = nullptr;
                tmp->right = nullptr;
                tmp->height = 1;
                tmp->balanceFactor = 0;
                return tmp;
            }

        public:
                    /* ----------- Member Functions ---------- */    
                /* ---- Constructors & Destructor respectively ---- */
            /* ------------------------ Default ------------------------ */
            explicit AVL( const allocator_type& allocator = allocator_type(), const key_compare& compare = key_compare()) :
                __root(nullptr),
                __comp(compare),
                __alloc(allocator),
                __rebindAlloc(allocator),
                __size(0) {}

            /* ----------------------- Range ------------------------ */
            template < class InputIt >
                AVL( InputIt first, InputIt last, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt()) {
                    difference_type distance = std::distance(first, last);
                    this->__root = nullptr;
                    this->__size = 0;
                    this->__comp = compare;
                    this->__alloc = allocator;
                    this->__rebindAlloc = allocator;
                    for (difference_type i = 0; i < distance; i++) {
                        this->insert(*first);
                        ++first;
                    }
                }

            /* ------------------------ Copy ------------------------ */
            AVL ( const AVL& x ) { *this = x; };
            
            /* ------------------ Assignment Operator --------------- */
            AVL& operator= ( const AVL& x ) {
                __traverseAndDelete(this->__root);
                this->__root = nullptr;
                if ( this != &x ) {
                    this->__alloc = x.__alloc;
                    this->__rebindAlloc = x.__rebindAlloc;
                    this->__comp = x.__comp;
                    this->__size = x.__size;
                    __traverseAndInsert(x.__root);
                }
                return (*this);
            }
            
            /* ---------------------- Destructor --------------------- */
            ~AVL() {}

        private:
            void    __traverseAndDelete( node_type * x ) {
                if (x == nullptr) {
                    this->__root = nullptr;
                    return ;
                }
                __traverseAndDelete(x->left);
                __traverseAndDelete(x->right);
                this->__alloc.deallocate(x->data, 1);
                this->__rebindAlloc.deallocate(x, 1);
                return ;
            }

            void    __traverseAndInsert( node_type * x ) {
                if (x == nullptr)
                    return ;
                this->__root = __insert(this->__root, *x->data);
                __traverseAndInsert(x->left);
                __traverseAndInsert(x->right);
                return ;
            }

        public:
            /* ---------------------- Iterators --------------------- */
            iterator begin() { return iterator(findMinValue(this->__root), this); }
            const_iterator begin() const { return iterator(findMinValue(this->__root), this); }
            iterator end() { return iterator(nullptr, this); }
            const_iterator end() const { return iterator(nullptr, this); }
            
            reverse_iterator rbegin() { return reverse_iterator(end()); }
            reverse_iterator rend() { return reverse_iterator(begin()); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        public:
            /* ----------------------- Capacity --------------------- */
            size_type size( void ) const { return this->__size; }
            size_type max_size( void ) const { return this->__alloc.max_size(); }
            bool empty() const { return this->__size == 0 ? true : false; }
            
            /* ------------------------ Lookup ---------------------- */
            node_type * findMinValue( node_type * node ) {
                if (this->__root == nullptr)
                    return nullptr;
                while (node->left != nullptr)
                    node = node->left;
                return node;
            }
            node_type * findMinValue( node_type * node ) const {
                if (this->__root == nullptr)
                    return nullptr;
                while (node->left != nullptr)
                    node = node->left;
                return node;
            }
            node_type * findMaxValue( node_type * node ) {
                while (node->right != nullptr)
                    node = node->right;
                return node;
            }
            node_type * findMaxValue( node_type * node ) const {
                while (node->right != nullptr)
                    node = node->right;
                return node;
            }
            node_type * successor( const key_type& key ) {
                node_type * successor = nullptr;
				node_type * root = this->__root;
				while (root != nullptr) {
					if (__comp(key, root->data->first)) {
						successor = root;
						root = root->left;
					}
					else if (!__comp(key, root->data->first))
						root = root->right;
				}
				return (successor);
            }
            node_type * successor( const key_type& key ) const {
                node_type * successor = nullptr;
				node_type * root = this->__root;
				while (root != nullptr) {
					if (__comp(key, root->data->first)) {
						successor = root;
						root = root->left;
					}
					else if (!__comp(key, root->data->first))
						root = root->right;
				}
				return (successor);
            }
            node_type * find(node_type * node, const key_type& key ) {
                if (node == nullptr)
                    return nullptr;
                if (!__comp(node->data->first, key) && !__comp(key, node->data->first))
                    return node;
                else if (!__comp(node->data->first, key)) {
					return find(node->left, key);
				}
                else if (__comp(node->data->first, key)) {
					return find(node->right, key);
                }
                return node;
            }
            node_type * find(node_type * node, const key_type& key ) const {
                if (node == nullptr)
                    return nullptr;
                if (!__comp(node->data->first, key) && !__comp(key, node->data->first))
                    return node;
                else if (!__comp(node->data->first, key)) {
					return find(node->left, key);
				}
                else if (__comp(node->data->first, key)) {
					return find(node->right, key);
                }
                return node;
            }
            bool    contains( const key_type& key ) {
                return __contains(__root, key);
            }
            bool    contains( const key_type& key ) const {
                return __contains(__root, key);
            }

            /* ---------------------- Modifiers --------------------- */
            void clear() {
                __traverseAndDelete(this->__root);
                this->__size = 0;
                return ;
            }
            bool insert( const value_type& value ) {
                if (!__contains(this->__root, value.first)) {
                    this->__root = __insert(this->__root, value);
                    this->__root->parent = nullptr;
                    this->__size++;
                    return true;
                }
                return false;
            }
            bool    remove( const key_type& key ) {
                if (__contains(this->__root, key)) {
                    this->__root = __remove(this->__root, key);
                    if (this->__root)
                        this->__root->parent = nullptr;
                    this->__size--;
                    return true;
                }
                return false;
            }
            void    swap( AVL &x ) {
                std::swap(this->__root, x.__root);
                std::swap(this->__alloc, x.__alloc);
                std::swap(this->__rebindAlloc, x.__rebindAlloc);
                std::swap(this->__comp, x.__comp);
                std::swap(this->__size, x.__size);
            }
            /* ---------------------- Getters --------------------- */
            rebind_allocator get_allocator() const { return this->__rebindAlloc; }   
            node_type * getRoot() const { return this->__root; }
            

        private:

            void    __update( node_type * node ) {
                
                int leftNodeHeight = (node->left == nullptr) ? -1 : node->left->height;
                int rightNodeHeight = (node->right == nullptr) ? -1 : node->right->height;
                node->height = std::max(leftNodeHeight, rightNodeHeight) + 1;
                node->balanceFactor = rightNodeHeight - leftNodeHeight;   
            }
            
            void    __setParent( node_type * root, node_type * newRoot ) {
                if (root->parent != nullptr) {
                    newRoot->parent = nullptr;
                    if (root->left)
                        root->left->parent = root;
                    if (root->right)
                        root->right->parent = root;
                    root->parent = newRoot;
                    return ;
                }
                newRoot->parent = root->parent;
                root->parent = newRoot;
                if (root->left)
                    root->left->parent = root;
                if (root->right)
                    root->right->parent = root;
                return ;
            }

            /* Rotations */
            node_type * __leftRotation( node_type * node ) {
                node_type * newParent = node->right;
                node->right = newParent->left;
                newParent->left = node;
                __setParent(node, newParent);
                __update(node);
                __update(newParent);
                return newParent;
            }

            node_type * __rightRotation( node_type * node ) {
                node_type * newParent = node->left;
                node->left = newParent->right;
                newParent->right = node;
                __setParent(node, newParent);
                __update(node);
                __update(newParent);
                return newParent;
            }

            node_type * __leftLeftCase( node_type * node ) {
                return __rightRotation(node);
            }
            
            node_type * __leftRightCase( node_type * node ) {
                node->left = __leftRotation(node->left);
                return __leftLeftCase(node);
            }
            
            node_type * __rightRightCase( node_type * node ) {
                return __leftRotation(node);
            }
            
            node_type * __rightLeftCase( node_type * node ) {
                node->right = __rightRotation(node->right);
                return __rightRightCase(node);
            }

            node_type * __balance( node_type * node ) {
                if (node->balanceFactor == -2) // Left heavy subtree.
                    return node->left->balanceFactor <= 0 ? __leftLeftCase(node) : __leftRightCase(node);
                else if (node->balanceFactor == 2) // Right heavy subtree needs balancing.
                    return node->right->balanceFactor >= 0 ? __rightRightCase(node) : __rightLeftCase(node);
                return node;
            }

            bool    __contains( node_type * node, key_type& key ) {
    
                if (node == nullptr)
                    return false;
                if (!__comp(node->data->first, key) && !__comp(key, node->data->first))
                    return true;
				else if (!__comp(node->data->first, key)) {
					return __contains(node->left, key);
				}
                else if (__comp(node->data->first, key)) {
					return __contains(node->right, key);
                }
                return true;
            }
            bool    __contains( node_type * node, key_type& key ) const {
    
                if (node == nullptr)
                    return false;
                if (!__comp(node->data->first, key) && !__comp(key, node->data->first))
                    return true;
				else if (!__comp(node->data->first, key)) {
					return __contains(node->left, key);
				}
                else if (__comp(node->data->first, key)) {
					return __contains(node->right, key);
                }
                return true;
            }

            node_type * __insert( node_type * node, const value_type& value ) {
                if (node == nullptr)
                    return __initNode(value);
				if (__comp(value.first, node->data->first)) {
					node->left = __insert(node->left, value);
                    node->left->parent = node;
				}
                else if (__comp(node->data->first, value.first)) {
					node->right = __insert(node->right, value);
                    node->right->parent = node;
                }
                __update(node);
                return (__balance(node));
            }

            node_type * __remove( node_type * node, key_type& key ) {
                if (node == nullptr)
                    return nullptr;
                if (__comp(key, node->data->first))
					node->left = __remove(node->left, key);
                else if (__comp(node->data->first, key))
					node->right = __remove(node->right, key);
                else {
                    if (node->left == nullptr)
                        return node->right;
                    else if (node->right == nullptr)
                        return node->left;
                    else {
                        node_type * successorValue = findMaxValue(node->left);
                        node->data = successorValue->data;
                        node->left = __remove(node->left, successorValue->data->first);
                    }
                }
                __update(node);
                return __balance(node);
            }


        private:    
            void __print(node_type *root, int space) {
                if (root == NULL) return ;
                space += 8;
                __print(root->right, space);
                std::cout << std::endl;
                for (int i = 10; i < space; i++)
                    std::cout << " ";
                std::cout << root->data->first << std::endl;
                __print(root->left, space);
            }
        
        public:
            void    print( void ) {
                __print(this->__root, 0);
            }
            
    }

;}