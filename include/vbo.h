#ifndef _COGE_VETEXBUFF 
    
    #define _COGE_VETEXBUFF
    #include <gl.h>

    // Declarations
    typedef struct {
	int m_size;
	const void * m_data;
	int m_usage;
	unsigned int m_vbo;
    } coge_vbo_t;

    void coge_gen_vbo_t   (coge_vbo_t * vbo);
    void coge_del_vbo_t   (coge_vbo_t * vbo);
    void coge_bind_vbo_t  (coge_vbo_t * vbo);
    void coge_unbind_vbo_t();

#endif



