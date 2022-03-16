#include <COGE/engine.h>
#include <GLAD/gl.h>
#include <GLFW/glfw3.h>

// Declarations 
#define WIDTH 640 
#define HEIGHT 480 

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


/*


// Ordering of vertices is:
//  Top left     0.0f, 1.0f
//  Bottom left  0.0f, 0.0f,
//  Top right    1.0f, 1.0f,
//  Bottom right 1.0f, 0.0f

// Components:
//  Pos,   Tex Pos, Random, Tex_id
//  ge_v2, ge_v2,   f32,  f32

*/