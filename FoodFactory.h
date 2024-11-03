#pragma once
#include <memory>
#include "Food.h"

enum class FoodType {
    Normal,
    Poisonous
};

class FoodFactory {
public:
    static std::unique_ptr<Food> createFood(FoodType type, const std::string& textureFile) {
        switch (type) {
            case FoodType::Normal:
                return std::make_unique<NormalFood>(textureFile);
            case FoodType::Poisonous:
                return std::make_unique<PoisonousFood>(textureFile);
            default:
                throw std::invalid_argument("Unknown food type");
        }
    }
};
