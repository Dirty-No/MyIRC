/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboivin <mboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:07:04 by mboivin           #+#    #+#             */
/*   Updated: 2021/09/30 18:46:14 by mboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP
# include <cstring>
# include <cstdlib>
# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include <unistd.h>
# include "numeric_replies.hpp"
# include "client.hpp"
# include "server.hpp"
# include "Channel.hpp"
# include "IRCParser.hpp"
# include "Message.hpp"

void	displayUsage( const char* program_name );

#ifndef nullptr
# define nullptr NULL
#endif // !nullpt

#endif
