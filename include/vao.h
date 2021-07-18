#ifndef _COGE_VERTEXARR 
    #define _COGE_VERTEXARR
    
    #include <gl.h>

    // Declaration
    typedef struct {
	unsigned int m_vao;
    } coge_vao_t;

    void coge_gen_vao_t   (coge_vao_t * vao);
    void coge_del_vao_t   (coge_vao_t * vao);
    void coge_bind_vao_t  (coge_vao_t *vao);
    void coge_unbind_vao_t();


#endif
