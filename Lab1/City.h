#pragma once
#include <string>
#include <map>
#include <vector>

constexpr auto INIT_BALANCE = 1000000;

class City;
using map_t = std::vector<std::vector<City*>>;
using country_t = std::string;


class City
{
public:


	int x, y;
	const country_t country;
	std::map<country_t, int> balance;
	std::map<country_t, int> tempBalance;
	bool checked = false;

private:
	std::map<country_t, int> calculateBalanceToTransport();
	void spendCoins(City* city, std::map<country_t, int> &balanceToTransport);

public:
	~City() {};
	City(country_t country, int x, int y) : country(country), x(x), y(y){
		balance[country] = INIT_BALANCE;
	}

	void sendCoins(map_t map);
	void recieveCoins(country_t country, int coins);

	void endDay();

	bool isAllCoinstCollected(int coinsTypesNum) {
		return coinsTypesNum == balance.size();
	};
};
