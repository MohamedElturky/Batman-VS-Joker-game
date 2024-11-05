#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Character {
protected:
    string name;
    int health;
    int energy;

public:
    Character(string n, int h, int e) : name(n), health(h), energy(e) {}

    int getHealth() const {
        return health;
    }

    int getEnergy() const {
        return energy;
    }

    string getName() const {
        return name;
    }

    void reduceHealth(int damage) {
        health -= damage;
    }

    void reduceEnergy(int amount) {
        energy -= amount;
    }


    virtual void attack(Character &opponent, int i) = 0;


    virtual ~Character() {}
};

class Batman : public Character {
private:
    struct Gadget {
        string name;
        int energyCost;
        int damage;
        int useLimit;
    };

    vector<Gadget> weapons;
    vector<Gadget> shields;

public:
    Batman() : Character("Batman", 100, 500) {
        weapons.push_back({"Batarang", 50, 11, -1});
        weapons.push_back({"Grapple Gun", 88, 18, 5});
        weapons.push_back({"Explosive Gel", 92, 10, 3});
        weapons.push_back({"Batclaw", 120, 20, 1});

        shields.push_back({"Cape Glide", 20, 0, -1});
        shields.push_back({"Smoke Pellet", 50, 0, 2});
    }

    void attack(Character &opponent, int i) override {
        if (i >= 0 && i < weapons.size()) {
            if (energy >= weapons[i].energyCost) {
                cout << name << " attacks " << opponent.getName() << " with " << weapons[i].name << "!" << endl;
                opponent.reduceHealth(weapons[i].damage);
                reduceEnergy(weapons[i].energyCost);
            } else {
                cout << name << " is out of energy and cannot attack!" << endl;
            }
        } else {
            cout << "Invalid weapon index!" << endl;
        }
    }

    void defend(int damage)  {
        if (energy >= shields[0].energyCost) {
            int reducedDamage = damage * 0.6;
            reduceHealth(reducedDamage);
            reduceEnergy(shields[0].energyCost);
            cout << name << " uses " << shields[0].name << " to reduce damage!" << endl;
        } else {
            reduceHealth(damage);
            cout << name << " cannot defend and takes full damage!" << endl;
        }
    }
};

class Joker : public Character {
protected:
    struct Gadget {
        string name;
        int energyCost;
        int damage;
        int useLimit;
    };

    vector<Gadget> weapons;
    vector<Gadget> shields;

public:
    Joker() : Character("Joker", 100, 500) {
        weapons.push_back({"Joy Buzzer", 40, 8, -1});
        weapons.push_back({"Laughing Gas", 56, 13, 8});
        weapons.push_back({"Acid Flower", 100, 22, 3});

        shields.push_back({"Trick Shield", 15, 32, -1});
        shields.push_back({"Rubber Chicken", 40, 80, 3});
    }

    void attack(Character &opponent, int i) override{
        if (i >= 0 && i < weapons.size()) {
            if (energy >= weapons[i].energyCost) {
                cout << name << " attacks " << opponent.getName() << " with " << weapons[i].name << "!" << endl;
                opponent.reduceHealth(weapons[i].damage);
                reduceEnergy(weapons[i].energyCost);
            } else {
                cout << name << " is out of energy and cannot attack!" << endl;
            }
        } else {
            cout << "Invalid weapon index!" << endl;
        }
    }
    
};

int main() {
    Batman batman;
    Joker joker;
    int i =0 ;
    int stateb,statej;

    while (batman.getHealth() > 0 && joker.getHealth() > 0) {
        cout <<"Batman attack or defend"<<endl<<"(attack : 0 , defend : 1):"<<endl;
        cin >>stateb;
        while (getchar()!='\n');
        if(stateb==0){
        cout << "Choose Batman's weapon: ";
        cin>>i;
        while (getchar()!='\n');
        batman.attack(joker,i);}
        else if(stateb == 1){
        cout << "Choose Batman's shield: ";
        cin >>i;
        batman.defend(i);
        }
        else{
        cout<<"invalid input!";
        }

        cout << "--------------------------------" << endl;

        cout <<"Joker attack or defend"<<endl<<"(attack : 0 , defend : 1):"<<endl;
        cin >>statej;
        if(statej==0){
        cout << "Choose Joker's weapon: ";
        cin>>i;
        joker.attack(joker,i);}
        else if(statej == 1){
        cout << "Choose Joker's shield: ";
        cin >>i;
        //joker.defend(i);
        }
        else{
        cout<<"invalid input!";
        }
        if(stateb&&statej){
            cout<<"both characters defend,skip turn\n";
            continue;
        }
        }

        cout << batman.getName() << "'s remaining health: " << batman.getHealth() << endl;
        cout << joker.getName() << "'s remaining health: " << joker.getHealth() << endl;
        cout << "--------------------------------" << endl;
    
    
    if (batman.getHealth() <= 0) {
        cout << joker.getName() << " wins!" << endl;
    } else if (joker.getHealth() <= 0) {
        cout << batman.getName() << " wins!" << endl;
    }

    return 0;
}
