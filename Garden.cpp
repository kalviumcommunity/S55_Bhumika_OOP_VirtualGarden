#include <iostream>
#include <string>
using namespace std;

// AbstractPlant now only handles watering and status display, making it adhere to SRP
class AbstractPlant {
public:
    virtual void water() = 0; 
    virtual void displayStatus() const = 0; 
};

// Plant class is responsible only for plant properties and watering, adhering to SRP
class Plant : public AbstractPlant {
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

    // Getter and Setter functions give each method a single purpose (SRP)
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

    // Responsibility for watering is specific to this method, following SRP
    void water() override {
        if (this->waterLevel < this->maxWaterLevel) {
            setWaterLevel(this->waterLevel + 1);
            totalWaterUsed++;
            cout << getName() << " has been watered. Current water level: " << getWaterLevel() << endl;
        } else {
            cout << getName() << " is fully watered." << endl;
        }
    }

    // Status display is separated, following SRP
    void displayStatus() const override { 
        cout << "Plant: " << getName() << ", Type: " << getType()
             << ", Growth Stage: " << getGrowthStage()
             << ", Water Level: " << getWaterLevel() << "/" << getMaxWaterLevel() << endl;
    }

    // Static function displays plant statistics, adhering to SRP by separating functionality
    static void displayStatics() {
        cout << "Total Plants: " << totalPlants << endl;
        cout << "Total Water Used: " << totalWaterUsed << endl;
    }
};

int Plant::totalPlants = 0;
int Plant::totalWaterUsed = 0;

// FloweringPlant focuses only on flower-specific details, following SRP
class FloweringPlant : public Plant {
private:
    string flowerColor;

public:
    FloweringPlant(string name, string type, int maxWater, string color)
        : Plant(name, type, maxWater), flowerColor(color) {}

    FloweringPlant() : Plant() {}

    void setFlowerColor(string color) { flowerColor = color; }
    string getFlowerColor() const { return flowerColor; }

    // Responsibility for displaying flower info is specific to this method, adhering to SRP
    void displayFlowerInfo() const {
        cout << "Flower Color: " << getFlowerColor() << endl;
    }

    void displayStatus() const override { 
        Plant::displayStatus(); 
        displayFlowerInfo();
    }
};

// GardenPlant adds only season information, adhering to SRP
class GardenPlant : public FloweringPlant {
private:
    string season;

public:
    GardenPlant(string name, string type, int maxWater, string color, string bloomSeason)
        : FloweringPlant(name, type, maxWater, color), season(bloomSeason) {}

    GardenPlant() : FloweringPlant() {}

    void setSeason(string s) { season = s; }
    string getSeason() const { return season; }

    // Separate method to display garden plant info, adhering to SRP
    void displayGardenPlantInfo() const {
        displayStatus(); 
        cout << "Bloom Season: " << getSeason() << endl;
    }
};

// User class handles only user-specific actions, keeping to SRP
class User {
private:
    string userName;

public:
    void setUserName(string name) { this->userName = name; }
    string getUserName() const { return this->userName; }

    // Responsibility for creating garden plants is specific to this method
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

    // Responsibility for watering plants is separate, following SRP
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

    // Responsibility for checking plant status is separate, following SRP
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
