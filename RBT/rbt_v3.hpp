/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_v3.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 07:56:52 by aabounak          #+#    #+#             */
/*   Updated: 2021/11/29 15:02:39 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"
# include <errno.h>

namespace ft {
    
    enum Color {
        RED = 1,
        BLACK = 0,
        DOUBLE_BLACK = 2,
    };

    template < class Pair, class Alloc = std::allocator<Pair> >
    struct Node {
        typedef Pair    value_type;
        typedef Alloc   allocator_type;

        allocator_type  alloc;
        value_type *    data;
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
        
        bool    isOnLeft( void ) {
            if (this->parent && this->parent->left)
                return this == this->parent->left;
            return false;
        }

        /* Node *  getGrandParent( void ) {
            if (this->parent && this->parent->parent)
                return this->parent->parent;
            return nullptr;
        }   */ 
 
    };


    template < class Pair, class Compare = std::less<Pair> , class Alloc = std::allocator<Pair> >
    class rbt_v3 {
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
				if (*__root->data == __val )
					return (__root);
				else if (*__root->data < __val)
					return (__search(__root->right, __val));
				else if (*__root->data > __val)
					return (__search(__root->left, __val));
				return (nullptr);
            }

        public:
        
                    /* ----------- Member Functions ---------- */    
                /* ---- Constructors & Destructor respectively ---- */
            /* ------------------------ Default ------------------------ */
            explicit rbt_v3( const allocator_type& allocator = allocator_type(), const key_compare& compare = key_compare()) :
                _root(nullptr),
                _comp(compare),
                _alloc(allocator),
                _size(0) {}

            /* ------------------------ Fill ------------------------ */
            explicit rbt_v3( const value_type& pair, const allocator_type& allocator = allocator_type(), const key_compare& compare = key_compare()) :
                _root(__initNode(pair)),
                _comp(compare),
                _alloc(allocator),
                _size(1) {}

            /* ---------------------- Detructor --------------------- */
            /* ~rbt_v3( void ) {} */

        public:
            /* --------------------- HHHHHHHHHH --------------------- */
            size_type   size( void ) const { return this->_size; }
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
            void    print() { if (this->_root) this->printHelper(this->_root, nullptr, false); }

            /* -------------------- Modifiers --------------------- */

        private:
            /* -- Left Rotation:
                The arrangement of the nodes on the right is transformed into the arrangements on the left node
                -- Algorithm:
                    1 - If Y has a left subtree, assign X as the parent of the left substree of Y.
                    2 - If the parent of X is NULL, make Y as the root of the tree. 
                    3 - Else if X is the left child of its parent P, make Y as the left child of P. 
                    4 - Else assign Y as the right child of P. 
                    5 - Make Y as the parent of X. */
            
            node_type * __rotateLeft( node_type *& node ) {
                node_type * x = node->right;
                node_type * y = x->left;
                x->left = node;
                node->right = y;
                node->parent = x;
                if (y != nullptr)
                    y->parent = node;
                return (x);
            }
        

            /* -- Right Rotation:
                The arrangement of the nodes on the left is transformed into the arrangements on the right node
                -- Algorithm:
                    1 - If X has a right subtree, assign Y as the parent of the right subtree of X. 
                    2 - If the parent of Y is NULL, make  as the root of the tree. 
                    3 - Else if Y is the right child of its parent P, make X as the right child of P. 
                    4 - Else assign X as the left cchild of P. 
                    5 - Make X as the parent of Y. */
            
            node_type * __rotateRight(node_type *& node)
            {
                node_type * x = node->left;
                node_type * y = x->right;
                x->right = node;
                node->left = y;
                node->parent = x;
                if (y != nullptr)
                    y->parent = node;
                return (x);
            }
            /* -- Insertion Violation Fix:
                This function is used for maintaining the property of a RBT \ 
                if the insertion of a newNode violates this property. 
                -- Alorithm:
                    1 - If <X> is ROOT, change color of <X> as BLACK.
                    2 - Do the followng if <X's PARENT> is not BLACK or <X> ain't->
                        I - If <X's AUNT> is RED (GP must have been black from the property of RBT.)
                            i - Change color of <PARENT> and <AUNT> as BLACK.
                            ii - Color <GRAND PARENT> as RED.
                            iii - Change <X = X's GRAND PARENT>, then repeat steps 2 and 3 for new <X>.
                        II - If <X's AUNT> is BLACK, then there can be four configurations for \
                        <X> <X's PARENT> and <X's GRAND PARENT>.
                            i - Determine the configuration:
                                -- Left Left (<PARENT> is LEFT CHILD of <GRAND PARENT> and <X> is LEFT CHILD of <PARENT>)
                                -- Left Right (<PARENT> is LEFT CHILD of <GRAND PARENT> and <X> is RIGHT CHILD of <PARENT>)
                                -- Right Right (<PARENT> is RIGHT CHILD of <GRAND PARENT> and <X> is RIGHT CHILD of <PARENT>)
                                -- Right Left (<PARENT> is RIGHT CHILD of <GRAND PARENT> and <X> is LEFT CHILD of <PARENT>)
                            ii - Change <X = X's PARENT>, repeat steps 2 and 3 for new <X>.
                            
                                        ROB-EDWARDS:
                            - If the imbalance is on the right child right subtree we do a left rotation.
                            - If the imbalance is on the right child left subtree we do a right left rotation.
                            - If the imbalance is on the left child right subtree we do a left right rotation.
                            - If the imbalance is on the left child left subtree we do a right rotation. */
            /* void __fixInsertionViolation(node_type * x) {
                return ;
            } */

        public:
            void    insert( const value_type& val ) {
                node_type * x = __initNode(val);
                if (this->_root == nullptr) {
                    this->_root = x;
                    this->_root->color = BLACK;
                } else
                    this->_root = this->__insert(this->_root, x);
            }

        private:

            bool LL = false;
            bool RR = false;
            bool LR = false;
            bool RL = false;
            
            node_type * __insert( node_type *& root, node_type *& nodeToInsert )
            {
                // F is true when RED RED conflict is there.
                bool F = false;
                
                // recursive calls to insert at proper position according to BST properties.
                if (root == nullptr)
                    return nodeToInsert;
                if (!_comp(*root->data, *nodeToInsert->data) && !_comp(*nodeToInsert->data, *root->data))
                    return root;
				else if (!_comp(*root->data, *nodeToInsert->data)) {
					root->left = __insert(root->left, nodeToInsert);
					root->left->parent = root;
                    if (root != this->_root)
                    {
                        if (root->color == RED && root->left->color == RED)
                            F = true;
                    }
				}
                else if (_comp(*root->data, *nodeToInsert->data)) {
					root->right = __insert(root->right, nodeToInsert);
					root->right->parent = root;
                    if (root != this->_root)
                    {
                        if (root->color == RED && root->right->color==RED)
                            F = true;
                    }
				}
                // at the same time of insertion, we are also assigning parent nodes
                // also we are checking for RED RED conflicts
        
                // now lets rotate.
                if (this->LL) { // for left rotate.
                    root = __rotateLeft(root);
                    root->color = BLACK;
                    root->left->color = RED;
                    this->LL = false;
                } else if (this->RR) { // for right rotate
                    root = __rotateRight(root);
                    root->color = BLACK;
                    root->right->color = RED;
                    this->RR = false;
                } else if (this->RL) { // for right and then left
                    root->right = __rotateRight(root->right);
                    root->right->parent = root;
                    root = __rotateLeft(root);
                    root->color = BLACK;
                    root->left->color = RED;
                    this->RL = false;
                } else if (this->LR) { // for left and then right
                    root->left = __rotateLeft(root->left);
                    root->left->parent = root;
                    root = __rotateRight(root);
                    root->color = BLACK;
                    root->right->color = RED;
                    this->LR = false;
                }
                // When rotation and recoloring is done flags are reset.
                // Now let's take care of RED RED conflict
                if (F) {
                    if (root->parent->right == root) { // to check which child is the current node of its parent
                        if (root->parent->left == nullptr || root->parent->left->color == BLACK) { // case when parent's sibling is black
                        // perform certaing rotation and recolouring. This will be done while backtracking. Hence setting up respective flags.
                            if (root->left != nullptr && root->left->color == RED)
                                this->RL = true;
                            else if (root->right != nullptr && root->right->color == RED)
                                this->LL = true;
                        }
                        else { // case when parent's sibling is red
                            root->parent->left->color = BLACK;
                            root->color = BLACK;
                            if (root->parent != this->_root)
                                root->parent->color = RED;
                        }
                    }
                    else {
                        if (root->parent->right == nullptr || root->parent->right->color == BLACK)
                        {
                            if (root->left != nullptr && root->left->color == RED)
                                this->RR = true;
                            else if (root->right != nullptr && root->right->color == RED)
                                this->LR = true;
                        }
                        else {
                            root->parent->right->color = BLACK;
                            root->color = BLACK;
                            if (root->parent != this->_root)
                                root->parent->color = RED;
                        }
                    }
                    F = false;
                }
                return (root); 
            }
        
        private:
                    /* ---------- | Recursive print of a "RBT" | ---------- */
            struct Trunk {
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
            }
    };
}