#ifndef CLASSES
#define CLASSES

using namespace std;

// Global
// Contains attributes common to all classes in the engine
class Global {
private:
	string name;
public:
	virtual string& getName() {
		return name;
	}
};

// Use, throw, drop, description, eat, combine
// Sharp, metal, 
class Item : Global {
private:
	string name;
	string description;
	unsigned int health;
	unsigned int weight;
public:
	Item(string name, unsigned int health, unsigned int weight, string description) {
		this->name = name;
		this->health = health;
		this->weight = weight;
		this->description = description;
	}
	virtual string& getName() {
		return this->name;
	}
};

// There are four main types of objects
// Characters: PCs and NPCs who inhabit locations, capable of interactins with the world and carrying items
// Items: Can be equipped by characters and potentially used
// Objects: Can't be equipped by characters, but can be interacted with
// Locations: Places that contain characters, items, and objects

class Inconsumable : Item {

};

class Consumable : Item {

};

class Equipment : Item {

};

class Weapon : Equipment {

};

class Melee : Weapon {

};

class Ranged : Weapon {

};

class Headpiece : Equipment {

};

class Chestpiece : Equipment {

};

class Legpiece : Equipment {

};

class Gloves : Equipment {

};

class Boots : Equipment {

};

class Drink : Consumable {

};

class Food : Consumable {

};

class Object : Global {
private:
	string name;
	string description;
	unsigned int health;
	unsigned int weight;

};

class Location : Global {
private:
	string name;
	vector<Location*> neighbors;
	vector<Item*> items;
public:
	Location(string name) {
		this->name = name;
	}
	virtual const vector<Location*>& getNeighbors() {
		return neighbors;
	}
	virtual void showNeighbors() {
		for (auto& el : neighbors) {
			cout << el->getName() << endl;
		}
	}
	virtual void showItems() {
		for (auto el : items) {
			cout << el->getName() << endl;
		}
	}
	virtual string& getName() {
		return this->name;
	}
	virtual void setItems(vector<Item*> items) {
		this->items = items;
	}
	virtual void addLoc(Location* loc) {
		this->neighbors.push_back(loc);
	}
	virtual bool operator==(Location loc) {
		return this->name == loc.name ? true : false;
	}
	virtual void removeLoc(Location* loc) {
		for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
			if (**iter == *loc) {
				neighbors.erase(iter);
				return;
			}
		}

		cerr << "Invalid removal of neighbor " << loc->name << " from location " << this->name << endl;
	}
};

class Character : Global {
private:
	string name;
	unsigned int health;
	Location* loc;
	vector<Item*> inventory;
	vector<string> status;
public:
	Character(string& name, unsigned int& health, Location* loc) {
		this->name = name;
		this->health = health;
		this->loc = loc;
	}

	// Increase character health
	virtual void incHP(unsigned int inc) {
		health += inc;
	}

	// Decrease character health
	virtual void decHP(unsigned int dec) {
		if (dec > health) {
			health = 0;
		}
		else {
			health -= dec;
		}
	}

	// Move to a new location
	virtual void move(Location* newLoc) {
		// You're in the location already
		if (newLoc == loc) {

		}
		// Location is a neighbor
		else {
			for (const auto& el : loc->getNeighbors()) {
				if (el == newLoc) {
					loc = el;
				}
			}
		}
		// Location is inaccessible

		
	}

	// Add an item to the inventory
	virtual void pickUp(Item* item) {
		for (const auto& el : inventory) {
			if (item == el) {
				cerr << "Redundant attempt to add item to inventory in PickUp";
				return;
			}
		}
		this->inventory.push_back(item);
	}

	// Print the inventory to stdout
	virtual void showInventory() {
		for (auto el : this->inventory) {
			cout << el->getName() << endl;
		}
	}

	// Return the location of the character
	virtual Location* getLoc() {
		return loc;
	}

	// Return the name of the character
	virtual string& getName() {
		return this->name;
	}

	// Throw an item at something
	virtual void throwItem(Item* item, Location* loc){

	}

	virtual void throwItem(Item* item, Character* character) {

	}

	virtual void throwItem(Item* item, Item* destItem) {

	}
};

class PC : Character {

};

class NPC : Character {

};

// World
// Contains attributes of the world, in particular keeping track of
// locations and items
class World : Global {
private:
	string name = "Wrightville";
	signed int time = 0;

	// Contains flags to keep track of various events around the world
	unordered_map<string, bool> flags;

	// Maps item names to Item objects
	// Used as a source to copy new items; items in this list should not
	// be referenced directly as there may be duplicates

	unordered_map<string, Item*> itemMap =
	{ {"Water Bottle", new Item("Water Bottle", 5, 1, "A bottle of dihydrogen monoxide")} };

	unordered_map<string, Location*> locMap =
	{ {"Library", new Location("Library")},
	  {"Basement", new Location("Basement")},
	  {"Tunnel", new Location("Tunnel")} };

public:
	void setFlag(string& flag, bool val) {
		flags[flag] = val;
	}
	void incTime(signed int time) {
		this->time += time;
	}
	Location* getLoc(string& loc) {
		return this->locMap[loc];
	}
	void linkLoc(string startLoc, string endLoc, bool twoWay = false) {
		Location* startPoint = locMap[startLoc];
		Location* endPoint = locMap[endLoc];

		startPoint->addLoc(endPoint);
		if (twoWay) {
			endPoint->addLoc(startPoint);
		}
	}
	void unLinkLoc(string startLoc, string endLoc, bool twoWay = false) {
		Location* startPoint = locMap[startLoc];
		Location* endPoint = locMap[endLoc];

		startPoint->removeLoc(endPoint);
		if (twoWay) {
			endPoint->removeLoc(startPoint);
		}
	}
};

#endif