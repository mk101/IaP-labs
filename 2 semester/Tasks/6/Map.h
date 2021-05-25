#pragma once
#include <vector>
#include <iostream>
#include <random>
#include "Player.h"

enum class MapType: uint8_t {Empty, PlayerHead, PlayerBody, Food};

class Map {
private:
	size_t n;
	size_t m;
	std::vector<MapType> map;

	std::random_device rd;
	std::mt19937 mt;
	std::uniform_int_distribution<size_t> distributionX;
	std::uniform_int_distribution<size_t> distributionY;

	void ClearPlayer();
public:
	Map(size_t N, size_t M);

	const MapType& At(size_t y, size_t x) const;
	MapType& At(size_t y, size_t x);

	void AddFood();
	bool IsFoodAte() const;
	bool IsOutOfMap(const Player& player) const;
	void UpdatePlayer(const Player& player);
	void Draw() const;
};
