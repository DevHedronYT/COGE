#include <tex.h>
#include <string.h>

void coge_gen_texture_t(coge_texture_t * tex) {
    stbi_set_flip_vertically_on_load(1);
    
    unsigned int color;

    if (strcmp(tex -> m_path, "") != 0) {
	tex -> m_buffer = stbi_load(tex -> m_path, &tex -> m_width, &tex -> m_height, &tex -> m_bpp, 4);
    }

    else {
	unsigned int color = 0xffffffff;
    }

    glGenTextures(1, &tex -> m_id);
    glBindTexture(GL_TEXTURE_2D, tex -> m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (strcmp(tex -> m_path, "") != 0) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex -> m_width, tex -> m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex -> m_buffer);
    }

    else {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, tex -> m_id);

    if (tex -> m_buffer) {
	stbi_image_free(tex -> m_buffer);
    }
    
}

void coge_bind_texture_t(coge_texture_t * tex) { 
    glActiveTexture(tex -> m_slot);
    glBindTexture(GL_TEXTURE_2D, tex -> m_id);
   
}



