/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:29:05 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/15 17:34:02 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "../iterator_traits/iterator_traits.hpp"
# include <stdexcept>

//! if Linux
// #define ptrdiff_t __gnu_cxx::ptrdiff_t

namespace ft {
    template < class T, class Node, class Tree >
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
                    this->__node = this->__avl->getRoot();
                    if (this->__node == nullptr)
                        return *this;
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
                        p = this->__node->parent;
                        while (p != nullptr && this->__node == p->right) {
                            this->__node = p;
                            p = p->parent;
                        }
                        this->__node = p;
                    }
                }
                return *this;
            }
            bidirectional_iterator& operator--() {
                Node * p;
                if (this->__node == nullptr) {
                    this->__node = this->__avl->getRoot();
                    if (this->__node == nullptr)
                        return *this;
                    while (this->__node->right != nullptr)
                        this->__node = this->__node->right;
                }
                else if (this->__node->left != nullptr) {
                        this->__node = this->__node->left;
                        while (this->__node->right != nullptr)
                            this->__node = this->__node->right;
                }
                else {
                    p = this->__node->parent;
                    while (p != nullptr && this->__node == p->left) {
                        this->__node = p;
                        p = p->parent;
                    }
                    this->__node = p;
                }
                return *this;
            }
            bidirectional_iterator operator++(int) { bidirectional_iterator saved(*this); ++(*this); return (saved); }
            bidirectional_iterator operator--(int) { bidirectional_iterator saved(*this); --(*this); return (saved); }

            Node * base() const { return this->__node; }

            operator bidirectional_iterator<const T, const Node, Tree> () const { return bidirectional_iterator<const T, const Node, Tree>(__node, __avl) ; }

        protected:
            Node *  __node;
            Tree const *  __avl;            
    };
    
            /* ----------- Non-member function overloads ----------- */
    template < class T, class Node, class Tree>
        bool operator== (const bidirectional_iterator<T, Node, Tree>& lhs, const bidirectional_iterator<T, Node, Tree>& rhs) { return lhs.base() == rhs.base(); }
    template < class T, class Node, class Tree>
        bool operator!= (const bidirectional_iterator<T, Node, Tree>& lhs, const bidirectional_iterator<T, Node, Tree>& rhs) { return !operator==(lhs, rhs); }
}