/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:33:38 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/01 16:59:40 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"
# include <errno.h>

namespace ft {

    template < class T, class Alloc = std::allocator<T> >
    struct Node {
        typedef T       value_type;
        typedef Alloc   allocator_type;

        allocator_type  alloc;
        value_type *    data;
        Node *          parent;
        Node *          left;
        Node *          right;

        private:
            value_type * __initNode( const value_type& val ) {
                value_type * node = alloc.allocate(1);
                alloc.construct(node, val);
                return node;
            }
        
        explicit Node( const allocator_type& allocator = allocator_type() ) :
            alloc(allocator),
            data(0),
            parent(nullptr),
            left(nullptr),
            right(nullptr) {}
            
        explicit Node( const value_type& val, const allocator_type& allocator = allocator_type() ) :
            alloc(allocator),
            data(__initNode(val)),
            parent(nullptr),
            left(nullptr),
            right(nullptr) {}
    };

    template < class T, class Compare = std::less<T> , class Alloc = std::allocator<T> >
    class AVL {
        public:
            typedef T           value_type;
            typedef Compare     key_compare;
            typedef Alloc       allocator_type;
            typedef size_t      size_type;
            typedef typename    allocator_type::template rebind<node_type>::other   rebind_allocator;

        private:
            node_type   *       __root;
            key_compare         __comp;
            rebind_allocator    __alloc;
            size_type           __size;

        public:
            explicit avl( const allocator_type& allocator = allocator_type(), const key_compare& compare = key_compare()) :
                __root(nullptr),
                __comp(compare),
                __alloc(allocator),
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

            bool    insert( value_type value ) {
                if (value == nullptr)
                    return false;
                if (!__contains(this->__root, value)) {
                    this->__root = __insert(this->__root, value);
                    this->__size++;
                    return true;
                }
                return false;
            }

        private:
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
    }

;}