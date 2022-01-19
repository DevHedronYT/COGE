#include "./game.h"
#include <COGE/engine.h>

i32 main() {
    if (!game_init()) {
        return -1;
    }
    f32 dt = 0.0f;
    while (game_should_run()) {
        game_process_input(dt);
        game_update(dt);
        game_render();
    }

    game_delete();
    return 0;
}

