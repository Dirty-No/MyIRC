/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboivin <mboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:48:18 by mboivin           #+#    #+#             */
/*   Updated: 2021/09/24 17:16:47 by mboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Message.hpp"
#include "IRCParser.hpp"

namespace ft_irc
{
	// default constructor
	Message::Message()
			: _sender(), _type(undefined), _output(), _command(), _params()
	{
	}

	// copy constructor
	Message::Message(const Message& other)
			: _sender(other._sender),
			  _type(other._type),
			  _output(other._output),
			  _command(other._command),
			  _params(other._params)
	{
	}

	// assignment operator
	Message&	Message::operator=(const Message& other)
	{
		if (this != &other)
		{
			_sender = other.getSender();
			_type = other.getType();
			_output = other.getOutput();
			_command = other.getCommand();
			_params = other.getParams();
		}
		return (*this);
	}

	// destructor
	Message::~Message() {}

	// getters
	IRCClient	Message::getSender() const
	{
		return (this->_sender);
	}

	reply_type	Message::getType() const
	{
		return (this->_type);
	}

	std::string	Message::getOutput(void) const
	{
		return (this->_output);
	}

	std::string	Message::getCommand(void) const
	{
		return (this->_command);
	}

	Message::str_vec	Message::getParams(void) const
	{
		return (this->_params);
	}

	// setters

	void	Message::setSender(const IRCClient& sender)
	{
		this->_sender = sender;
	}

	void	Message::setType(reply_type type)
	{
		this->_type = type;
	}

	void	Message::setOutput(const std::string& output)
	{
		this->_output = output;
	}

	void	Message::setCommand(const std::string& command)
	{
		this->_command = command;
	}

	void	Message::setParam(const std::string& param)
	{
		if (!param.empty() && (_params.size() < MSG_MAX_PARAMS))
			this->_params.push_back(param);
	}

	// end message with CRLF
	void	Message::appendSeparator()
	{
		this->_output.append("\r\n");
	}

	// debug
	void	Message::displayMessage() const
	{
		std::cout << "command: " << getCommand() << '\n'
				  << "params:  ";
		
		for (std::size_t i = 0; i < _params.size(); i++)
			std::cout << "'" << _params[i] << "' ";
		std::cout << std::endl;
	}

	void	Message::displayReply() const
	{
		std::cout << "Reply: '" << getOutput() << "'" << std::endl;
	}
}