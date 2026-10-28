/**
 * \file our-movie.cpp
 * \author CS 70 Provided Code
 *
 * \brief Provides the main() function for creating and running
 *        a specific asciimation movie.
 *
 */

#include "asciimation.hpp"
#include "scene.hpp"

/**
 * \brief Creates and plays our ASCIImation movie
 */
void makeOurMovie() {
    Scene theScene;
    Asciimation ourMovie;
    ourMovie.play(theScene);
}

int main() {
    makeOurMovie();
    return 0;
}
