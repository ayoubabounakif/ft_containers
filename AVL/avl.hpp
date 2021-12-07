/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:33:38 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/07 18:06:27 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"
# include "../iterator/iterator_traits/iterator_traits.hpp"
# include "../iterator/iterator/iterator.hpp"
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
            typedef Node        node_type;
            typedef Compare     key_compare;
            typedef Alloc       allocator_type;
            typedef size_t      size_type;
            typedef typename    allocator_type::template rebind<node_type>::other   rebind_allocator;
            typedef             bidirectional_iterator<value_type, node_type, AVL>             iterator;
            typedef             bidirectional_iterator<const value_type, const node_type, AVL> const_iterator;

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
                if (x == nullptr)
                    return ;
                __traverseAndDelete(x->left);
                __traverseAndDelete(x->right);
                // this->__alloc.destroy(x->data);
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
            iterator  begin() { return iterator(findMinValue(this->__root), this); }
            const_iterator  begin() const { return iterator(findMinValue(this->__root), this); }
            iterator  end() { return iterator(nullptr, this); }
            const_iterator  end() const { return iterator(nullptr, this); }

        public:
            /* ----------------------- Capacity --------------------- */
            size_type   size( void ) const { return this->__size; }
            size_type   max_size( void ) const { return this->__alloc.max_size(); }
            bool        empty() const { return this->_size == 0 ? true : false; }
            
            node_type * findMinValue( node_type * node ) {
                while (node->left != nullptr)
                    node = node->left;
                return node;
            }
            node_type * findMaxValue( node_type * node ) {
                while (node->right != nullptr)
                    node = node->right;
                return node;
            }
            node_type * find(node_type * node, value_type& value ) {
                if (node == nullptr)
                    return nullptr;
                if (!__comp(node->data->__first, value.__first) && !__comp(value.__first, node->data->__first))
                    return node;
                else if (!__comp(node->data->__first, value.__first)) {
					return find(node->left, value);
				}
                else if (__comp(node->data->__first, value.__first)) {
					return find(node->right, value);
                }
                return node;
            }
            bool    contains( value_type value ) {
                return __contains(__root, value);
            }

            void    insert( value_type value ) {
                if (!__contains(this->__root, value)) {
                    this->__root = __insert(this->__root, value);
                    this->__root->parent = nullptr;
                    this->__size++;
                    return ;
                }
                return ;
            }

            void    remove( value_type value ) {
                if (__contains(this->__root, value)) {
                    this->__root = __remove(this->__root, value);
                    this->__root->parent = nullptr;
                    this->__size--;
                    return ;
                }
                return ;
            }

            rebind_allocator    get_allocator() const { return this->__rebindAlloc; }   
            node_type * getRoot() const { return this->__root; }
            

        private:

            void    __update( node_type * node ) {
                
                int leftNodeHeight = (node->left == nullptr) ? -1 : node->left->height;
                int rightNodeHeight = (node->right == nullptr) ? -1 : node->right->height;

                // Update this node's height
                node->height = std::max(leftNodeHeight, rightNodeHeight) + 1;

                // Update the balance factor.
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

            // Re-balance a node if its balance factor is +2 or -2
            node_type * __balance( node_type * node ) {
                
                // Left heavy subtree.
                if (node->balanceFactor == -2) {
                    
                    // Left-Left case
                    if (node->left->balanceFactor <= 0)
                        return __leftLeftCase(node);

                    // Left-Right case
                    else {
                        return __leftRightCase(node);
                    }
                }

                // Right heavy subtree needs balancing.
                else if (node->balanceFactor == 2) {
                    
                    // Right-Right case
                    if (node->right->balanceFactor >= 0)
                        return __rightRightCase(node);

                    // Right-Left case
                    else
                        return __rightLeftCase(node);
                }

                // Node either has a balance factor of 0, +1 or -1 which is fine.
                return node;
            }

            bool    __contains( node_type * node, value_type value ) {
    
                if (node == nullptr)
                    return false;
                if (!__comp(node->data->__first, value.__first) && !__comp(value.__first, node->data->__first))
                    return true;
				else if (!__comp(node->data->__first, value.__first)) {
					return __contains(node->left, value);
				}
                else if (__comp(node->data->__first, value.__first)) {
					return __contains(node->right, value);
                }
                return true;
            }

            node_type * __insert( node_type * node, value_type& value ) {
                
                if (node == nullptr)
                    return __initNode(value);

                /* Dig into left subtree, the value we're looking
                    for is smaller than teh current value. */
				if (__comp(value.__first, node->data->__first)) {
					node->left = __insert(node->left, value);
                    node->left->parent = node;
				}

               /* Dig into right subtree, the value we're looking
                    for is greater than the current value. */
                else if (__comp(node->data->__first, value.__first)) {
					node->right = __insert(node->right, value);
                    node->right->parent = node;
                }

                // Update balance factor and height values.
                __update(node);
                
                // Re-balance the tree
                return (__balance(node));
                
            }

            node_type * __remove( node_type * node, value_type& value ) {


                if (node == nullptr)
                    return nullptr;
                
                /* Dig into left subtree, the value we're looking
                    for is smaller than the current value. */
                if (__comp(value.__first, node->data->__first)) {
					node->left = __remove(node->left, value);
				}

                /* Dig into right subtree, the value we're looking
                    for is greater than the current value. */
                else if (__comp(node->data->__first, value.__first)) {
					node->right = __remove(node->right, value);
                }

                /* Found the node we wish to remove */
                else {
                    
                    
                    /* This is the case with only a right subtree or no subtree at all.
                        In this situation just swap the node we wish to remove with it's right child. */
                    if (node->left == nullptr)
                        return node->right;

                    /* This is the case with only a left subtree or no subtree at all.
                        In this situation just swap the node we wish to remove with it's left child. */
                    else if (node->right == nullptr)
                        return node->left;

                    /* When removing a node from a binary tree with two links the
                        successor of the node being removed can either be the largest value
                        in the left subtree or the smallest value in the right subtree.
                        As a heuristic, I will remove from the subtree with the most nodes
                        in hopes that this may help with balancing. */
                    else {
                        
                        /* Choose to remove from the left subtree */
                        if (node->left->height > node->right->height) {

                            /* Swap the value of the successor into the node. */
                            node_type * successorValue = findMaxValue(node->left);
                            node->data = successorValue;

                            /* Find the largest node in the left subtree */
                            node->left = __remove(node->left, successorValue);
                            
                        }
                        else {
                            
                            /* Swap the value of the successor into the node. */
                            node_type * successorValue = findMinValue(node->right);
                            node->data = successorValue;

                            /* Go into the right subtree and remove the leftmost node we ound
                                and swapped data with. This prevents us from having two nodes
                                in our tree with the same value. */
                            node->right = __remove(node->right, successorValue);
                        }
                    }   
                }
                
                // Update balance factor and height values.
                __update(node);

                // Re-balance the tree
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
                std::cout << root->data->__first << std::endl;
                __print(root->left, space);
            }
        
        public:
            void    print( void ) {
                __print(this->__root, 0);
            }
            
    }

;}