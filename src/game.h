#include <COGE/engine.h>
#include <GLAD/gl.h>
#include <GLFW/glfw3.h>

// Declarations 
#define WIDTH 1680
#define HEIGHT 1050

#define COMPONENTS_PER_VERT 6
#define SQUARES 2
#define VERTS SQUARES * 4

typedef enum {
    ACTIVE,
    MENU,
    WIN
} game_state;

i32  game_init();
void game_process_input(f32 dt);
void game_update(f32 dt);
void game_render();
void game_delete();

u08 game_should_run();

