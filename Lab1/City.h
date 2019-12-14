#pragma once
#include <string>
#include <map>
#include <vector>

class City;
using map_t = std::vector<std::vector<City*>>;
using country_t = std::string;


class City
{
public:


	int x, y;
	country_t country;
	std::map<country_t, int> balance;
	std::map<country_t, int> tempBalance;
	bool checked = false;

private:
	std::map<std::string, int> calculateBalanceToTransport();
	void spendCoins(City* city, std::map<std::string, int> &balanceToTransport);

public:
	~City() {};
	City(std::string country, int x, int y) : country(country), x(x), y(y){
		balance[country] = 1000000;
	}

	void sendCoins(map_t map);
	void recieveCoins(country_t country, int coins);

	void endDay();

	bool isAllCoinstCollected(int coinsTypesNum) {
		return coinsTypesNum == balance.size();
	};
};