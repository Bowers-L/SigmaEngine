#include "Texture.h"

#include "SigmaEngine/Core/Log.h"
#include "SigmaEngine/Util/GLDebug.h"

#include "glad/glad.h"
#include <stb_image.h>

namespace SigmaEngine {
	Texture::Texture(const char* imgPath) {

		//Create a texture buffer on GPU to store the image.
		GLCall(glGenTextures(1, &m_ID));
		bind();

		//Clamp overflowed (s, t)
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		//Linear Filtering
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		//Load the image
		unsigned char* img = stbi_load(imgPath, &m_Width, &m_Height, &m_nChannels, STBI_rgb);
		GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
		SG_ASSERT(img != nullptr, "Could Not Load Image! ", imgPath);
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, img));
		stbi_image_free(img);	//Don't need the image buffer once it's loaded into the texture.

		SG_CORE_INFO("Width: {}", m_Width);
		SG_CORE_INFO("Height: {}", m_Height);
		unbind();
	}

	void Texture::bind() const {
		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
	}

	void Texture::unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	int Texture::width() const {
		return m_Width;
	}

	int Texture::height() const {
		return m_Height;
	}

	unsigned int Texture::id() const {
		return m_ID;
	}
}

