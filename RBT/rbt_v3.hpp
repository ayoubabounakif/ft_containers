/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_v3.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 07:56:52 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/11 17:31:16 by aabounak         ###   ########.fr       */
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


    template < class Pair, class Compare = std::less<Pair> , class Alloc = std::allocator<Pair> >
    class rbt_v3 {
        
        private:
            struct Node {

                Pair *          data;
                Node *          parent;
                Node *          left;
                Node *          right;
                Color           color;
            
                Node *  aunt() {
                    // If no parent or grandparent, then no aunt
                    if (this->parent == nullptr || this->parent->parent == nullptr)
                        return nullptr;
                    if (parent->isOnLeft())
                        return parent->parent->right;
                    else
                        return parent->parent->left;
                }
                
                Node *  sibling() {
                    if (this->parent == nullptr)
                        return nullptr;
                    if (isOnLeft())
                        return this->parent->right;
                    else
                        return this->parent->left;
                }

                bool    isOnLeft( void ) {
                    if (this->parent && this->parent->left)
                        return this == this->parent->left;
                    return false;
                }

                bool    hasRedChild() {
                    return (this->left != nullptr && this->left->color == RED) or
                        (this->right != nullptr && this->right->color == RED);
                }

            };
        
        public:
            typedef Pair                    value_type;
            typedef Compare                 key_compare;
            typedef Alloc                   allocator_type;
            typedef Node                    node_type;
            typedef size_t                  size_type;
            typedef typename                allocator_type::template rebind<node_type>::other   rebind_allocator;
            
            
        private:
            node_type *         _root;
            key_compare         _comp;
            allocator_type      _alloc;
            rebind_allocator    _rebindAlloc;
            size_type           _size;

            node_type * __initNode( const value_type& __pair ) {
                node_type * node = _rebindAlloc.allocate(1);
                node->data = _alloc.allocate(1);
                _alloc.construct(node->data, __pair);
                node->parent = nullptr;
                node->left = nullptr;
                node->right = nullptr;
                node->color = RED;
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
                _rebindAlloc(allocator),
                _size(0) {}

            /* ------------------------ Fill ------------------------ */
            explicit rbt_v3( const value_type& pair, const allocator_type& allocator = allocator_type(), const key_compare& compare = key_compare()) :
                _root(__initNode(pair)),
                _comp(compare),
                _alloc(allocator),
                _rebindAlloc(allocator),
                _size(0) {}

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
            node_type * __rotateRight( node_type *& node )
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

        public:
            void    insert( const value_type& val ) {
                node_type * x = __initNode(val);
                this->_root = this->__insert(this->_root, x);
            }

            void    deleteValue( const value_type& val ) {
                if (this->_root == nullptr)
                    return ;
                node_type *v = __search(val);
                if (*v->data != val) {
                    std::cout << "No node found to delete with value:" << val << std::endl;
                    return ;
                }
                __deleteNode(v);
            }


        private:

            bool LL = false;
            bool RR = false;
            bool LR = false;
            bool RL = false;
            
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
            void    __swapColors( node_type *& x1, node_type *& x2 ) {
                std::swap(x1->color, x2->color);
            }

            void    __swapValues( node_type *& u, node_type *& v ) {
                std::swap(u->data, v->data);
            }
            
            // searches for given value
            // if found returns the node (used for delete)
            // else returns the last node while traversing (used in insert)
            node_type * __search( const value_type& val ) {
                node_type * temp = this->_root;
                while (temp != nullptr) {
                    if (val < *temp->data) {
                        if (temp->left == nullptr)
                            break ;
                        else
                            temp = temp->left;
                    } else if (val == *temp->data)
                        break ;
                    else {
                        if (temp->right == nullptr)
                            break ;
                        else
                            temp = temp->right;
                    }
                }
                return temp;
            }

            // find node that do not have a left child
            // in the subtree of the given node
            node_type * __successor( node_type *x ) {
                node_type *temp = x;
                while (temp->left != NULL)
                    temp = temp->left;
                return temp;
            }

            // find node that replaces a deleted node in BST
            node_type * __BSTreplace( node_type *& x ) {
                // when node have 2 children
                if (x->left != nullptr && x->right != nullptr)
                    return __successor(x->right);

                // when leaf
                if (x->left == nullptr && x->right == nullptr)
                    return nullptr;

                // when single child
                if (x->left != nullptr)
                    return x->left;
                else
                    return x->right;
            }


            void    __deleteNode( node_type *& v ) {
                node_type * u = __BSTreplace(v);

                // True when u and v are both black
                bool uvBlack = ((u == nullptr || u->color == BLACK) && (v->color == BLACK));
                node_type * parent = v->parent;

                if (u == nullptr) {
                    // u is nullptr therefore v is leaf
                    if (v == this->_root)
                        // v is this->_root, making this->_root nullptr
                        this->_root = nullptr;
                    else {
                        if (uvBlack)
                            // u and v both black
                            // v is leaf, fix double black at v
                            __fixDoubleBlack(v);
                        else {
                            // u or v is red
                            if (v->sibling() != nullptr)
                                // sibling is not nullptr, make it red"
                                v->sibling()->color = RED;
                        }

                        // delete v from the tree
                        if (v->isOnLeft())
                            parent->left = nullptr;
                        else
                            parent->right = nullptr;
                    }
                    
                    // delete v;
                    this->_alloc.destroy(v->data);
                    this->_alloc.deallocate(v->data, 1);
                    this->_rebindAlloc.deallocate(v, 1);
                    
                    return ;
                }

                if (v && (v->left == nullptr || v->right == nullptr)) {
                    // v has 1 child
                    if (v == this->_root) {
                        // v is root, assign the value of u to v, and delete u
                        *v->data = *u->data;
                        v->left = v->right = nullptr;

                        // delete u
                        this->_alloc.destroy(u->data);
                        this->_alloc.deallocate(u->data, 1);
                        this->_rebindAlloc.deallocate(u, 1);
                        
                    }
                    else {
                        // Detach v from tree and move u up
                        if (v->isOnLeft())
                            parent->left = u;
                        else
                            parent->right = u;
                            
                        // delete v
                        this->_alloc.deallocate(v->data, 1);
                        this->_alloc.destroy(v->data);
                        this->_rebindAlloc.deallocate(v, 1);
                        
                        u->parent = parent;
                        if (uvBlack)
                        // u and v both black, fix double black at u
                            __fixDoubleBlack(u);
                        else
                            // u or v red, color u black
                            u->color = BLACK;
                    }
                    return ;
                }

                // v has 2 children, swap values with successor and recurse
                __swapValues(u, v);
                __deleteNode(u);
            }

            void    __fixDoubleBlack( node_type *& x ) {
                if (x == this->_root)
                // Reached root
                    return ;

                node_type * sibling = x->sibling();
                node_type * parent = x->parent;
                if (sibling == nullptr)
                    // No sibiling, double black pushed up
                    __fixDoubleBlack(parent);
                else {
                    if (sibling->color == RED) {
                        // Sibling red
                        parent->color = RED;
                        sibling->color = BLACK;
                        if (sibling->isOnLeft())
                            // left case
                            __rotateRight(parent);
                        else
                            // right case
                            __rotateLeft(parent);
                        __fixDoubleBlack(x);
                    }
                    else {
                        // Sibling black
                        if (sibling->hasRedChild()) {
                        // at least 1 red children
                            if (sibling->left != nullptr && sibling->left->color == RED) {
                                if (sibling->isOnLeft()) {
                                    // left left
                                    sibling->left->color = sibling->color;
                                    sibling->color = parent->color;
                                    __rotateRight(parent);
                                }
                                else {
                                    // right left
                                    sibling->left->color = parent->color;
                                    __rotateRight(sibling);
                                    __rotateLeft(parent);
                                }
                            }
                            else {
                                if (sibling->isOnLeft()) {
                                    // left right
                                    sibling->right->color = parent->color;
                                    __rotateLeft(sibling);
                                    __rotateRight(parent);
                                }
                                else {
                                    // right right
                                    sibling->right->color = sibling->color;
                                    sibling->color = parent->color;
                                    __rotateLeft(parent);
                                }
                            }
                            parent->color = BLACK;
                        }
                        else {
                            // 2 black children
                            sibling->color = RED;
                            if (parent->color == BLACK)
                                __fixDoubleBlack(parent);
                            else
                                parent->color = BLACK;
                        }
                    }
                }
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
            void printHelper( Node* root, Trunk *prev, bool isLeft ) {
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