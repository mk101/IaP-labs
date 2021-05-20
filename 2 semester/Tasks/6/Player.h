#pragma once
#include <vector>

enum class Direction : uint8_t {Left, Up, Right , Down};

struct MapCeil {
	size_t x;
	size_t y;
};

class Player {
private:
	std::vector<MapCeil> ceils;
	size_t size;
	Direction dir;
public:
	Player(size_t x, size_t y, size_t size, Direction dir);
	void Move();
	void ChangeDirection(Direction d);
	bool IsPlayerCollide() const;
	size_t GetSize() const;
	const MapCeil& GetHead() const;
	const std::vector<MapCeil>& GetPlayer() const;
	void AddBody();
};
