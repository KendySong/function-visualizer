#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Texture.hpp"
#include "../App/Log.hpp"

Texture::Texture(const char* texturePath, int slot)
{
	m_slot = slot;
	m_textureID = 0;

	int width;
	int height;
	int	nbChan;
	stbi_set_flip_vertically_on_load(true);
	uint8_t* pixels = stbi_load(texturePath, &width, &height, &nbChan, 0);
	
	if (pixels == NULL)
	{
		Log::instance()->log("[ERROR] texture " + std::string(texturePath) + " not found\n", RED);
		return;
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTextureUnit(m_slot, m_textureID);
	stbi_image_free(pixels);
}

unsigned int Texture::getTextureID() noexcept
{
	return m_textureID;
}