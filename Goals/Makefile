CC = g++
CFLAGS =  -g
SRCS = AttackTargetGoal_Evaluator.cpp ExploreGoal_Evaluator.cpp Feature.cpp Goal_AttackTarget.cpp Goal_DodgeSideToSide.cpp Goal_Explore.cpp Goal_FollowPath.cpp Goal_GetItem.cpp Goal_HuntTarget.cpp Goal_MoveToPosition.cpp Goal_NegotiateDoor.cpp Goal_SeekToPosition.cpp Goal_Think.cpp Goal_TraverseEdge.cpp Goal_Types.cpp Goal_Wander.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = debug
all:	$(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
clean:
	$(RM) *.o *~$(MAIN)

