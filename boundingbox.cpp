/**
 * \file boundingbox.cpp
 * \author CS 70 Provided Code
 *
 * \brief Implements the BoundingBox class
 *
 */

#include "boundingbox.hpp"

#include <algorithm>  // for std::min and std::max

BoundingBox::BoundingBox(int x, int y, int width, int height)
    : x_{x}, y_{y}, width_{width}, height_{height} {
}

void BoundingBox::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void BoundingBox::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}

bool BoundingBox::isOverlappingWith(const BoundingBox& other) const {
    // Two boxes overlap if they share any area
    // They don't overlap if one is completely to the left, right, above, or
    // below the other
    return !(x_ >= other.x_ + other.width_ || other.x_ >= x_ + width_
             || y_ >= other.y_ + other.height_ || other.y_ >= y_ + height_);
}

bool BoundingBox::isContainedIn(const BoundingBox& container) const {
    return x_ >= container.x_ && y_ >= container.y_
           && x_ + width_ <= container.x_ + container.width_
           && y_ + height_ <= container.y_ + container.height_;
}

BoundingBox BoundingBox::findUnion(const BoundingBox& other) const {
    int new_x = std::min(x_, other.x_);
    int new_y = std::min(y_, other.y_);
    int new_right = std::max(x_ + width_, other.x_ + other.width_);
    int new_bottom = std::max(y_ + height_, other.y_ + other.height_);
    return BoundingBox(new_x, new_y, new_right - new_x, new_bottom - new_y);
}

BoundingBox BoundingBox::findIntersection(const BoundingBox& other) const {
    int new_x = std::max(x_, other.x_);
    int new_y = std::max(y_, other.y_);
    int new_right = std::min(x_ + width_, other.x_ + other.width_);
    int new_bottom = std::min(y_ + height_, other.y_ + other.height_);
    if (new_x >= new_right || new_y >= new_bottom) {
        // No intersection
        return BoundingBox();
    }
    return BoundingBox(new_x, new_y, new_right - new_x, new_bottom - new_y);
}

bool BoundingBox::includesPoint(int x, int y) const {
    return x >= x_ && x < x_ + width_ && y >= y_ && y < y_ + height_;
}

void BoundingBox::wrapWithin(const BoundingBox& bounds) {
    if (!isContainedIn(bounds)) {
        // to right of box
        if (x_ > bounds.x_ + bounds.width_) {
            x_ = bounds.x_ - width_;
        }
        // to left of box
        if (x_ + width_ < bounds.x_) {
            x_ = bounds.x_ + bounds.width_;
        }
        // below box
        if (y_ > bounds.y_ + bounds.height_) {
            y_ = bounds.y_ - height_;
        }
        // above box
        if (y_ + height_ < bounds.y_) {
            y_ = bounds.y_ + bounds.height_;
        }
    }
}
