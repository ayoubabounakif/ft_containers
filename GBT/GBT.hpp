/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:19:07 by aabounak          #+#    #+#             */
/*   Updated: 2021/11/05 16:02:40 by aabounak         ###   ########.fr       */
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
    
    template < class T, class Compare = std::less<T> , class Alloc = std::allocator<T> >
    class GBT
    {
        public:
        
            typedef             T                                       value_type;
            typedef             Compare                                 key_compare;
            typedef             Alloc                                   allocator_type;
            
            struct Node {
                value_type  * data;
                Node        * parent;
                Node        * left;
                Node        * right;
                short         color;      
            };            
          
            typedef typename    Alloc::template rebind<Node>::other   rebind_allocator;
            
             
            // Constructor
            GBT( void ) {
                this->_root = NULL;
            }

            void    preOrder( Node * root ) {
                if (root == NULL) { return ; }
                std::cout << *root->data << " ";
                preOrder(root->left);
                preOrder(root->right);
            }

            void    inOrder( Node * root ) {
                if (root == NULL) { return ; }
                inOrder(root->left);
                std::cout << *root->data << " ";
                inOrder(root->right);
            }

            void    postOrder( Node * root ) {
                if (root == NULL) { return ; }
                postOrder(root->left);
                postOrder(root->right);
                std::cout << *root->data << " ";
            }

            Node *  getRoot( void ) {
                return this->_root;
            }

            void    insert( value_type key ) {
                Node * tmpNode = newNode(key);
                this->_root = this->BST_insert(this->_root, tmpNode);
                return ;
            }

        private:
            Node    *           _root;
            key_compare         _comp;
            allocator_type      _alloc;
            rebind_allocator    _nodeAlloc;

            Node *  newNode( value_type key ) {
                Node  * nouveauNode;
                nouveauNode = _nodeAlloc.allocate(1);
                nouveauNode->data = _alloc.allocate(1);
                *(nouveauNode->data) = key;
                nouveauNode->parent = NULL;
                nouveauNode->left = NULL;
                nouveauNode->right = NULL;
                nouveauNode->color = GREEN;
                return nouveauNode;
            }

            // Insertion of a node
            Node * BST_insert( Node *root,  Node *newNode ) {
                if (root == NULL) { return newNode; }
                if (*root->data < *newNode->data) { root->right = BST_insert(root->right, newNode); }
                else if (*root->data > *newNode->data) { root->left = BST_insert(root->left, newNode); }
                return root;
            }

            
    }; 
}
