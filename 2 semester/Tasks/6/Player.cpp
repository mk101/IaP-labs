#include "Player.h"

void ChangeCoordR(size_t& x, size_t& y, Direction dir) {
	switch (dir) {
	case Direction::Down:
		y--;
		break;
	case Direction::Up:
		y++;
		break;
	case Direction::Left:
		x++;
		break;
	case Direction::Right:
		x--;
		break;
	}
}

Player::Player(size_t x, size_t y, size_t size, Direction dir) : size(size), dir(dir), ceils() {
	size_t xx, yy;
	xx = x;
	yy = y;
	
	for (int i = 0; i < size; i++) {
		ceils.push_back({ xx, yy });
		ChangeCoordR(xx, yy, dir);
	}
}

void Player::Move() {
	/*auto iter = ceils.rbegin();
	while (iter != ceils.rend() + 1) {
		iter->x = (iter + 1)->x;
		iter->y = (iter + 1)->y;
		iter++;
	}*/

	for (auto iter = ceils.rbegin(); iter != ceils.rend() - 1; iter++) {
		iter->x = (iter + 1)->x;
		iter->y = (iter + 1)->y;
	}

	switch (dir) {
	case Direction::Down:
		ceils.at(0).y++;
		break;
	case Direction::Up:
		ceils.at(0).y--;
		break;
	case Direction::Left:
		ceils.at(0).x--;
		break;
	case Direction::Right:
		ceils.at(0).x++;
		break;
	}
}

void Player::ChangeDirection(Direction d) {
	if ((uint8_t)dir % 2 == (uint8_t)d % 2) {
		return;
	}
	dir = d;
}

const MapCeil& Player::GetHead() const {
	return ceils.at(0);
}

const std::vector<MapCeil>& Player::GetPlayer() const {
	return ceils;
}

void Player::AddBody() {
	const auto& last = ceils.back();
	const auto& secLast = ceils.at(ceils.size() - 2);
	Direction tailDir = dir;
	size_t x, y;

	if (last.x < secLast.x) {
		tailDir = Direction::Right;
	} else if (last.x > secLast.x) {
		tailDir = Direction::Left;
	} else if (last.y < secLast.y) {
		tailDir = Direction::Up;
	} else if (last.y > secLast.y) {
		tailDir = Direction::Down;
	}

	x = last.x;
	y = last.y;

	ChangeCoordR(x, y, tailDir);
	ceils.push_back({ x, y });
	size++;
}

bool Player::IsPlayerCollide() const {
	auto iter = ceils.begin();
	const auto& head = *iter;
	iter++;
	while (iter != ceils.end()) {
		if (iter->x == head.x && iter->y == head.y) {
			return true;
		}

		iter++;
	}

	return false;
}

size_t Player::GetSize() const {
	return size;
}
