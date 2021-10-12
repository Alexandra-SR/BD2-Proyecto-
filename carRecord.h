#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std; 


struct Car {


    int deleteNext; 
    unsigned int id;
    char model[2];
    unsigned int year;
    unsigned int price;
    char transmission[10];
    unsigned int mileage;
    char fuelType[6];
    unsigned int tax;
    float milesPerGaloon;
    float engineSize;

    

    Car(unsigned int id,
        string Model,
        unsigned int year,
        unsigned int price,
        string Transmission,
        unsigned int mileage,
        string FuelType,
        unsigned int tax,
        float milesPerGaloon,
        float engineSize) {
        this->id = id;
        strcpy(model, Model.c_str());
        this->year = year;
        this->price = price;
        strcpy(transmission, Transmission.c_str()); 
        this->mileage = mileage;
        strcpy(fuelType, FuelType.c_str()); 
        this->tax = tax;
        this->milesPerGaloon = milesPerGaloon;
        this->engineSize = engineSize;
        this->deleteNext = -1;
    }


    Car() = default;

};
