#include "DB.h"

DB::DB(std::string name) {
	CreateDirectory("DB", NULL);
	this->name = name;
	std::fstream db;
	db.open(".\\DB\\" + name);
	if (db.is_open())
		load(name);
	else
		create(name);
}

void DB::load(std::string name) {
	std::fstream DB;
	DB.open(".\\DB\\" + name);
	std::string table;
	while (getline(DB, table)) {
		this->tables[table] = Table(name + "_" + table);
	}
}

void DB::create(std::string name) {
	this->name = name;
	this->update();
}

void DB::add(std::string name, std::vector<std::string> fields) {
	this->tables[name] = Table(this->name + "_" + name, fields);
	this->update();
}

void DB::update() const {
	std::ofstream db;
	db.open(".\\DB\\" + this->name);
	for (const std::pair<const std::string, Table>& table : this->tables) {
		db << table.first << '\n';
		table.second.update();
	}
	db.close();
}

void DB::remove(std::vector<std::string> tables) {
	for (std::string tname : tables) {
		this->tables[tname].remove();
		this->tables.erase(tname);
	}
	this->update();
}

bool DB::write(std::string name, std::vector<std::string> args) {
	if (this->tables.find(name) == end(this->tables))
		return false;
	this->tables[name].write(args);
}

std::vector<std::vector<std::string>> DB::select(std::string from, std::vector<std::pair<std::string, std::string>> equalities, std::vector<std::string> fields) {
	return this->tables[from].select(equalities, fields);
}

Table::Table(std::string name, std::vector<std::string> fields) {
	CreateDirectory("tables", NULL);

	this->name = name;
	std::fstream table;
	table.open(".\\tables\\" + name);
	if (table.is_open()) {
		this->load(name);
	} else {
		this->create(name, fields);
	}
}

void Table::load(std::string name) {
	std::fstream table;
	table.open(".\\tables\\" + name);
	std::string actual, line;
	getline(table, line);
	int i = 1;
	for (const char& a : line) {
		if (a == '~' && actual.size() > 0) {
			this->fields[actual] = i;
			this->r_fields[i] = actual;
			i++;
			actual.clear();
		} else if (a != '~')
			actual += std::string(1, a);
	}
	actual.clear();

	while (getline(table, line)) {
		this->data.push_back(std::vector<std::string>());
		for (const char& a : line) {
			if (a == '~') {
				this->data.back().push_back(actual);
				actual.clear();
			} else {
				actual += std::string(1, a);
			}
		}
	}
	table.close();
}

void Table::create(std::string name, std::vector<std::string> fields) {
	for (int i = 0; i < fields.size(); i++) {
		this->fields[fields[i]] = i + 1;
		this->r_fields[i + 1] = fields[i];
	}
	this->update();
}

bool Table::write(std::vector<std::string> data) {
	std::cout << this->fields.size() << ' ' << data.size() << '\n';
	if (data.size() != this->fields.size())
		return false;
	this->data.push_back(data);
	this->update();
	return true;
}

void Table::remove() {
	std::remove(std::string(".\\tables\\" + this->name).c_str());
}

void Table::update() const {
	std::ofstream table;
	table.open(".\\tables\\" + this->name);
	for (int i = 1; i <= this->r_fields.size(); i++) {
		table << this->r_fields.at(i) << '~';
	}
	table << '\n';
	for (const std::vector<std::string> &entry : data) {
		for (const std::string& field : entry) {
			table << field << '~';
		}
		table << '\n';
	}
	table.close();
}

std::vector<std::vector<std::string>> Table::select(std::vector<std::pair<std::string, std::string>> equalities, std::vector<std::string> fields) {
	std::vector<std::vector<std::string>> raw_results = this->data;
	for (const std::pair<std::string, std::string>& equality : equalities) {
		if (this->fields.find(equality.first) == end(this->fields)) {
			throw "No existe ese campo";
		}
	}
	for (int i = 0; i < raw_results.size(); i++) {
		std::vector<std::string>& actual = raw_results[i];
		for (const std::pair<std::string, std::string>& equality : equalities) {
			if (utils::to_lower(actual[this->fields[equality.first] - 1]) != utils::to_lower(equality.second)) {
				raw_results.erase(raw_results.begin() + i);
				i--;
				break;
			}
		}
	}

	// format
	if (fields.empty())
		return raw_results;

	std::vector<std::vector<std::string>> results;
	for (std::vector<std::string> raw_result : raw_results) {
		std::vector<std::string> result;
		for (const std::string & field : fields) {
			result.push_back(raw_result[this->fields[field] - 1]);
		}
		results.push_back(result);
	}
	return results;
}