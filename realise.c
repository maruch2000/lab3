#include "golfile.h"

static Laptop* laptops = NULL;
static int laptop_count = 0;

void init_database() {
    laptops = NULL;
    laptop_count = 0;
}

void loadFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file)
        return;

    fread(&laptop_count, sizeof(int), 1, file);

    if (laptop_count > 0) {
        laptops = malloc(laptop_count * sizeof(Laptop));
        for (int i = 0; i < laptop_count; ++i) {
            Laptop* l = &laptops[i];
            size_t len;
            fread(&len, sizeof(size_t), 1, file);
            l->model = malloc(len + 1);
            fread(l->model, sizeof(char), len, file);
            l->model[len] = '\0';
            fread(&l->price, sizeof(float), 1, file);
            fread(&l->year, sizeof(int), 1, file);
        }
    }
    fclose(file);
}

void saveFile(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file)
        return;

    fwrite(&laptop_count, sizeof(int), 1, file);

    for (int i = 0; i < laptop_count; ++i) {
        Laptop* l = &laptops[i];
        size_t len = strlen(l->model);
        fwrite(&len, sizeof(size_t), 1, file);
        fwrite(l->model, sizeof(char), len, file);
        fwrite(&l->price, sizeof(float), 1, file);
        fwrite(&l->year, sizeof(int), 1, file);
    }

    fclose(file);
}

void add(Laptop laptop) {
    laptops = realloc(laptops, (laptop_count + 1) * sizeof(Laptop));
    laptops[laptop_count++] = laptop;
}

Laptop* getLaptops() {
    return laptops;
}

int getLaptopCount() {
    return laptop_count;
}

void freeMem(Laptop* laptops, int count) {
    for (int i = 0; i < count; ++i) {
        free(laptops[i].model);
    }
    free(laptops);
}

void deleteLaptop(int index) {
    if (index >= 0 && index < laptop_count) {
        for (int i = index; i < laptop_count - 1; ++i) {
            laptops[i] = laptops[i + 1];
        }
        laptop_count--;
        laptops = realloc(laptops, laptop_count * sizeof(Laptop));
    }
}

void editLaptop(int index, const char* new_model, float new_price, int new_year) {
    if (index >= 0 && index < laptop_count) {
        Laptop* l = &laptops[index];
        free(l->model);
        l->model = strdup(new_model);
        l->price = new_price;
        l->year = new_year;
    }
}

void searchLaptop(const char* model, float min_price, float max_price, Laptop** results, int* result_count) {
    *result_count = 0;
    *results = NULL;
    for (int i = 0; i < laptop_count; ++i) {
        Laptop* l = &laptops[i];
        if (strstr(l->model, model) != NULL && l->price >= min_price && l->price <= max_price) {
            (*results) = realloc(*results, ((*result_count) + 1) * sizeof(Laptop));
            (*results)[(*result_count)] = *l;
            (*result_count)++;
        }
    }
}

void menu() {
    printf("1. View laptops\n");
    printf("2. Add laptop\n");
    printf("3. Delete laptop\n");
    printf("4. Edit laptop\n");
    printf("5. Search laptop\n");
    printf("6. Save database\n");
    printf("7. Load database\n");
    printf("8. EXIT\n");
    printf("\nEnter choice: ");
}

void userMenu() {
    while (1) {
        menu();
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int count;
                Laptop* lpts = getLaptops();
                if (laptop_count == 0) {
                    printf("No laptops available.\n");
                } else {
                    for (int i = 0; i < laptop_count; ++i) {
                        Laptop* l = &lpts[i];
                        printf("Model: %s  Price: %.2f  Year: %d\n", l->model, l->price, l->year);
                    }
                }
                break;
            }
            case 2: {
                char model[100];
                float price;
                int year;

                printf("Enter laptop model: ");
                scanf("%s", model);
                printf("Enter price: ");
                scanf("%f", &price);
                printf("Enter year: ");
                scanf("%d", &year);

                Laptop laptop = { strdup(model), price, year };
                add(laptop);
                break;
            }
            case 3: {
                int count;
                Laptop* lpts = getLaptops();
                if (laptop_count == 0) {
                    printf("No laptops to delete.\n");
                } else {
                    printf("Select index to delete:\n");
                    for (int i = 0; i < laptop_count; ++i) {
                        Laptop* l = &lpts[i];
                        printf("%d. Model: %s  Price: %.2f  Year: %d\n", i, l->model, l->price, l->year);
                    }

                    int index;
                    scanf("%d", &index);
                    deleteLaptop(index);
                }
                break;
            }
            case 4: {
                int count;
                Laptop* lpts = getLaptops();
                if (laptop_count == 0) {
                    printf("No laptops to edit.\n");
                } else {
                    printf("Select index to edit:\n");
                    for (int i = 0; i < laptop_count; ++i) {
                        Laptop* l = &lpts[i];
                        printf("%d. Model: %s  Price: %.2f  Year: %d\n", i, l->model, l->price, l->year);
                    }

                    int index;
                    scanf("%d", &index);

                    char new_model[100];
                    float new_price;
                    int new_year;

                    printf("Enter new model: ");
                    scanf("%s", new_model);
                    printf("Enter new price: ");
                    scanf("%f", &new_price);
                    printf("Enter new year: ");
                    scanf("%d", &new_year);

                    editLaptop(index, new_model, new_price, new_year);
                }
                break;
            }
            case 5: {
                char model[100];
                float min_price, max_price;

                printf("Enter model to search: ");
                scanf("%s", model);
                printf("Enter minimum price: ");
                scanf("%f", &min_price);
                printf("Enter maximum price: ");
                scanf("%f", &max_price);

                Laptop* results;
                int result_count;
                searchLaptop(model, min_price, max_price, &results, &result_count);

                if (result_count == 0) {
                    printf("No laptops found.\n");
                } else {
                    for (int i = 0; i < result_count; ++i) {
                        Laptop* l = &results[i];
                        printf("Model: %s  Price: %.2f
