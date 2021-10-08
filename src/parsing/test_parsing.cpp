/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboivin <mboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:25:08 by mboivin           #+#    #+#             */
/*   Updated: 2021/10/08 15:42:29 by mboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <iostream>
#include <string>
#include "Client.hpp"
#include "Message.hpp"
#include "Parser.hpp"

// Compare Messages and display only values that differe

static int	cmp_msg(const ft_irc::Message& msg, const ft_irc::Message& expected)
{
	int	ret = 1;

	if (msg.getCommand() != expected.getCommand())
	{
		std::cout << "   Message command:  " << msg.getCommand()
				  << "\n-> Expected command: " << expected.getCommand() << std::endl;
		ret = 0;
	}
	if (msg.getParams() != expected.getParams())
	{
		std::cout << "   Message params:  ";
		for (std::list<std::string>::const_iterator it = msg.getParams().begin();
			 it != msg.getParams().end();
			 ++it)
		{
			std::cout << "'" << *it << "' ";
		}

		std::cout << "\n-> Expected params: ";
		for (std::list<std::string>::const_iterator it = expected.getParams().begin();
			 it != expected.getParams().end();
			 ++it)
		{
			std::cout << "'" << *it << "' ";
		}
		std::cout << std::endl;
		ret = 0;
	}
	if (msg.getResponse() != expected.getResponse())
	{
		std::cout << "   Message response:  " << msg.getResponse()
				  << "-> Expected response: " << expected.getResponse() << std::endl;
		ret = 0;
	}
	return (ret);
}

// Test parsing use cases

int	test_parsing()
{
	ft_irc::Parser	parser;
	ft_irc::Client	dummy_client;
	ft_irc::Message	msg(dummy_client);

	// Set dummy values to client
	dummy_client.setNick("nick");
	dummy_client.setUsername("username");

	// Wrong command format is silently ignored
	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "123");
		assert(cmp_msg(msg, expected));
	}

	// Unknown command
	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "foo");
		expected.setCommand("foo");
		expected.setResponse(":irc.42.fr 421 foo :Unknown command\r\n");
		assert(cmp_msg(msg, expected));
	}

	// Uppercase command if valid
	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "PArt");
		expected.setCommand("PART");
		assert(cmp_msg(msg, expected));
	}

	// Valid command
	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "QUIT");
		expected.setCommand("QUIT");
		assert(cmp_msg(msg, expected));
	}

	// Simple parameter checking
	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "JOIN  ");
		expected.setCommand("JOIN");
		assert(cmp_msg(msg, expected));

		msg = parser.parseMessage(dummy_client, "JOIN #general");
		expected.setParam("#general");
		assert(cmp_msg(msg, expected));
	}

	// Trailing parameter can contain spaces and colons
	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "QUIT :Gone to have lunch at: MyFavPlace");
		expected.setCommand("QUIT");
		expected.setParam(":Gone to have lunch at: MyFavPlace");
		assert(cmp_msg(msg, expected));
	}

	// Trailing parameter must start with a colon
	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "QUIT :Gone to have lunch");
		expected.setCommand("QUIT");
		expected.setParam(":Gone to have lunch");
		assert(cmp_msg(msg, expected));
	}

	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "TOPIC #test :another topic");
		expected.setCommand("TOPIC");
		expected.setParam("#test");
		expected.setParam(":another topic");
		assert(cmp_msg(msg, expected));
	}

	// Many middle parameters
	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "KICK #Finnish John :Speaking English");
		expected.setCommand("KICK");
		expected.setParam("#Finnish");
		expected.setParam("John");
		expected.setParam(":Speaking English");
		assert(cmp_msg(msg, expected));
	}

	// List of middle parameters
	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "JOIN #foo,#bar");
		expected.setCommand("JOIN");
		expected.setParam("#foo");
		expected.setParam("#bar");
		assert(cmp_msg(msg, expected));
	}

	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "JOIN #foo, #bar");
		expected.setCommand("JOIN");
		expected.setParam("#foo");
		expected.setParam("#bar");
		assert(cmp_msg(msg, expected));
	}

	{
		ft_irc::Message	expected(dummy_client);

		msg = parser.parseMessage(dummy_client, "QUIT :#foo,#bar");
		expected.setCommand("QUIT");
		expected.setParam(":#foo,#bar");
		assert(cmp_msg(msg, expected));
	}

	return (0);
}
