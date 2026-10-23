#include "Item.h"
#include <map>

// This function converts a Rarity r to the assigned value in Item.h
int Item::rarValue(Rarity r) {
    return static_cast<int>(r);
}

// It uses a map to convert the inputted rarity string by the user into a enum type with its own value
const std::map<std::string, Item::Rarity> Item::strRarMap = { 
    {"epic", Item::Rarity::epic}, {"rare", Item::Rarity::rare}, {"common", Item::Rarity::common}
};

// Conversely, this function maps the enum class type into the supposed names/strings of the rarity(epic to common)
const std::map<Item::Rarity, std::string> Item::rarStrMap = {
    {Item::Rarity::epic, "epic"}, {Item::Rarity::rare, "rare"}, {Item::Rarity::common, "common"}, {Item::Rarity::none, ""}
};

// Then, it converts the rarity enum type into a readable string, which will be used for displaying outputs
std::string Item::rartoStr(Rarity r) {
    auto found = rarStrMap.find(r);
    if(found != rarStrMap.end()){ 
        return found->second;
    }
    return "";
}

// This explicitly assigns the armor into their specific/required rarity type
/*If an item inputted by the user is not any of the IDs below, it immediately 
settles the rarity of the item from the user's provided rarity. */ 
Item::Rarity Item::armorRar(std::string id, std::string rarityStr) {
    if (id == "diamond") {
        return Rarity::epic;
    } if (id == "iron") {
        return Rarity::rare;
    } if (id == "leather") {    
        return Rarity::common;
    } if (id == "potion") {
        return Rarity::none;
    }

    auto found = strRarMap.find(rarityStr);
    if(found != strRarMap.end()){
        return found->second;
    }
    return Rarity::none;
}