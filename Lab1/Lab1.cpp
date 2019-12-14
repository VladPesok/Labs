// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "City.h"
#include <iomanip>


int buildCountry(country_t country, int xl, int yl, int xh, int yh, map_t &map) {
	for (int i = xl; i < xh + 1; ++i)
	{
		for (int j = yl; j < yh + 1; ++j)
		{
			if (i > 0 && i < map.size()) {
				if (j > 0 && j < map[i].size()) {
					map[i][j] = new City(country, i, j);
				}
			}
		}
	}
	return (xh - xl + 1) * (yh - yl + 1);
}


void printMap(map_t map)
{
	for (int i = 0; i < map.size(); i++)
	{

		for (int j = 0; j < map[i].size(); j++)
		{
			std::cout << std::setw(10);
			if (map[i][j])
			{
					std::cout << map[i][j]->country;
			}
			else
			{
				std::cout << "null";
			}
		}
		std::cout << std::endl;
	}
}

void coinCycle(map_t map, std::map<std::string, int> countries)
{

	if (countries.size() == 0)
	{
		std::cout << "Go away" << std::endl;
		return;
	}

	if (countries.size() == 1)
	{
		std::cout << countries.begin()->first << " 0" << std::endl;
		return;
	}

	int checkedCountriesCounter = 0;
	std::map<std::string, int> checkedCitiesCounts;
	std::map<std::string, bool> checkedCountries;

	bool checked = false;
	int days = 0;
	while (checkedCountriesCounter < countries.size())
	{
		for (int i = 0; i < map.size(); ++i)
		{
			for (int j = 0; j < map[i].size(); j++)
			{
				if (map[i][j])
				{
					map[i][j]->sendCoins(map);
				}
			}
		}

		days++;

		for (int i = 0; i < map.size(); ++i) {
			for (int j = 0; j < map[i].size(); ++j) {
				if (map[i][j])
				{
					map[i][j]->endDay();
					if (!map[i][j]->checked && map[i][j]->isAllCoinstCollected(countries.size()))
					{
						std::string country = map[i][j]->country;
						if (checkedCitiesCounts.find(country) != checkedCitiesCounts.end())
						{
							checkedCitiesCounts[country]++;
						}
						else
						{
							checkedCitiesCounts[country] = 1;
						}
						map[i][j]->checked = true;
					}
				}
			}
		}

		for (std::map<std::string, int>::iterator it = checkedCitiesCounts.begin(); it != checkedCitiesCounts.end(); ++it) {
			if (it->second == countries[it->first])
			{
				if (checkedCountries.find(it->first) == checkedCountries.end())
				{
					std::cout << it->first << " " << days << std::endl;
					checkedCountriesCounter++;
					checkedCountries[it->first] = true;
				}
			}

		}
		if (!checked) {
			bool changed = false;
			for (int i = 0; i < map.size(); ++i)
			{
				for (int j = 0; j < map[i].size(); j++)
				{
					if (map[i][j])
					{
						if (map[i][j]->balance.size() > 1) {
							changed = true;
						}
					}
				}
			}
			if (!changed) {
				std::cout << "not valid";
				break;
			}
			checked = true;
		}
	}
}


int main()
{
	int x = 10;
	int y = 10;

	while (true) {
		int number;
		map_t map(x, std::vector<City*>(y));
		std::map <country_t, int> countries;
		std::cout << "Enter countries num:\n";
		std::cin >> number;
		if (number == 0) {
			break;
		}
		for (int i = 0; i < number; ++i) {
			std::cout << "Country:\n";
			std::string name;
			int xl, yl, xh, yh;
			std::cin >> name;
			std::cin >> xl;
			std::cin >> yl;
			std::cin >> xh;
			std::cin >> yh;
			countries[name] = buildCountry(name, xl, yl, xh, yh, map);
		}
		std::cout << "Cycle start\n";
		printMap(map);
		coinCycle(map, countries);
	}
	return 0;
}

