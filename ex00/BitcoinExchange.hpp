/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 02:55:51 by lomont            #+#    #+#             */
/*   Updated: 2026/01/20 04:59:49 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <exception>
#include <cstdlib>

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

class FileOpeningException : public std::exception
{
	public:
		const char* what( void ) const throw();
		virtual ~FileOpeningException( void ) throw();
};

class BitcoinDatabase
{
	private:
		//Member variable
		std::ifstream			_file;
		FileOpeningException	exception;

		//Member function
		void	openDatabaseFile( void );
		void	createDatabaseMap( void );
	public:
		std::map<std::string, std::string> map;

		//Canonical form
		BitcoinDatabase( void );
		BitcoinDatabase( BitcoinDatabase& src );
		BitcoinDatabase& operator=( BitcoinDatabase & other);
		~BitcoinDatabase( void );
};

class InputDatabase {
	private:
		std::ifstream			_file;
		FileOpeningException	exception;
		void OpenInputFile(const char* filename);
	public:
		std::map<std::string, std::string> InputMap;
		//Canonical form

		InputDatabase( const char* str );
		InputDatabase( InputDatabase& src );
		InputDatabase & operator=( InputDatabase& other );
		~InputDatabase( void );

		//member functions
		void			CheckParsing( void );
		void			createIndexDatabase( const std::string& str );
		bool			checkDate( const std::string& str );
		bool			checkSyntax( const std::string& str );
		bool			checkValue( const std::string& str );

};

#endif
