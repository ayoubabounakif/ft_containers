/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:26:16 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/15 18:24:55 by aabounak         ###   ########.fr       */
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

namespace ft {
	template < class T, class Container = std::vector<T> >
	class stack {
		public:
			typedef T			value_type;
			typedef	size_t		size_type;
			typedef	Container	container_type;

			/* ---- Constructor & Destructor respectively ---- */
			explicit stack (const container_type& cntr = container_type()) { this->_cntr = cntr; };
			// virtual ~stack( void ) {};

			/* -------- Member functions -------- */
			bool empty() const { return _cntr.empty(); };
			size_type size() const { return _cntr.size(); };
			value_type& top() { return _cntr.back(); };
			const value_type& top() const { return _cntr.back(); };
			void push (const value_type& val) { return _cntr.push_back(val); };
			void pop() { return _cntr.pop_back(); };

		/* ---- Non-member function overloads ---- */
			// bool operator== (const stack<T, Container>&, const stack<T, Container>&);

		protected:
			container_type  _cntr;
	};
	
	/* -------------- Relational operators [NOT WORKING] ---------------- */
	/* ----- TO-DO :
				1 - Make ft::vector (With overloading); */
	/* template <class T, class Container>
	  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs == rhs ? true : false); };
	template <class T, class Container>
	  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._cntr != rhs._cntr ? true : false ); };
	template <class T, class Container>
	  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._cntr < rhs._cntr ? true : false ); };
	template <class T, class Container>
	  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._cntr <= rhs._cntr ? true : false ); };
	template <class T, class Container>
	  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._cntr > rhs._cntr ? true : false ); };
	template <class T, class Container>
	  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._cntr >= rhs._cntr ? true : false ); }; */
;}
