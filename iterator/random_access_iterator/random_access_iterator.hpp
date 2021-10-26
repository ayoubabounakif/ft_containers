/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:26:04 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/25 17:13:35 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "../iterator_traits/iterator_traits.hpp"

//! if Linux
#define ptrdiff_t __gnu_cxx::ptrdiff_t

namespace ft {
    template < class T >
    class random_access_iterator {
        public:
                    /* ------------ Member Types ----------- */
            typedef iterator_traits< iterator<std::random_access_iterator_tag, T> > iterator_traits;
            typedef typename iterator_traits::value_type        value_type;
            typedef typename iterator_traits::difference_type   difference_type;
            typedef typename iterator_traits::pointer           pointer;
            typedef typename iterator_traits::reference         reference;
            typedef typename iterator_traits::iterator_category iterator_category;

                    /* ----------- Member Functions ---------- */    
                /* ---- Constructors & Destructor respectively ---- */
            random_access_iterator() : _data(0) {};
            random_access_iterator( value_type * element ) : _data(element) {};
            random_access_iterator( const random_access_iterator& rhs ) : _data(rhs._data) {}
            random_access_iterator& operator= ( const random_access_iterator& rhs ) { this->_data = rhs._data; return (*this); } 
            virtual ~random_access_iterator() {};
            
                /* Misc Operators */
            random_access_iterator& operator+= ( difference_type rhs ) { this->_data += rhs; return *this; };
            random_access_iterator& operator-= ( difference_type rhs ) { this->_data -= rhs; return *this; };
            
            reference operator*() const { return *_data; }
            pointer   operator->() const { return _data; }
            
            reference operator[]( difference_type rhs ) const { return (_data[rhs]); };
    
                /* Arithmetic Operators */
            random_access_iterator& operator++() { ++_data; return *this; }
            random_access_iterator& operator--() { --_data; return *this; }
            random_access_iterator  operator++( int ) { random_access_iterator tmp(*this); ++_data; return tmp; }
            random_access_iterator  operator--( int ) { random_access_iterator tmp(*this); --_data; return tmp; }

            difference_type operator+( const random_access_iterator& rhs ) const { return _data + rhs._data; }
            difference_type operator-( const random_access_iterator& rhs ) const { return _data - rhs._data; }
            random_access_iterator operator+( difference_type rhs ) const { return random_access_iterator(_data + rhs); }
            random_access_iterator operator-( difference_type rhs ) const { return random_access_iterator(_data - rhs); }

            operator random_access_iterator<const value_type> () const { return random_access_iterator<const value_type>(_data) ; }

            pointer getData( void ) const { return (this->_data); }

        protected:
            pointer  _data;
    };

            /* ----------- Non-member function overloads ----------- */
    /* ------------------------ Relational Operators ------------------------ */
            /* ---------------- Equivalent Operators --------------- */
            /* Here are some operators whose work is same.
                (a != b) is equivalent to !(a == b)
                (a > b) equivalent to (b < a)
                (a <= b) equivalent to !(b < a) */
    template < class T >
		random_access_iterator<T> operator+ (ptrdiff_t lhs, const random_access_iterator<T>& rhs) { return (rhs + lhs); }
	template < class T >
		bool operator== (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return lhs.getData() == rhs.getData(); }
	template < class T >
		bool operator!= (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return !operator==(lhs, rhs); }
	template < class T >
 		bool operator<  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return lhs.getData() < rhs.getData(); }
	template < class T >
 		bool operator>  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return operator<(rhs, lhs); }
	template < class T >
 		bool operator<=  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return !operator<(rhs, lhs); }
	template < class T >
 		bool operator>=  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return !operator<(lhs, rhs); }
}