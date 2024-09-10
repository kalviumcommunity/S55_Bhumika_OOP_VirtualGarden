#include <iostream>
#include <string>
using namespace std;

class Plant {
public:
    static int totalPlants; 
    static int totalWaterUsed; 

private:
    string name;
    string type;
    string growthStage;
    int waterLevel;
    int maxWaterLevel;

public:
    Plant() {
        this->name = "";
        this->type = "";
        this->growthStage = "seedling";
        this->waterLevel = 0;
        this->maxWaterLevel = 0;
        totalPlants++; 
    }

    Plant(string n, string t, int maxWater) {
        setName(n);
        setType(t);
        setGrowthStage("seedling");
        setWaterLevel(0);
        setMaxWaterLevel(maxWater);
        totalPlants++; 
    }

    ~Plant() {
        totalPlants--; 
    }

    void setName(string n) { this->name = n; }
    string getName() const { return this->name; }

    void setType(string t) { this->type = t; }
    string getType() const { return this->type; }

    void setGrowthStage(string stage) { this->growthStage = stage; }
    string getGrowthStage() const { return this->growthStage; }

    void setWaterLevel(int level) { this->waterLevel = level; }
    int getWaterLevel() const { return this->waterLevel; }

    void setMaxWaterLevel(int level) { this->maxWaterLevel = level; }
    int getMaxWaterLevel() const { return this->maxWaterLevel; }

    void water() {
        if (this->waterLevel < this->maxWaterLevel) {
            setWaterLevel(this->waterLevel + 1);
            totalWaterUsed++; 
            cout << getName() << " has been watered. Current water level: " << getWaterLevel() << endl;
        } else {
            cout << getName() << " is fully watered." << endl;
        }
    }

    void displayStatus() const {
        cout << "Plant: " << getName() << ", Type: " << getType() << ", Growth Stage: " << getGrowthStage()
             << ", Water Level: " << getWaterLevel() << "/" << getMaxWaterLevel() << endl;
    }

    static void displayStatics() {
        cout << "Total Plants: " << totalPlants << endl;
        cout << "Total Water Used: " << totalWaterUsed << endl;
    }
};

int Plant::totalPlants = 0;
int Plant::totalWaterUsed = 0;

class User {
private:
    string userName;

public:
    void setUserName(string name) { this->userName = name; }
    string getUserName() const { return this->userName; }

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
            allPlantsFullyWatered = true;
            for (int i = 0; i < size; i++) {
                if (plants[i].getWaterLevel() < plants[i].getMaxWaterLevel()) {
                    plants[i].water();
                    allPlantsFullyWatered = false;
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

    Plant::displayStatics();

    delete[] myGarden;
    return 0;
}
