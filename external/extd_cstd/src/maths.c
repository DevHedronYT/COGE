#include <extd_cstd/lib.h>

f32 dist2D(f32 x1, f32 y1, f32 x2, f32 y2) {
    return sqrt(sq(x2 - x1) + sq(y2 - y1));
}

f32 dir2D(f32 x1, f32 y1, f32 x2, f32 y2) {
    return atan2(y2 - y1, x2 - x1);  
}

f32 ilerp(f32 start, f32 stop, f32 amt) {
    return start + (stop - start) * amt; 
}

i64 randnum_gen(i64 lower, i64 upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

v2_t v2_add(v2_t v1, v2_t v2) {
    return mk_v2(v1.x + v2.x, v1.y + v2.y);
}

v2_t v2_sub(v2_t v1, v2_t v2) {
    return mk_v2(v2.x - v1.x, v2.y - v1.y);
}

v2_t v2_lerp(v2_t v1, v2_t v2, f32 amt) {
    v2_t vec;
    vec.x = ilerp(v1.x, v2.x, amt);
    vec.y = ilerp(v1.y, v2.y, amt);
    return vec;
}


void v2_scale(v2_t * v, f32 scalar) {
    assert(v != NULL);
    v -> x *= scalar;
    v -> y *= scalar;
}

void v2_normalize(v2_t * v) {
    assert(v != NULL);
    f32 mag = v2_mag(*v);

    if (mag != 1.0f) {
        v -> x = v -> x / mag;
        v -> y = v -> y / mag;  
    }
}


void v2_limit(v2_t * v, f32 scalar) {
    assert(v != NULL);
    f32 len = v -> x * v -> x + v -> y * v -> y;
    f32 len_t = scalar * scalar;
    if (len > len_t) {
        v2_normalize(v);
        v2_scale(v, scalar);
    }         
}

void v2_rotate(v2_t * v, f32 theta) {
    assert(v != NULL);
    f32 temp = v -> x;
    v -> x = temp * cosf(theta) - v -> y * sinf(theta);
    v -> y = temp * sinf(theta) + v -> y * cosf(theta);
}

void v2_mag_set(v2_t * v, f32 scalar) {
    assert(v != NULL);
    v2_normalize(v);
    v2_scale(v, scalar);
}

void v2_negate(v2_t * v) {
    assert(v != NULL);
    v -> x = -v -> x;
    v -> y = -v -> y;   
}

f32 v2_mag(v2_t v) {
    return (sqrt(sq(v.x) + sq(v.y))); 
}

f32 v2_angle(v2_t v) {
    return atan2(v.y, v.x);
}

f32 v2_dot_prod(v2_t v1, v2_t v2) {
    return v1.x * v2.x + v1.y * v2.y; 
}

f32 v2_dist_between(v2_t v1, v2_t v2) {
    f32 dx = v1.x - v2.x;
    f32 dy = v1.y - v2.y;
    return sqrt(sq(dx) + sq(dy));
}

f32 v2_angle_between(v2_t v1, v2_t v2) {
    if (v1.x == 0 && v1.y == 0) return 0.0f;
    if (v2.x == 0 && v2.y == 0) return 0.0f;

    f32 dot = v2_dot_prod(v1, v2);
    f32 v1mag = v2_mag(v1);
    f32 v2mag = v2_mag(v2);
    f32 amt = dot / (v1mag * v2mag);

    if (amt <= -1) {
        return pi;
    } else if (amt >= 1) {
        return 0;
    }
    return acos(amt);
}

v2_t v2_projection(v2_t v1, v2_t v2) {
    f32 dot = v2_dot_prod(v1, v2);
    f32 len = v2_dot_prod(v2, v2);
    if (len == 0.0f) return v2;

    v2_t return_val = v2;
    v2_scale(&return_val, dot / len);
    return return_val;
}

v3_t v3_add(v3_t v1, v3_t v2) {
    return mk_v3(v1.x + v2.x,
                 v1.y + v2.y,
                 v1.z + v2.z);
}

v3_t v3_sub(v3_t v1, v3_t v2) {
    return mk_v3(v2.x - v1.x,
                 v2.y - v1.y,
                 v2.z - v1.z);
}

v3_t v3_lerp(v3_t v1, v3_t v2, f32 amt) {
    v1.x = ilerp(v1.x, v2.x, amt);
    v1.y = ilerp(v1.y, v2.y, amt);   
    v1.z = ilerp(v1.z, v2.z, amt);
    return v1;
}

void v3_limit(v3_t * v, f32 scalar) {
    assert(v != NULL);
    f32 len = sq(v -> x) + sq(v -> y);
    f32 len_t = sq(scalar);
    if (len > len_t) {
        v3_normalize(v);
        v3_scale(v, scalar);
    }   
}

void v3_scale(v3_t * v, f32 scalar) {
    assert(v != NULL);
    v -> x *= scalar;
    v -> y *= scalar;
    v -> z *= scalar;
}

void v3_normalize(v3_t * v) {
    assert(v != NULL);
    f32 mag = v3_mag(*v);


    if (mag != 1.0f) {
        v -> x = v -> x / mag;
        v -> y = v -> y / mag;
        v -> z = v -> z / mag;
    }
}

void v3_mag_set(v3_t * v, f32 scalar) {
    assert(v != NULL);
    v3_normalize(v);
    v3_scale(v, scalar);
}

void v3_negate(v3_t * v) {
    assert(v != NULL);
    v -> x = -v -> x;
    v -> y = -v -> y;
    v -> z = -v -> z;
}

f32 v3_mag(v3_t v) {
    return (sqrt(sq(v.x) + sq(v.y) + sq(v.z))); 
}

f32 v3_dot_prod(v3_t v1, v3_t v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;  
}

v3_t v3_cross_prod(v3_t v1, v3_t v2) {
    v3_t v_o;
    v_o.x = v1.y * v2.z - v1.z * v2.y;
    v_o.y = v1.z * v2.x - v1.z * v2.z;
    v_o.z = v1.x * v2.y - v1.y * v2.x;
    return v_o;
}


f32 v3_dist_between(v3_t v1, v3_t v2) {
    f32 dx = v2.x - v1.x;
    f32 dy = v2.y - v1.y;
    f32 dz = v2.z - v1.z;
    return sqrt(sq(dx) + sq(dy) + sq(dz)); 
}



f32 v3_angle_between(v3_t v1, v3_t v2) {
    if (v1.x == 0 && v1.y == 0) return 0.0f;
    if (v2.x == 0 && v2.y == 0) return 0.0f;
    if (v2.z == 0 && v2.z == 0) return 0.0f;

    f32 dot = v3_dot_prod(v1, v2);
    f32 v1mag = v3_mag(v1);
    f32 v2mag = v3_mag(v2);
    f32 amt = dot / (v1mag * v2mag);

    if (amt <= -1) {
        return pi;
    } else if (amt >= 1) {
        return 0;
    }
    return acos(amt);   
}

v3_t v3_projection(v3_t v1, v3_t v2) {
    f32 dot = v3_dot_prod(v1, v2);
    f32 len = v3_dot_prod(v2, v2);
    if (len == 0.0f) return v2;

    v3_t return_val = v2;
    v3_scale(&return_val, dot / len);
    return return_val;   
}

v4_t v4_add(v4_t v1, v4_t v2) {
    return mk_v4((v1.x + v2.x),
          (v1.y + v2.y),
          (v1.z + v2.z),
          (v1.w + v2.w));  
}

v4_t v4_sub(v4_t v1, v4_t v2) {
    return mk_v4((v2.x - v1.x),
          (v2.y - v1.y),
          (v2.z - v1.z),
          (v2.w - v1.w));    
}

v4_t v4_lerp(v4_t v1, v4_t v2, f32 amt) {
    v4_t vec;
    vec.x = ilerp(v1.x, v2.x, amt);
    vec.y = ilerp(v1.y, v2.y, amt);   
    vec.z = ilerp(v1.z, v2.z, amt);
    vec.w = ilerp(v1.w, v2.w, amt);
    return vec;
}

void v4_limit(v4_t * v, f32 scalar) {
    assert(v != NULL);
    f32 len = sq(v -> x) + sq(v -> y);
    f32 len_t = sq(scalar);
    if (len > len_t) {
        v4_normalize(v);
        v4_scale(v, scalar);
    }        
}

void v4_scale(v4_t * v, f32 scalar) {
    assert(v != NULL);
    v -> x *= scalar;
    v -> y *= scalar;  
    v -> z *= scalar;
    v -> w *= scalar;
}

void v4_normalize(v4_t * v) {
    assert(v != NULL);
    f32 mag = v4_mag(*v);
    if (mag != 1.0f) {
        v -> x = v -> x / mag;
        v -> y = v -> y / mag;
        v -> z = v -> z / mag;
        v -> w = v -> w / mag;
    }
}

void v4_mag_set(v4_t * v, f32 scalar) {
    assert(v != NULL);
    v4_normalize(v);
    v4_scale(v, scalar); 
}

void v4_negate(v4_t * v) {
    assert(v != NULL);
    v -> x = -v -> x;
    v -> y = -v -> y;
    v -> z = -v -> z;
    v -> w = -v -> w;
}


f32 v4_mag(v4_t v) {
    return (sqrt(sq(v.x) + sq(v.y) + sq(v.z) + sq(v.w))); 
}

f32 v4_dot_prod(v4_t v1, v4_t v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;  
}

f32 v4_dist_between(v4_t v1, v4_t v2) {
    f32 dx = v2.x - v1.x;
    f32 dy = v2.y - v1.y;
    f32 dz = v2.z - v1.z;
    f32 dw = v2.w - v1.w;
    return sqrt(sq(dx) + sq(dy) + sq(dz) + sq(dw)); 
}

// projects v1 on v2
v4_t v4_projection(v4_t v1, v4_t v2) {
    f32 dot = v4_dot_prod(v1, v2);
    f32 len = v4_dot_prod(v2, v2);
    if (len == 0.0f) return v2;

    v4_t return_val = v2;
    v4_scale(&return_val, dot / len);
    return return_val;   
}

v3_t v2_to_v3(const v2_t v) {
    return mk_v3(v.x, v.y, 1);
}

v4_t v3_to_v4(const v3_t v) {
    return mk_v4(v.x, v.y, v.z, 1);
}

v3_t v4_to_v3(const v4_t v) {
    return mk_v3(v.x, v.y, v.z);
}

v2_t v3_to_v2(const v3_t v) {
    return mk_v2(v.x, v.y);
}


m4x4_t mk_m4x4(f32 m00, f32 m01, f32 m02, f32 m03,
               f32 m04, f32 m05, f32 m06, f32 m07,
               f32 m08, f32 m09, f32 m10, f32 m11,
               f32 m12, f32 m13, f32 m14, f32 m15) { 
    m4x4_t mat = {{
        {m00, m01, m02, m03},
        {m04, m05, m06, m07},
        {m08, m09, m10, m11},
        {m12, m13, m14, m15}
    }};

    return mat;
}

m4x4_t mk_zero_m4x4() {
    return mk_m4x4( 
                    0, 0, 0, 0,
                    0, 0, 0, 0, 
                    0, 0, 0, 0, 
                    0, 0, 0, 0
                  );
}

m4x4_t mk_identity_m4x4() {
    return mk_m4x4(
                     1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1
                    
                  );
}

m4x4_t mk_diag_m4x4(f32 val) {
    return mk_m4x4(
                    val, 000, 000, 000,
                    000, val, 000, 000,
                    000, 000, val, 000,
                    000, 000, 000, val
                  );
}

m4x4_t m4x4_add(m4x4_t m1, m4x4_t m2) {
    for (u16 i = 0; i < 4; i++) {
        for (u16 j = 0; j < 4; j++) {
            m1.elems[i][j] += m2.elems[i][j];
        }
    }
    m4x4_t mat = m1;
    return mat;
}

m4x4_t m4x4_sub(m4x4_t m1, m4x4_t m2) {    
    for (u16 i = 0; i < 4; i++) {
        for (u16 j = 0; j < 4; j++) {
            m2.elems[i][j] -= m1.elems[i][j];
        }
    }
    m4x4_t mat = m2;
    return mat;
} 
m4x4_t m4x4_mult(m4x4_t m1, m4x4_t m2) {
 	m4x4_t result = mk_zero_m4x4(); 
	for (u32 y = 0; y < 4; ++y) {
		for (u32 x = 0; x < 4; ++x) {
			f32 sum = 0.0f;
			for (u32 e = 0; e < 4; ++e) {
				sum += m1.elems[e][x] * m2.elems[y][e];
			}
			result.elems[y][x] = sum;
		}
	}

	return result;
} 

m4x4_t m4x4_mult_n(u32 m4x4_count, ...) {
    va_list matrices;
    va_start(matrices, m4x4_count);
        m4x4_t ident = mk_identity_m4x4();
        for (u32 i = 0; i < m4x4_count; ++i) {
            ident = m4x4_mult(ident, va_arg(matrices, m4x4_t));
        }

    va_end(matrices);

    return ident;
}

v3_t m4x4_mult_v3(m4x4_t m, v3_t v) {
    return v4_to_v3(m4x4_mult_v4(m, mk_v4(v.x, v.y, v.z, 1)));
}

v4_t m4x4_mult_v4(m4x4_t m, v4_t v) {
    return mk_v4(
                m.elems[0][0] * v.x + m.elems[1][0] * v.y + m.elems[2][0] * v.z + m.elems[3][0] * v.w,  
                m.elems[0][1] * v.x + m.elems[1][1] * v.y + m.elems[2][1] * v.z + m.elems[3][1] * v.w,  
                m.elems[0][2] * v.x + m.elems[1][2] * v.y + m.elems[2][2] * v.z + m.elems[3][2] * v.w,  
                m.elems[0][3] * v.x + m.elems[1][3] * v.y + m.elems[2][3] * v.z + m.elems[3][3] * v.w
         );
}

m4x4_t m4x4_scale_by_v3(m4x4_t mat, const v3_t vector) {
    mat.elems[0][0] *= vector.x;
    mat.elems[1][1] *= vector.y;
    mat.elems[2][2] *= vector.z;
    return mat;
}

// Takes in an identity matrix
m4x4_t m4x4_translate_by_v3(m4x4_t mat, const v3_t vector) {
    mat.elems[3][0] += vector.x;
    mat.elems[3][1] += vector.y;
    mat.elems[3][2] += vector.z;
    return mat;
}

m4x4_t m4x4_rotate_by_v3(f32 degrees, v3_t axis) {
    m4x4_t mat = mk_identity_m4x4();

    f32 a = degrees;
    f32 c = (f32)cosf(a);
    f32 s = (f32)sinf(a);

    v3_normalize(&axis);
    f32 x = axis.x;
    f32 y = axis.y;
    f32 z = axis.z;

    //First column
    mat.elems[0][0] = c + (x * x) * (1 - c);
    mat.elems[0][1] = x * y * (1 - c) - (z * s);
    mat.elems[0][2] = x * z * (1 - c) + (y * s);

    //Second column
    mat.elems[1][0] = y * x * (1 - c) + z * s;
    mat.elems[1][1] = c + y * y * (1 - c);
    mat.elems[1][2] = y * z * (1 - c) - x * s;

    //Third column
    mat.elems[2][0] = z * x * (1 - c) - y * s;
    mat.elems[2][1] = z * y * (1 - c) + x * s;
    mat.elems[2][2] = c + z * z * (1 - c);

    return mat;

}




m4x4_t m4x4_orthographic_projection(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f) {
    return mk_m4x4
    (
        
        2.0f / (r - l), 0, 0,  0,
        0, +2.0f / (t - b), 0, 0,
        0, 0, -2.0f / (f - n), 0,
        -(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n), 1.0f
               
    );
}



m4x4_t m4x4_perspective_projection(f32 fov, f32 asp_ratio, f32 n, f32 f) {
    m4x4_t result = mk_zero_m4x4(); 

    f32 q = 1.0f / (f32)tan(deg_to_rad(0.5f * fov));
    f32 a = q / asp_ratio;
    f32 b = (n + f) / (n - f);
    f32 c = (2.0f * n * f) / (n - f);

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


m4x4_t m4x4_lookat(v3_t pos, v3_t target, v3_t up) {

    v3_t f = v3_sub(target, pos);
    v3_t s = v3_sub(f, up);

    v3_normalize(&f);
    v3_normalize(&s);
    v3_t u = v3_cross_prod(s, f);

    m4x4_t result = mk_identity_m4x4();
    result.elems[0][0] = s.x;
    result.elems[1][0] = s.y;
    result.elems[2][0] = s.z;

    result.elems[0][1] = u.x;
    result.elems[1][1] = u.y;
    result.elems[2][1] = u.z;

    result.elems[0][2] = -f.x;
    result.elems[1][2] = -f.y;
    result.elems[2][2] = -f.z;

    result.elems[3][0] = -v3_dot_prod(s, pos);;
    result.elems[3][1] = -v3_dot_prod(u, pos);
    result.elems[3][2] = v3_dot_prod(f, pos); 

    return result;   
}
