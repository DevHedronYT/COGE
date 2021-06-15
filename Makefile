CC = gcc

FILES = Main.c Data/GLAD/*.c Data/STB/*.c

LDFLAGS += -LLibs
LDFLAGS += -lglfw3

COMMONFLAGS = -std=c89 -march=native -mtune=native -pipe -IData
# -02
MACFLAGS = -framework CoreFoundation -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
LINUXFLAGS = -Wl,--no-as-needed -lm -ldl -lpthread

mac: 
	$(CC) $(FILES) $(COMMONFLAGS) $(MACFLAGS) $(LDFLAGS) -o app

linux:
	$(CC) $(FILES) $(COMMONFLAGS) $(LINUXFLAGS) $(LDFLAGS) -o app

