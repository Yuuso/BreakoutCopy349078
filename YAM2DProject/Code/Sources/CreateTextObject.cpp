#include "CreateTextObject.h"

#include <TextComponent.h>
#include <Texture.h>


yam2d::GameObject* createTextObject()
{
	yam2d::Texture* fontTexture = new yam2d::Texture("Fonts/font.png");

	// Create font clip areas (sprite sheet), from dat file and texture. Dat-file is made with bitmap font builder.
	yam2d::SpriteSheet* font = yam2d::SpriteSheet::autoFindFontFromTexture(fontTexture, "Fonts/font.dat");

	yam2d::GameObject* gameObject = new yam2d::GameObject(0, 0);
	yam2d::TextComponent* textComponent = new yam2d::TextComponent(gameObject, font);
	gameObject->addComponent(textComponent);
	textComponent->getText()->setText("Text");
	textComponent->getText()->setColor(60, 0, 190);

	return gameObject;
}