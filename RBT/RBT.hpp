/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:19:07 by aabounak          #+#    #+#             */
/*   Updated: 2021/11/23 10:34:33 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"
# include <errno.h>

# define RED 1
# define BLACK 0
# define DOUBLE_BLACK 2

namespace ft {
    
    /* --       Description:
        RBT is a self-balancing BST in which each node contains \
        an extra bit for denoting the color of the node, either RED or BLACK */
    
    /* --       RBT Properties:
        1 - R/B Property: Every node is colored, either RED or BLACK.
        2 - Root Property: The ROOT is always BLACK.
        3 - Leaf Property: Every LEAF (NIL) is BLACK.
        4 - Red Property: If a RED node has CHILDREN, they will always be BLACK.
        5 - Depth Property: For each NODE, any SIMPLE PATH from this node to any \
        of its DESCENDANT LEAF has the same BLACK-DEPTH (The number of BLACK nodes) */

    /* --       How the RBT maintains SELF-BALANCING property:
        1 - The R/B color is meant for balancing the tree.
        2 - The limitations put on the NODE COLORS ensure that any SIMPLE PATH \
        from the ROOT to a LEAF is not more than twice as long as any other such PATH. \
        It helps in maintaining the self-balancing property of the RBT. */

    template < class T, class Compare = std::less<T> , class Alloc = std::allocator<T> >
    class RBT
    {
        public:
        
            typedef             T                  value_type;
            typedef             Compare            key_compare;
            typedef             Alloc              allocator_type;
            typedef             size_t              size_type;



       
            
            struct Node {

                value_type  * data;
                Node        * parent;
                Node        * left;
                Node        * right;
                short         color;

                Node ( const value_type& x ) : data(x), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}

                /* Check if node is left child of parent */
                bool    isOnLeft( void ) {
                    return this == this->parent->left;
                }
                
            };           




            /* --- THESE ARE PUBLIC --- */

            typedef typename    Alloc::template rebind<Node>::other   rebind_allocator;
             
            // Constructor
            RBT( void ) {
                this->_root = nullptr;
                this->_size = 0;
            }
            
            Node *  getRoot( void ) {
                return this->_root;
            }

            size_type   getTreeSize( void ) {
                return this->_size;
            }

            /* --   Insertion of an element into a RBT:
                While inserting a new node, the ney node is always inserted as a RED node.
                After insertion of a new node, if the tree is violating the properties of the RBT
                we do the following operations:
                    1 - Recolor
                    2 - Rotation */
            void    insert( value_type key ) {
                Node * tmpNode = newNode(key);
                this->_root = this->BST_insert(this->_root, tmpNode);
                this->_size++;
                if (tmpNode->parent == nullptr)
                {
                    tmpNode->color = BLACK;
                    return ;
                }
                if (tmpNode->parent->parent == nullptr)
                    return ;
                fixInsertionViolation(this->_root, tmpNode);
            }

            void    deleteNode( value_type key ) {
                Node * tmpNode = search(this->_root, key);
                if (tmpNode == nullptr)
                    return ;
                RBT_delete(this->_root, tmpNode);
            }

            void    printTree() {
                if (_root) {
                    printHelper(this->_root, nullptr, false);
                }
            }

            /* Node *  minimum( Node * node ) {
                while (getRoot()->left != nullptr) { node = node->left; }
                return node;
            }

            Node *  maximum( Node * node ) {
                while (getRoot()->right != nullptr) { node = node->right; }
                return node;
            } */




        /** ------ THESE ARE PRIVATES ------- */


        private:
            Node    *           _root;
            key_compare         _comp;
            allocator_type      _alloc;
            rebind_allocator    _nodeAlloc;
            size_type           _size;

            /* --   Why newly inserted nodes are always RED in a RBT?
                This is because insertion a RED node does not vioolate the depth property of a RBT.
                If you attack a RED node to another RED node, then the rule is violated \
                but it is easier to fix this problem than the problem introduced by violating the DEPTH property. */
            Node *  newNode( value_type key ) {
                Node  * nouveauNode;
                nouveauNode = _nodeAlloc.allocate(1);
                nouveauNode->data = _alloc.allocate(1);
                *(nouveauNode->data) = key;
                nouveauNode->parent = nouveauNode->left = nouveauNode->right = nullptr;
                nouveauNode->color = RED;
                return nouveauNode;
            }

            Node *  maximum( Node * node ) {
                while (node->right != nullptr)
                    node = node->right;
                return node;
            }
            
            Node *  minimum( Node * node ) {
                while (node->left != nullptr)
                    node = node->left;
                return node;
            }

            Node *  inorder_predecessor( Node * node ) {
                if (node == nullptr)
                    return nullptr;
                if (node->left != nullptr)
                    return maximum(node->left);
                Node * temp = node->parent;
                while (temp != nullptr && node == temp->right) {
                    node = temp;
                    temp = temp->parent;
                }
                return temp;
            }

            
            Node * inorder_successor( Node * node ) {
                if (node == nullptr)
                    return nullptr;
                if (node->right != nullptr)
                    return minimum(node->right);
                Node * temp = node->parent;
                while (temp != nullptr && node == temp->right) {
                    node = temp;
                    temp = temp->parent;
                }
                return temp;
            }

            Node *  search( Node * root, value_type key ) {
                if (root == nullptr)
                    return (nullptr);
                if (*root->data == key)
                    return root;
                else if (*root->data > key)
                    return search(root->left, key);
                else if (*root->data < key)
                    return search(root->right, key);
                return nullptr;
            }
                    

            /* -- Deletion in RBT
                Step 1: Perform BST Deletion
                Step 2: Apply the appropriate case
                    Case 1:
                        - If NODE to be deleted is a RED LEAF NODE -> Just remove it from the tree.
                    Case 2:
                        - If DB NODE is ROOT -> Remove the DB & ROOT NODE becomes BLACK
                    Case 3:
                        - If DB's SIBLING is BLACK and both its CHILDREN are BLACK 
                            a -> Remove the DB 
                            b -> Add BLACK to its PARENT (P)
                                (3.1) |-> If P is RED, make it BLACK.
                                (3.2) |-> If P is BLACK, make it DB
                            c -> Make SIBLING RED
                        - If DB still exists, apply other cases 
                    Case 4:
                        - If DB's SIBLING is RED 
                            a -> Swap colors of DB's PARENT with DB's sibling 
                            b -> Rotate PARENT in DB's direction 
                            c -> Check which case can be applied to this new tree and perform that action
                    Case 5:
                        - If DB's SIBLING is BLACK && DB's SIBLING's CHILD which is FAR from DB is BLACK, 
                        && DB's SIBLING's CHILD which is NEAR to DB is RED
                            a -> Swap color of DB's SIBLING with SIBLING'S CHILD who is NEAR to DB
                            b -> Rotate SIBLING in opposite direction to DB 
                            c -> Apply Case 6
                    Case 6:
                        - If DB's SIBLING is BLACK && DB's SIBLING'S FAR CHILD is RED
                            a -> Swap color of DB's PARENT with DB's SIBLING's color 
                            b -> Rotate DB's PARENT in DB's direction 
                            c -> Remove DB sign nd make the NODE BLACK 
                            d -> Change color of DB's SIBLING's FAR RED CHILD to BLACK */

            /* ------------- I SHOULD HAVE THE FIX FUNCTION IN HERE -------- */
            void    fixDeletionViolation( Node *& x ) {
                if (this->_root == x) {
                    x->color = BLACK;
                    return ;
                }
                else if (x->color == RED)
                    return ;
                Node * sibling = nullptr;
                if (x->isOnLeft())
                    sibling = x->parent->right;
                else
                    sibling = x->parent->left;
                if (sibling != nullptr && sibling->color == BLACK) {
                    /* Case3 */
                    if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                        x->color = BLACK;
                        sibling->color = RED;
                        if (x->parent->color == BLACK) {
                            x->parent->color = DOUBLE_BLACK;
                            fixDeletionViolation(x->parent);
                        }
                        else
                            x->parent->color = BLACK;
                        return ;
                    }
                    if (x->isOnLeft()) {
                        /* Case 4 */
                        if ((sibling->left != nullptr || sibling->left->color == RED) &&
                        (sibling->right != nullptr || sibling->right->color == BLACK)) {
                            std::swap(sibling->left->color, sibling->color);
                            rotateRight(this->_root, sibling);
                        }
                        else if (sibling->right != nullptr && sibling->right->color == RED) {
                            /* Case 5 */
                            std::swap(x->parent->color, sibling->color);
                            rotateLeft(this->_root, x->parent);
                            x->color = BLACK;
                            sibling->right->color = BLACK;
                        }
                    }
                    else if (!x->isOnLeft()) { // Mirror te previous
                        /* Case 4 */
                        if ((sibling->right != nullptr || sibling->right->color == RED) &&
                        (sibling->left != nullptr || sibling->left->color == BLACK)) {
                            std::swap(sibling->right->color, sibling->color);
                            rotateLeft(this->_root, sibling);
                        }
                        else if (sibling->left != nullptr && sibling->left->color == RED) {
                            /* Case 5 */
                            std::swap(x->parent->color, sibling->color);
                            rotateRight(this->_root, x->parent);
                            x->color = BLACK;
                            sibling->left->color = BLACK;
                        }
                    }
                }
                else if (sibling != nullptr && sibling->color == RED) {
					std::swap(x->parent->color, sibling->color);
					if (x->parent->left == x)
						rotateLeft(this->_root, x->parent);
                    else
						rotateRight(this->_root, x->parent);
					fixDeletionViolation(x->parent);
					return ;
				}
            }

            void    RBT_delete( Node *& root, Node *& x ) {
                if  (x == nullptr)
                    return ;
                if (*root->data == *x->data) {
                    if (x->left == nullptr && x->right == nullptr) { // if no children
                        if (x == this->_root) {
                            _nodeAlloc.deallocate(x, 1);
                            _alloc.deallocate(x->data, 1);
                            /* x = nullptr;
                            x->data = nullptr; */
                            this->_size--;
                            return ;
                        }
                        fixDeletionViolation(x);
                        _alloc.deallocate(x->data, 1);
                        _nodeAlloc.deallocate(x, 1);
                        /* x = nullptr;
                        x->data = nullptr; */
                        this->_size--;
                    }
                    else { // If CHILDREN
                        if (x->left) {
                            Node * predecessor = inorder_predecessor(x);
                            x->data = predecessor->data;
                            RBT_delete(x, predecessor);
                        }
                        else if (x->right) {
                            Node * successor = inorder_successor(x);
                            x->data = successor->data;
                            RBT_delete(x, successor);
                        }
                    }
                    return ;
                }
                if (*root->data < *x->data)
                    RBT_delete(root->right, x);
                else
                    RBT_delete(root->left, x);
                return ;
            }


            /* ---------------------- Operations ---------------------- */
                /* --- Subtrees rotations // */
            
            /* -- Left Rotation:
                The arrangement of the nodes on the right is transformed into the arrangements on the left node
                -- Algorithm:
                    1 - If Y has a left subtree, assign X as the parent of the left substree of Y.
                    2 - If the parent of X is NULL, make Y as the root of the tree. 
                    3 - Else if X is the left child of its parent P, make Y as the left child of P. 
                    4 - Else assign Y as the right child of P. 
                    5 - Make Y as the parent of X. */
            void    rotateLeft( Node *& root, Node *& x ) {
                Node * y = x->right; x->right = y->left;
                if (y->left != nullptr) y->left->parent = x;
                y->parent = x->parent;
                if (x->parent == nullptr) root = y;
                else if (x == x->parent->left) x->parent->left = y;
                else x->parent->right = y;
                y->left = x; x->parent = y;
            }

            /* -- Right Rotation:
                The arrangement of the nodes on the left is transformed into the arrangements on the right node
                -- Algorithm:
                    1 - If X has a right subtree, assign Y as the parent of the right subtree of X. 
                    2 - If the parent of Y is NULL, make  as the root of the tree. 
                    3 - Else if Y is the right child of its parent P, make X as the right child of P. 
                    4 - Else assign X as the left cchild of P. 
                    5 - Make X as the parent of Y. */
            void    rotateRight( Node *&root, Node *&x ) {
                Node * y = x->left; x->left = y->right;
                if (y->right != nullptr) y->right->parent = x;
                y->parent = x->parent;
                if (x->parent == nullptr) root = y;
                else if (x == x->parent->right) x->parent->right = y;
                else x->parent->left = y;
                y->right = x; x->parent = y;
            }

            /* -- Insertion Violation Fix:
                This function is used for maintaining the property of a RBT \ 
                if the insertion of a newNode violates this property. 
                -- Alorithm:
                    1 - If <X> is ROOT, change color of <X> as BLACK.
                    2 - Do the followng if <X's PARENT> is not BLACK or <X> ain't ROOT.
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
                
            void    fixInsertionViolation(Node *&root, Node *&x) {
                Node *parent_x = nullptr;
                Node *grand_parent_x = nullptr;
                while ((x != root) && (x->color != BLACK) && (x->parent->color == RED)) {
                    parent_x = x->parent;
                    grand_parent_x = x->parent->parent;
                    /* -- Case: A
                        <PARENT>> is LEFT CHILD of <GRAND PARENT> of <X> */
                    if (parent_x == grand_parent_x->left) {   
                        Node *aunt_x = grand_parent_x->right;
                        /* -- Case : 1
                            <X's AUNT> is also RED --->> RECOLORING required */
                        if (aunt_x != nullptr && aunt_x->color == RED) {
                            parent_x->color = BLACK;
                            aunt_x->color = BLACK;
                            grand_parent_x->color = RED;
                            x = grand_parent_x;
                        }
                        else {
                            /* -- Case : 2
                                <X>> is RIGHT CHILD of its <PARENT> || LEFT-ROTATION required */
                            if (x == parent_x->right) {
                                rotateLeft(root, parent_x);
                                x = parent_x;
                                parent_x = x->parent;
                            }
                            /* -- Case : 3
                                <X> is LEFT CHILD of its <PARENT> || RIGHT-ROTATION required */
                            rotateRight(root, grand_parent_x);
                            std::swap(parent_x->color, grand_parent_x->color);
                            x = parent_x;
                        }
                    }
                    /* -- Case: B
                        <PARENT> is RIGHT CHILD of <GRAND PARENT> of <X> */
                    else {
                        Node *aunt_x = grand_parent_x->left;
                        /* -- Case : 1
                            <X's AUNT> is also RED --->> RECOLORING required */
                        if (aunt_x != nullptr && aunt_x->color == RED) {
                            parent_x->color = BLACK;
                            aunt_x->color = BLACK;
                            grand_parent_x->color = RED;
                            x = grand_parent_x;
                        }
                        else {
                            /* -- Case : 2
                                <X>> is LEFT CHILD of its <PARENT> || RIGHT-ROTATION required */
                            if (x == parent_x->left) {
                                rotateRight(root, parent_x);
                                x = parent_x;
                                parent_x = x->parent;
                            }
                            /* -- Case : 3
                                <X> is RIGHT CHILD of its <PARENT> || LEFT-ROTATION required */
                            rotateLeft(root, grand_parent_x);
                            std::swap(parent_x->color, grand_parent_x->color);
                            x = parent_x;
                        }
                    }
                }
                root->color = BLACK;
            }

            Node *  BST_insert( Node *root, Node *z ) {
                if (root == nullptr) { return z; }
                if (*root->data < *z->data) {
                    root->right = BST_insert(root->right, z);
                    root->right->parent = root;
                }
                else if (*root->data > *z->data) {
                    root->left = BST_insert(root->left, z);
                    root->left->parent = root;
                }
                return root;
            }

                    /* ---------- | Recursive print of a "RBT" | ---------- */

            struct Trunk {
                Trunk *prev;
                std::string str;
                Trunk( Trunk *prev, std::string str ) { this->prev = prev; this->str = str; }
            };

            // Helper function to print branches of the binary tree
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
