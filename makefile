CC = gcc

FILES = Main.c Data/GLAD/*.c Data/STB/*.c

LDFLAGS += -LLibs
LDFLAGS += -lglfw3

COMMONFLAGS = -std=c99 -march=native -mtune=native -O2 -pipe -IData

MACFLAGS = -framework CoreFoundation -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
LINUXFLAGS = -Wl,--no-as-needed -lm -ldl -lpthread

mac: 
	$(CC) $(FILES) $(COMMONFLAGS) $(MACFLAGS) $(LDFLAGS) -o app

linux:
	$(CC) $(FILES) $(COMMONFLAGS) $(LINUXFLAGS) $(LDFLAGS) -o app

