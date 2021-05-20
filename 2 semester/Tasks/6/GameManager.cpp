#include "GameManager.h"

void GameManager::ClearConsole() const {
	system("cls");
}

void GameManager::Tick() {
	KeyPress();
	if (map.IsFoodAte()) {
		score++;
		player.AddBody();
		map.UpdatePlayer(player);
		map.AddFood();
	}
	map.UpdatePlayer(player);
	player.Move();
	DrawMap();
	DrawUI();
}

void GameManager::KeyPress() {
	if (_kbhit()) {
		char k = _getch();
		switch (k) {
		case 'a':
			player.ChangeDirection(Direction::Left);
			break;
		case 'd':
			player.ChangeDirection(Direction::Right);
			break;
		case 'w':
			player.ChangeDirection(Direction::Up);
			break;
		case 's':
			player.ChangeDirection(Direction::Down);
			break;
		}
	}
}

void GameManager::DrawMap() const {
	map.Draw();
}

void GameManager::DrawUI() const {
	std::wcout << L"Score: " << score << std::endl << L"Size: " << player.GetSize() << std::endl;
}

GameManager::GameManager(size_t n, size_t m, size_t playerX, size_t playerY, size_t playerSize, size_t deltaTime)
	: map(n,m), player(playerX, playerY, playerSize, Direction::Left), deltaTime(deltaTime), isGameEnd(false), score(0) {}

void GameManager::StartLoop() {
	map.UpdatePlayer(player);
	map.AddFood();
	while (!isGameEnd) {
		ClearConsole();
		Tick();
		if (player.IsPlayerCollide()) {
			isGameEnd = true;
		} else if (map.IsOutOfMap(player)) {
			isGameEnd = true;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(deltaTime));
	}
}

size_t GameManager::GetResult() const {
	return score;
}
