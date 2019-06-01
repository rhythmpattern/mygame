#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>


class Room
{
 public:
  Room(std::string mapName);
  ~Room();
  void Update();
  void Render();

 private:
  void clear();
};


#endif
