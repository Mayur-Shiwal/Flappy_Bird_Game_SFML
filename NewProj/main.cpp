#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Game.h"

using namespace sf;
using namespace std;

int main() {

	RenderWindow window(VideoMode(WinWidth, WinHeight), "FlappyBird");
	Game game(window);
	game.startGameLoop();

	return 0;
}