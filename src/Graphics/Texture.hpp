#include <iostream>

#include <glad/glad.h>

#pragma once
class Texture
{
private :
	unsigned int m_slot;
	unsigned int m_textureID;

public :	
	Texture(const char* texturePath, int slot);
	unsigned int getTextureID() noexcept;
};