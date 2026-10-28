/**
 * \file sprite.cpp
 * \author CS 70 Provided Code
 *
 * \brief Implements the Sprite class
 *
 */

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

#include "sprite.hpp"

Sprite::Sprite(std::string fname, int x, int y)
    : bounds_{x, y, 0, 0},  // Will set actual size after reading file
      velocityX_{0},
      velocityY_{0} {
    fname = "spriteImages/" + fname;
    std::ifstream inputFile(fname);
    if (inputFile.fail()) {
        throw std::runtime_error("Could not open sprite file: " + fname);
    }
    readFromStream(inputFile);
}

Sprite::Sprite(std::istream& inputFile, int x, int y)
    : bounds_{x, y, 0, 0},  // Will set actual size after reading file
      velocityX_{0},
      velocityY_{0} {
    readFromStream(inputFile);
}

void Sprite::readFromStream(std::istream& inputFile) {
    // Read dimensions from file
    int width = 0;
    int height = 0;
    inputFile >> width;
    inputFile >> height;

    inputFile.get();  // Read past the newline character after the height

    // Validate that the sprite fits within our maximum dimensions
    if (width * height > MAX_SPRITE_DATA || width <= 0 || height <= 0) {
        throw std::runtime_error("Sprite dimensions are invalid");
    }

    if (inputFile.fail()) {
        throw std::runtime_error("Couldn't read sprite dimensions");
    }

    // Update bounds with actual dimensions
    bounds_.width_ = width;
    bounds_.height_ = height;

    // Initialize the entire array to spaces (for safety)
    for (int i = 0; i < MAX_SPRITE_DATA; ++i) {
        contents_[i] = ' ';
    }

    // Read in characters from the text file, copying them into the character
    // array. We only read up to the actual sprite dimensions.
    for (int i = 0; i < width * height; ++i) {
        inputFile >> contents_[i];
    }
}

char Sprite::getCharAt(int x, int y) const {
    if (x > bounds_.width_ || y > bounds_.height_ || x < 0 || y < 0) {
        throw std::runtime_error("coordinate invalid");
    }
    return contents_[x + y * bounds_.width_];
}

void Sprite::setPosition(int x, int y) {
    bounds_.x_ = x;
    bounds_.y_ = y;
}

void Sprite::setVelocity(int vx, int vy) {
    velocityX_ = vx;
    velocityY_ = vy;
}

BoundingBox Sprite::getBoundingBox() const {
    return bounds_;
}

void Sprite::move(const BoundingBox& screenBounds) {
    bounds_.x_ = bounds_.x_ + velocityX_;
    bounds_.y_ = bounds_.y_ + velocityY_;

    if (!bounds_.isContainedIn(screenBounds)) {
        bounds_.wrapWithin(screenBounds);
    }
}
