#ifndef ME_H 

    #define ME_H
    
    #include "./types.h"

    #define pi 3.141592653589793238462643383279
    #define deg_to_rad(deg) deg * (pi / 180)
    #define rad_to_deg(rad) rad * (180 / pi)
    #define sq(e) e * e
   
    f32 dist2D     (f32 x1, f32 y1, f32 x2, f32 y2);
    f32 dir2D      (f32 x1, f32 y1, f32 x2, f32 y2);
    f32 ilerp      (f32 start, f32 stop, f32 amt);
    i64 randnum_gen(i64 lower, i64 upper);

    // Note projection functions 
    // project v1 onto v2

    typedef struct {
        f32 x;
        f32 y;
    } v2_t;

    #define mk_v2_zero() (v2_t)  { 0.0f, 0.0f }
    #define mk_v2_one () (v2_t)  { 1.0f, 1.0f }
    #define mk_v2(_x, _y) (v2_t) { _x, _y }

    v2_t v2_add      (v2_t v1, v2_t v2);
    v2_t v2_sub      (v2_t v1, v2_t v2);
    v2_t v2_lerp     (v2_t v1, v2_t v2, f32 amt);
    void v2_scale    (v2_t * v, f32 scalar);
    void v2_normalize(v2_t * v);
    void v2_limit    (v2_t * v, f32 scalar);
    void v2_rotate   (v2_t * v, f32 theta);
    void v2_mag_set  (v2_t * v, f32 scalar);
    void v2_negate   (v2_t * v);

    f32  v2_mag          (v2_t v);
    f32  v2_angle        (v2_t v);
    f32  v2_dot_prod     (v2_t v1, v2_t v2);
    f32  v2_dist_between (v2_t v1, v2_t v2);
    f32  v2_angle_between(v2_t v1, v2_t v2);
    v2_t v2_projection   (v2_t v1, v2_t v2);


    typedef struct {
        f32 x;
        f32 y;
        f32 z;
    } v3_t;

    #define mk_v3_zero()      (v3_t) { 0.0f, 0.0f, 0.0f }
    #define mk_v3_one ()      (v3_t) { 1.0f, 1.0f, 1.0f }
    #define mk_v3(_x, _y, _z) (v3_t) { _x, _y, _z }

    v3_t v3_add      (v3_t v1, v3_t v2);
    v3_t v3_sub      (v3_t v1, v3_t v2);
    v3_t v3_lerp     (v3_t v1, v3_t v2, f32 amt);
    void v3_limit    (v3_t * v, f32 scalar);
    void v3_scale    (v3_t * v, f32 scalar);
    void v3_normalize(v3_t * v);
    void v3_mag_set  (v3_t * v, f32 scalar);
    void v3_negate   (v3_t * v);

    f32   v3_mag          (v3_t v);
    f32   v3_dot_prod     (v3_t v1, v3_t v2);
    v3_t  v3_cross_prod   (v3_t v1, v3_t v2);
    f32   v3_dist_between (v3_t v1, v3_t v2); 
    f32   v3_angle_between(v3_t v1, v3_t v2);
    v3_t  v3_projection   (v3_t v1, v3_t v2);

    typedef struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } v4_t;

    #define mk_v4_zero()          (v4_t) { 0.0f, 0.0f, 0.0f, 0.0f }
    #define mk_v4_one ()          (v4_t) { 1.0f, 1.0f, 1.0f, 1.0f }
    #define mk_v4(_x, _y, _z, _w) (v4_t) { _x, _y, _z, _w }


    v4_t v4_add      (v4_t v1, v4_t v2);
    v4_t v4_sub      (v4_t v1, v4_t v2);
    v4_t v4_lerp     (v4_t v1, v4_t v2, f32 amt);
    void v4_limit    (v4_t * v, f32 scalar);
    void v4_scale    (v4_t * v, f32 scalar);
    void v4_normalize(v4_t * v);
    void v4_mag_set  (v4_t * v, f32 scalar);
    void v4_negate   (v4_t * v);

    f32  v4_mag         (v4_t v);
    f32  v4_dot_prod    (v4_t v1, v4_t v2);
    f32  v4_dist_between(v4_t v1, v4_t v2); 
    v4_t v4_projection  (v4_t v1, v4_t v2);


    v3_t v2_to_v3(const v2_t v);
    v4_t v3_to_v4(const v3_t v);
    v3_t v4_to_v3(const v4_t v);
    v2_t v3_to_v2(const v3_t v);

    typedef struct {
        f32 elems[4][4];
    } m4x4_t;

    m4x4_t mk_m4x4(f32 m00, f32 m01, f32 m02, f32 m03,
                   f32 m04, f32 m05, f32 m06, f32 m07,
                   f32 m08, f32 m09, f32 m10, f32 m11,
                   f32 m12, f32 m13, f32 m14, f32 m15);
    // Some of the code has been took from
    // https://github.com/MrFrenik/gunslinger/blob/v0.02-alpha/include/math/gs_math.h
    // https://github.com/arkanis/single-header-file-c-libs/blob/master/math_3d.h
    // learnopengl.com/Getting-started/Transformations
    m4x4_t mk_zero_m4x4    ();
    m4x4_t mk_identity_m4x4();
    m4x4_t mk_diag_m4x4    (f32 val);

    m4x4_t m4x4_add    (m4x4_t m1, m4x4_t m2); 
    m4x4_t m4x4_sub    (m4x4_t m1, m4x4_t m2); 
    m4x4_t m4x4_mult   (m4x4_t m1, m4x4_t m2); 
    m4x4_t m4x4_mult_n (u32 m4x4_count, ...);
    v3_t   m4x4_mult_v3(m4x4_t m, v3_t v);
    v4_t   m4x4_mult_v4(m4x4_t m, v4_t v);

    m4x4_t m4x4_scale_by_v3    (m4x4_t mat, const v3_t vector);
    m4x4_t m4x4_translate_by_v3(m4x4_t mat, const v3_t vector);
    m4x4_t m4x4_rotate_by_v3   (f32 degrees, v3_t axis);

    m4x4_t m4x4_orthographic_projection(f32 l, f32 r, f32 b, 
                                        f32 t, f32 n, f32 f);
    
    m4x4_t m4x4_perspective_projection(f32 fov, f32 asp_ratio, f32 n, f32 f);
    m4x4_t m4x4_lookat                (v3_t pos, v3_t target, v3_t up);

    // Add:
    //  m3x3_t 
        //  lookat
    //  quternions
        //  
    // objects
    // rays

    typedef struct {
        v2_t pos;
        v2_t vel;
        f32 w;
        f32 h;
        u08 coll_l;
        u08 coll_r;
        u08 coll_b;
        u08 coll_t;
    } phys_obj_t;

    /* 
     * Best detection using SAT 
     * Separating Axis Theorem
     * Add x velocity then check 
     * horizontal collisions. Then
     * do the same thing for vertical
     * collisions
    */ 
    #define phys_obj_coll_detect(m, l) \
        ((((m.pos.x + m.w >= l.pos.x)  && \
           (l.pos.x + l.w >= m.pos.x)) && \
           (m.pos.y + m.h >= l.pos.y)) && \
           (l.pos.y + l.h >= m.pos.y))    \

#endif
