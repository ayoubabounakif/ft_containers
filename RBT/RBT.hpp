/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:19:07 by aabounak          #+#    #+#             */
/*   Updated: 2021/11/05 18:42:24 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"

# define RED 1
# define BLACK 0
# define BLACKED_BLACK 007

namespace ft {
    
    template < class T, class Compare = std::less<T> , class Alloc = std::allocator<T> >
    class RBT
    {
        public:
        
            typedef             T                  value_type;
            typedef             Compare            key_compare;
            typedef             Alloc              allocator_type;
            
            struct Node {
                value_type  * data;
                Node        * parent;
                Node        * left;
                Node        * right;
                short         color;      
            };            
          
            typedef typename    Alloc::template rebind<Node>::other   rebind_allocator;
             
            // Constructor
            RBT( void ) {
                this->_root = NULL;
            }

            /* void    preOrder( Node * root ) {
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
            } */

            Node *  getRoot( void ) {
                return this->_root;
            }

            void    insert( value_type key ) {
                Node * tmpNode = newNode(key);
                this->_root = this->BST_insert(this->_root, tmpNode);
                return ;
            }

            void printTree() {
                if (_root) {
                    printHelper(this->_root, nullptr, false);
                }
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
                nouveauNode->parent = nouveauNode->left = nouveauNode->right = NULL;
                nouveauNode->color = RED;
                return nouveauNode;
            }

            // Insertion of a node
            Node * BST_insert( Node *root,  Node *newNode ) {
                if (root == NULL) { return newNode; }
                if (*root->data < *newNode->data) { root->right = BST_insert(root->right, newNode); }
                else if (*root->data > *newNode->data) { root->left = BST_insert(root->left, newNode); }
                return root;
            }
            

                    /* ---------- | Recursive print of a "RBT" | ---------- */

            struct Trunk {
                Trunk *prev;
                std::string str;
                Trunk(Trunk *prev, std::string str) { this->prev = prev; this->str = str; }
            };

            // Helper function to print branches of the binary tree
            void showTrunks(Trunk *p) {
                if (p == nullptr) { return ; }
                showTrunks(p->prev);
                std::cout << p->str;
            }
            
            void printHelper(Node* root, Trunk *prev, bool isLeft) {
                if (root == nullptr) { return; }
                std::string prev_str = "    ";
                Trunk *trunk = new Trunk(prev, prev_str);
                printHelper(root->right, trunk, true);
                if (!prev) { trunk->str = "——— "; }
                else if (isLeft) { trunk->str = " .——— "; prev_str = "   |"; }
                else { trunk->str = " `——— "; prev->str = prev_str; }
                showTrunks(trunk);
                std::string sColor = root->color ? "R" : "B";
                std::cout << *root->data << "(" << sColor <<  ")" << std::endl;
                if (prev) { prev->str = prev_str; }
                trunk->str = "   |";
                printHelper(root->left, trunk, false);
            }
    }; 
}
