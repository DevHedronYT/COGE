#ifndef __GE_ME__ 

    #define __GE_ME__ 
    
    #include <types.h>
   
    #define ge_pi 3.14159265358979
    #define ge_deg_to_rad(deg) deg * (ge_pi / 180)
    #define ge_rad_to_deg(rad) rad * (180 / ge_pi)
    #define ge_sqr(e) e * e
    #define ge_dist1D(c1, c2) c2 - c1
   
    f32_t ge_dist2D  (f32_t x1, f32_t y1, f32_t x2, f32_t y2);
    f32_t ge_dir2D   (f32_t x1, f32_t y1, f32_t x2, f32_t y2);
    f32_t ge_inv_sqrt(f32_t num);
    f32_t ge_ilerp   (f32_t start, f32_t stop, f32_t amt);
   
    i64_t ge_randnum_gen(i64_t lower, i64_t upper);

    // Note projection functions 
    // project v1 onto v2

    typedef struct {
        f32_t x;
        f32_t y;
    } ge_v2_t;

    #define ge_mk_v2_zero() (ge_v2_t)  { 0.0f, 0.0f }
    #define ge_mk_v2_one () (ge_v2_t)  { 1.0f, 1.0f }
    #define ge_mk_v2(_x, _y) (ge_v2_t) { _x, _y }

    ge_v2_t * ge_mk_v2_ptr(f32_t x, f32_t y);

    emp_t ge_add_v2    (ge_v2_t * v1, ge_v2_t * v2);
    emp_t ge_sub_v2    (ge_v2_t * v1, ge_v2_t * v2);
    emp_t ge_lerp_v2   (ge_v2_t * v1, ge_v2_t * v2, f32_t amt);
    emp_t ge_limit_v2  (ge_v2_t * v, f32_t scalar);
    emp_t ge_scale_v2  (ge_v2_t * v, f32_t scalar);
    emp_t ge_normal_v2 (ge_v2_t * v);
    emp_t ge_rotate_v2 (ge_v2_t * v, f32_t theta);
    emp_t ge_set_v2_mag(ge_v2_t * v, f32_t scalar);
    emp_t ge_negate_v2 (ge_v2_t * v);

    f32_t ge_v2_mag          (ge_v2_t * v);
    f32_t ge_v2_angle        (ge_v2_t * v);
    f32_t ge_v2_dot_prod     (ge_v2_t * v1, ge_v2_t * v2);
    f32_t ge_dist_between_v2 (ge_v2_t * v1, ge_v2_t * v2);
    f32_t ge_angle_between_v2(ge_v2_t * v1, ge_v2_t * v2);

    ge_v2_t ge_v2_projection(ge_v2_t * v1, ge_v2_t * v2);

    typedef struct {
        f32_t x;
        f32_t y;
        f32_t z;
    } ge_v3_t;

    #define ge_mk_v3_zero() (ge_v3_t) { 0.0f, 0.0f, 0.0f }
    #define ge_mk_v3_one () (ge_v3_t) { 1.0f, 1.0f, 1.0f }
    #define ge_mk_v3(_x, _y, _z) (ge_v3_t) { _x, _y, _z }

    ge_v3_t * ge_mk_v3_ptr(f32_t x, f32_t y, f32_t z);

    emp_t ge_add_v3    (ge_v3_t * v1, ge_v3_t * v2);
    emp_t ge_sub_v3    (ge_v3_t * v1, ge_v3_t * v2);
    emp_t ge_lerp_v3   (ge_v3_t * v1, ge_v3_t * v2, f32_t amt);
    emp_t ge_limit_v3  (ge_v3_t * v, f32_t scalar);
    emp_t ge_scale_v3  (ge_v3_t * v, f32_t scalar);
    emp_t ge_normal_v3 (ge_v3_t * v);
    emp_t ge_set_v3_mag(ge_v3_t * v, f32_t scalar);
    emp_t ge_negate_v3 (ge_v3_t * v);
    
    f32_t ge_v3_mag         (ge_v3_t * v);
    f32_t ge_v3_dot_prod    (ge_v3_t * v1, ge_v3_t * v2);
    f32_t ge_dist_between_v3(ge_v3_t * v1, ge_v3_t * v2); 
    ge_v3_t  ge_v3_cross_prod(ge_v3_t * v1, ge_v3_t * v2);
    ge_v3_t  ge_v3_projection(ge_v3_t * v1, ge_v3_t * v2);
    f32_t ge_angle_between_v3(ge_v3_t * v1, ge_v3_t * v2);


    typedef struct {
        f32_t x;
        f32_t y;
        f32_t z;
        f32_t w;
    } ge_v4_t;

    #define ge_mk_v4_zero() (ge_v4_t) { 0.0f, 0.0f, 0.0f, 0.0f }
    #define ge_mk_v4_one () (ge_v4_t) { 1.0f, 1.0f, 1.0f, 1.0f }
    #define ge_mk_v4(_x, _y, _z, _w) (ge_v4_t) { _x, _y, _z, _w }

    ge_v4_t * ge_mk_v4_ptr(f32_t x, f32_t y, f32_t z, f32_t w);

    emp_t ge_add_v4    (ge_v4_t * v1, ge_v4_t * v2);
    emp_t ge_sub_v4    (ge_v4_t * v1, ge_v4_t * v2);
    emp_t ge_lerp_v4   (ge_v4_t * v1, ge_v4_t * v2, f32_t amt);
    emp_t ge_limit_v4  (ge_v4_t * v, f32_t scalar);
    emp_t ge_scale_v4  (ge_v4_t * v, f32_t scalar);
    emp_t ge_normal_v4 (ge_v4_t * v);
    emp_t ge_set_v4_mag(ge_v4_t * v, f32_t scalar);
    emp_t ge_negate_v4 (ge_v4_t * v);
    
    f32_t ge_v4_mag         (ge_v4_t * vec);
    f32_t ge_v4_dot_prod    (ge_v4_t * v1, ge_v4_t * v2);
    f32_t ge_dist_between_v4(ge_v4_t * v1, ge_v4_t * v2); 

    ge_v4_t ge_v4_projection(ge_v4_t * v1, ge_v4_t * v2);

    ge_v3_t ge_v2_to_v3(const ge_v2_t v);
    ge_v4_t ge_v3_to_v4(const ge_v3_t v);
    ge_v3_t ge_v4_to_v3(const ge_v4_t v);
    ge_v2_t ge_v3_to_v2(const ge_v3_t v);

    typedef struct {
        f32_t elems[4][4];
    } ge_m4x4_t;

    ge_m4x4_t ge_mk_m4x4(f32_t m00, f32_t m01, f32_t m02, f32_t m03,
                   f32_t m04, f32_t m05, f32_t m06, f32_t m07,
                   f32_t m08, f32_t m09, f32_t m10, f32_t m11,
                   f32_t m12, f32_t m13, f32_t m14, f32_t m15);
    // Some of the code has been took from
    // https://github.com/MrFrenik/gunslinger/blob/v0.02-alpha/include/math/gs_math.h
    // https://github.com/arkanis/single-header-file-c-libs/blob/master/math_3d.h
    // learnopengl.com/Getting-started/Transformations
    ge_m4x4_t ge_zero_m4x4();
    ge_m4x4_t ge_identity_m4x4();
    ge_m4x4_t ge_diag_m4x4(f32_t val);

    ge_m4x4_t ge_scale_m4x4_by_v3(ge_m4x4_t mat, const ge_v3_t vector);
    emp_t ge_m4x4_add(ge_m4x4_t * m1, ge_m4x4_t * m2); 
    // Subtracts m1 from m2
    emp_t ge_m4x4_sub(ge_m4x4_t * m1, ge_m4x4_t * m2); 
    ge_m4x4_t ge_m4x4_mult(ge_m4x4_t m1, ge_m4x4_t m2); 
    ge_v4_t ge_m4x4_mult_v4(ge_m4x4_t m, ge_v4_t v);
    ge_v3_t ge_m4x4_mult_v3(ge_m4x4_t m, ge_v3_t v);
    ge_m4x4_t ge_scale_m4x4_by_v3(ge_m4x4_t mat, const ge_v3_t vector);
    ge_m4x4_t ge_m4x4_rotate(ge_m4x4_t input, f32_t rad, ge_v3_t axis);
    ge_m4x4_t ge_translate_m4x4(ge_m4x4_t mat, const ge_v3_t vector);
    ge_m4x4_t ge_mk_ortho_projection_m4x4(f32_t l, f32_t r, f32_t b, 
                                    f32_t t, f32_t n, f32_t f);
    
    ge_m4x4_t ge_mk_perspective_projection_m4x4(f32_t fov, f32_t asp_ratio, f32_t n, f32_t f);
    ge_m4x4_t ge_m4x4_mult_n(u32_t m4x4_count, ...);
    ge_m4x4_t ge_m4x4_lookat(ge_v3_t pos, ge_v3_t target, ge_v3_t up);

    // Add:
    //  m3x3_t 
        //  lookat
    //  quternions
        //  
    // objects
    // rays



#endif
