/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:19:07 by aabounak          #+#    #+#             */
/*   Updated: 2021/11/03 18:04:07 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"

# define GREEN 420
# define BLACK 42
# define BLACK_BLACK 99

namespace ft {
    class GBT
    { 
        public:
            // Constructor
            GBT() { _root = NULL; }
            ~GBT();

            struct Node {
                // Constructor
                Node(int x) {
                    this->data = x;
                    this->parent = this->left = this->right = NULL;
                    this->color = GREEN;
                }
                int     data;
                Node  * parent;
                Node  * left;
                Node  * right;
                short   color;      
            };

            /* A utility function to insert a new node with given key */
            Node * insert(Node * pt) {
                /* If the tree is empty, return a new node */
                if (this->_root == NULL)
                    return pt;
                /* Otherwise, recur down the tree */
                if (pt->data < this->_root->data) {
                    this->_root->left = this->insert(pt);
                    this->_root->left->parent = this->_root;
                }
                if (pt->data > this->_root->data) {
                    this->_root->right = this->insert(pt);
                    this->_root->right->parent = this->_root;
                }
                return this->_root;
            }

            void    inOrderTraversal(Node *node) {
                (void)node;
                if (_root == NULL)
                    return ;
                inOrderTraversal(_root->left);
                std::cout << _root->data << " ";
                inOrderTraversal(_root->right);
            }
            
        private:
            Node *  _root;
    }; 
}
