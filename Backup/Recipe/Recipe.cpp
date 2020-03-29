#include "Arduino.h"
#include "Recipe.h"

uint8_t Recipe::findSize() {
    return sizeof(components) / sizeof(components[0]);
}


Ingredient Recipe::getIngredient(uint8_t a) {
    return components[a].ing;
}

float Recipe::getIngVolume(uint8_t a) {
    return components[a].volume;
}

uint8_t Recipe:: getSize() {
    return size;
}