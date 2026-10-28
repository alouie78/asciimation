/**
 * \file asciimation.cpp
 * \author CS 70 Provided Code
 *
 * \brief Implements the Asciimation class
 *
 */

#include "display.hpp"
#include "asciimation.hpp"
#include "sprite.hpp"

#include <iostream>
#include <unistd.h>

Asciimation::Asciimation()
    : movieScreenBounds_{0, 0, MOVIE_WIDTH, MOVIE_HEIGHT} {
}

void Asciimation::play(Scene& scene) {
    // Time to sleep between screen refreshes
    const int PAUSE_TIME_IN_MICROSECONDS = 40000;

    Display display{MOVIE_WIDTH, MOVIE_HEIGHT};

    // Play the movie by refreshing the screen with new data, every so often
    int key = 0;
    bool finished = false;
    int numsprites = scene.getNumSprites();

    while (!finished) {
        clearFrame();

        // Render and move all sprites
        for (int i = 0; i < numsprites; ++i) {
            renderSprite(scene.getSprite(i));
        }

        // Show the frame on the screen
        copyToScreen(display);
        display.refresh();

        // Sleep between updates
        usleep(PAUSE_TIME_IN_MICROSECONDS);

        // Check to see if the user has entered 'q' to quit
        key = display.checkForKeypress();
        if (key == 'q') {
            finished = true;
        }

        // Update the scene for the next frame
        scene.advance(key, movieScreenBounds_);
    }
}

void Asciimation::clearFrame() {
    for (int i = 0; i < MOVIE_WIDTH * MOVIE_HEIGHT; ++i) {
        frame_[i] = ' ';
    }
}

// Don't understand why this is not printing out the correct sprites
// Asked grutors for helpl, compared with classmates, and should be correct
// Don't know where we went wrong, looking for an explanation!!
void Asciimation::renderSprite(const Sprite& sprite) {
    BoundingBox spriteBounds = sprite.getBoundingBox();
    BoundingBox overlap = spriteBounds.findIntersection(movieScreenBounds_);
    for (int y = 0; y < overlap.height_; ++y) {
        for (int x = 0; x < overlap.width_; ++x) {
            char character =
                    sprite.getCharAt(x + (overlap.x_ - spriteBounds.x_),
                    y + (overlap.y_ - spriteBounds.y_));
            frame_[(overlap.y_ + y) * MOVIE_WIDTH +
                    (overlap.x_ + x)] = character;
        }
    }
}

void Asciimation::copyToScreen(Display& display) const {
    for (int y = 0; y < MOVIE_HEIGHT; ++y) {
        for (int x = 0; x < MOVIE_WIDTH; ++x) {
            display.putCharAt(movieScreenBounds_.x_ + x,
                                movieScreenBounds_.y_ + y,
                              frame_[y * MOVIE_WIDTH + x]);
        }
    }
}
