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

    Plant() {
        this->name = "";
        this->type = "";
        this->growthStage = "seedling";
        this->waterLevel = 0;
        this->maxWaterLevel = 0;
    }

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
            cout << this->name << " has been watered. Current water level: " << this->waterLevel << endl;
        } else {
            cout << this->name << " is fully watered." << endl;
        }
    }

    void displayStatus() const {
        cout << "Plant: " << this->name << ", Type: " << this->type << ", Growth Stage: " << this->growthStage
             << ", Water Level: " << this->waterLevel << "/" << this->maxWaterLevel << endl;
    }
};

class User {
public:
    void createPlant(Plant& p) {
        string name, type;
        int maxWaterLevel;
        cout << "Enter plant name: ";
        cin >> name;
        cout << "Enter plant type (e.g., flower, vegetable): ";
        cin >> type;
        cout << "Enter maximum water level: ";
        cin >> maxWaterLevel;

        p = Plant(name, type, maxWaterLevel);
    }

    void waterPlants(Plant* plants, int size) { 
        bool allPlantsFullyWatered = false;
        while (!allPlantsFullyWatered) {
            allPlantsFullyWatered = true; // Assume all plants are fully watered
            for (int i = 0; i < size; i++) {
                if (plants[i].waterLevel < plants[i].maxWaterLevel) {
                    plants[i].water(); // Water the plant
                    allPlantsFullyWatered = false; // Found a plant that still needs watering
                }
            }
        }
    }

    void checkPlants(const Plant* plants, int size) const { 
        for (int i = 0; i < size; i++) {
            plants[i].displayStatus();
        }
    }
};

int main() {
    const int gardenSize = 2;
    Plant* myGarden = new Plant[gardenSize]; 
    User user;

    for (int i = 0; i < gardenSize; i++) {
        user.createPlant(myGarden[i]); 
    }

    user.waterPlants(myGarden, gardenSize); 
    user.checkPlants(myGarden, gardenSize); 

    delete[] myGarden; 
    return 0;
}
