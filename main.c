#include "golfile.h"

int main() {
    init_database();
    loadFile("laptop_database.bin");
    userMenu();
    saveFile("laptop_database.bin");
    freeMem(laptops, laptop_count);
    return 0;
}
