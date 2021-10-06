/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:07:12 by aabounak          #+#    #+#             */
/*   Updated: 2021/10/06 12:24:52 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <stdlib.h>
# include <string>
# include <vector>
# include <stack>
# include <deque>
# include <list>

namespace ft {
    template <class T, class Container = deque<T>>
    class Stack {
        public:
            Stack() { std::cout << "ft_::Stack Constructor called" << std::endl; };
            ~Stack() { std::cout << "ft_::Stack Destructor called" << std::endl; };

        typedef	typename	T           value_type;
        typedef	typename    Container   container_type;
        typedef	typename    size_t      size_type;
        
    }
}