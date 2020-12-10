#ifndef CLASSES
#define CLASSES

using namespace std;

class Item {
private:
	string name;
	string owner;
	unsigned int health;
	unsigned int weight;
	unordered_map<string, bool> properties;
public:
	Item(string name, unsigned int health, unsigned int weight, string owner, bool equippable, bool drinkable, bool edible) {
		this->name = name;
		this->owner = owner;
		this->health = health;
		this->weight = weight;
		properties["equippable"] = equippable;
		properties["drinkable"] = drinkable;
		properties["edible"] = edible;
	}
	string& getName() {
		return this->name;
	}
	void 
};

class Location {
private:
	string name;
	vector<Location*> neighbors;
	vector<Item*> items;
public:
	Location(string name) {
		this->name = name;
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

class Character {
private:
	string name;
	signed int health;
	Location* loc;
	vector<string> status;
	vector<Item*> inventory;
public:
	Character(string name, signed int health, Location* loc) {
		this->name = name;
		this->health = health;
		this->loc = loc;
	}
	virtual void incHP(signed int hp) {
		this->health += hp;
	}
	virtual void move(Location* location) {
		this->loc = location;
	}
	virtual void equip(Item* item) {
		this->inventory.push_back(item);
	}
	virtual void showInventory() {
		for (auto el : this->inventory) {
			cout << el->getName() << endl;
		}
	}
	virtual string& getLoc() {
		return this->loc->getName();
	}
	virtual string& getName() {
		return this->name;
	}
};

class World {
private:
	signed int time = 0;
	unordered_map<string, bool> flags;

	unordered_map<string, Item*> itemMap =
	{ {"Library", new Item("Library")} };

	unordered_map<string, Location*> locMap =
	{ {"Library", new Location("Library")},
	  {"Basement", new Location("Basement")},
	  {"Tunnel", new Location("Tunnel")} };

public:
	void setFlag(string flag, bool val) {
		flags[flag] = val;
	}
	void incTime(signed int time) {
		this->time += time;
	}
	Location* getLoc(string loc) {
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