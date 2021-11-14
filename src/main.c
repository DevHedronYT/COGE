#include <GLAD/gl.h>
#include <GLFW/glfw3.h>
#include <ge.h>

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

#define COMPONENTS_PER_VERT 5
#define SQUARES 1
#define VERTS SQUARES * 4

///////////////////////////
///////////////////////////
// Batch Rendering Stuff 
///////////////////////////
///////////////////////////
typedef struct {
    ge_v3_t pos;
    ge_v4_t col;
    ge_v2_t tex_pos;
    i32_t   tex_id;
} vertex_t; 

static vertex_t * create_quad(vertex_t * target, f32_t x, f32_t y, i32_t w, i32_t h, i32_t tex_id) {
    target -> pos = ge_mk_v3(x, y, 0.0f);
    target -> col = ge_mk_v4(0.5f, 0.5f, 1.0f, 1.0f);
    target -> tex_pos = ge_mk_v2(0.0f, 0.0f);
    target -> tex_id = tex_id - 1;
    target++;

    target -> pos = ge_mk_v3(x, y + h, 0.0f);
    target -> col = ge_mk_v4(0.5f, 0.5f, 1.0f, 1.0f);
    target -> tex_pos = ge_mk_v2(0.0f, 1.0f);
    target -> tex_id = tex_id - 1;
    target++;

    target -> pos = ge_mk_v3(x + w, y, 0.0f);
    target -> col = ge_mk_v4(0.5f, 0.5f, 1.0f, 1.0f);
    target -> tex_pos = ge_mk_v2(1.0f, 0.0f);
    target -> tex_id = tex_id - 1;
    target++;

    target -> pos = ge_mk_v3(x + w, y + w, 0.0f);
    target -> col = ge_mk_v4(0.5f, 0.5f, 1.0f, 1.0f);
    target -> tex_pos = ge_mk_v2(1.0f, 1.0f);
    target -> tex_id = tex_id - 1;
    target++;

    return target;
} 


/*
static Vertex* CreateTriangle(Vertex* target, float x, float y, float width, float height, float texID) {
    target -> Position = { x, y, 0.0f };
    target -> Color = { 0.5f, 0.4f, 1.0f, 0.5f };
    target -> TexCoords = { 0.0f, 0.0f };
    target -> TexID = texID - 1;
    target++;

    target -> Position = { x, y + height, 0.0f };
    target -> Color = { 0.7f, 0.2f, 1.0f, 0.5f };
    target -> TexCoords = { 0.0f, 1.0f };
    target -> TexID = texID - 1;
    target++;

    target -> Position = { x + width, y + height, 0.0f };
    target -> Color = { 0.5f, 0.9f, 1.0f, 0.5f };
    target -> TexCoords = { 1.0f, 1.0f };
    target -> TexID = texID - 1;
    target++;

    return target;

}
*/

///////////////////////////
///////////////////////////
// Main 
///////////////////////////
///////////////////////////
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
    ge_shader_t shader;
    ge_mk_shader(&shader, "res/shaders/vs.frag", "res/shaders/fs.frag");
    ge_bind_shader(shader);

    ge_set_mat4_uniform(&shader, "projection", &projection.elems[0][0]);
    ge_set_mat4_uniform(&shader, "rotation", &rotation.elems[0][0]);
    ge_set_mat4_uniform(&shader, "view", &view.elems[0][0]);
    
    ///////////////////////////
    ///////////////////////////
    // Textures 
    ///////////////////////////
    ///////////////////////////
    ge_tex_t tex;

    ge_mk_tex(&tex, "res/images/Hedron.png", 0);
    ge_bind_tex(&tex); 

    ge_set_int(&shader, "uTexture", tex.slot);

    ///////////////////////////
    ///////////////////////////
    // Vertices..etc..
    ///////////////////////////
    ///////////////////////////

    // Ordering of vertices is:
    //  Top left     0.0f, 1.0f
    //  Bottom left  0.0f, 0.0f,
    //  Top right    1.0f, 1.0f,
    //  Bottom right 1.0f, 0.0f
   
    // Components:
    //  Pos,   Tex Pos, Random 
    //  ge_v2, ge_v2,   f32_t       


    i32_t size = 100;
    ge_v2_t pos = ge_mk_v2(0 - size / 2, 0 - size / 2); 

    f32_t vertices[COMPONENTS_PER_VERT * VERTS] = {
        //       coordinates             texture    color  
        pos.x,        pos.y,           0.0f, 0.0f,  1.0f, 
        pos.x,        pos.y + size,    0.0f, 1.0f,  1.0f,
        pos.x + size, pos.y,           1.0f, 0.0f,  1.0f,
        pos.x + size, pos.y + size,    1.0f, 1.0f,  1.0f
    };  

    u32_t indices[VERTS + 2 * SQUARES] = {
        0, 1, 2,
        2, 1, 3
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

    ge_vertex_buffer_layout(0, 2, GL_FLOAT, GL_FALSE, COMPONENTS_PER_VERT * sizeof(GL_FLOAT), 0);
    ge_vertex_buffer_layout(1, 2, GL_FLOAT, GL_FALSE, COMPONENTS_PER_VERT * sizeof(GL_FLOAT), 2 * sizeof(GL_FLOAT));
    ge_vertex_buffer_layout(2, 1, GL_FLOAT, GL_FALSE, COMPONENTS_PER_VERT * sizeof(GL_FLOAT), 4 * sizeof(GL_FLOAT));


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

        if (ge_key(GLFW_KEY_S)) {
            ge_shader_hot_reload(&shader); 
            ge_set_mat4_uniform(&shader, "projection", &projection.elems[0][0]);
        }

        /* if (view.elems[3][0] > w) {
            increment_x = -10;
        }

        if (view.elems[3][0] < 0) {
            increment_x = 10;
        } */

        //if (view.elems)

        view = ge_translate_m4x4(view, vel);
        ge_set_mat4_uniform(&shader, "rotation", &rotation.elems[0][0]);
        ge_set_mat4_uniform(&shader, "view", &view.elems[0][0]);
        
        ge_draw_verts(VERTS + 2 * SQUARES);
        glfwSwapBuffers(win);
        glfwPollEvents();
        ge_sleep(16);
    }

    ///////////////////////////
    ///////////////////////////
    // Destruction 
    ///////////////////////////
    ///////////////////////////   
    ge_rm_shader(&shader);
    ge_rm_vao(&vao);
    ge_rm_ibo(&ibo);
    ge_rm_vbo(&vbo);
    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}

