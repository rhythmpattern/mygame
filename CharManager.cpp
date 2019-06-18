#include "CharManager.h"
#define LOG

CharManager* CharManager::pInstance = 0;

CharManager::CharManager()
{
  
   
}


void CharManager::Clear()
{
   //delete the chars
  std::vector<Character*>::iterator it = m_Chars.begin();
  for (it; it != m_Chars.end(); ++it)
  {
#ifdef LOG
    std::cout << "deleting entity id: " << (*it)->ID() << " of type "
              << GetNameOfType((*it)->EntityType()) << "(" << (*it)->EntityType() << ")" <<endl;
#endif

    delete *it;
  }
  

  m_Chars.clear();
 
}

void CharManager::Render()
{
  std::vector<Character*>::iterator curChar = m_Chars.begin();
  for (curChar; curChar != m_Chars.end(); ++curChar)
    {
      if ((*curChar)->isAlive())
   (*curChar)->draw();
    }
}

void CharManager::Update()
{
  bool bSpawnPossible = true;

   std::vector<Character*>::iterator curChar = m_Chars.begin();
  for (curChar; curChar != m_Chars.end(); ++curChar)
  {
    //if this bot's status is 'respawning' attempt to resurrect it from
    //an unoccupied spawn point
    if ((*curChar)->isSpawning() && bSpawnPossible)
    { 
      bSpawnPossible = AttemptToAddChar(*curChar);
    }
    
    //if this bot's status is 'dead' add a grave at its current location 
    //then change its status to 'respawning'
    else if ((*curChar)->isDead())
    { 
      //create a grave
      GraveManager::Instance()->AddGrave((*curChar)->Pos());

      //change its status to spawning
      (*curChar)->SetSpawning();
    }

    //if this bot is alive update it.
    else if ( (*curChar)->isAlive())
    { 
      (*curChar)->Update(); 
       
    }  
  } 
}


bool CharManager::AttemptToAddChar(Character* pChar)
{
  
  //make sure there are some spawn points available
  if (Game::Instance()->GetMap()->GetSpawnPoints().size() <= 0)
  {
    std::cout << ("Map has no spawn points!"); return false;
  }

  //we'll make the same number of attempts to spawn a bot this update as
  //there are spawn points
  int attempts = Game::Instance()->GetMap()->GetSpawnPoints().size();
  //g_screenLog->log(LL_INFO, "attempts = %d",attempts);

  while (--attempts >= 0)
  { 
    //select a random spawn point
    Vector2D pos = Game::Instance()->GetMap()->GetRandomSpawnPoint();

    //check to see if it's occupied
    std::vector<Character*>::const_iterator curChar = m_Chars.begin();

    bool bAvailable = true;

    for (curChar; curChar != m_Chars.end(); ++curChar)
    {
      //if the spawn point is unoccupied spawn a bot
      if (Vec2DDistance(pos, (*curChar)->Pos()) < (*curChar)->BRadius())
      {
        bAvailable = false;
      }
    }

    if (bAvailable)
    {  
      pChar->Spawn(pos);

      return true;   
    }
  }

  return false;
}


void CharManager::AddChars(unsigned int NumCharsToAdd)
{
     while (NumCharsToAdd--)
  {
    //create a bot. (its position is irrelevant at this point because it will
    //not be rendered until it is spawned)
    #ifdef LOG
    std::cout << "Creating new Character()\n";
    #endif
    //Character* rb = new Character(this, Vector2D(0,0));
    Character* rb =  GameObjectFactory::Instance()->create("Character");
    //Zombie* rb = new Zombie(this, Vector2D(0,0));

    rb->load();
    //switch the default steering behaviors on
    rb->GetSteering()->WallAvoidanceOn();
    rb->GetSteering()->SeparationOn();
    m_Chars.push_back(rb);
    //register the bot with the entity manager
     EntityMgr->RegisterEntity(rb);
   
    
#ifdef LOG
     std::cout << "Adding bot with ID " << rb->ID() << "\n";
#endif
} 
}

void CharManager::AddChar(Character* pChar)
 {m_Chars.push_back(pChar);}
