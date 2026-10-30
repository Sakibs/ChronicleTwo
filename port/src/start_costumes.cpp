#include "start_costumes.hpp"

#include "memcard.hpp"
#include "userdata.hpp"

namespace {
// The item types the costume screen lists: Max's (5 to 7) and Monica's (8 to 10), as UpdateCostumeList reads them.
constexpr int kFirstCostumeType = 5;
constexpr int kLastCostumeType = 10;

template <typename Visit> void ForEachCostume(Visit visit) {
    // One entry per costume flag bit, plus GetCostumeList's terminator.
    short list[64 + 1];
    for (int type = kFirstCostumeType; type <= kLastCostumeType; ++type) {
        GetCostumeList(~0UL, type, list);
        for (const short *item = list; *item >= 0; ++item) {
            visit(*item);
        }
    }
}
} // namespace

u64 AllCostumeBits() {
    u64 bits = 0;
    ForEachCostume([&](int item_no) {
        if (const COSBIT_INFO *info = GetCosInfo(item_no)) {
            bits |= u64{1} << info->bit_no;
        }
    });
    return bits;
}

void GiveAllCostumes(CUserDataManager *user_data) {
    ForEachCostume([&](int item_no) {
        if (user_data->SearchAllHaveItem(item_no) == nullptr) {
            user_data->GetItem(item_no, 1);
        }
    });
    user_data->SetCostumeBit(user_data->GetCostumeBit() | AllCostumeBits());
}
