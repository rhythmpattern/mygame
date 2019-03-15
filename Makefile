CC = g++
CFLAGS = -g

OBJS = debug2.o 2D/Vector2D.o Game/Entity.o Game/EntityManager.o Character.o Triggers/Trigger_HealthGiver.o Triggers/Trigger_SoundNotify.o Triggers/Trigger_WeaponGiver.o Navigation/PathPlanner.o SteeringBehaviors.o TargetingSystem.o WeaponSystem.o SensoryMemory.o Messaging/MessageDispatcher.o Map.o Game.o Time/CrudeTimer.o UserOptions.o Goals/AttackTargetGoal_Evaluator.o Goals/ExploreGoal_Evaluator.o Goals/Feature.o Goals/Goal_AttackTarget.o Goals/Goal_DodgeSideToSide.o Goals/Goal_Explore.o Goals/Goal_FollowPath.o Goals/Goal_GetItem.o Goals/Goal_HuntTarget.o Goals/Goal_MoveToPosition.o Goals/Goal_NegotiateDoor.o Goals/Goal_SeekToPosition.o Goals/Goal_Think.o Goals/Goal_TraverseEdge.o Goals/Goal_Types.o Goals/Goal_Wander.o Armory/Shooter.o Armory/Projectile.o Armory/Projectile_Shot.o misc/FrameCounter.o Door.o GraveMarkers.o Fuzzy/FuzzyModule.o Fuzzy/FuzzyOperators.o Fuzzy/FuzzySet_LeftShoulder.o Fuzzy/FuzzySet_RightShoulder.o Fuzzy/FuzzySet_Singleton.o Fuzzy/FuzzySet_Triangle.o Fuzzy/FuzzyVariable.o
SRCS = $(OBJS:.o=.cpp)
LOCALLIBDIR = /SDL2
LDFLAGS = -L$(LOCALLIBDIR)
LDLIBS = -lSDL2 -lSDL2_image

MAIN = debug2
all:	$(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LDFLAGS) $(LDLIBS)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@ 
clean:
	$(RM) *.o */*.o

