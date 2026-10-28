/**
 * \file scene.hpp
 * \author Amanda Louie, Catherine Buckner
 *
 * \brief Provides the interface definition for the Scene class which
 *        manages a scene, including multiple sprites.  It stores the a specific scene.
 *
 */

#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include "sprite.hpp"
#include "boundingbox.hpp"
#include "numsprites.hpp"

#include <string>

/**
 * \class Scene
 * \brief 
 *
 * \details
 *
 */
class Scene {
 public:
    /**
     * \brief  Creates a Scene object containing sprites.
     */
    Scene();

    /**
     * \brief Updates the scene for the next frame.
     * \param key The integer of a charater used to change behavior if necessary (did not implement).
     * \param screenBounds The boundingBox of the screen.
     */
    void advance(int key, BoundingBox screenBounds);

    /**
     * \brief gets the sprite at a specified index.
     * \param index The integer of the desired sprite.
     * \return Sprite in scene at specified index.
     */
    const Sprite& getSprite(int index) const;

    /**
     * \brief gets the number of sprites in the scene.
     * \returns the number of sprites in the scene.
     */
    int getNumSprites() const;

 private:
    // Creates an array for the sprite of size NUM_SPRITES
    Sprite sprites_[NUM_SPRITES];
};

#endif  // ASCIIMATION_HPP_INCLUDED
