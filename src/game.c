#include "./game.h"

ge_win_t win;

m4x4_t projection;
m4x4_t view;
m4x4_t rotation;

u64 shaders[2];
u64 textures[2];
const i32 samplers[2] = { 0, 1 };

ge_res_manager_t resource_manager;

ge_shader_t * current_shader;


#define SIZE 100

const f32 pos_x = WIDTH / 2 - SIZE / 2;
const f32 pos_y = HEIGHT / 2 - SIZE / 2;
const f32 pos_two_x = 0 - SIZE / 2;
const f32 pos_two_y = 0 - SIZE / 2;

// Ordering of vertices is:
//  Top left     0.0f, 1.0f
//  Bottom left  0.0f, 0.0f,
//  Top right    1.0f, 1.0f,
//  Bottom right 1.0f, 0.0f

// Components:
//  Pos,   Tex Pos, Random, Tex_id
//  ge_v2, ge_v2,   f32,  f32
typedef struct {
    f32 * vertices;
    u32 * indices;
    u64 v_size;
    u64 i_size;
} vertices_t;

vertices_t vertices;

ge_vao_t vao;
ge_ibo_t ibo;
ge_vbo_t vbo;

u32 fp_size = COMPONENTS_PER_VERT * sizeof(GL_FLOAT);


v3_t vel = { 0, 0, 0 };
i08 increment_x = 10;
i08 increment_y = 10;

f32 rad = 0.0f;

ge_keyboard_event_t left;
ge_keyboard_event_t right;
ge_keyboard_event_t bottom; 
ge_keyboard_event_t top;

i32 game_init() {
    ge_init();
    win = ge_mk_win(WIDTH, HEIGHT, "GL Game", 1);

    projection = m4x4_orthographic_projection(0, WIDTH, HEIGHT, 0, -1, 1);
    view = mk_diag_m4x4(1.0f);
    rotation = m4x4_rotate_by_v3(deg_to_rad(0), mk_v3(0, 0, 1));

    ge_mk_res_manager(&resource_manager);

    char new_str[9] = {0};
    for (u08 i = 0; i < 2; i++) {
        char * num = i32_to_str(i);
        strcat(new_str, "shader_");
        strcat(new_str, num);
        new_str[8] = '\0';
        shaders[i] = ge_mk_res_shader("res/shaders/vs.frag", "res/shaders/fs.frag", new_str, &resource_manager);
        memset(new_str, 0, 9);
    }

    current_shader = resource_manager.shader.data[shaders[0]] -> val;
    ge_bind_shader(*current_shader);

    ge_set_mat4_uniform(current_shader, "projection", &projection.elems[0][0]);
    ge_set_mat4_uniform(current_shader, "rotation", &rotation.elems[0][0]);
    ge_set_mat4_uniform(current_shader, "view", &view.elems[0][0]);

    textures[0] = ge_mk_res_texture("res/images/PFP.png", "profile", &resource_manager);
    textures[1] = ge_mk_res_texture("res/images/Hedron.png", "hedron", &resource_manager);

    for (u08 i = 0; i < 2; i++) {
        ge_bind_tex(resource_manager.textures.data[textures[i]] -> val);
    }


    f32 verts[COMPONENTS_PER_VERT * VERTS] = {
        //       coordinates             texture    color  tex_id 
        pos_x,        pos_y,           0.0f, 0.0f,  0.5f,   1.0f, 
        pos_x,        pos_y + SIZE,    0.0f, 1.0f,  1.5f,   1.0f,
        pos_x + SIZE, pos_y,           1.0f, 0.0f,  1.75f,   1.0f,
        pos_x + SIZE, pos_y + SIZE,    1.0f, 1.0f,  1.2f,   1.0f,

        pos_two_x,        pos_two_y,           0.0f, 0.0f,  1.2f,   0.0f, 
        pos_two_x,        pos_two_y + SIZE,    0.0f, 1.0f,  1.3f,   0.0f,
        pos_two_x + SIZE, pos_two_y,           1.0f, 0.0f,  1.4f,   0.0f,
        pos_two_x + SIZE, pos_two_y + SIZE,    1.0f, 1.0f,  1.5f,   0.0f

    }; 

    vertices.vertices = verts;
    vertices.v_size = COMPONENTS_PER_VERT * VERTS;


    u32 indices[VERTS + 2 * SQUARES] = {
        0, 1, 2,
        2, 1, 3,

        4, 5, 6,
        6, 5, 7
    }; 

    vertices.indices = indices;
    vertices.i_size = VERTS + 2 * SQUARES;


    ge_call_gl(glUniform1iv(glGetUniformLocation(current_shader -> id, "uTexture"), 2, samplers));

    ge_mk_vao(&vao);
    
    ge_mk_ibo(&ibo, vertices.indices, GL_STATIC_DRAW, sizeof(u32) * (VERTS + 2 * SQUARES));
    ge_bind_ibo(ibo);

    ge_mk_vbo(&vbo, vertices.vertices, sizeof(f32) * vertices.v_size, GL_STATIC_DRAW);
    ge_bind_vbo(vbo);

    // The offset can be found by the index that element is found at
    ge_vertex_buffer_layout(0, 2, GL_FLOAT, GL_FALSE, fp_size, 0);
    ge_vertex_buffer_layout(1, 2, GL_FLOAT, GL_FALSE, fp_size, 2 * sizeof(GL_FLOAT));
    ge_vertex_buffer_layout(2, 1, GL_FLOAT, GL_FALSE, fp_size, 4 * sizeof(GL_FLOAT));
    ge_vertex_buffer_layout(3, 1, GL_FLOAT, GL_FALSE, fp_size, 5 * sizeof(GL_FLOAT));

    left = ge_mk_keyboard_event(GLFW_KEY_LEFT, GLFW_KEY_A);
    right = ge_mk_keyboard_event(GLFW_KEY_RIGHT, GLFW_KEY_D);
    bottom = ge_mk_keyboard_event(GLFW_KEY_DOWN, GLFW_KEY_S); 
    top = ge_mk_keyboard_event(GLFW_KEY_UP, GLFW_KEY_W);

    log_msg("Game Initialized, Using OpenGL Version: %s", ge_get_ogl_version());
    return 1;
}


void game_process_input(f32 dt) {
    if (ge_check_keyboard_events(&right)) {
        vel.x += increment_x;
    }

    if (ge_check_keyboard_events(&left)) {
        vel.x -= increment_x;
    }

    if (ge_check_keyboard_events(&top)) {
        vel.y -= increment_y;
    }

    if (ge_check_keyboard_events(&bottom)) {
        vel.y += increment_y;
    }

    if (ge_key(GLFW_KEY_R)) {
        rad += 0.001f;
        rotation = m4x4_rotate_by_v3(rad, mk_v3(0, 0, 1));
    }

    if (ge_key(GLFW_KEY_N)) {
        current_shader = resource_manager.shader.data[shaders[1]] -> val;
        ge_bind_shader(*current_shader);
        log_msg("%s",current_shader -> fs.content);
        ge_set_mat4_uniform(current_shader, "projection", &projection.elems[0][0]);
        ge_call_gl(glUniform1iv(glGetUniformLocation(current_shader -> id, "uTexture"), 2, samplers));
    }

    if (ge_key(GLFW_KEY_U)) {
        current_shader = resource_manager.shader.data[shaders[0]] -> val;
        ge_bind_shader(*current_shader);
        log_msg("%s",current_shader -> fs.content);
        ge_set_mat4_uniform(current_shader, "projection", &projection.elems[0][0]);
        ge_call_gl(glUniform1iv(glGetUniformLocation(current_shader -> id, "uTexture"), 2, samplers));
    }

    if (ge_key(GLFW_KEY_S)) {
        ge_shader_hot_reload(current_shader); 
        ge_set_mat4_uniform(current_shader, "projection", &projection.elems[0][0]);
        ge_call_gl(glUniform1iv(glGetUniformLocation(current_shader -> id, "uTexture"), 2, samplers));
    }
}

void game_update(f32 dt) {
    view = m4x4_translate_by_v3(view, vel);
    ge_set_mat4_uniform(current_shader, "rotation", &rotation.elems[0][0]);
    ge_set_mat4_uniform(current_shader, "view", &view.elems[0][0]);
    vel.x = 0;
    vel.y = 0;
    vel.z = 0;
}

void game_render() {
    ge_fill_win(0.5, 0.5, 1.0, 0.4);
    ge_draw_verts(VERTS + 2 * SQUARES);
    glfwSwapBuffers(win);
    glfwPollEvents();
    // ge_sleep(16);
}

void game_delete() {
    ge_rm_shader(current_shader);
    ge_rm_vao(&vao);
    ge_rm_ibo(&ibo);
    ge_rm_vbo(&vbo);
    glfwDestroyWindow(win);
    glfwTerminate();
}

u08 game_should_run() {
    return !glfwWindowShouldClose(win);
}