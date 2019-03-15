#include <iostream>
#include "Game.h"
#include "Map.h"


int main() { Game* game = new Game(); Map* map = game->GetMap(); game->Update(); game->Update();
std::cout << "Hello World" << map->GetSizeY() ;
 return 0;
}
