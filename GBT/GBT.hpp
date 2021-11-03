/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:19:07 by aabounak          #+#    #+#             */
/*   Updated: 2021/11/03 21:19:22 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"

# define GREEN 420
# define BLACK 42
# define BLACK_BLACK 99

namespace ft {
    struct Node {
        int     data;
        Node  * parent;
        Node  * left;
        Node  * right;
        short   color;      
    };
    
    template < class Alloc = std::allocator<int> >
    class GBT
    {

            typedef    Alloc           allocator_type;
            // typedef    T               value_type;


            /* Node    *   searchTree( T k ) {
                return searchTreeHelper(this->_root, k);
            } */
        private:
            Node    *       _root;
            Node    *       _TNULL;
            allocator_type  _alloc;
        
        // Pre-Order Traversal
        void    preOrderHelper(Node * node) {
            if (node != _TNULL) {
                std::cout << node->data << " ";
                preOrderHelper(node->left);
                preOrderHelper(node->right);
            }
        }

        public:       
            
             
            // Constructor
            GBT( void ) {
                _TNULL = new Node;
                _TNULL->color = BLACK;
                _TNULL->left = nullptr;
                _TNULL->right = nullptr;
                _root = _TNULL;
            }

            // ~GBT( void ) { _alloc.deallocate(_TNULL, 1); }
            ~GBT( void ) { delete this->_TNULL; }
            
            void    preOrder( void ) {
                preOrderHelper(this->_root);
            }

            // Insertion of a node
            void    insert( int key ) {

                Node * node = new Node;
                node->parent = nullptr;
                node->data = key;
                node->left = _TNULL;
                node->right = _TNULL;
                node->color = GREEN;

                Node * y = nullptr;
                Node * x = this->_root;

                while (x != _TNULL) {
                    y = x;
                    if (node->data < x->data)
                        x = x->left;
                    if (node->data > x->data)
                        x = x->right;
                }

                node->parent = y;
                if (y == nullptr)
                    this->_root = node;
                else if (node->data < y->data)
                    y->left = node;
                else if (node->data > y->data)
                    y->right = node;

                if (node->parent == nullptr) {
                    node->color = BLACK;
                    return ;
                }

                if (node->parent->parent == nullptr)
                    return ;
            }

            Node *  getRoot( void ) {
                return this->_root;
            }
    }; 
}
