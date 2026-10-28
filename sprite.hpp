/**
 * \file sprite.hpp
 * \author CS 70 Provided Code
 *
 * \brief Interface definition for the Sprite class
 *
 * \details Represents a single ASCIImation sprite, including its position,
 * velocity, and character data.
 */

#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <utility>  // actually unnecessary but CPPLINT (incorrectly) wants it
#include "boundingbox.hpp"

/**
 * \class Sprite
 * \brief Holds the contents of a single ASCIImation sprite
 *
 * \details
 * Stores an array of characters that will be displayed to the screen, along
 * with the sprite's current location and velocity. Sprites can have variable
 * dimensions up to the maximum size.
 *
 */
class Sprite {
 public:
    // Maximum sprite dimensions
    static constexpr int MAX_SPRITE_DATA = 800;  // for fixed-size array

    /**
     * \brief Reads a text file containing the characters for a sprite
     * \param fname The filename to read the sprite from
     * \param x Initial x position of the sprite
     * \param y Initial y position of the sprite
     * \post The sprite's character array is populated with data from the file
     */
    Sprite(std::string fname, int x, int y);

    /**
     * \brief Reads an istream containing the characters for a sprite
     * \param input The input stream to read the sprite from
     * \param x Initial x position of the sprite
     * \param y Initial y position of the sprite
     * \post The sprite's character array is populated with data from the stream
     */
    Sprite(std::istream& input, int x, int y);

    // disable default/copy constructors and assignment operator
    Sprite() = delete;
    Sprite(const Sprite& other) = delete;
    Sprite& operator= (const Sprite& other) = delete;

    /**
     * \brief returns the sprite's bounding box
     * \returns returns the sprite's bounding box
     */
    BoundingBox getBoundingBox() const;

    /**
     * \brief sets the sprite's velocity
     * \param vx new x velocity of the sprite
     * \param vy new y velocity of the sprite
     */
    void setVelocity(int vx, int vy);

    /**
     * \brief sets the sprite's position
     * \param x new x position of the sprite
     * \param y new y position of the sprite
     */
    void setPosition(int x, int y);

     /**
     * \brief returns the character at the specified position in the sprite's character array
     * \param x the x coordinate of the sprite where the character is positioned
     * \param y the y coordinate of the sprite where the character is positioned
     * \returns returns the character at the specified position in the sprite's character array
     */
    char getCharAt(int x, int y) const;

    /**
     * \brief updates the sprite's position based on its velocity, wrapping around the screen if necessary
     * \param screenBounds a constant reference to the size of the screen    
     */
    void move(const BoundingBox& screenBounds);


 private:
    // The sprite's position and size
    BoundingBox bounds_;

    // Velocity in pixels per frame
    int velocityX_;
    int velocityY_;

    // array to hold MAX_SPRITE_DATA characters of sprite data
    char contents_[MAX_SPRITE_DATA];

    // Helper function to read sprite data from a stream
    void readFromStream(std::istream& input);
};

#endif  // SPRITE_HPP_INCLUDED
