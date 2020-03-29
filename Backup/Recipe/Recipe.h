#ifndef Recipe_h
#define Recipe_h

#include "Arduino.h"
#include "../Ingredient/Ingredient.h"

class Recipe: public Ingredient {
    private:
        const struct RC *components;
        uint8_t size;

        uint8_t findSize();

    public:
        Recipe (const RC components_[]) {
            components = components_;
            size = findSize();
        }

        Recipe () {}
        ~Recipe() {}

        Ingredient getIngredient(uint8_t a);
        float getIngVolume(uint8_t a);
        uint8_t getSize();
};

struct RC {
    public:
    Ingredient ing;
    float volume;
};

#endif