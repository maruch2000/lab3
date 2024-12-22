#ifndef GOLFILE_H
#define GOLFILE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char* model;
    float price;
    int year;
} Laptop;
void init_database();
void loadFile(const char* filename);
void saveFile(const char* filename);
void add(Laptop laptop);
Laptop* getLaptops();
int getLaptopCount();
void freeMem(Laptop* laptops, int count);
void deleteLaptop(int index);
void editLaptop(int index, const char* new_model, float new_price, int new_year);
void searchLaptop(const char* model, float min_price, float max_price, Laptop** results, int* result_count);
void menu();
void userMenu();
extern Laptop* laptops;
extern int laptop_count;
#endif

