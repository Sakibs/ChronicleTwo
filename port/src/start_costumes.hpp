#pragma once

#include "common.h"

class CUserDataManager;

// CT_START_WITH_ALL_COSTUMES (CMake option, on in the iOS presets) starts every new game with all of Max's and
// Monica's costumes; retail starts with the few the opening costume screen offers.
#ifdef CT_START_WITH_ALL_COSTUMES
inline constexpr bool kStartWithAllCostumes = true;
#else
inline constexpr bool kStartWithAllCostumes = false;
#endif

/**
 * Returns the costume flags with every costume of the costume table collected.
 */
u64 AllCostumeBits();

/**
 * Puts one of each costume the player does not hold yet in the inventory and marks every costume collected.
 */
void GiveAllCostumes(CUserDataManager *user_data);
