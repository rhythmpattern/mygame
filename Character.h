#ifndef CHARACTER_H
#define CHARACTER_H

#include "Game/MovingEntity.h"
#include <vector>
#include <iosfwd>
#include <map>
#include "misc/utils.h"
#include "TargetingSystem.h"
#include "WeaponSystem.h"
#include "LoadParams.h"
#include "ZombieWeaponSystem.h"
#include "GameObjectFactory.h"
#include "ObjectEnumerations.h"

class Game;
class Steering;
class PathPlanner;
class Regulator;
class Weapon;
class Character;
class Goal_Think;
class SensoryMemory;
class WeaponSystem;
class Goal_Think_Zombie;
class Goal_Think;
class BaseCreator;
class Character : public MovingEntity{

	protected: 


		enum Status{alive, dead, spawning};
		
		
		Status                m_Status;	
		Game*                    m_pWorld;
		Goal_Think*		m_pBrain;
		SensoryMemory*		m_pSensoryMem;
		bool			m_bPossessed ;
		TargetingSystem*	m_pTargSys;
		Steering*		m_pSteering;
		PathPlanner*		m_pPathPlanner;
		int 			m_iHealth;
		int 			m_iMaxHealth;
		int			m_iScore;
		Vector2D		m_vFacing;
		double 			m_dFieldOfView;
		int 			m_iNumUpdatesHitPersistant;
		bool			m_bHit;
  		WeaponSystem*                m_pWeaponSys;
		std::vector<Vector2D>	m_vecBotVB;
		std::vector<Vector2D>	m_vecBotVBTrans;
		void UpdateMovement();
		void SetUpVertexBuffer();
                		
		
		
		 Regulator*                         m_pWeaponSelectionRegulator;
  Regulator*                         m_pGoalArbitrationRegulator;
  Regulator*                         m_pTargetSelectionRegulator;
  Regulator*                         m_pTriggerTestRegulator;
  Regulator*                         m_pVisionUpdateRegulator;

		


	public : 


		Character(Game* world, Vector2D pos);
 Character():MovingEntity(){}

		void load();
		virtual void draw();
		virtual ~Character();

	
	       void handleinput();
		void Update();
	     	bool HandleMessage(const Telegram& msg);
		void Write(std::ostream& os)const{}
		void Read(std::ifstream& is) {}
		bool RotateFacingTowardPosition(Vector2D target);
		int Health()const{return m_iHealth;}
		int MaxHealth(unsigned int val);
		int MaxHealth()const{return m_iMaxHealth;}
		void ReduceHealth(unsigned int val);
		void IncreaseHealth(unsigned int val);
		void RestoreHealthToMaximum();
		int Score()const{return m_iScore;}
		void IncrementScore(){++m_iScore;}
		Vector2D Facing()const{return m_vFacing;}
		double FieldOfView()const{return m_dFieldOfView;}
		bool		isPossessed()const{return m_bPossessed;}
		bool isDead()const{return m_Status == dead;}
		bool isAlive()const{return m_Status == alive;}
		bool isSpawning()const{return m_Status == spawning;}
		void SetSpawning(){m_Status = spawning;}
		void SetDead(){m_Status = dead;}
		void SetAlive(){m_Status = alive;}
		double CalculateTimeToReachPosition(Vector2D pos)const;
		bool isAtPosition(Vector2D pos) const;

		void FireWeapon(Vector2D pos);
		void ChangeWeapon(unsigned int type);
		void TakePossession();
		void Exorcise();
		void Spawn(Vector2D pos);
		bool isReadyForTriggerUpdate()const;
		bool hasLOSto(Vector2D pos)const;
		bool canWalkTo(Vector2D pos)const;
		bool canWalkBetween(Vector2D from, Vector2D to)const;
		bool canStepLeft(Vector2D& PositionOfStep)const;
		bool canStepRight(Vector2D& PositionOfStep)const;
		
  		bool canStepForward(Vector2D& PositionOfStep)const;
  		bool canStepBackward(Vector2D& PositionOfStep)const;
		
		Game* const GetWorld(){return m_pWorld;}
		Steering* const GetSteering(){return m_pSteering;}
		Goal_Think* const GetBrain(){return m_pBrain;}
		const TargetingSystem* const GetTargetSys()const{return m_pTargSys;}
		PathPlanner* const           GetPathPlanner(){return m_pPathPlanner;}
		TargetingSystem* const GetTargetSys(){return m_pTargSys;}
		Character* const GetTargetBot()const{return m_pTargSys->GetTarget();}
		SensoryMemory* const GetSensoryMem()const{return m_pSensoryMem;}
		 WeaponSystem* const          GetWeaponSys()const{return m_pWeaponSys;}

	    

};

class CharacterCreator : public BaseCreator
{
  Character* createGameObject() const
  {
    return new Character();
  }
};



#endif
