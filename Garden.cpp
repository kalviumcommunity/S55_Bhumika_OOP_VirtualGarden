#include <iostream>
#include <string>
using namespace std;

class Plant {
public:
    string name;
    string type;
    string growthStage;
    int waterLevel;
    int maxWaterLevel;

    Plant(string n, string t, int maxWater) {
        this->name = n; 
        this->type = t; 
        this->growthStage = "seedling";
        this->waterLevel = 0;
        this->maxWaterLevel = maxWater; 
    }

    void water() {
        if (this->waterLevel < this->maxWaterLevel) { 
            this->waterLevel++; 
            cout << this->name << " has been watered. Current water level: " << this->waterLevel << endl; // Used this pointer here
        } else {
            cout << this->name << " is fully watered." << endl; 
        }
    }

    void displayStatus() {
        cout << "Plant: " << this->name << ", Type: " << this->type << ", Growth Stage: " << this->growthStage
             << ", Water Level: " << this->waterLevel << "/" << this->maxWaterLevel << endl; 
    }
};

class Garden {
public:
    Plant* plants[10];
    int plantCount;

    Garden() : plantCount(0) {}

    void addPlant(Plant* p) {
        if (plantCount < 10) {
            plants[plantCount++] = p;
            cout << p->name << " has been added to the garden." << endl;
        } else {
            cout << "The garden is full!" << endl;
        }
    }

    void waterAll() {
        for (int i = 0; i < plantCount; i++) {
            plants[i]->water();
        }
    }

    void displayAllPlants() {
        for (int i = 0; i < plantCount; i++) {
            plants[i]->displayStatus();
        }
    }
};

class User {
public:
    void createPlant(Garden& g) {
        string name, type;
        int maxWaterLevel;
        cout << "Enter plant name: ";
        cin >> name;
        cout << "Enter plant type (e.g., flower, vegetable): ";
        cin >> type;
        cout << "Enter maximum water level: ";
        cin >> maxWaterLevel;

        Plant* p = new Plant(name, type, maxWaterLevel);
        g.addPlant(p);
    }

    void waterPlants(Garden& g) {
        g.waterAll();
    }

    void checkPlants(Garden& g) {
        g.displayAllPlants();
    }
};

int main() {
    Garden myGarden;
    User user;

    user.createPlant(myGarden);

    user.waterPlants(myGarden);

    user.checkPlants(myGarden);

    return 0;
}
