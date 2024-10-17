#include <iostream>
#include <string>
using namespace std;

class Plant {
private:
    string name;
    string type;
    string growthStage;
    int waterLevel;
    int maxWaterLevel;

public:
    static int totalPlants;
    static int totalWaterUsed;

    // Default constructor
    Plant() {
        this->name = "";
        this->type = "";
        this->growthStage = "seedling";
        this->waterLevel = 0;
        this->maxWaterLevel = 0;
        totalPlants++;
    }

    // Parameterized constructor
    Plant(string n, string t, int maxWater) {
        name = n;
        type = t;
        growthStage = "seedling";
        waterLevel = 0;
        maxWaterLevel = maxWater;
        totalPlants++;
    }

    // Destructor
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

// Single Inheritance
class FloweringPlant : public Plant {
private:
    string flowerColor;

public:
   
    FloweringPlant(string name, string type, int maxWater, string color) : Plant(name, type, maxWater) {
        flowerColor = color;
    }

    FloweringPlant() : Plant() {}  

    void setFlowerColor(string color) { flowerColor = color; }
    string getFlowerColor() const { return flowerColor; }

    void displayFlowerInfo() const {
        cout << "Flower Color: " << getFlowerColor() << endl;
    }
};

// Multilevel Inheritance
class GardenPlant : public FloweringPlant {
private:
    string season;  

public:
    GardenPlant(string name, string type, int maxWater, string color, string bloomSeason)
        : FloweringPlant(name, type, maxWater, color) {
        season = bloomSeason;
    }

    GardenPlant() : FloweringPlant() {}  

    void setSeason(string s) { season = s; }
    string getSeason() const { return season; }

    void displayGardenPlantInfo() const {
        displayStatus();         
        displayFlowerInfo();    
        cout << "Bloom Season: " << getSeason() << endl;
    }
};


class User {
private:
    string userName;

public:
    void setUserName(string name) { this->userName = name; }
    string getUserName() const { return this->userName; }

    void createGardenPlant(GardenPlant& p) {
        string name, type, color, season;
        int maxWaterLevel;

        cout << "Enter plant name: ";
        cin >> name;
        cout << "Enter plant type (e.g., flower, vegetable): ";
        cin >> type;
        cout << "Enter maximum water level: ";
        cin >> maxWaterLevel;
        cout << "Enter flower color: ";
        cin >> color;
        cout << "Enter bloom season: ";
        cin >> season;

       
        p = GardenPlant(name, type, maxWaterLevel, color, season);
    }

    void waterPlants(GardenPlant* plants, int size) {
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

    void checkPlants(const GardenPlant* plants, int size) const {
        for (int i = 0; i < size; i++) {
            plants[i].displayGardenPlantInfo();
        }
    }
};

int main() {
    const int gardenSize = 2;
    GardenPlant* myGarden = new GardenPlant[gardenSize];  

    User user;
    for (int i = 0; i < gardenSize; i++) {
        user.createGardenPlant(myGarden[i]);  
    }

    user.waterPlants(myGarden, gardenSize);  
    user.checkPlants(myGarden, gardenSize);  

    Plant::displayStatics();  

    delete[] myGarden;  
    return 0;
}
