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

    void waterPlants(Plant plants[], int size) {
        for (int i = 0; i < size; i++) {
            plants[i].water();
        }
    }

    void checkPlants(const Plant plants[], int size) const {
        for (int i = 0; i < size; i++) {
            plants[i].displayStatus();
        }
    }
};

int main() {
    const int gardenSize = 2;
    Plant myGarden[gardenSize];
    User user;

    for (int i = 0; i < gardenSize; i++) {
        user.createPlant(myGarden[i]);
    }

    user.waterPlants(myGarden, gardenSize);
    user.checkPlants(myGarden, gardenSize);

    return 0;
}
