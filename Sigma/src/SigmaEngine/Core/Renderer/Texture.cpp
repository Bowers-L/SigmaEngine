//#include "Texture.h"
//#include "Engine/Log.h"
//
//namespace texture {
//	namespace {
//		SDL_Rect GetDestRect(SDL_Texture* texture, int x, int y) {
//			SDL_Rect dest;
//			dest.x = x;
//			dest.y = y;
//
//			SDL_CALL(SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h));
//			return dest;
//		}
//	}
//
//	SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* fileName) {
//
//		SDL_Texture* texture;
//
//		DEBUG_LOG("Loading Texture %s", fileName);
//		
//		texture = IMG_LoadTexture(renderer, fileName);
//
//		return texture;
//	}
//
//	void BlitTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, float scaleW, float scaleH) {
//		SDL_Rect dest = GetDestRect(texture, x, y);
//		dest.w *= scaleW;
//		dest.h *= scaleH;
//		SDL_RenderCopy(renderer, texture, NULL, &dest);
//	}
//
//	void BlitTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
//		BlitTexture(renderer, texture, x, y, 1, 1);
//	}
//}