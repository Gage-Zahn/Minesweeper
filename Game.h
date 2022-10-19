#include <vector>
#include <string>
using namespace std;

class Game{
	class Tile {
	public:
		bool bomb;
		bool revealed;
		bool flagged;
		short adjecentBombs;
		unsigned int col;
		unsigned int row;
		bool upRow;
		bool downRow;
		bool upCol;
		bool downCol;
		Tile(bool bomb, unsigned int col, unsigned int row, Game game);
		Tile();
		void AdjecencyCheck(Game game);
		void Reveal(Game game);
	};
	
	unsigned int totalBombs;
	unsigned int height;
	unsigned int width;

public:
	Tile* board;
	Game(string configFile);
	Game(string brdFile, short boardType, string configFile);
	unsigned int GetHeight();
	unsigned int GetWidth();
	unsigned int GetTotalBombs();
	unsigned int foundBombs;
	unsigned int clearedTiles;
	bool debug;
	int remainingBombs;
	short state; // 0 lose, 1 playing, 2 win
};