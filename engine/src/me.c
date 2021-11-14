#include <me.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>

f32_t ge_dist2D(f32_t x1, f32_t y1, f32_t x2, f32_t y2) {
    return sqrt(ge_sqr(ge_dist1D(x1, x2)) + ge_sqr(ge_dist1D(y1, y2)));
}

f32_t ge_dir2D(f32_t x1, f32_t y1, f32_t x2, f32_t y2) {
    return atan2(y2 - y1, x2 - x1);  
}

f32_t ge_inv_sqrt(f32_t num) {
    i64_t i;
    f32_t x2, y;

    x2 = num * 0.5f;
    y = num;
    i = * (i64_t *) &y;
    i = 0x5f3759df - (i >> 1);
    y = * (f32_t *) &i;
    y = y * (1.5f - (x2 * ge_sqr(y)));

    return y; 
}

f32_t ge_ilerp(f32_t start, f32_t stop, f32_t amt) {
    return start + (stop - start) * amt; 
}

i64_t ge_randnum_gen(i64_t lower, i64_t upper) {
    return (rand() % (upper - lower + 1)) + lower;
}


ge_v2_t * ge_mk_v2_ptr(f32_t x, f32_t y) {
    ge_v2_t * v = calloc(1, sizeof(ge_v2_t));
    v -> x = x;
    v -> y = y;
    return v;
}

emp_t ge_add_v2(ge_v2_t * v1, ge_v2_t * v2) {
    v1 -> x += v2 -> x;
    v1 -> y += v2 -> y;
}

emp_t ge_sub_v2(ge_v2_t * v1, ge_v2_t * v2) {
    v1 -> x -= v2 -> x;
    v1 -> y -= v2 -> y;
}

emp_t ge_lerp_v2(ge_v2_t * v1, ge_v2_t * v2, f32_t amt) {
    v1 -> x = ge_ilerp(v1 -> x, v2 -> x, amt);
    v1 -> y = ge_ilerp(v1 -> y, v2 -> y, amt);
}
emp_t ge_limit_v2(ge_v2_t * v, f32_t scalar) {
    f32_t len = v -> x * v -> x + v -> y * v -> y;
    f32_t len_t = scalar * scalar;
    if (len > len_t) {
        ge_normal_v2(v);
        ge_scale_v2(v, scalar);
    }        
}

emp_t ge_scale_v2(ge_v2_t * v, f32_t scalar) {
    v -> x *= scalar;
    v -> y *= scalar;
}

emp_t ge_normal_v2(ge_v2_t * v) {
    f32_t mag = ge_v2_mag(v);

    if (mag != 1.0f) {
        v -> x = v -> x / mag;
        v -> y = v -> y / mag;  
    }
}


emp_t ge_rotate_v2(ge_v2_t * v, f32_t theta) {
    f32_t temp = v -> x;
    v -> x = v -> x * cos(theta) - v -> y * sin(theta);
    v -> y = temp * sin(theta) + v -> y * cos(theta);
}

emp_t ge_set_v2_mag(ge_v2_t * v, f32_t scalar) {
    ge_normal_v2(v);
    ge_scale_v2(v, scalar);
}

emp_t ge_negate_v2 (ge_v2_t * v) {
    v -> x = -v -> x;
    v -> y = -v -> y;
}

f32_t ge_v2_mag(ge_v2_t * v) {
    return (sqrt(v -> x * v -> x + v -> y * v -> y)); 
}

f32_t ge_v2_angle(ge_v2_t * v) {
    return atan2(v -> y, v -> x);
}

f32_t ge_v2_dot_prod(ge_v2_t * v1, ge_v2_t * v2) {
    return v1 -> x * v2 -> x + v1 -> y * v2 -> y; 
}

f32_t ge_dist_between_v2(ge_v2_t * v1, ge_v2_t * v2) {
    f32_t dx = v1 -> x - v2 -> x;
    f32_t dy = v1 -> y - v2 -> y;
    return sqrt(dx * dx + dy * dy);
}

f32_t ge_angle_between_v2(ge_v2_t * v1, ge_v2_t * v2) {
    if (v1 -> x == 0 && v1 -> y == 0) return 0.0f;
    if (v2 -> x == 0 && v2 -> y == 0) return 0.0f;

    f32_t dot = ge_v2_dot_prod(v1, v2);
    f32_t v1mag = ge_v2_mag(v1);
    f32_t v2mag = ge_v2_mag(v2);
    f32_t amt = dot / (v1mag * v2mag);

    if (amt <= -1) {
        return M_PI;
    } else if (amt >= 1) {
        return 0;
    }
    return acos(amt);
}

ge_v2_t ge_v2_projection(ge_v2_t * v1, ge_v2_t * v2) {
    f32_t dot = ge_v2_dot_prod(v1, v2);
    f32_t len = ge_v2_dot_prod(v2, v2);
    if (len == 0.0f) return *v2;

    ge_v2_t return_val = *v2;
    ge_scale_v2(&return_val, dot / len);
    return return_val;
}

ge_v3_t * ge_mk_v3_ptr(f32_t x, f32_t y, f32_t z) {
    ge_v3_t * v = calloc(1, sizeof(ge_v3_t));
    v -> x = x;
    v -> y = y;
    v -> z = z;
    return v;
}


emp_t ge_add_v3(ge_v3_t * v1, ge_v3_t * v2) {
    v1 -> x += v2 -> x;
    v1 -> y += v2 -> y;
    v1 -> z += v2 -> z;
}

emp_t ge_sub_v3(ge_v3_t * v1, ge_v3_t * v2) {
    v1 -> x -= v2 -> x;
    v1 -> y -= v2 -> y;
    v1 -> z -= v2 -> z;
}

emp_t ge_lerp_v3(ge_v3_t * v1, ge_v3_t * v2, f32_t amt) {
    v1 -> x = ge_ilerp(v1 -> x, v2 -> x, amt);
    v1 -> y = ge_ilerp(v1 -> y, v2 -> y, amt);   
    v1 -> z = ge_ilerp(v1 -> z, v2 -> z, amt);
}

emp_t ge_limit_v3(ge_v3_t * v, f32_t scalar) {
    f32_t len = v -> x * v -> x + v -> y * v -> y;
    f32_t len_t = scalar * scalar;
    if (len > len_t) {
        ge_normal_v3(v);
        ge_scale_v3(v, scalar);
    }   
}

emp_t ge_scale_v3(ge_v3_t * v, f32_t scalar) {
    v -> x *= scalar;
    v -> y *= scalar;
    v -> z *= scalar;
}

emp_t ge_normal_v3(ge_v3_t * v) {
    f32_t mag = ge_v3_mag(v);


    if (mag != 1.0f) {
        v -> x = v -> x / mag;
        v -> y = v -> y / mag;
        v -> z = v -> z / mag;
        
    }
}

emp_t ge_set_v3_mag(ge_v3_t * v, f32_t scalar) {
    ge_normal_v3(v);
    ge_scale_v3(v, scalar);
}

emp_t ge_negate_v3(ge_v3_t * v) {
    v -> x = -v -> x;
    v -> y = -v -> y;
    v -> z = -v -> z;
}

f32_t ge_v3_mag(ge_v3_t * v) {
    return (sqrt(v -> x * v -> x + v -> y * v -> y + v -> z * v -> z)); 
}

f32_t ge_v3_dot_prod(ge_v3_t * v1, ge_v3_t * v2) {
    return v1 -> x * v2 -> x + v1 -> y * v2 -> y + v1 -> z * v2 -> z;  
}

f32_t ge_dist_between_v3(ge_v3_t * v1, ge_v3_t * v2) {
    f32_t dx = v2 -> x - v1 -> x;
    f32_t dy = v2 -> y - v1 -> y;
    f32_t dz = v2 -> z - v1 -> z;
    return sqrt(dx * dx + dy * dy + dz * dz); 
}

ge_v3_t ge_v3_cross_prod(ge_v3_t * v1, ge_v3_t * v2) {
    ge_v3_t v_o;
    v_o.x = v1 -> y * v2 -> z - v1 -> z * v2 -> y;
    v_o.y = v1 -> z * v2 -> x - v1 -> z * v2 -> z;
    v_o.z = v1 -> x * v2 -> y - v1 -> y * v2 -> x;
    return v_o;
}


ge_v3_t ge_v3_projection(ge_v3_t * v1, ge_v3_t * v2) {
    f32_t dot = ge_v3_dot_prod(v1, v2);
    f32_t len = ge_v3_dot_prod(v2, v2);
    if (len == 0.0f) return *v2;

    ge_v3_t return_val = *v2;
    ge_scale_v3(&return_val, dot / len);
    return return_val;   
}

f32_t ge_angle_between_v3(ge_v3_t * v1, ge_v3_t * v2) {
    if (v1 -> x == 0 && v1 -> y == 0) return 0.0f;
    if (v2 -> x == 0 && v2 -> y == 0) return 0.0f;
    if (v2 -> z == 0 && v2 -> z == 0) return 0.0f;

    f32_t dot = ge_v3_dot_prod(v1, v2);
    f32_t v1mag = ge_v3_mag(v1);
    f32_t v2mag = ge_v3_mag(v2);
    f32_t amt = dot / (v1mag * v2mag);

    if (amt <= -1) {
        return M_PI;
    } else if (amt >= 1) {
        return 0;
    }
    return acos(amt);   
}

ge_v4_t * ge_mk_v4_ptr(f32_t x, f32_t y, f32_t z, f32_t w) {
    ge_v4_t * v = calloc(1, sizeof(ge_v4_t));
    v -> x = x;
    v -> y = y;
    v -> z = z;
    v -> w = w;
    return v;
}


emp_t ge_add_v4(ge_v4_t * v1, ge_v4_t * v2) {
    v1 -> x += v2 -> x;    
    v1 -> y += v2 -> y;
    v1 -> z += v2 -> z;
    v1 -> w += v2 -> w;
}

emp_t ge_sub_v4(ge_v4_t * v1, ge_v4_t * v2) {
    v1 -> x -= v2 -> x;
    v1 -> y -= v2 -> y;
    v1 -> z -= v2 -> z;
    v1 -> w -= v2 -> w;
}

emp_t ge_lerp_v4(ge_v4_t * v1, ge_v4_t * v2, f32_t amt) {
    v1 -> x = ge_ilerp(v1 -> x, v2 -> x, amt);
    v1 -> y = ge_ilerp(v1 -> y, v2 -> y, amt);   
    v1 -> z = ge_ilerp(v1 -> z, v2 -> z, amt);
    v1 -> w = ge_ilerp(v1 -> w, v2 -> w, amt);
}

emp_t ge_limit_v4(ge_v4_t * v, f32_t scalar) {
    f32_t len = v -> x * v -> x + v -> y * v -> y;
    f32_t len_t = scalar * scalar;
    if (len > len_t) {
        ge_normal_v4(v);
        ge_scale_v4(v, scalar);
    }        
}

emp_t ge_scale_v4(ge_v4_t * v, f32_t scalar) {
    v -> x *= scalar;
    v -> y *= scalar;  
    v -> z *= scalar;
    v -> w *= scalar;
}

emp_t ge_normal_v4(ge_v4_t * v) {
    f32_t mag = ge_v4_mag(v);
    if (mag != 1.0f) {
        v -> x = v -> x / mag;
        v -> y = v -> y / mag;
        v -> z = v -> z / mag;
        v -> w = v -> w / mag;
    }
}

emp_t ge_set_v4_mag(ge_v4_t * v, f32_t scalar) {
    ge_normal_v4(v);
    ge_scale_v4(v, scalar); 
}

emp_t ge_negate_v4(ge_v4_t * v) {
    v -> x = -v -> x;
    v -> y = -v -> y;
    v -> z = -v -> z;
    v -> w = -v -> w;
}




f32_t ge_v4_mag(ge_v4_t * v) {
    return (sqrt(v -> x * v -> x + v -> y * v -> y + v -> z * v -> z + v -> w * v -> w)); 
}

f32_t ge_v4_dot_prod(ge_v4_t * v1, ge_v4_t * v2) {
    return v1 -> x * v2 -> x + v1 -> y * v2 -> y + v1 -> z * v2 -> z + v1 -> w * v2 -> w;  
}

f32_t ge_dist_between_v4(ge_v4_t * v1, ge_v4_t * v2) {
    f32_t dx = v2 -> x - v1 -> x;
    f32_t dy = v2 -> y - v1 -> y;
    f32_t dz = v2 -> z - v1 -> z;
    f32_t dw = v2 -> w - v1 -> w;
    return sqrt(dx * dx + dy * dy + dz * dz + dw * dw); 
}

// projects v1 on v2
ge_v4_t ge_v4_projection(ge_v4_t * v1, ge_v4_t * v2) {
    f32_t dot = ge_v4_dot_prod(v1, v2);
    f32_t len = ge_v4_dot_prod(v2, v2);
    if (len == 0.0f) return *v2;

    ge_v4_t return_val = *v2;
    ge_scale_v4(&return_val, dot / len);
    return return_val;   
}

ge_v3_t ge_v2_to_v3(const ge_v2_t v) {
    return ge_mk_v3(v.x, v.y, 1);
}

ge_v4_t ge_v3_to_v4(const ge_v3_t v) {
    return ge_mk_v4(v.x, v.y, v.z, 1);
}

ge_v3_t ge_v4_to_v3(const ge_v4_t v) {
    return ge_mk_v3(v.x, v.y, v.z);
}

ge_v2_t ge_v3_to_v2(const ge_v3_t v) {
    return ge_mk_v2(v.x, v.y);
}


ge_m4x4_t ge_mk_m4x4(f32_t m00, f32_t m01, f32_t m02, f32_t m03,
               f32_t m04, f32_t m05, f32_t m06, f32_t m07,
               f32_t m08, f32_t m09, f32_t m10, f32_t m11,
               f32_t m12, f32_t m13, f32_t m14, f32_t m15) { 
    ge_m4x4_t mat = {{
        {m00, m01, m02, m03},
        {m04, m05, m06, m07},
        {m08, m09, m10, m11},
        {m12, m13, m14, m15}
    }};

    return mat;
}

ge_m4x4_t ge_zero_m4x4() {
    return ge_mk_m4x4( 
                    0, 0, 0, 0,
                    0, 0, 0, 0, 
                    0, 0, 0, 0, 
                    0, 0, 0, 0
                  );
}

ge_m4x4_t ge_identity_m4x4() {
    return ge_mk_m4x4(
                     1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1
                    
                  );
}

ge_m4x4_t ge_diag_m4x4(f32_t val) {
    return ge_mk_m4x4(
                    val, 000, 000, 000,
                    000, val, 000, 000,
                    000, 000, val, 000,
                    000, 000, 000, val
                  );
}

emp_t ge_m4x4_add(ge_m4x4_t * m1, ge_m4x4_t * m2) {
    for (u16_t i = 0; i < 4; i++) {
        for (u16_t j = 0; j < 4; j++) {
            m1 -> elems[i][j] += m2 -> elems[i][j];
        }
    }
}

emp_t ge_m4x4_sub(ge_m4x4_t * m1, ge_m4x4_t * m2) {
    for (u16_t i = 0; i < 4; i++) {
        for (u16_t j = 0; j < 4; j++) {
            m2 -> elems[i][j] -= m1 -> elems[i][j];
        }
    }
} 
ge_m4x4_t ge_m4x4_mult(ge_m4x4_t m1, ge_m4x4_t m2) {
 	ge_m4x4_t result = ge_zero_m4x4(); 
	for (u32_t y = 0; y < 4; ++y) {
		for (u32_t x = 0; x < 4; ++x) {
			f32_t sum = 0.0f;
			for (u32_t e = 0; e < 4; ++e) {
				sum += m1.elems[e][x] * m2.elems[y][e];
			}
			result.elems[y][x] = sum;
		}
	}

	return result;
} 

ge_m4x4_t ge_scale_m4x4_by_v3(ge_m4x4_t mat, const ge_v3_t vector) {
    mat.elems[0][0] *= vector.x;
    mat.elems[1][1] *= vector.y;
    mat.elems[2][2] *= vector.z;
    return mat;
}


ge_v4_t ge_vec_mult(ge_v4_t x, ge_v4_t y) {
    return ge_mk_v4(
                x.x * y.x,
                x.y * y.y,
                x.z * y.z,
                x.w * y.w
            );
}

ge_v4_t ge__v4add(ge_v4_t one, ge_v4_t two) {
    one.x += two.x;
    one.y += two.y;
    one.z += two.z;
    one.w = 1;
    return one;
}

// Takes in an identity matrix
ge_m4x4_t ge_translate_m4x4(ge_m4x4_t mat, const ge_v3_t vector) { 
    ge_v4_t new_vec = ge_mk_v4(vector.x, vector.y, vector.z, 1);
    
    ge_v4_t m_0 = ge_mk_v4(mat.elems[0][0], mat.elems[0][1], mat.elems[0][2], mat.elems[0][3]);
    ge_v4_t m_1 = ge_mk_v4(mat.elems[1][0], mat.elems[1][1], mat.elems[1][2], mat.elems[1][3]);
    ge_v4_t m_2 = ge_mk_v4(mat.elems[2][0], mat.elems[2][1], mat.elems[2][2], mat.elems[2][3]);
    ge_v4_t m_3 = ge_mk_v4(mat.elems[3][0], mat.elems[3][1], mat.elems[3][2], mat.elems[3][3]);
    
    ge_scale_v4(&m_0, new_vec.x);
    ge_scale_v4(&m_1, new_vec.y);
    ge_scale_v4(&m_2, new_vec.z);
    


    ge_v4_t add = ge__v4add(m_0, m_1);
    ge_v4_t add_two = ge__v4add(add, m_2);
    ge_v4_t add_three = ge__v4add(add_two, m_3);


    ge_m4x4_t identity = ge_diag_m4x4(1.0f);
    mat.elems[3][0] = add_three.x;
    mat.elems[3][1] = add_three.y;
    mat.elems[3][2] = add_three.z;
    mat.elems[3][3] = 1;

    return mat;
}

ge_m4x4_t ge_m4x4_rotate(ge_m4x4_t input, f32_t rad, ge_v3_t axis) {
    ge_m4x4_t mat = ge_identity_m4x4();

    f32_t c = (f32_t)cos(rad);
    f32_t s = (f32_t)sin(rad);

    ge_normal_v3(&axis);
    f32_t x = axis.x;
    f32_t y = axis.y;
    f32_t z = axis.z; 

    mat.elems[0][0] = c + (1 - c) * x * x;
    mat.elems[0][1] = (1 - c) * x * y + s * z;
    mat.elems[0][2] = (1 - c) * x * z - s * y;
    mat.elems[0][3] = 0;

    //Second column
    mat.elems[1][0] = (1 - c) * y * x - s * z;
    mat.elems[1][1] = c + (1 - c) * y * y;
    mat.elems[1][2] = (1 - c) * y * z + s * x;
    mat.elems[1][3] = 0;

    //Third column
    mat.elems[2][0] = (1 - c) * z * x + s * y;
    mat.elems[2][1] = (1 - c) * z * y - s * x;
    mat.elems[2][2] = c + (1 - c) * z * z; 
    mat.elems[2][3] = 0;

    mat.elems[3][0] = 0;
    mat.elems[3][1] = 0;
    mat.elems[3][2] = 0;
    mat.elems[3][3] = 1;

    return ge_m4x4_mult(input, mat);
}

ge_m4x4_t ge_m4x4_mult_n(u32_t m4x4_count, ...) {
    va_list matrices;
    va_start(matrices, m4x4_count);
        ge_m4x4_t ident = ge_identity_m4x4();
        for (uint32_t i = 0; i < m4x4_count; ++i) {
            ident = ge_m4x4_mult(ident, va_arg(matrices, ge_m4x4_t));
        }

    va_end(matrices);

    return ident;
}


ge_v4_t ge_m4x4_mult_v4(ge_m4x4_t m, ge_v4_t v) {
    return ge_mk_v4(
                m.elems[0][0] * v.x + m.elems[1][0] * v.y + m.elems[2][0] * v.z + m.elems[3][0] * v.w,  
                m.elems[0][1] * v.x + m.elems[1][1] * v.y + m.elems[2][1] * v.z + m.elems[3][1] * v.w,  
                m.elems[0][2] * v.x + m.elems[1][2] * v.y + m.elems[2][2] * v.z + m.elems[3][2] * v.w,  
                m.elems[0][3] * v.x + m.elems[1][3] * v.y + m.elems[2][3] * v.z + m.elems[3][3] * v.w
         );
}


ge_v3_t ge_m4x4_mult_v3(ge_m4x4_t m, ge_v3_t v) {
    return ge_v4_to_v3(ge_m4x4_mult_v4(m, ge_mk_v4(v.x, v.y, v.z, 1)));
}


ge_m4x4_t ge_mk_ortho_projection_m4x4(f32_t l, f32_t r, f32_t b, f32_t t, f32_t n, f32_t f) {
    return ge_mk_m4x4
    (
        
        2.0f / (r - l), 0, 0,  0,
        0, 2.0f / (t - b), 0, 0,
        0, 0, -2.0f / (f - n), 0,
        -(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n), 1.0f
               
    );

}



ge_m4x4_t ge_mk_perspective_projection_m4x4(f32_t fov, f32_t asp_ratio, f32_t n, f32_t f) {
    ge_m4x4_t result = ge_zero_m4x4(); 

    f32_t q = 1.0f / (f32_t)tan(ge_deg_to_rad(0.5f * fov));
    f32_t a = q / asp_ratio;
    f32_t b = (n + f) / (n - f);
    f32_t c = (2.0f * n * f) / (n - f);

    result.elems[0][0] = a;
    result.elems[1][1] = q;
    result.elems[2][2] = b;
    result.elems[3][2] = c;
    result.elems[3][3] = -1.0f;

    // a, 0, 0,  0,
    // 0, q, 0,  0,
    // 0, 0, b,  0,
    // 0, 0, c, -1
    return result;
}


ge_m4x4_t ge_m4x4_lookat(ge_v3_t pos, ge_v3_t target, ge_v3_t up) {
    ge_sub_v3(&target, &pos);
    ge_normal_v3(&target);
    ge_v3_t f = target; 

    ge_v3_t s = ge_v3_cross_prod(&f, &up);
    ge_normal_v3(&s);

    ge_v3_t u = ge_v3_cross_prod(&s, &f);

    ge_m4x4_t result = ge_identity_m4x4();
    result.elems[0][0] = s.x;
    result.elems[1][0] = s.y;
    result.elems[2][0] = s.z;

    result.elems[0][1] = u.x;
    result.elems[1][1] = u.y;
    result.elems[2][1] = u.z;

    result.elems[0][2] = -f.x;
    result.elems[1][2] = -f.y;
    result.elems[2][2] = -f.z;

    result.elems[3][0] = -ge_v3_dot_prod(&s, &pos);;
    result.elems[3][1] = -ge_v3_dot_prod(&u, &pos);
    result.elems[3][2] = ge_v3_dot_prod(&f, &pos); 

    return result;   
}
