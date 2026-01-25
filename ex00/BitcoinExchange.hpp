/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 02:55:51 by lomont            #+#    #+#             */
/*   Updated: 2026/01/25 17:56:43 by lomont           ###   ########.fr       */
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

class FileHeaderException : public std::exception
{
	public:
		const char* what( void ) const throw();
		virtual ~FileHeaderException( void ) throw();
};

class BitcoinDatabase
{
	private:
		//Member variable
		std::ifstream			_file;
		FileOpeningException	OpeningException;
		FileHeaderException		HeaderException;

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

class BitcoinExchange {
	private:
		std::ifstream			_file;
		FileOpeningException	OpeningException;
		FileHeaderException		HeaderException;
		void OpenInputFile(const char* filename);
	public:
		//Canonical form

		BitcoinExchange( const char* str, BitcoinDatabase& BitcoinDatabase );
		BitcoinExchange( BitcoinExchange& src );
		BitcoinExchange & operator=( BitcoinExchange& other );
		~BitcoinExchange( void );

		//member functions

		void			printExchange(const std::string& str, std::map<std::string, std::string> database ) const;
		void			CheckParsing( std::map<std::string, std::string> database );
		bool			checkDate( const std::string& str, size_t* index );
		bool			checkSyntax( const std::string& str, size_t* index );
		bool			checkValue( const std::string& str, size_t* index );
		static bool		validateDate(const std::string& str, int d, int m, int y);
};

#endif
