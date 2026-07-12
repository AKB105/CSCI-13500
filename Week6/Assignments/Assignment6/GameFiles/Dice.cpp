#include "Dice.h"
#include <cstdlib>
#include <ctime>
 
// TODO: Implement rollDice().
// - Should return a random integer between 1 and 6, inclusive.
// - Think carefully about where to seed the random number generator.
//   If you seed it INSIDE this function, what happens every time it's called?
int RollDice() {
    // TODO: Replace this placeholder
    //Note: In my rock paper scissors game, I used srand(time(0)) at the beginning of main() to avoid patterns. 
    //However, this new method should work aswell, as it keeps the boolean false, no matter how many times the function is called.
    static bool reset_seed = false;
    if (!reset_seed) {
        srand(time(nullptr));
        reset_seed = true;
    }

    return rand() % 6 + 1;
}