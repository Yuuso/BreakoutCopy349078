#pragma once

#include <Texture.h>
#include <GameObject.h>
#include <SpriteComponent.h>


yam2d::GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false)
{
	// Load texture to be used as texture for sprite.
	yam2d::Texture* texture = new yam2d::Texture(bitmapFileName.c_str());

	// If user wants to create texture which white coros is treated as atransparent color.
	if (isWhiteTransparentColor)
	{
		// Set white to transparent. Here color values are from 0 to 255 (RGB)
		texture->setTransparentColor(255, 255, 255);
	}

	// Create new sprite GameObject from texture.
	yam2d::GameObject* gameObject = new yam2d::GameObject(0, 0);
	yam2d::SpriteComponent* sprite = new yam2d::SpriteComponent(gameObject, texture);

	// Resize the sprite to be correct size
	gameObject->setSize(sizeX, sizeY);

	// Add sprite component to game object
	gameObject->addComponent(sprite);
	return gameObject;
}

yam2d::GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor = false)
{
	// Load texture to be used as texture for sprite.
	yam2d::Texture* texture = new yam2d::Texture(bitmapFileName.c_str());

	// If user wants to create texture which white coros is treated as atransparent color.
	if (isWhiteTransparentColor)
	{
		// Set white to transparent. Here color values are from 0 to 255 (RGB)
		texture->setTransparentColor(255, 255, 255);
	}

	// Create new sprite GameObject from texture.
	yam2d::GameObject* gameObject = new yam2d::GameObject(0, 0);
	yam2d::SpriteComponent* sprite = new yam2d::SpriteComponent(gameObject, texture);

	// Resize the sprite to be correct size
	gameObject->setSize(sizeX, sizeY);

	// Specify clip area by start point and size in pixels
	yam2d::Sprite::PixelClip clip;
	clip.topLeft.x = clipStartX;
	clip.topLeft.y = clipStartY;
	clip.clipSize.x = clipSizeX;
	clip.clipSize.y = clipSizeY;

	// Set pixel clip for sprite
	sprite->getSprite()->setClip(float(texture->getWidth()), float(texture->getHeight()), clip);

	// Add sprite component to game object
	gameObject->addComponent(sprite);
	return gameObject;
}