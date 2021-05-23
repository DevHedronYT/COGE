CC = gcc
FRAMEWORKS = -framework CoreFoundation -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

FLAGS = -std=c89 -march=native -mtune=native -Ofast -pipe -D _GLFW_COCOA=1
CFLAGS += -IData

FILES = Main.c Data/*.c Data/GLAD/*.c Data/STB/*.c

LDFLAGS += -LLibs
LDFLAGS += -lglfw3

LINUX = -lm -ldl -lpthread

# LD_LIBRARY_PATH = $(currentdir)/Libs
app: 
	$(CC) $(FILES) $(CFLAGS) $(LDFLAGS) $(FRAMEWORKS) -o app

linux:
	$(CC) $(FILES) $(CFLAGS) $(LINUX) $(LDFLAGS) -o app

