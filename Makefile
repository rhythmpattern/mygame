CC = g++
CFLAGS = -g -w

OBJS = Armory/Weapon.o PauseState.o CharManager.o GraveManager.o Armory/Melee.o Room.o ProjectileManager.o Zombie.o PlayerSteering.o InputHandler.o Player.o ZombieWeaponSystem.o Goals/Goal_Think_Zombie.o Goals/Goal_Zombie.o Goals/Goal_Pause.o Goals/Goal_FlyWander.o Goals/Goal_FlyExplore.o Goals/Goal_Think_Fly.o Goals/Goal_Fly.o BLayer.o TileLayer.o GameStateMachine.o debug.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o TextureManager.o StateParser.o GameObjectFactory.o PlayState.o LevelParser.o base64.o Level.o ObjectLayer.o 2D/Vector2D.o Game/Entity.o Game/EntityManager.o Character.o Triggers/Trigger_HealthGiver.o Triggers/Trigger_SoundNotify.o Triggers/Trigger_WeaponGiver.o Navigation/PathPlanner.o SteeringBehaviors.o TargetingSystem.o WeaponSystem.o SensoryMemory.o Messaging/MessageDispatcher.o Map.o Game.o Time/CrudeTimer.o UserOptions.o Goals/AttackTargetGoal_Evaluator.o Goals/ExploreGoal_Evaluator.o Goals/Feature.o Goals/Goal_AttackTarget.o Goals/Goal_DodgeSideToSide.o Goals/Goal_Explore.o Goals/Goal_FollowPath.o Goals/Goal_GetItem.o Goals/Goal_HuntTarget.o Goals/Goal_MoveToPosition.o Goals/Goal_NegotiateDoor.o Goals/Goal_SeekToPosition.o Goals/Goal_Think.o Goals/Goal_TraverseEdge.o Goals/Goal_Types.o Goals/Goal_Wander.o Armory/Shooter.o Armory/Projectile.o Armory/Projectile_Shot.o misc/FrameCounter.o Door.o GraveMarkers.o Fuzzy/FuzzyModule.o Fuzzy/FuzzyOperators.o Fuzzy/FuzzySet_LeftShoulder.o Fuzzy/FuzzySet_RightShoulder.o Fuzzy/FuzzySet_Singleton.o Fuzzy/FuzzySet_Triangle.o Fuzzy/FuzzyVariable.o Scriptor.o
SRCS = $(OBJS:.o=.cpp)
LOCALLIBDIR = /SDL2
LDFLAGS = -L$(LOCALLIBDIR) -ggdb3
LDLIBS = -lSDL2 -lSDL2_image -lz

MAIN = debug
all:	$(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LDFLAGS) $(LDLIBS)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@ 
clean:
	$(RM) *.o */*.o

