/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:05:24 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/01 16:40:35 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <stdlib.h>
# include <string>

namespace ft {

    /* --       Definition:
        This class couples together a pair of values, which may be of different types (T1 and T2).
        The individual values can be accessed through its public members first and second. */

    template < class T1, class T2 > struct pair {
        public:
        
                /* ------------ Member Types ----------- */
            typedef T1  first_type;
            typedef T2  second_type;

                        /* ----------- Member Functions ---------- */    
                /* ---- Constructors & Destructor respectively ---- */
            /* ------------------------ Default ------------------------ */  
            pair() : __first(nullptr), __second(nullptr) {}
            
            /* ------------------------ Copy --------------------------- */
            template<class U, class V>
                pair ( const pair<U,V>& pr ) : __first(pr.__first), __second(pr.__second) {}
                
            /* ------------------- Initialization ---------------------- */
            pair ( const first_type& a, const second_type& b ) : __first(a), __second(b) {}
            pair& operator= ( const pair& pr ) {
                if (this != &pr) {
                    this->__first = pr.__first;
                    this->__second = pr.__second;
                }
                return *this;
            }
            
            /* ----------------------- Detructor ----------------------- */
            ~pair() {}
        
        private:
            first_type  __first;
            second_type __second;
    };

            /* ----------- Non-member function overloads ----------- */
    /* ------------------------ Relational Operators ------------------------ */
            /* Here are some operators whose work is same.
                (a != b) is equivalent to !(a == b)
                (a > b) equivalent to (b < a)
                (a <= b) equivalent to !(b < a) */

    template <class T1, class T2>
        bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.__first==rhs.__first && lhs.__second==rhs.__second; }
    template <class T1, class T2>
        bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs==rhs); }
    template <class T1, class T2>
        bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.__first<rhs.__first || (!(rhs.__first<lhs.__first) && lhs.__second<rhs.__second); }
    template <class T1, class T2>
        bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs<lhs); }
    template <class T1, class T2>
        bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs<lhs; }
    template <class T1, class T2>
        bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs<rhs); }
}