#ifndef LEVEL_COMMAND_H
#define LEVEL_COMMAND_H

class Level;
class Room;

class LevelCommand {
 public :
  LevelCommand (Level* pLevel , Room* m_pRoom);
  ~LevelCommand();

};

#endif
