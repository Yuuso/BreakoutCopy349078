#pragma once

#include <GameObject.h>


yam2d::GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false);

yam2d::GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor = false);