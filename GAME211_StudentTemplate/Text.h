#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_test_font.h>
#include <SDL_ttf.h>

class Text{
public:
	SDL_Surface* displayText;
	TTF_Font* font;
	int size;
	int x = 0;
	int y = 0;
	const char* file;
	const char* text;

	Text(const char* _file, int _size, const char* _text);
	~Text();
	void Draw(SDL_Renderer* renderer);
	void UpdateText(std::string _text);
};

