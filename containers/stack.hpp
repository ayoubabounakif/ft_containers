/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:26:16 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/15 21:12:13 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* --------------------------- Base Libraries  ------------------------------ */
# include <iostream>
# include <stdlib.h>
# include <string>
/* ----------------------------- Containers --------------------------------- */
# include <vector>
# include <stack>
# include <deque>
# include <list>
/* ------------------------------ Allocator --------------------------------- */
# include <memory>

# include "vector.hpp"

namespace ft {
	template < class T, class Container = ft::vector<T> >
	class stack {
		public:
			typedef	Container	container_type;
			typedef typename Container::value_type  value_type;
			typedef typename Container::size_type   size_type;
			typedef typename Container::reference   reference;
			typedef typename Container::const_reference   const_reference;

			/* ---- Constructor & Destructor respectively ---- */
			explicit stack (const container_type& cntr = container_type()) { this->__cntr = cntr; };
			virtual ~stack( void ) {};
            stack( const stack& other ) { *this = other; }
            stack& operator=( const stack& other ) { this->__cntr = other.__cntr; }

			/* -------- Member functions -------- */
			bool empty() const { return __cntr.empty(); };
			size_type size() const { return __cntr.size(); };
			value_type& top() { return __cntr.back(); };
			const value_type& top() const { return __cntr.back(); };
			void push (const value_type& val) { return __cntr.push_back(val); };
			void pop() { return __cntr.pop_back(); };

		/* ---- Non-member function overloads ---- */
			friend bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs.__cntr == rhs.__cntr); };
            friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs.__cntr != rhs.__cntr ); };
            friend bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs.__cntr < rhs.__cntr ); };
            friend bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs.__cntr <= rhs.__cntr ); };
            friend bool operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs.__cntr > rhs.__cntr ); };
            friend bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs.__cntr >= rhs.__cntr ); };

        protected:
			container_type  __cntr;
	};

	/* -------------- Relational operators [NOT WORKING] ---------------- */
	template <class T, class Container>
	  bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs == rhs); };
	template <class T, class Container>
	  bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs != rhs); };
	template <class T, class Container>
	  bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs < rhs); };
	template <class T, class Container>
	  bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs <= rhs); };
	template <class T, class Container>
	  bool operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs > rhs); };
	template <class T, class Container>
	  bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return (lhs >= rhs); };
;}
