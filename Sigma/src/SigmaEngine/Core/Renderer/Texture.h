#pragma once

namespace SigmaEngine {
	class Texture {
	private:
		int m_Width, m_Height, m_nChannels;
		unsigned int m_ID;
	public:
		Texture(const char* imgPath);
		void bind() const;
		void unbind() const;

		int width() const;
		int height() const;
		unsigned int id() const;
	};
}

