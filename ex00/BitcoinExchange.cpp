/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 02:55:34 by lomont            #+#    #+#             */
/*   Updated: 2026/01/25 18:10:59 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//Exception

const char* FileOpeningException::what( void ) const throw() {
	return ( "Error when trying to open the file, exiting program..." );
}

FileOpeningException::~FileOpeningException( void ) throw() {
	//std::cout << "Exception: FileOpeningException destructor called" << std::endl;
	return ;
}

const char* FileHeaderException::what( void ) const throw() {
	return ( "Wrong Header file, please insert precisely this header => " );
}

FileHeaderException::~FileHeaderException( void ) throw() {
	//std::cout << "Exception: FileHeaderException destructor called" << std::endl;
	return ;
}

//-----------------------------------------------------------------------------------------------

//Canonical form

BitcoinDatabase::BitcoinDatabase( void ) {
	//std::cout << "BitcoinDatabase constructor called" << std::endl;
	try
	{
		openDatabaseFile();
		createDatabaseMap();
	} catch(const FileOpeningException& e) {
		std::cerr << "Database file: " << e.what() << '\n';
		exit(1);
	} catch (FileHeaderException& e) {
		std::cerr << "Database file: " << e.what() << "'date,exchange_rate'" << std::endl;
		exit (1);
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		exit(1);
	}
	return ;
}

BitcoinDatabase::BitcoinDatabase( BitcoinDatabase & src ) {
	//std::cout << "BitcoinDatabase copy constructor called" << std::endl;
	(void) src;
	return ;
}

BitcoinDatabase & BitcoinDatabase::operator=( BitcoinDatabase & other) {
	//std::cout << "BitcoinDatabase assignment operator called" << std::endl;
	(void) other;
	return (*this);
}

BitcoinDatabase::~BitcoinDatabase( void ) {
	//std::cout << "BitcoinDatabase destructor called" << std::endl;
	this->_file.close();
	return ;
}

//Member functions

void	BitcoinDatabase::openDatabaseFile( void ) {
	this->_file.open("data.csv", std::ios_base::in);
	if (!_file.is_open()) {
		throw this->OpeningException;
	}
	return ;
}

void	BitcoinDatabase::createDatabaseMap( void ) {
	std::string		str;
	std::string		Key;
	std::string		Value;

	getline(this->_file, str);
	if (str != "date,exchange_rate")
		throw this->HeaderException;
	while (getline(this->_file, str)) {
		if (!BitcoinExchange::validateDate(str, 0, 0, 0))
			throw ( std::exception() );
		std::pair<std::string, std::string> pair;
		char	delimiter = str.find(',');
		pair.first = str.substr(0, delimiter);
		pair.second = str.substr(delimiter + 1, str.size() - 1);
		this->map.insert(pair);
	}
}


//-----------------------------------------------------------------------------------------------

//Canonical form

BitcoinExchange::BitcoinExchange( const char* str, BitcoinDatabase& BitcoinDatabase ) {
	try {
		OpenInputFile(str);
		CheckParsing(BitcoinDatabase.map);
	} catch (FileOpeningException& e) {
		std::cerr << "Input file: " << e.what() << std::endl;
		exit(1);
	} catch (FileHeaderException& e) {
		std::cerr << "Input file: " << e.what() << "'date | value'" << std::endl;
		exit (1);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	return ;
}

BitcoinExchange::BitcoinExchange( BitcoinExchange& src ) {
	//std::cout << "BitcoinExchange copy constructor called" << std::endl;
	(void) src;
	return ;
}

BitcoinExchange & BitcoinExchange::operator=( BitcoinExchange& other ) {
	//std::cout << "BitcoinExchange assignment operator called" << std::endl;
	(void) other;
	return (*this) ;
}

BitcoinExchange::~BitcoinExchange( void ) {
	return;
}

//Member function

void BitcoinExchange::OpenInputFile(const char* filename) {
	this->_file.open(filename, std::ios_base::in);
	if (!this->_file.is_open()) {
		throw this->OpeningException;
	}
	return ;
}

void	BitcoinExchange::CheckParsing( std::map<std::string, std::string> database ) {
	std::string	str;
	size_t		index = 0;

	getline(this->_file, str);
	if (str != "date | value")
		throw this->HeaderException;
	while (getline(this->_file, str)) {
		if (!checkDate(str, &index) || !checkSyntax(str, &index) || !checkValue(str, &index) || !validateDate(str, 0, 0, 0)) {
			continue;
		}
		printExchange(str, database);
	}
	return ;
}

bool BitcoinExchange::checkDate(const std::string& str, size_t* index) {
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
	*index = i;
	validateDate(str, 0, 0, 0);
	return (true);
}

bool	BitcoinExchange::checkSyntax(const std::string &str, size_t* index) { //error when comparing inexistant position
	if (str.size() < 13)
		return (false);
	if (!str.compare(11, 3, " | "))
		return (false);
	*index += 3;
	return (true);
}

bool	BitcoinExchange::checkValue(const std::string &str, size_t* index) {
	size_t		i, k;
	std::string	value;

	i = *index;
	k = i;
	value = str.substr(k, str.size());
	for (size_t j = 0, l = 0; j < value.size() - 1 ; j++) {
		if (value[j] == '.') {
			if (++l > 1)
				return (false);
			j++;
		}
		if (!isdigit(value[j])) {
			if (value[j] == '-')
				std::cerr << "Error: not a positive number." << std::endl;
			return (false);
		}
	}
	double n = atof(value.c_str());
	if (n < 0 )  {
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	else if (n > 1000) {
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}
	*index = i;
	return (true);
}

bool	BitcoinExchange::validateDate(const std::string& str, int d, int m, int y) {
	struct tm t = {};
	time_t	realtime;
	char delimiter;
	std::istringstream is(str);

	if (is >> y >> delimiter >> m >> delimiter >> d) {
		t.tm_mday = d;
		t.tm_mon = m - 1;
		t.tm_year = y - 1900;
		t.tm_isdst = -1;
	}
	realtime = mktime(&t);
	const struct tm *time = localtime(&realtime);
	if (time->tm_mday == d && time->tm_mon == m - 1 && time->tm_year == y - 1900) {
		return (true);
	}
	std::cerr << "Error: bad input => " << str << std::endl;
	return (false);
}

void BitcoinExchange::printExchange(const std::string& str, std::map<std::string, std::string> database ) const {
	std::string										date;
	std::string										nbr;
	std::map<std::string, std::string>::iterator	it;

	date = str.substr(0, 10);
	nbr = str.substr(13, str.size());
	it = database.upper_bound(date);
	it--;
	std::cout << date << " => " << nbr << " = " << atof(it->second.c_str()) * atof(nbr.c_str()) << std::endl;
}
