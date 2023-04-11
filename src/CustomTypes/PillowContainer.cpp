#include "CustomTypes/PillowContainer.hpp"
#include "logging.hpp"

DEFINE_TYPE(CustomPillows, PillowContainer);

namespace CustomPillows {
    void PillowContainer::Awake() {
        INFO("Piles array: {}", piles.convert());
        if (piles) {
            INFO("Size: {}", piles.size());
        }
    }
}
