#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <map>

/* This block includes all attributes set to public needed by the item and
includes lookups to map the rarity string names to their respective enums and vice versa.*/ 
class Item {
    public:
        bool equipped = false;
        std::string type;
        std::string id;
        enum class Rarity { 
            epic = 3, 
            rare = 2, 
            common = 1, 
            none = 0 
        };
        Rarity rarity;
        static Rarity armorRar(std::string id, std::string rarityStr = "");
        static int rarValue(Rarity r);
        static std::string rartoStr(Rarity r);
        static const std::map<std::string, Rarity> strRarMap;
        static const std::map<Rarity, std::string> rarStrMap;
};

#include "Item.tpp"
#endif