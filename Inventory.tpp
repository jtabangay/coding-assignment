#include <iostream>
#include "Inventory.h"

// This is a helper function to determine if the item inputted is of the type weapon, which returns true if the item is any of the three.
bool weapon(const std::string& id) {
    return id == "sword" || id == "bow" || id == "dagger";
}

// This block helps format the weapon rarity(wr) to be displayed, similar to the Sample I/Os given.
std::string wr(const std::string& id, Item::Rarity r) {
    if(weapon(id)) {
        return "(" + Item::rartoStr(r) + ")";
    }
    return "";
}

/*Another helper function for formatting outputs, this checks for the rarity of an item
and calls the wr function if there is a specific rarity inputted by the use. If none, it displays the item name alone.*/ 
std::string itemDisplay(std::string& id, Item::Rarity r) {
    std::string getWR = wr(id, r);
    if(getWR != "") {
        return id + " " + getWR;
    }
    return id;
}

/*Lines 28-115, 164-177, 179-201 encompasses the blocks used for creating the functionality 
of each desired command*/

/*Starts searching from the back/end of a vector, finding the instance that was most recently added*/
int Inventory::findItem(std::string id, Item::Rarity r) {
    for(int i = (int)items.size() - 1; i >= 0; i--) {
        if(items[i].id == id && items[i].rarity == r) {
            return i;
        }
    }
    return -1;
}

/*Then, it adds the item to the set inventory grid if the n*n(or 9 spaces) is not full.
Otherwise, it will present an "inventory full!" message*/
void Inventory::addItem(std::string id, std::string rarity) {
    Item::Rarity r = Item::armorRar(id, rarity);
    Item newItem;
    newItem.id = id;
    newItem.rarity = r;

    if(items.size() >= n*n) {
        std::cout << "inventory is full!" << std::endl;
        return;
    }
    if(id != "potion" && findItem(id, r) != -1) {
        std::cout << itemDisplay(id, r) << " already in the inventory" << std::endl;
        return;
    }
    if(weapon(id)) {
        newItem.type = "weapon";
    } else if(id == "potion") {
        newItem.type = "consumable";
    }
    else {
        newItem.type = "armor";
    }

    items.push_back(newItem);
    std::cout << itemDisplay(id, r) << " added!" << std::endl;
}

/*Calls the findItem() function and determines if such specific item exists and can be dropped.*/
void Inventory::dropItem(std::string id, std::string rarity) {
    Item::Rarity r = Item::armorRar(id, rarity);

    int idx = findItem(id, r);
    if(idx == -1) {
        std::cout << "no " << itemDisplay(id, r) << " in the inventory!" << std::endl;
        return;
    }

    items.erase(items.begin() + idx);
    std::cout << itemDisplay(id, r) << " dropped!" << std::endl;
}

/*Uses the same logic as dropItem() wherein it calls the findItem() function and determines if such specific item can be used.
Includes a constraint on weapon and armor items, as those cannot be consumed.*/
void Inventory::useItem(std::string id) {
    if(id != "potion") {
        std::cout << id << " not consumable!" << std::endl;
        return;
    }
    int idx = findItem(id, Item::Rarity::none);
    if(idx == -1) {
        std::cout << "no " << id << " in the inventory!" << std::endl;
        return;
    }
    items.erase(items.begin() + idx);
    std::cout << id << " used!" << std::endl;
}

/*Is parallel to the useItem() function, however the constraint is placed upon potions, as those cannot be equipped.*/

void Inventory::equipItem(std::string id, std::string rarity) {
    Item::Rarity r = Item::armorRar(id, rarity);

    if(id == "potion") {
        std::cout << id << " not equippable!" << std::endl;
        return;
    }

    int idx = findItem(id, r);
    if(idx == -1) {
        std::cout << "no " << itemDisplay(id, r) << " in the inventory!" << std::endl;
        return;
    }
    if(items[idx].equipped) {
        std::cout << itemDisplay(id, r) << " is already equipped!" << std::endl;
        return;
    }
    items[idx].equipped = true;
    std::cout << itemDisplay(id, r) << " equipped!" << std::endl;
}

/*This is useful in the sorting algorithm as it compares each item and 
returns them based on the number inputted(1 for alphabetical, 2 for rarity)*/
bool Inventory::compareItems(Item x, Item y, int order) {
    if(order == 1) {
        if(x.id == y.id) {
            return Item::rarValue(x.rarity) > Item::rarValue(y.rarity);
        }
        return x.id < y.id;
    }
    if(order == 2) {
        if(x.rarity == y.rarity) {
            return x.id < y.id;
        }
        return Item::rarValue(x.rarity) > Item::rarValue(y.rarity);
    }
    return false;
}

/*The start of the actual merge sort algorithm, wherein a recursive function
uses two arrays, divides them in half, sorts the items in each array, and 
combines/merges them back again using the vector "comb"*/
void Inventory::mSort(std::vector<Item>& arr, int left, int right, int order) {
    if(left >= right) {
        return;
    }
    int middle = left + (right - left)/2;
    mSort(arr, left, middle, order);
    mSort(arr, middle + 1, right, order);
    std::vector<Item> comb;
    int a = left;
    int b = middle + 1;

    while(a <= middle && b <= right) {
        if(compareItems(arr[a], arr[b], order)) {
            comb.push_back(arr[a++]);
        }
        else {
            comb.push_back(arr[b++]);
        }
    }
    while(a <= middle) {
        comb.push_back(arr[a++]);
    }
    while(b <= right) {
        comb.push_back(arr[b++]);
    }
    for(int c = 0; c < comb.size(); c++) {
        arr[left+c] = comb[c];
    }
}

/*This relies on the "order" inputted by the user and calls the mSort() function.
Then, it outputs if the inventory has been sorted appropriately according to the input.
Contains a constraint which only allows the user to type 1 or 2.*/
void Inventory::sort(int order) {
    if(items.size() > 1) {
        mSort(items, 0, items.size() - 1, order);
    }
    if(order == 1) {
        std::cout << "inventory sorted alphabetically!" << std::endl;
    }
    else if(order == 2) {
        std::cout << "inventory sorted by rarity!" << std::endl;
    }
    else {
        std::cout << "please type 1 or 2 only" << std::endl;
    }
}

/*Is the output display function of the program, presenting every command entered*/
void Inventory::inventoryCheck() {
    std::cout << "-------------------- INVENTORY --------------------" << std::endl;
    std::string separator = "     ";

    for(int i = 0; i < items.size(); i++) {
        std::string display = itemDisplay(items[i].id, items[i].rarity);
        if(items[i].equipped) {
            display += " [E]";
        }
        std::cout << display;

        if((i + 1) % n == 0) {
            std::cout << std::endl;
        }
        else if(i != items.size() - 1) {
            std::cout << separator;
        }
    }
    if(items.size() > 0 && items.size() % n != 0) {
        std::cout << std::endl;
    }
    std::cout << "---------------------------------------------------" << std::endl;
}