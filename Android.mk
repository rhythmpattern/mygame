LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_CPPFLAGS += -fexceptions -w
LOCAL_MODULE := main
MAIN = debug
LOCAL CFLAGS := -g -include android file open.h
SDL_PATH := ../SDL
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/../SDL2_image/

# Add your application source files here...
LOCAL_SRC_FILES := parser.cpp LevelCreator.cpp Goals/Goal_2DMove.cpp Armory/Weapon.cpp PauseState.cpp CharManager.cpp GraveManager.cpp Armory/Melee.cpp Room.cpp ProjectileManager.cpp Zombie.cpp PlayerSteering.cpp InputHandler.cpp Player.cpp ZombieWeaponSystem.cpp Goals/Goal_Think_Zombie.cpp Goals/Goal_Zombie.cpp Goals/Goal_Pause.cpp Goals/Goal_FlyWander.cpp Goals/Goal_FlyExplore.cpp Goals/Goal_Think_Fly.cpp Goals/Goal_Fly.cpp BLayer.cpp TileLayer.cpp GameStateMachine.cpp debug.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp TextureManager.cpp StateParser.cpp GameObjectFactory.cpp PlayState.cpp LevelParser.cpp base64.cpp Level.cpp ObjectLayer.cpp 2D/Vector2D.cpp Game/Entity.cpp Game/EntityManager.cpp Character.cpp Triggers/Trigger_HealthGiver.cpp Triggers/Trigger_SoundNotify.cpp Triggers/Trigger_WeaponGiver.cpp Navigation/PathPlanner.cpp SteeringBehaviors.cpp TargetingSystem.cpp WeaponSystem.cpp SensoryMemory.cpp Messaging/MessageDispatcher.cpp Map.cpp Game.cpp Time/CrudeTimer.cpp UserOptions.cpp Goals/AttackTargetGoal_Evaluator.cpp Goals/ExploreGoal_Evaluator.cpp Goals/Feature.cpp Goals/Goal_AttackTarget.cpp Goals/Goal_DodgeSideToSide.cpp Goals/Goal_Explore.cpp Goals/Goal_FollowPath.cpp Goals/Goal_GetItem.cpp Goals/Goal_HuntTarget.cpp Goals/Goal_MoveToPosition.cpp Goals/Goal_NegotiateDoor.cpp Goals/Goal_SeekToPosition.cpp Goals/Goal_Think.cpp Goals/Goal_TraverseEdge.cpp Goals/Goal_Types.cpp Goals/Goal_Wander.cpp Armory/Shooter.cpp Armory/Projectile.cpp Armory/Projectile_Shot.cpp misc/FrameCounter.cpp Door.cpp GraveMarkers.cpp Fuzzy/FuzzyModule.cpp Fuzzy/FuzzyOperators.cpp Fuzzy/FuzzySet_LeftShoulder.cpp Fuzzy/FuzzySet_RightShoulder.cpp Fuzzy/FuzzySet_Singleton.cpp Fuzzy/FuzzySet_Triangle.cpp Fuzzy/FuzzyVariable.cpp Scriptor.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -lz

include $(BUILD_SHARED_LIBRARY)
