#include <iostream>
#include "Inventory.h"

using namespace std;

/*This file processes user inputs/commands to manage the inventory.
Assigned a variable i to Inventory, so that the i.<> lines are easier to read.
int L keeps the inputs from reahing more than 15 lines of command from the user*/ 
int main() {
    Inventory i;
    string input;
    int L=0;

// The program utilizes if-else statements and a for-loop block to execute a function based on words(commands) inputted by user and constrain them to 15 lines of command per session.
// Also includes an "end" functionality, just in case the user wants to end the program in less than 15 commands. 
    for(int command = 0; command < 21; command++) {
        if(!(cin >> input) || input == "end") {
            break;
        }

        if(input == "add") {
            string item; cin >> item;
            if(item == "sword" || item == "bow" || item == "dagger") {
                string r; cin >> r;
                i.addItem(item, r);
            } else {
                i.addItem(item);
            }
        }else if(input == "drop") {
            string item; cin >> item;
            if(item == "sword" || item == "bow" || item == "dagger") {
                string r; cin >> r;
                i.dropItem(item, r);
            } else {
                i.dropItem(item);
            }
        }
        else if(input == "use") {
            string item; cin >> item;
            i.useItem(item);
        }else if(input == "equip") {
            string item; cin >> item;
            if(item == "potion") {
                i.equipItem(item);
            }
            else if(item == "sword" || item == "bow" || item == "dagger") {
                string r; cin >> r;
                i.equipItem(item, r);
            } else {
                i.equipItem(item);
            }
        }
        else if(input == "sort") {
            int s; cin >> s;
            i.sort(s);
        }
        else if(input == "i") {
            i.inventoryCheck();
        }

        L++;
    }
}