#include "RenderUtil.h"
//
//namespace core {
//	void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
//
//		int r2 = SDL_pow(radius, 2);
//
//		//Loop on a square enclosing the circle.
//		for (int x = centerX - radius; x <= centerX + radius; x++) {
//			for (int y = centerY - radius; y <= centerY + radius; y++) {
//				//Circle Equation: (x-centerX)^2 + (y-centerY)^2 = radius^2
//				int x2 = SDL_pow(x - centerX, 2);
//				int y2 = SDL_pow(y - centerY, 2);
//				if (x2 + y2 <= r2) {
//					SDL_RenderDrawPoint(renderer, x, y);
//				}
//			}
//		}
//	}
//
//	void drawRect(SDL_Renderer* renderer, int x, int y, int width, int height) {
//		SDL_Rect rect;
//		rect.x = x;
//		rect.y = y;
//		rect.w = width;
//		rect.h = height;
//		SDL_RenderDrawRect(renderer, &rect);
//	}
//}