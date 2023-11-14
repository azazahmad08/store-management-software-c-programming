#include <stdio.h>
#include <stdlib.h>

// Structure to represent a product
struct Product {
    char name[50];
    float price;
    int stock;
};

// Function to add a new product to the store
void addProduct(struct Product *products, int *numProducts) {
    printf("Enter product name: ");
    scanf("%s", products[*numProducts].name);

    printf("Enter product price: ");
    scanf("%f", &products[*numProducts].price);

    printf("Enter available stock: ");
    scanf("%d", &products[*numProducts].stock);

    (*numProducts)++;
}

// Function to display all products in the store
// Change this in the displayProducts function
void displayProducts(struct Product *products, int numProducts) {
    printf("\nProducts in the store:\n");
    printf("%-20s %-10s %-10s\n", "Name", "Price", "Stock");

    // Move the declaration outside the loop
    int i;
    for (i = 0; i < numProducts; i++) {
        printf("%-20s $%-9.2f %-10d\n", products[i].name, products[i].price, products[i].stock);
    }
    printf("\n");
}

// Change this in the saveToFile function
void saveToFile(struct Product *products, int numProducts) {
    FILE *file = fopen("store_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Move the declaration outside the loop
    int i;
    for (i = 0; i < numProducts; i++) {
        fprintf(file, "%s %f %d\n", products[i].name, products[i].price, products[i].stock);
    }

    fclose(file);
}


// Function to load products from a file
int loadFromFile(struct Product *products) {
    FILE *file = fopen("store_data.txt", "r");
    if (file == NULL) {
        return 0; // File does not exist or cannot be opened
    }

    int numProducts = 0;
    while (fscanf(file, "%s %f %d", products[numProducts].name, &products[numProducts].price, &products[numProducts].stock) == 3) {
        numProducts++;
    }

    fclose(file);
    return numProducts;
}

int main() {
    struct Product products[100]; // Assuming a maximum of 100 products
    int numProducts = 0;

    // Load existing data from file
    numProducts = loadFromFile(products);

    int choice;
    do {
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(products, &numProducts);
                break;
            case 2:
                displayProducts(products, numProducts);
                break;
            case 3:
                saveToFile(products, numProducts);
                printf("Data saved. Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
