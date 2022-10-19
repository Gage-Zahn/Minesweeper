#include "Game.h"
#include "Random.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//------------Game Functions-----------
Game::Game(string configFile) {
	ifstream configs(configFile);
	unsigned int mines;
	string temp;
	getline(configs, temp);
	width = stoul(temp);
	getline(configs, temp);
	height = stoul(temp);
	getline(configs, temp);
	mines = stoul(temp);
	this->state = 1;
	this->debug = 0;
	this->totalBombs = mines;
	this->remainingBombs = mines;
	foundBombs = 0;
	clearedTiles = 0;

	board = new Tile[height * width];
	for (unsigned int col = 0; col < width; col++) {
		for (unsigned int row = 0; row < height; row++) {
			board[col*height +row] = Tile(0, col, row, *this);
		}
	}
	unsigned int placedBombs = 0;
	while (placedBombs != totalBombs) {
		int col = Random::Int(0, width-1);
		int row = Random::Int(0, height-1);
		if (board[col * height + row].bomb == 1) {
			continue;
		}
		board[col*height + row].bomb = 1;
		placedBombs++;
	}
	for (unsigned int i = 0; i < height * width; i++) {
		board[i].AdjecencyCheck(*this);
	}
}

Game::Game(string brdFile, short boardType, string configFile) {
	this->state = 1;
	this->debug = 0;
	this->totalBombs = 0;
	this->remainingBombs = 0;
	foundBombs = 0;
	clearedTiles = 0;

	ifstream configs(configFile);
	unsigned int mines = 0;
	string temp;
	getline(configs, temp);
	width = stoul(temp);
	getline(configs, temp);
	height = stoul(temp);
	getline(configs, temp);
	mines = stoul(temp);
	configs.close();

	board = new Tile[height * width];

	ifstream file(brdFile);
	if (!file.is_open())
		cout << "failed to open " << brdFile << '\n';
	else {
		unsigned int col = 0;
		unsigned int row = 0;
		string line;
		
		while (getline(file,line)) {
			for (char i : line) {
				bool armed = (i == '1');
				board[col * height + row] = Tile(armed, col, row, *this);
				totalBombs += armed;
				remainingBombs += armed;
				col++;
			}
			row++;
			col = 0;
		}	
	}
	for (unsigned int i = 0; i < height * width; i++) {
		board[i].AdjecencyCheck(*this);
	}
}

unsigned int Game::GetHeight() {
	return height;
}

unsigned int Game::GetWidth() {
	return width;
}

unsigned int Game::GetTotalBombs() {
	return totalBombs;
}

//------------Tile Functions-----------
Game::Tile::Tile() {
	bomb = 0;
	col = 0;
	row = 0;
	revealed = 0;
	adjecentBombs = 0;
	upRow = 0;
	downRow = 0;
	upCol = 0;
	downCol = 0;
	flagged = 0;
}

Game::Tile::Tile(bool bomb, unsigned int col, unsigned int row, Game game) {
	this->bomb = bomb;
	this->col = col;
	this->row = row;
	revealed = 0;
	adjecentBombs = 0;
	flagged = 0;
	upRow = 0;
	downRow = 0;
	upCol = 0;
	downCol = 0;
}

void Game::Tile::AdjecencyCheck(Game game) {

	unsigned int maxCol = game.GetWidth() - 1;
	unsigned int maxRow = game.GetHeight() - 1;
	if (this->bomb)
		adjecentBombs = 0;
	else {
		if (col + 1 <= maxCol)
			upCol = 1;
		if (row + 1 <= maxRow)
			upRow = 1;
		if (col - 1 >= 0 && col != 0)
			downCol = 1;
		if (row - 1 >= 0 && row != 0)
			downRow = 1;
		if (upCol) {
			adjecentBombs += game.board[(col + 1) * game.GetHeight() + row].bomb;
			if (upRow)
				adjecentBombs += game.board[(col + 1) * game.GetHeight() + row + 1].bomb;
			if (downRow)
				adjecentBombs += game.board[(col + 1) * game.GetHeight() + row - 1].bomb;
		}
		if (downCol) {
			adjecentBombs += game.board[(col - 1) * game.GetHeight() + row].bomb;
			if (upRow)
				adjecentBombs += game.board[(col - 1) * game.GetHeight() + row + 1].bomb;
			if (downRow)
				adjecentBombs += game.board[(col - 1) * game.GetHeight() + row - 1].bomb;
		}
		if (upRow)
			adjecentBombs += game.board[col * game.GetHeight() + row + 1].bomb;
		if (downRow)
			adjecentBombs += game.board[col * game.GetHeight() + row - 1].bomb;
	}
}

void Game::Tile::Reveal(Game game) {
	if (this->adjecentBombs == 0 && !this->flagged) {
		this->revealed = 1;
		if (upRow && !game.board[this->col * game.GetHeight() + this->row + 1].revealed)
			game.board[this->col * game.GetHeight() + this->row + 1].Reveal(game);
		if (downRow && !game.board[this->col * game.GetHeight() + this->row - 1].revealed)
			game.board[this->col * game.GetHeight() + this->row - 1].Reveal(game);
		if (upCol && !game.board[(this->col + 1) * game.GetHeight() + this->row].revealed)
			game.board[(this->col + 1) * game.GetHeight() + this->row].Reveal(game);
		if (downCol && !game.board[(this->col - 1) * game.GetHeight() + this->row].revealed)
			game.board[(this->col - 1) * game.GetHeight() + this->row].Reveal(game);
		if (downCol && upRow && !game.board[(this->col - 1) * game.GetHeight() + this->row + 1].revealed)
			game.board[(this->col - 1) * game.GetHeight() + this->row + 1].Reveal(game);
		if (downCol && downRow && !game.board[(this->col - 1) * game.GetHeight() + this->row - 1].revealed)
			game.board[(this->col - 1) * game.GetHeight() + this->row - 1].Reveal(game);
		if (upCol && downRow && !game.board[(this->col + 1) * game.GetHeight() + this->row - 1].revealed)
			game.board[(this->col + 1) * game.GetHeight() + this->row - 1].Reveal(game);
		if (upCol && upRow && !game.board[(this->col + 1) * game.GetHeight() + this->row + 1].revealed)
			game.board[(this->col + 1) * game.GetHeight() + this->row + 1].Reveal(game);
	}
	else if (!this->bomb && !this->flagged) {
		this->revealed = 1;
	}
}