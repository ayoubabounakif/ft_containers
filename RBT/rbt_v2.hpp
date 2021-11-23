/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_v2.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 07:56:52 by aabounak          #+#    #+#             */
/*   Updated: 2021/11/23 10:35:01 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"
# include <errno.h>

namespace ft {
    
    enum Color {
        RED = 0,
        BLACK = 1,
        DOUBLE_BLACK = 2,
    };

    template < class Pair, class Alloc = std::allocator<Pair> >
    struct Node {
        typedef Pair    value_type;
        typedef Alloc   allocator_type;

        allocator_type  alloc;
        value_type *     data;
        Node *          parent;
        Node *          left;
        Node *          right;
        Color           color;

        value_type * initPair( const value_type& val ) {
            value_type * pair = alloc.allocate(1);
            alloc.construct(pair, val);
            return pair;
        }

        explicit Node( const allocator_type& allocator = allocator_type() ) :
            alloc(allocator),
            data(0),
            parent(nullptr),
            left(nullptr),
            right(nullptr),
            color(RED) {}
            

        explicit Node( const value_type& val, const allocator_type& allocator = allocator_type() ) :
            alloc(allocator),
            data(initPair(val)),
            parent(nullptr),
            left(nullptr),
            right(nullptr),
            color(RED) {}
        
        ~Node() {
            /* if (this->data) {
                alloc.destroy(data);
                alloc.dellocate(data, 1);
            } */
        }
        
/*         bool    isOnLeft( void ) {
            if (this->parent && this->parent->left)
                return this == this->parent->left;
            return false;
        }

        Node *  getGrandParent( void ) {
            if (this->parent && this->parent->parent)
                return this->parent->parent;
            return nullptr;
        }   */ 
 
    };


    template < class Pair, class Compare = std::less<Pair> , class Alloc = std::allocator<Pair> >
    class rbt_v2 {
        public:
            typedef Pair                    value_type;
            typedef Compare                 key_compare;
            typedef Alloc                   allocator_type;
            typedef Node<value_type, Alloc> node_type;
            typedef size_t                  size_type;
            typedef typename                allocator_type::template rebind<node_type>::other   rebind_allocator;
            
            
        private:
            node_type *         _root;
            key_compare         _comp;
            rebind_allocator    _alloc;
            size_type           _size;

            node_type * __initNode( const value_type& __pair ) {
                node_type * node = _alloc.allocate(1);
                _alloc.construct(node, __pair);
                return node;
            }

            node_type * __search( node_type * __root, value_type __val) {
                if (__root == nullptr)
					return (nullptr);
				if (*(__root->data) == __val )
					return (__root);
				else if (*(__root->data) < __val)
					return (__search(__root->right, __val));
				else if (*(__root->data) > __val)
					return (__search(__root->left, __val));
				return (nullptr);
            }

        public:
        
                    /* ----------- Member Functions ---------- */    
                /* ---- Constructors & Destructor respectively ---- */
            /* ------------------------ Default ------------------------ */
            explicit rbt_v2( const allocator_type& allocator = allocator_type(), const key_compare& compare = key_compare()) :
                _root(nullptr),
                _comp(compare),
                _alloc(allocator),
                _size(0) {}

            /* ------------------------ Fill ------------------------ */
            explicit rbt_v2( const value_type& pair, const allocator_type& allocator = allocator_type(), const key_compare& compare = key_compare()) :
                _root(__initNode(pair)),
                _comp(compare),
                _alloc(allocator),
                _size(1) {}

            /* ---------------------- Detructor --------------------- */
            /* ~rbt_v2( void ) {} */

            /* --------------------- Operations --------------------- */
            size_type   size( void ) const { return this->_size; }
            node_type * min( node_type * node ) {
                if (this->_root == nullptr)
                    return node;
                while (node->left != nullptr)
                    node = node->left;
                return node;
            }
            node_type * max( node_type * node ) {
                if (this->_root == nullptr)
                    return node;
                while (node->right != nullptr)
                    node = node->right;
                return node;
            }
            // void    print() { if (this->_root) this->printHelper(this->_root, nullptr, false); }

            /* -------------------- Modifiers --------------------- */
            void    insert( const value_type& val ) {
				node_type * x = __initNode(val);
                this->_root = this->__insert(this->_root, x);
                this->_size++;
                if (x->parent == nullptr)
                {
                    x->color = BLACK;
                    return ;
                }
                if (x->parent->parent == nullptr)
                    return ;
            }

        private:
            node_type * __insert( node_type *& __root, node_type *& __nodeToInsert ) {
                if (__root == nullptr)
                    return __nodeToInsert;
				if ( __root->data > __nodeToInsert->data) {
					__root->left = __insert(__root->left, __nodeToInsert);
					__root->left->parent = __root;
				} else if (__root->data < __nodeToInsert->data) {
					__root->right = __insert(__root->right, __nodeToInsert);
					__nodeToInsert->right->parent = __root;
				}
				return (__root);
            }








        
        private:
                    /* ---------- | Recursive print of a "RBT" | ---------- */
/*             struct Trunk {
                Trunk *prev;
                std::string str;
                Trunk( Trunk *prev, std::string str ) { this->prev = prev; this->str = str; }
            };
            void showTrunks(Trunk *p) {
                if (p == nullptr) { return ; }
                showTrunks(p->prev);
                std::cout << p->str;
            }
            void printHelper( Node<Pair>* root, Trunk *prev, bool isLeft ) {
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
            } */
    };
}