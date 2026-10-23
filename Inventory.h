#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include "Item.h"

// Manages a grid-like set of Item objects, handling the required functions such as, adding, dropping, using, equipping, sorting, and displaying items.
// It establishes the inventory size constraint using an nxn grid.

class Inventory {
    int n = 3; // initializes the inventory grid based on the formula provided, creating a 3x3 grid
    bool compareItems(Item x, Item y, int order);
    void mSort(std::vector<Item>& arr, int left, int right, int order);
    public: // 
        std::vector<Item> items; // container for the list of items instantiated
        int findItem(std::string id, Item::Rarity r); 
        void addItem(std::string, std::string rarity = ""); 
        void dropItem(std::string, std::string rarity = "");
        void useItem(std::string);
        void equipItem(std::string, std::string rarity = "");
        void sort(int order);
        void inventoryCheck();
};

#include "Inventory.tpp"
#endif