CXX = g++
CPPFLAGS = -g

OBJS = main.cpp game.cpp ball.cpp geometry.cpp paddle.cpp brick.cpp

INCLUDE_PATHS = -I/usr/local/include/GL -I/opt/X11/include

LIBDIRS  = -L/usr/local/lib -L/usr/X11R6/lib -L/usr/lib
LIBS = -lX11 -lglut -lGL -lGLU -lm

app: $(OBJS)
	$(CXX) $(CPPFLAGS) -o app $(OBJS) $(INCLUDE_PATHS) $(LIBDIRS) $(LIBS)

clean:
	rm -f $(C++OBJ) app
