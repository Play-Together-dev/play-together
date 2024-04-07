//
// Created by athena on 24/03/24.
//

#ifndef PLAY_TOGETHER_SPECIALBOXES_H
#define PLAY_TOGETHER_SPECIALBOXES_H

#include "Player.h"

class SpecialBoxes {
    private :
        float x; // the horizontal  position
        float y; // the vertical position
        float hight;
        float width;
        /**
         * The player gets slower
         * @param player
         */
        void getSlower(Player* player);
        /**
         * The player gets faster (the speed accelerates)
         * @param player
         */
        void getFaster(Player* player);
        /**
         * The player changes color depending on the one that he is currently
         * @param player
         */
        void changeFigure(Player* player);
        /**
         * The player changes size depending on his current size
         * @param player
         */
        void changeSize(Player* player);
        void getBigger(Player* player);
        void getSmaller(Player* player);
    public:

        SpecialBoxes();

        SpecialBoxes(float X, float Y, float boxHeight , float boxWidth);

        float getHight();

        float getWidth();


        float const getX();

        float const getY();

        bool operator==(SpecialBoxes& box) const;

        /**
         * Responsible to apply the effect of the box on the player
         * @param player the player
         * @param state the effect that will be applied
         */
       void applySpecialBoxPower(Player* player,int state);
        [[nodiscard]] SDL_FRect getBoundingBox() const;

};


#endif //PLAY_TOGETHER_SPECIALBOXES_H
