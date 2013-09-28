CXX = g++
CPPFLAGS = -g -o

OBJS = main.cpp game.cpp ball.cpp geometry.cpp paddle.cpp brick.cpp InitShader.cpp

INCLUDE_PATHS = -I/usr/local/include/GL -I/opt/X11/include

LIBDIRS  = -L/usr/local/lib -L/usr/X11R6/lib -L/usr/lib
LIBS = -lX11 -lglut -lGL -lGLEW -lGLU -lm

app: $(OBJS)
	$(CXX) $(CPPFLAGS) app $(OBJS) $(INCLUDE_PATHS) $(LIBDIRS) $(LIBS)

clean:
	rm -f $(C++OBJ) app
