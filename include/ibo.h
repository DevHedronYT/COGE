#ifndef _COGE_INDEXBUFF 
    
    #define _COGE_INDEXBUFF
    #include <stdio.h>
    #include <gl.h>

    typedef struct {
	const unsigned int * m_data;
	unsigned int m_size;
	int m_usage; 
	unsigned int m_ibo;
	unsigned int m_count;
    } coge_ibo_t;
    
    void coge_gen_ibo_t   (coge_ibo_t * indexBuffer);
    void coge_del_ibo_t   (coge_ibo_t * indexBuffer);
    void coge_bind_ibo_t  (coge_ibo_t * indexBuffer);
    void coge_unbind_ibo_t();

#endif
