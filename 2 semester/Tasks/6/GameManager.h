#pragma once
#include <conio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Map.h"
#include "Player.h"

class GameManager {
private:
	size_t deltaTime;
	size_t score;
	Map map;
	Player player;
	bool isGameEnd;

	void ClearConsole() const;
	void Tick();
	void KeyPress();
	void DrawMap() const;
	void DrawUI() const;
public:
	GameManager(size_t n, size_t m, size_t playerX, size_t playerY, size_t playerSize, size_t deltaTime);
	void StartLoop();
	size_t GetResult() const;
};

