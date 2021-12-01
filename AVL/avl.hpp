/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:33:38 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/01 19:26:20 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"

# include <errno.h>

namespace ft {
    

    template < class T, class Compare = std::less<T> , class Alloc = std::allocator<T> >
    class AVL {

        struct Node;

        public:
            typedef T           value_type;
            typedef Node        node_type;
            typedef Compare     key_compare;
            typedef Alloc       allocator_type;
            typedef size_t      size_type;
            typedef typename    allocator_type::template rebind<node_type>::other   rebind_allocator;

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
            explicit AVL( const allocator_type& allocator = allocator_type(), const key_compare& compare = key_compare()) :
                __root(nullptr),
                __comp(compare),
                __alloc(allocator),
                __rebindAlloc(allocator),
                __size(0) {}


            // explicit avl( const value_type& val, const allocator_type& allocator = allocator_type(), const key_compare& compare = key_compare()) :

        public:
            size_type   size( void ) const { return this->__size; }
            node_type * min( node_type * node ) {
                if (node == nullptr)
                    return node;
                while (node->left != nullptr)
                    node = node->left;
                return node;
            }
            node_type * max( node_type * node ) {
                if (node == nullptr)
                    return node;
                while (node->right != nullptr)
                    node = node->right;
                return node;
            }

            bool    contains( value_type value ) {
                return __contains(__root, value);
            }

            void    insert( value_type value ) {
                if (!__contains(this->__root, value)) {
                    this->__root = __insert(this->__root, value);
                    this->__size++;
                    return ;
                }
                return ;
            }

        private:

            void    __update( node_type * node ) {
                
                int leftNodeHeight = (node->left == nullptr) ? -1 : node->left->height;
                int rightNodeHeight = (node->right == nullptr) ? -1 : node->right->height;

                // Update this node's height
                node->height = 1 + std::max(leftNodeHeight, rightNodeHeight);

                // Update the balance factor.
                node->balanceFactor = rightNodeHeight - leftNodeHeight;   
            }
            
            /* Rotations */
            node_type * __leftRotation( node_type * node ) {
                node_type * newParent = node->right;
                node->right = newParent->left;
                newParent->left = node;
                __update(node);
                __update(newParent);
                return newParent;
            }

            node_type * __rightRotation( node_type * node ) {
                node_type * newParent = node->left;
                node->left = newParent->right;
                newParent->right = node;
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

            node_type * __insert( node_type * node, value_type value ) {
                
                // Base case.
                if (node == nullptr) return __initNode(value);

                // Compare current value to the value in the node
                int cmp = __comp(*node->data, value);
                
                // Dig into left subtree
                if (cmp < 0)
                    node->left = __insert(node->left, value);
                else
                    node->right = __insert(node->right, value);

                // Update balance factor and height values.
                __update(node);
                
                // Re-balance the tree
                return (__balance(node));
                
            }

            bool    __contains( node_type * node, value_type value ) {
                
                if (node == nullptr) return false;
                
                // Compare current value to the value in the node
                int cmp = __comp(*node->data, value);
                
                // Dig into left subtree
                if (cmp < 0) return __contains(node->left, value);
                
                // Dig into right subtree
                if (cmp > 0) return __contains(node->right, value);
                
                // Found value in tree.
                return true;
            }

        private:
            void    __inOrder( node_type * root )
            {
                if (root == nullptr)
                    return ;
                std::cout << *root->data << " ";
                __inOrder(root->left);
                __inOrder(root->right);
            }
        
        public:
            void    inOrder( void ) { __inOrder(this->__root); }
        
    }

;}