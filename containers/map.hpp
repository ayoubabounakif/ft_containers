/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:18:31 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/13 18:58:19 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <stdlib.h>
# include <string>
# include <vector>
# include <stack>
# include <deque>
# include <list>
# include <memory>
# include <cmath>
# include <stdexcept>
# include <iterator>

# include "../AVL/avl.hpp"
# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"

namespace ft {
    
    /* --       Definition:
    Maps are associative containers that store elements formed by
    a combination of a key value and a mapped value, following a specific order. */

    template <class Key, class T, class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> >
    > class map {
        public:
        
                    /* ------------ Member Types ----------- */
            typedef             Key                 key_type;
            typedef             T                   mapped_type;
            typedef             ft::pair<const key_type, mapped_type>  value_type;
            typedef             ptrdiff_t           difference_type;
            typedef             size_t              size_type;
            typedef             Compare             key_compare;
            typedef             Allocator           allocator_type;
            typedef typename    allocator_type::reference           reference;
            typedef typename    allocator_type::const_reference     const_reference;
            typedef typename    allocator_type::pointer             pointer;
            typedef typename    allocator_type::const_pointer       const_pointer;
            typedef typename    AVL<value_type, Compare, Allocator>::iterator   iterator;
            typedef typename    AVL<value_type, Compare, Allocator>::const_iterator   const_iterator;
            

                    /* ------------- Member Class ------------ */ 
            class value_compare : public std::binary_function<value_type, value_type, bool> {
                protected:
                    Compare __comp;
                    value_compare( Compare c ) : __comp(c) {}
                public:
                    bool operator()( const value_type& lhs, const value_type& rhs ) const { return this->__comp(lhs.first, rhs.first); }
            };

                    /* ----------- Member Functions ---------- */    
                /* ---- Constructors & Destructor respectively ---- */
            /* ------------------------ Default ------------------------ */ 
            explicit map( const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : __tree(), __alloc(alloc), __comp(comp) {}
            
            /* ----------------------- Range ------------------------ */
            template< class InputIt >
                map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {
                    this->__comp = comp;
                    this->__alloc = alloc;
                    this->__tree(first, last);
                }
            
            /* ------------------------ Copy ------------------------ */
            map( const map& other ) { *this = other; }

            /* ------------------ Assignment Operator --------------- */
            map& operator=( const map& other ) {
                this->__tree = other.__tree;
                return *this;
            }
            
            /* ---------------------- Detructor --------------------- */
            ~map() {}

            /* ---------------------- Iterators --------------------- */
            iterator begin() { return this->__tree.begin(); }
            const_iterator begin() const { return this->__tree.begin(); }
            iterator end() { return this->__tree.end(); }
            const_iterator end() const { return this->__tree.end(); }

            /* ----------------------- Capacity --------------------- */
            bool empty() const { return this->__tree.empty(); }
            size_type size() const { return this->__tree.size(); }
            size_type max_size() const { return this->__tree.max_size(); }

            /* -------------------- Element access ------------------ */
            mapped_type& operator[] ( const key_type& k ) { return (*((this->insert(make_pair(k, mapped_type()))).first)).second; }
            
            /* ---------------------- Modifiers --------------------- */
            void clear() { this->__tree.clear(); }
            /* pair<iterator, bool> insert( const value_type& value ) {} */
            /* iterator insert( iterator hint, const value_type& value ) {} */
            template < class InputIt >
                void insert( InputIt first, InputIt last ) { for (; first != last; ++first) this->__tree.insert(*first); return ; }
            void erase( iterator pos ) { this->__tree.remove(pos->first); return ; }
            void erase( iterator first, iterator last ) { for (; first != last; ++first) this->__tree.remove(*first->first); return ; }
            size_type erase( const key_type& x ) { return (this->__tree.remove(x)); }
            void swap( map& other ) {
                AVL<value_type, key_compare, allocator_type> tmpTree = other.__tree;
                other.__tree = this->__tree;
                this->__tree = tmpTree;
                return ;
            }

            /* ----------------------- Lookup ----------------------- */
            
            /* ---------------------- Observers --------------------- */
            key_compare key_comp() const { return this->__comp; }
            value_compare value_comp() const { return value_compare(); }


            /* ---------------------- Allocator --------------------- */
            allocator_type get_allocator() const { return this->__alloc; }
    
        private:
            AVL<value_type, key_compare, allocator_type>    __tree;
            key_compare     __comp;
            allocator_type  __alloc;
    };

                /* ----------- Non-member function overloads ----------- */
    /* ------------------------ Relational Operators ------------------------ */
            /* ---------------- Equivalent Operators --------------- */
            /* Here are some operators whose work is same.
                (a != b) is equivalent to !(a == b)
                (a > b) equivalent to (b < a)
                (a <= b) equivalent to !(b < a) */

    template< class Key, class T, class Compare, class Alloc >
        bool operator==( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) {
            if (lhs.size() != rhs.size())
                return (lhs.size() == rhs.size());
            return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
        }
    template< class Key, class T, class Compare, class Alloc >
        bool operator!=( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (!operator==(lhs, rhs)); }
    template< class Key, class T, class Compare, class Alloc >
        bool operator<( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
    template< class Key, class T, class Compare, class Alloc >
        bool operator<=( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (operator<(rhs, lhs)); }
    template< class Key, class T, class Compare, class Alloc >
        bool operator>( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (!operator<(rhs, lhs)); }	
    template< class Key, class T, class Compare, class Alloc >
        bool operator>=( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (!operator<(lhs, rhs)); }

    /* ------------------------------- Swap --------------------------------- */
	template< class Key, class T, class Compare, class Alloc >
        void swap( map<Key, T, Compare, Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs ) { lhs.swap(rhs); }
        
}