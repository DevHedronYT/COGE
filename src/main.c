#include "./game.h"
#include <COGE/engine.h>



i32 main() {
    if (!game_init()) {
        return -1;
    }

    /*
        f32 last_tick = clock();
        f32 dt = 0.0f;
        f32 dt_accum = 0.0f;

        f32 timestep = 1.0f/60.0f;
    */

    while (game_should_run()) {
        /* 
            dt = ((clock() - last_tick) / CLOCKS_PER_SEC) * 1000.0f;
            last_tick = clock();
            dt_accum += dt;
        */ 

        game_process_input(1);
        game_update(1);
        /* 
            if (dt_accum >= timestep) {
                dt_accum = 0.0f;
            }
        */
        game_render();
        //ge_sleep(16);
    }

    game_delete();
    return 0;
}

