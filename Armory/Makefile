CC = g++
CFLAGS =  -g
SRCS = Projectile.cpp Projectile_Shot.cpp Shooter.cpp
OBJS = $(SRCS:.c=.o)
MAIN = debug
all:	$(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
clean:
	$(RM) *.o *~$(MAIN)

