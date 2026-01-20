/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 02:55:34 by lomont            #+#    #+#             */
/*   Updated: 2026/01/20 05:14:24 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//Exception

const char* FileOpeningException::what( void ) const throw() {
	return ( "Error when trying to open the file, exitin program..." );
}

FileOpeningException::~FileOpeningException( void ) throw() {
	std::cout << "Exception: FileOpeningException destructor called" << std::endl;
	return ;
}

//Canonical form

BitcoinDatabase::BitcoinDatabase( void ) : exception(FileOpeningException()) {
	std::cout << "BitcoinDatabase constructor called" << std::endl;
	try
	{
		openDatabaseFile();
		createDatabaseMap();
	}
	catch(const FileOpeningException& e)
	{
		std::cerr << e.what() << '\n';
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return ;
}

BitcoinDatabase::~BitcoinDatabase( void ) {
	std::cout << "BitcoinDatabase destructor called" << std::endl;
	this->_file.close();
	return ;
}

//Member functions

void	BitcoinDatabase::openDatabaseFile( void ) {
	this->_file.open("data.csv", std::ios_base::in);
	if (!_file.is_open()) {
		std::cout << "Can't open data.csv" << std::endl;
		throw this->exception;
	}
	std::cout << "_file opened!" << std::endl;
	return ;
}

void	BitcoinDatabase::createDatabaseMap( void ) {
	std::string		str;
	std::string		Key;
	std::string		Value;

	getline(this->_file, str);
	while (getline(this->_file, str)) {
		//std::cout << "index end of string = " << str.size() << std::endl;
		std::pair<std::string, std::string> pair;
		char	delimiter = str.find(',');
		pair.first = str.substr(0, delimiter);
		pair.second = str.substr(delimiter + 1, str.size() - 1);
		this->map.insert(pair);
	}
	// for (std::map<std::string, std::string>::iterator it = map.begin(); it != map.end(); it++)
	// 	std::cout << "Key = " << it->first << " Value = " << it->second << std::endl;
}


//-----------------------------------------------------------------------------------------------

//Exception

//Canonical form

InputDatabase::InputDatabase( const char* str ) {
	OpenInputFile(str);
	CheckParsing();
	std::cout << "Input map perfectly created" << std::endl;
}

InputDatabase::~InputDatabase( void ) {
	return;
}

//Member function
void InputDatabase::OpenInputFile(const char* filename) {
	this->_file.open(filename, std::ios_base::in);
	if (!this->_file.is_open()) {
		throw this->exception;
	}
	return ;
}

void	InputDatabase::CheckParsing( void ) {
	std::string	str;

	getline(this->_file, str);
	if (!str.compare("date | value\n")) {
		std::cerr << "doesn't match" << std::endl;
		return ; //throw exception
	}
	while (getline(this->_file, str)) {
		if (!checkDate(str) || !checkSyntax(str) || !checkValue(str)) {
			std::cerr << "error while parsing input file" << std::endl;
			continue;
		}
		createIndexDatabase(str);
		std::cout << "OK" << std::endl;
	}
	std::cout << "Input file perfectly parsed!" << std::endl;
	return ;
}

bool InputDatabase::checkDate(const std::string& str) {
	size_t	i;

	i = 0;
	for (; i < 4; i++) {
		if (!isdigit(str[i]))
			return (false);
	}
	for (size_t j = 0; j < 2; j++) {
		if (str[i++] != '-')
			return (false);
		for (size_t k = 0; k < 2; k++) {
			if (!isdigit(str[i++]))
				return (false);
		}
	}
	for (size_t l = 0; l < i; l++) {
		std::cout << str[l];
	}
	return (true);
}

bool InputDatabase::checkSyntax(const std::string &str) {
	if (!str.compare(11, 3, " | "))
		return (false);
	return (true);
}

bool InputDatabase::checkValue(const std::string &str) {
	size_t		i, k;
	std::string	value;

	i = 13;
	k = i;
	while (str[i]) {
		i++;
	}
	value = str.substr(13, i - k - 1);
	for (size_t j = 0, l = 0; ; j++) {
		if (value[j] == '.') {
			if (++l > 1)
				return (false);
			j++;
		}
		if (!isdigit(value[j])) // faire attention au char \n
			return (false);
	}
	double n = atof(value.c_str());
	if (n < 0 && n > 1000)
		return (false);
	return (true);
}

void InputDatabase::createIndexDatabase( const std::string& str ) {
	std::pair<std::string, std::string> pair;

	pair.first = str.substr(0, 10);
	pair.second = str.substr(12, str.length() - 13);
	this->InputMap.insert(pair);
	std::cout << "Voici pair 1 = " << pair.first << "Voici pair 2 = " << pair.second << std::endl;
	return ;
}
