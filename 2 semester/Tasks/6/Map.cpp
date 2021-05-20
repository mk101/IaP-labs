#include "Map.h"

void Map::ClearPlayer() {
	for (auto& c : map) {
		if (c == MapType::PlayerBody || c == MapType::PlayerHead) {
			c = MapType::Empty;
		}
	}
}

Map::Map(size_t N, size_t M) : n(N), m(M), map(N*M, MapType::Empty) {}

const MapType& Map::At(size_t y, size_t x) const {
	return map.at(y * n + x);
}

MapType& Map::At(size_t y, size_t x) {
	return map.at(y * n + x);
}

void Map::AddFood() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<size_t> distributionX(0, m);
	std::uniform_int_distribution<size_t> distributionY(0, n);

	MapCeil food = { distributionX(mt), distributionY(mt) };
	while (At(food.y, food.x) != MapType::Empty) 	{
		MapCeil food = { distributionX(mt), distributionY(mt) };
	}

	At(food.y, food.x) = MapType::Food;
}

bool Map::IsFoodAte() const {
	for (const auto& c : map) {
		if (c == MapType::Food) {
			return false;
		}
	}

	return true;
}

bool Map::IsOutOfMap(const Player& player) const {
	return player.GetHead().x < 0 || player.GetHead().x >= m
		|| player.GetHead().y < 0 || player.GetHead().y >= n;
}

void Map::UpdatePlayer(const Player& player) {
	ClearPlayer();
	auto& ceils = player.GetPlayer();
	auto iter = ceils.begin();

	At(iter->y, iter->x) = MapType::PlayerHead;
	iter++;

	while (iter != ceils.end()) {
		At(iter->y, iter->x) = MapType::PlayerBody;
		iter++;
	}
}

void Map::Draw() const {
	for (int i = 0; i < m + 2; i++) {
		std::wcout << L"-";
	}

	std::wcout << std::endl;

	for (int i = 0; i < n; i++) {
		std::wcout << L"|";
		for (int j = 0; j < m; j++) {
			switch (At(i, j)) {
			case MapType::Empty:
				std::wcout << L" ";
				break;
			case MapType::Food:
				std::wcout << L"F";
				break;
			case MapType::PlayerBody:
				std::wcout << L"o";
				break;
			case MapType::PlayerHead:
				std::wcout << L"\x1B[31mO\033[0m";
				break;
			}
		}
		std::wcout << L"|" << std::endl;
	}
	for (int i = 0; i < m + 2; i++) {
		std::wcout << L"-";
	}
}
