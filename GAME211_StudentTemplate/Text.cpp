#include "Text.h"

Text::Text(const char* _file, int _size, const char* _text) {
	file = _file;
	size = _size;
	text = _text;
	font = TTF_OpenFont(file, size);
	displayText = TTF_RenderText_Solid(font, text, { 255, 255, 255 });
}

Text::~Text() {
	delete file;
	delete text;
	delete font;
	delete displayText;
}

void Text::Draw(SDL_Renderer* renderer) {
	if (!text) {
		std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
	}
	else {
		SDL_Texture* text_texture;
		text_texture = SDL_CreateTextureFromSurface(renderer, displayText);
		SDL_Rect dest = { x, y, displayText->w , displayText->h };
		SDL_RenderCopy(renderer, text_texture, NULL, &dest);

		SDL_DestroyTexture(text_texture);
	}
}