#include <ge.h>
#include <GLAD/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

//////////////////////////
//////////////////////////
// Hash Tables 
//////////////////////////
//////////////////////////
typedef struct {
    const str_t id;
    u64_t       hash;
    ret_t       val;
} ht_item_t;

typedef struct {
    ht_item_t ** data;
    u32_t        len;
    u32_t        capacity;
} ht_t; 

ht_t  create_ht(u32_t capacity);
u64_t hash_id(const str_t id);
emp_t increase_ht_capacity(ht_t * ht, u32_t capacity);
emp_t __insert_to_ht(ht_t * ht, const str_t id, ret_t data);
ret_t __get_from_ht(ht_t ht, const str_t id);
u32_t rm_from_ht(ht_t * ht, const str_t id);
emp_t rm_ht(ht_t * ht);

#define insert_to_ht(ht, id, data) \
    __insert_to_ht(ht, id, (ret_t) data)

#define get_from_ht(ht, id, type) \
    (type)__get_from_ht(ht, id)


// Capacity MUST BE power of 2
ht_t create_ht(u32_t capacity) {
    ht_t table;
    table.data = (ht_item_t**) calloc(capacity, sizeof(ht_item_t*)); 
    table.len = 0;
    table.capacity = capacity;
    return table;
}

#define FNV_OFFSET 14695981039346656037
#define FNV_PRIME 1099511628211
u64_t hash_id(const str_t id) {
    u64_t hash = FNV_OFFSET;
    for (const char * p = id; *p; p++) {
        hash ^= (u64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

// Capacity MUST BE power of 2
emp_t increase_ht_capacity(ht_t * ht, u32_t capacity) {
    ht_t new_ht;
    new_ht.data = (ht_item_t**) calloc(capacity, sizeof(ht_item_t*));
    new_ht.len = 0;
    new_ht.capacity = capacity;
    for (u64_t i = 0; i < ht -> capacity; i++) {
        if (ht -> data[i] -> val != NULL) {
            __insert_to_ht(&new_ht, ht -> data[i] -> id, ht -> data[i] -> val);
        }
    }

    rm_ht(ht);
    ht = &new_ht;
}

emp_t __insert_to_ht(ht_t * ht, const str_t id, ret_t data) {
    ht_item_t * item = (ht_item_t *) calloc(1, sizeof(ht_item_t));
    item -> hash = hash_id(id);
    item -> id = id;
    item -> val = data;
    u64_t index = item -> hash & (u64_t)(ht -> capacity - 1);

    ht_item_t * current = ht -> data[index];
    while (current != NULL) {
        index++;
        current = ht -> data[index];
    }

    if (index > ht -> capacity) {
        increase_ht_capacity(ht, ht -> capacity * 2);
        ht -> data[index] = item;
    }

    if (ht -> data[index] == NULL) {
        ht -> data[index] = item;
    } 

    ht -> len++;
}

ret_t __get_from_ht(ht_t ht, const str_t id) {
    u64_t index = hash_id(id) & (u64_t)(ht.capacity - 1); 
    ht_item_t * data = ht.data[index];
        
    if (data == NULL) {
        return NULL;
    }

    if (data -> val == NULL) {
        return NULL;
    }

    while (ge_str_compare(data -> id, id) != 1) {
        index++; 
        data = ht.data[index]; 
    }

    if (data -> val != NULL && ge_str_compare(data -> id, id)) {
        return data -> val; 
    }

    return NULL;
}

u32_t rm_from_ht(ht_t * ht, const str_t id) {
    u64_t index = hash_id(id) & (u64_t)(ht -> capacity - 1); 
    ht_item_t * data = ht -> data[index];
    
    if (data -> val == NULL) {
        return 0;
    }

    while (ge_str_compare(data -> id, id) != 1) {
        index++; 
        data = ht -> data[index]; 
    }

    if (data -> val != NULL && ge_str_compare(data -> id, id)) {
        data = NULL;
        ht -> data[index] = NULL;
    }
    return index;
}

emp_t rm_ht(ht_t * ht) {
    for (u32_t i = 0; i < ht -> capacity; i++) {
        free(ht -> data[i]);
    }
    free(ht -> data);
}


//////////////////////////
//////////////////////////
// Resource Manager 
//////////////////////////
//////////////////////////
typedef struct {
    ht_t shader;
    ht_t textures;
} res_manager;

emp_t make_res_manager(res_manager * manager);
ge_shader_t * get_shader(const str_t name, res_manager * manager);
emp_t get_texture(const str_t name, res_manager * manager);


emp_t make_res_manager(res_manager * manager) {
    manager -> shader = create_ht(100);
    manager -> textures = create_ht(100);
}


ge_shader_t * get_shader(const str_t name, res_manager * manager) {
    ge_shader_t * shader = get_from_ht(manager -> shader, name, ret_t);
    return shader; 
}

emp_t mk_shader(str_t vs, str_t fs, const str_t name, res_manager * res_manager) {
    ge_shader_t * shader = calloc(1, sizeof(ge_shader_t));
    ge_mk_shader(shader, vs, fs);
    insert_to_ht(&res_manager -> shader, name, shader);
}

emp_t get_texture(const str_t name, res_manager * manager) {

}

//////////////////////////
//////////////////////////
// Keys 
//////////////////////////
//////////////////////////
typedef struct {
    i32_t keys[GLFW_KEY_LAST];
} ge_keyboard_event_t;

#define ge_mk_keyboard_event(...) (ge_keyboard_event_t) { {__VA_ARGS__}  }

u08_t ge_check_keyboard_events(ge_keyboard_event_t * e) {
    for (u32_t i = 0; i < GLFW_KEY_LAST; i++) {
        if (ge_key(e -> keys[i])) {
            return 1;
        }
    }
    return 0;
} 

#define COMPONENTS_PER_VERT 6
#define SQUARES 2
#define VERTS SQUARES * 4

//////////////////////////
//////////////////////////
// Games 
//////////////////////////
//////////////////////////
typedef enum {
    ACTIVE,
    MENU,
    WIN
} game_state;

#define WIDTH 640
#define HEIGHT 480

emp_t game_init();
emp_t game_process_input(f32_t dt);
emp_t game_update(f32_t dt);
emp_t game_render();

i32_t main(emp_t) {
    
    ///////////////////////////
    ///////////////////////////
    // Initialization
    ///////////////////////////
    ///////////////////////////
    ge_init();

    i32_t w = 1680;
    i32_t h = 1050;

    ge_win_t win = ge_mk_win(w, h, "GL Game", 1);
    
    ge_m4x4_t projection = ge_mk_ortho_projection_m4x4(0, w, h, 0, -1, 1);
    ge_m4x4_t view = ge_diag_m4x4(1.0f);
    ge_m4x4_t rotation = ge_m4x4_rotate(ge_diag_m4x4(1.0f), ge_deg_to_rad(0), ge_mk_v3(0, 0, 1));

    ge_log_i("OpenGL Version: %s", ge_get_renderer_version());

    ///////////////////////////
    ///////////////////////////
    // Shaders
    ///////////////////////////
    ///////////////////////////
    res_manager manager;
    make_res_manager(&manager);

    mk_shader("res/shaders/vs.frag", "res/shaders/fs.frag", "normal", &manager);
    mk_shader("res/shaders/vs.frag", "res/shaders/fs.frag", "normal_two", &manager);

    ge_shader_t * shader_one = get_shader("normal", &manager);  
    ge_shader_t * shader_two = get_shader("normal_two", &manager);  

    ge_shader_t * shader = shader_one;

    ge_bind_shader(*shader);
    ge_bind_shader(*shader);

    ge_set_mat4_uniform(shader, "projection", &projection.elems[0][0]);
    ge_set_mat4_uniform(shader, "rotation", &rotation.elems[0][0]);
    ge_set_mat4_uniform(shader, "view", &view.elems[0][0]);
    
    ///////////////////////////
    ///////////////////////////
    // Textures 
    ///////////////////////////
    ///////////////////////////
    ge_tex_t tex = {0};
    ge_tex_t tex_two = {0};

    ge_mk_tex(&tex, "res/images/PFP.png", 0);
    ge_mk_tex(&tex_two, "res/images/Hedron.png", 1);

    ge_bind_tex(&tex); 
    ge_bind_tex(&tex_two); 

    i32_t samplers[2] = { 0, 1 };

    call_gl(glUniform1iv(glGetUniformLocation(shader -> id, "uTexture"), 2, samplers));


    ///////////////////////////
    ///////////////////////////
    // Vertices..etc..
    ///////////////////////////
    ///////////////////////////
    ///////////////////////////

    // Ordering of vertices is:
    //  Top left     0.0f, 1.0f
    //  Bottom left  0.0f, 0.0f,
    //  Top right    1.0f, 1.0f,
    //  Bottom right 1.0f, 0.0f
   
    // Components:
    //  Pos,   Tex Pos, Random, Tex_id
    //  ge_v2, ge_v2,   f32_t,  f32_t


    i32_t size = 100;
    ge_v2_t pos = ge_mk_v2(w / 2 - size / 2, h / 2 - size / 2); 
    ge_v2_t pos_two = ge_mk_v2(0 - size / 2, 0 - size / 2); 


    f32_t vertices[COMPONENTS_PER_VERT * VERTS] = {
        //       coordinates             texture    color  tex_id 
        pos.x,        pos.y,           0.0f, 0.0f,  0.5f,   1.0f, 
        pos.x,        pos.y + size,    0.0f, 1.0f,  1.5f,   1.0f,
        pos.x + size, pos.y,           1.0f, 0.0f,  1.75f,   1.0f,
        pos.x + size, pos.y + size,    1.0f, 1.0f,  1.2f,   1.0f,

        pos_two.x,        pos_two.y,           0.0f, 0.0f,  1.2f,   0.0f, 
        pos_two.x,        pos_two.y + size,    0.0f, 1.0f,  1.3f,   0.0f,
        pos_two.x + size, pos_two.y,           1.0f, 0.0f,  1.4f,   0.0f,
        pos_two.x + size, pos_two.y + size,    1.0f, 1.0f,  1.5f,   0.0f

    }; 


/*

    for (i32_t y = 0; y < 10; y++) {
        for (i32_t x = 0; x < 10; x++) {
            vertices[x + y]
        }
    }
*/

    u32_t indices[VERTS + 2 * SQUARES] = {
        0, 1, 2,
        2, 1, 3,

        4, 5, 6,
        6, 5, 7

    }; 

    ///////////////////////////
    ///////////////////////////
    // Vertex Buffer, Vertex Array, Index Buffer
    ///////////////////////////
    ///////////////////////////
    ge_vao_t vao;
    ge_mk_vao(&vao);

    ge_ibo_t ibo;
    ge_mk_ibo(&ibo, indices, GL_STATIC_DRAW, sizeof(indices));
    ge_bind_ibo(ibo);

    ge_vbo_t vbo; 
    ge_mk_vbo(&vbo, vertices, sizeof(vertices), GL_STATIC_DRAW);
    ge_bind_vbo(vbo);

    // The offset can be found by the index that element is found at

    u32_t fp_size = COMPONENTS_PER_VERT * sizeof(GL_FLOAT);
    ge_vertex_buffer_layout(0, 2, GL_FLOAT, GL_FALSE, fp_size, 0);
    ge_vertex_buffer_layout(1, 2, GL_FLOAT, GL_FALSE, fp_size, 2 * sizeof(GL_FLOAT));
    ge_vertex_buffer_layout(2, 1, GL_FLOAT, GL_FALSE, fp_size, 4 * sizeof(GL_FLOAT));
    ge_vertex_buffer_layout(3, 1, GL_FLOAT, GL_FALSE, fp_size, 5 * sizeof(GL_FLOAT));


    ///////////////////////////
    ///////////////////////////
    // Game Loop & Game Related Stuff
    ///////////////////////////
    ///////////////////////////   

    ge_v3_t vel = ge_mk_v3(0, 0, 0);
    i08_t increment_x = 10;
    i08_t increment_y = 10;

    f32_t rad = 0.0f;

    ge_keyboard_event_t left = ge_mk_keyboard_event(GLFW_KEY_LEFT, GLFW_KEY_A);
    ge_keyboard_event_t right = ge_mk_keyboard_event(GLFW_KEY_RIGHT, GLFW_KEY_D);
    ge_keyboard_event_t bottom = ge_mk_keyboard_event(GLFW_KEY_DOWN, GLFW_KEY_S); 
    ge_keyboard_event_t top = ge_mk_keyboard_event(GLFW_KEY_UP, GLFW_KEY_W);

    while (!glfwWindowShouldClose(win)) {
        ge_cls(0.5, 0.5, 1.0, 0.4);
        vel.x = 0;
        vel.y = 0;
        vel.z = 0;

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
            rotation = ge_m4x4_rotate(rotation, rad, ge_mk_v3(0, 0, 1));
        }


        if (ge_key(GLFW_KEY_N)) {
            shader = shader_two;
            ge_bind_shader(*shader);
            ge_log_i("%s",shader -> fs.content);
            ge_set_mat4_uniform(shader, "projection", &projection.elems[0][0]);
            call_gl(glUniform1iv(glGetUniformLocation(shader -> id, "uTexture"), 2, samplers));
        }

        if (ge_key(GLFW_KEY_U)) {
            shader = shader_one;
            ge_bind_shader(*shader);
            ge_log_i("%s",shader -> fs.content);
            ge_set_mat4_uniform(shader, "projection", &projection.elems[0][0]);
            call_gl(glUniform1iv(glGetUniformLocation(shader -> id, "uTexture"), 2, samplers));
        }

        if (ge_key(GLFW_KEY_S)) {
            ge_shader_hot_reload(shader); 
            ge_set_mat4_uniform(shader, "projection", &projection.elems[0][0]);
            call_gl(glUniform1iv(glGetUniformLocation(shader -> id, "uTexture"), 2, samplers));
        }

        /* if (view.elems[3][0] > w) {
            increment_x = -10;
        }

        if (view.elems[3][0] < 0) {
            increment_x = 10;
        } */

        //if (view.elems)

        view = ge_translate_m4x4(view, vel);
        ge_set_mat4_uniform(shader, "rotation", &rotation.elems[0][0]);
        ge_set_mat4_uniform(shader, "view", &view.elems[0][0]);
        
        ge_draw_verts(VERTS + 2 * SQUARES);
        glfwSwapBuffers(win);
        glfwPollEvents();
        // ge_sleep(16);
    }

    ///////////////////////////
    ///////////////////////////
    // Destruction 
    ///////////////////////////
    ///////////////////////////   
    ge_rm_shader(shader);
    ge_rm_vao(&vao);
    ge_rm_ibo(&ibo);
    ge_rm_vbo(&vbo);
    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}

