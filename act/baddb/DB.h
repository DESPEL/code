#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstdio>
#include <Windows.h>

#include "Utils.h"

struct Table {
	std::string name;
	std::unordered_map<std::string, int> fields;
	std::unordered_map<int, std::string> r_fields;
	std::vector<std::vector<std::string>> data;

	Table(){}
	Table(std::string, std::vector<std::string> = {});

	void update() const;
	void load(std::string);
	void create(std::string, std::vector<std::string>);
	void remove();
	bool write(std::vector<std::string>);

	std::vector<std::vector<std::string>> select(std::vector<std::pair<std::string, std::string>>, std::vector<std::string> = {});
};

struct DB {
	std::string name;
	std::unordered_map<std::string, Table> tables;

	DB(std::string);
	DB(){}

	void update() const;
	void load(std::string);
	void add(std::string, std::vector<std::string> = {});
	void create(std::string);
	void remove(std::vector<std::string>);
	bool write(std::string, std::vector<std::string>);

	// select (fields) from (table) where (argsequal)
	std::vector<std::vector<std::string>> select(std::string, std::vector<std::pair<std::string, std::string>>, std::vector<std::string> = {});
};