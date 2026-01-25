/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 02:55:51 by lomont            #+#    #+#             */
/*   Updated: 2026/01/25 15:47:25 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <exception>
#include <cstdlib>
#include <ctime>

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

		InputDatabase( const char* str, BitcoinDatabase& BitcoinDatabase );
		InputDatabase( InputDatabase& src );
		InputDatabase & operator=( InputDatabase& other );
		~InputDatabase( void );

		//member functions
		void			CheckParsing( std::map<std::string, std::string> database );
		void			createIndexDatabase( const std::string& str );
		bool			checkDate( const std::string& str, size_t* index );
		bool			checkSyntax( const std::string& str, size_t* index );
		bool			checkValue( const std::string& str, size_t* index );

};

// class BitcoinExchange
// {
// 	private:
// 		//Member variable

// 		//Member function
// 		void findDate(std::map<std::string, std::string> database, std::map<std::string, std::string> input);
// 	public:
// 		//Canonical form
// 		BitcoinExchange( BitcoinDatabase& BitcoinDatabase, InputDatabase& InputDatabase );
// 		BitcoinExchange( BitcoinExchange& src );
// 		BitcoinExchange& operator=( BitcoinExchange & other);
// 		~BitcoinExchange( void );
// };

bool	validateDate(const std::string& str, int d, int m, int y);

#endif
