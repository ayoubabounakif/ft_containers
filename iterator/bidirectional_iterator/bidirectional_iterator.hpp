/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:29:05 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/06 23:06:33 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "../iterator_traits/iterator_traits.hpp"
# include <stdexcept>

//! if Linux
// #define ptrdiff_t __gnu_cxx::ptrdiff_t

namespace ft {
    template < class T, class Node, class Tree>
    class bidirectional_iterator {
        public:
                            /* ------------ Member Types ----------- */
            typedef iterator_traits< iterator<std::bidirectional_iterator_tag, T> > iterator_traits;
            typedef typename iterator_traits::value_type        value_type;
            typedef typename iterator_traits::difference_type   difference_type;
            typedef typename iterator_traits::pointer           pointer;
            typedef typename iterator_traits::reference         reference;
            typedef typename iterator_traits::iterator_category iterator_category;

                    /* ----------- Member Functions ---------- */    
                /* ---- Constructors & Destructor respectively ---- */
            bidirectional_iterator() : __node(), __avl() {};
            bidirectional_iterator( Node * node, const Tree *avl ) : __node(node), __avl(avl) {};
            bidirectional_iterator( const bidirectional_iterator& rhs ) { *this = rhs; }
            bidirectional_iterator& operator= ( const bidirectional_iterator& rhs ) {
                this->__node = rhs.__node; this->__avl = rhs.__avl;
                return *this; }
            virtual ~bidirectional_iterator() {};

                /* Misc Operators */    
            reference operator*() const { return *this->__node->data; }
            pointer   operator->() const { return this->__node->data; }

                /* Arithmetic Operators */
            bidirectional_iterator& operator++() {
                Node * p;
                if (this->__node == nullptr) {
                    // ++ from end(). get the root of the tree
                    this->__node = this->__avl->getRoot();

                    // error! ++ requested for an empty tree
                    if (this->__node == nullptr)
                        return *this;

                    // move to the smallest value in the tree,
                    // which is the first node inorder
                    while (this->__node->left != nullptr)
                        this->__node = this->__node->left;
                }
                else {
                    if (this->__node->right != nullptr) {
                        this->__node = this->__node->right;
                        while (this->__node->left != nullptr)
                            this->__node = this->__node->left;
                    }
                    else {
                        // have already processed the left subtree, and
                        // there is no right subtree. move up the tree,
                        // looking for a parent for which nodePtr is a left child,
                        // stopping if the parent becomes NULL. a non-NULL parent
                        // is the successor. if parent is NULL, the original node
                        // was the last node inorder, and its successor
                        // is the end of the list
                        p = this->__node->parent;
                        while (p != nullptr && this->__node == p->right) {
                            this->__node = p;
                            p = p->parent;
                        }
                        // if we were previously at the right-most node in
                        // the tree, this->__node = nullptr, and the iterator specifies
                        // the end of the list
                        this->__node = p;
                    }
                }
                return *this;
            }
            
            bidirectional_iterator operator++(int) { bidirectional_iterator saved(*this); ++(*this); return (saved); }

            bidirectional_iterator& operator--() {
                Node * p;
                if (this->__node == nullptr) {
                    // -- from end(). get the root of the tree
                    this->__node = this->__avl->getRoot();

                    // error! -- requested for an empty tree
                    if (this->__node == nullptr)
                        return *this;

                    // move to the largest value in the tree,
                    // which is the last node inorder
                    while (this->__node->right != nullptr)
                        this->__node = this->__node->right;
                }
                else if (this->__node->left != nullptr) {
                        // must have gotten here by processing all the nodes
                        // on the left branch. predecessor is the farthest
                        // right node of the left subtree
                        this->__node = this->__node->left;
                        while (this->__node->right != nullptr)
                            this->__node = this->__node->right;
                }
                else {
                    // must have gotten here by going right and then
                    // far left. move up the tree, looking for a parent
                    // for which nodePtr is a right child, stopping if the
                    // parent becomes NULL. a non-NULL parent is the
                    // predecessor. if parent is NULL, the original node
                    // was the first node inorder, and its predecessor
                    // is the end of the list
                    p = this->__node->parent;
                    while (p != nullptr && this->__node == p->left) {
                        this->__node = p;
                        p = p->parent;
                    }
                    // if we were previously at the left-most node in
                    // the tree, nodePtr = NULL, and the iterator specifies
                    // the end of the list
                    this->__node = p;
                }
                return *this;
            }

            bidirectional_iterator operator--(int) { bidirectional_iterator saved(*this); --(*this); return (saved); }

            Node * base() const { return this->__node; }

        protected:
            Node *  __node;
            Tree const *  __avl;            
    };
    
    template < class T, class Node, class Tree>
        bool operator== (const bidirectional_iterator<T, Node, Tree>& lhs, const bidirectional_iterator<T, Node, Tree>& rhs) { return lhs.base() == rhs.base(); }
    template < class T, class Node, class Tree>
        bool operator!= (const bidirectional_iterator<T, Node, Tree>& lhs, const bidirectional_iterator<T, Node, Tree>& rhs) { return !operator==(lhs, rhs); }
}