/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 02:55:34 by lomont            #+#    #+#             */
/*   Updated: 2026/01/25 16:06:19 by lomont           ###   ########.fr       */
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

//Canonical form

BitcoinDatabase::BitcoinDatabase( void ) : exception(FileOpeningException()) {
	//std::cout << "BitcoinDatabase constructor called" << std::endl;
	try
	{
		openDatabaseFile();
		createDatabaseMap();
	}
	catch(const FileOpeningException& e)
	{
		std::cerr << "Database file: " << e.what() << '\n';
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return ;
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
		//std::cout << "Can't open data.csv" << std::endl;
		throw this->exception;
	}
	//std::cout << "_file opened!" << std::endl;
	return ;
}

void	BitcoinDatabase::createDatabaseMap( void ) {
	std::string		str;
	std::string		Key;
	std::string		Value;

	getline(this->_file, str);
	while (getline(this->_file, str)) {
		//std::cout << "index end of string = " << str.size() << std::endl;
		if (!validateDate(str, 0, 0, 0))
			throw (std::exception());
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

InputDatabase::InputDatabase( const char* str, BitcoinDatabase& BitcoinDatabase ) {
	try {
		OpenInputFile(str);
		CheckParsing(BitcoinDatabase.map);
		//std::cout << "Input map perfectly created" << std::endl;
		//for (std::map<std::string, std::string>::iterator it = InputMap.begin(); it != InputMap.end(); it++) {
			//std::cout << "Voici pair 1 = '" << it->first << "'" << " Voici pair 2 = '" << it->second << "'" << std::endl;
		//}
	} catch (FileOpeningException& e) {
		std::cerr << "Input file: " << e.what() << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return ;
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

void	InputDatabase::CheckParsing( std::map<std::string, std::string> database ) {
	std::string	str;
	size_t		index = 0;

	getline(this->_file, str);
	if (!str.compare("date | value\n")) {
		//std::cerr << "doesn't match" << std::endl;
		return ; //throw exception
	}
	while (getline(this->_file, str)) {
		if (!checkDate(str, &index) || !checkSyntax(str, &index) || !checkValue(str, &index) || !validateDate(str, 0, 0, 0)) {
			//std::cerr << "error while parsing input file" << std::endl;
			continue;
		}
		std::string _date = str.substr(0, 10);
		std::string _nbr = str.substr(13, str.size());

		std::map<std::string, std::string>::iterator it;

		it = database.upper_bound(_date);
		it--;

		//std::cout.precision(2);
		std::cout << _date << " => " << _nbr << " = " << atof(it->second.c_str()) * atof(_nbr.c_str()) << std::endl;

		//createIndexDatabase(str);
		//std::cout << "OK" << std::endl;
	}
	//std::cout << "Input file perfectly parsed!" << std::endl;
	return ;
}

bool InputDatabase::checkDate(const std::string& str, size_t* index) {
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
	//debug
	// for (size_t l = 0; l < i; l++) {
	// 	std::cout << str[l];
	// }
	*index = i;
	validateDate(str, 0, 0, 0);
	return (true);
}

bool InputDatabase::checkSyntax(const std::string &str, size_t* index) { //error when comparing inexistant position
	if (str.size() < 13)
		return (false);
	if (!str.compare(11, 3, " | "))
		return (false);
	*index += 3;
	return (true);
}

bool InputDatabase::checkValue(const std::string &str, size_t* index) {
	size_t		i, k;
	std::string	value;

	i = *index;
	k = i;
	value = str.substr(k, str.size());
	//std::cout << "Value = '" << value << "'" << std::endl;
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

void InputDatabase::createIndexDatabase( const std::string& str ) {
	std::pair<std::string, std::string> pair;

	pair.first = str.substr(0, 10);
	pair.second = str.substr(13);
	this->InputMap.insert(pair);
	//std::cout << "Voici pair 1 = '" << pair.first << "'" << " Voici pair 2 = '" << pair.second << "'" << std::endl;
	return ;
}

//validateDate
bool	validateDate(const std::string& str, int d, int m, int y) {
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
	//std::cout << "Here d = " << d << " delimiter = " << delimiter << "m = " << m << "delimiter = " << delimiter << "y = " << y << std::endl;
	realtime = mktime(&t);
	const struct tm *time = localtime(&realtime);
	//std::cout << "Here timeday = " << time->tm_mday << " timemonth = "<< time->tm_mon << " timeyear" << time->tm_year << std::endl;
	if (time->tm_mday == d && time->tm_mon == m - 1 && time->tm_year == y - 1900) {
		//std::cout << "Date corresponding" << std::endl;
		return (true);
	}
	std::cerr << "Error: bad input => " << str << std::endl;
	return (false);
}

//-----------------------------------------------------------------------------------------------

//canonical form

// BitcoinExchange::BitcoinExchange( BitcoinDatabase& BitcoinDatabase, InputDatabase& InputDatabase ) {
// 	try
// 	{
// 		findDate(BitcoinDatabase.map, InputDatabase.InputMap);
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}

// 	return ;
// }

// BitcoinExchange::~BitcoinExchange( void ) {
// 	return ;
// }


// void BitcoinExchange::findDate(std::map<std::string, std::string> database, std::map<std::string, std::string> input) {
// 	std::string	databaseDate;
// 	std::string	inputDate;

// 	(void)input;
// 	std::map<std::string, std::string>::iterator it;

// 	for (std::map<std::string, std::string>::iterator itt = input.begin(); itt != input.end(); itt++) {
// 		it = database.upper_bound(itt->first);
// 		it--;
// 		//std::cout << it->first << " and " << itt->first << std::endl;
// 		std::cout.precision(2);
// 		std::cout << itt->first << " => " << itt->second << " = " << atof(it->second.c_str()) * atof(itt->second.c_str()) << std::endl;
// 	}

// }
