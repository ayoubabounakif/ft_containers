/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:19:07 by aabounak          #+#    #+#             */
/*   Updated: 2021/11/03 19:03:51 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"

# define GREEN 420
# define BLACK 42
# define BLACK_BLACK 99

namespace ft {
    struct Node {
        int     data;
        Node  * parent;
        Node  * left;
        Node  * right;
        short   color;      
    };
    
    template < class T, class Alloc = std::allocator<T> >
    class GBT
    { 
        public:

            typedef    T               value_type;
            typedef    Alloc           allocator_type;

            // Constructor
            GBT() {
                _TNULL = _alloc.allocate(1);
                _TNULL->color = GREEN;
                _TNULL->left = nullptr;
                _TNULL->right = nullptr;
                _root = _TNULL;
            }
            
            ~GBT() { _alloc.deallocate(_TNULL, 1); }

        private:
            Node    *       _root;
            Node    *       _TNULL;
            allocator_type  _alloc;
    }; 
}
