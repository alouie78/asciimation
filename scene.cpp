/**
 * \file scene.cpp
 * \author Amanda Louie, Catherine Buckner
 *
 * \brief Implements the Scene class
 *
 */

#include "scene.hpp"

#include <iostream>
#include <unistd.h>

Scene::Scene()
    : sprites_{
          {"mystery1.tsprite", 30, 5},  // mystery image at column 30, row 5
          {"cactus.tsprite", 60, 15},   // cactus at column 60, row 15
          {"book.tsprite", 10, 15}      // book at column 10, row 15
      } {
    sprites_[0].setVelocity(1, 0);  // Just horizontal scrolling
    sprites_[1].setVelocity(1, 0);  // Just horizontal scrolling
    sprites_[2].setVelocity(1, 0);  // Just horizontal scrolling
}

void Scene::advance(int key, BoundingBox screenBounds) {
    (void)key;
    for (int i = 0; i < NUM_SPRITES; ++i) {
        sprites_[i].move(screenBounds);
    }
}

const Sprite& Scene::getSprite(int index) const {
    return sprites_[index];
}

int Scene::getNumSprites() const {
    return NUM_SPRITES;
}
