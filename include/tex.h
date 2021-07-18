#ifndef _COGE_TEXTURE
    #define _COGE_TEXTURE

    #include <stb_image.h>
    #include <gl.h>

    typedef struct {
	unsigned int m_id;
	const char * m_path;
	unsigned int m_slot;
	unsigned char * m_buffer;
	int m_width;
	int m_height; 
	int m_bpp;
    } coge_texture_t;

    void coge_gen_texture_t (coge_texture_t * tex); 
    void coge_bind_texture_t(coge_texture_t * tex); 

#endif
