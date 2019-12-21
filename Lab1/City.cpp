#include "pch.h"
#include "City.h"

#include <iostream>


void City::sendCoins(map_t map) {
	std::map<country_t, int> balanceToTransport = calculateBalanceToTransport();

	if (x < map.size() - 1 && map[x + 1][y]) {
		spendCoins(map[x + 1][y], balanceToTransport);
	}

	if (x > 0 && map[x - 1][y]) {
		spendCoins(map[x - 1][y], balanceToTransport);
	}

	if (y < map.at(x).size() - 1 && map[x][y + 1]) {
		spendCoins(map[x][y + 1], balanceToTransport);
	}

	if (y > 0 && map[x][y - 1]) {
		spendCoins(map[x][y - 1], balanceToTransport);
	}
}

void City::recieveCoins(country_t country, int coins)
{
	if (tempBalance.find(country) != tempBalance.end()){
		tempBalance[country] += coins;
	} else {
		tempBalance[country] = coins;
	}
}

void City::endDay()
{
	for (auto& it : tempBalance) {
		if (balance.find(it.first) != balance.end())
		{
			balance[it.first] += it.second;
		}
		else
		{
			balance[it.first] = it.second;
		}
		it.second = 0;
	}
}

std::map<country_t, int> City::calculateBalanceToTransport()
{
	
	std::map<country_t, int> balanceToTransport;
	for (auto const& x : balance)
	{
		if (static_cast<int>(x.second / 1000) != 0) {
			balanceToTransport[x.first] = cash;
		}
	}

	return balanceToTransport;
}

void City::spendCoins(City* city, std::map<country_t, int> &balanceToTransport)
{
	for (auto& e : balanceToTransport) {
		city->recieveCoins(e.first, e.second);
		balance[e.first] -= e.second;
	}
}



