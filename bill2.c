#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 100

// Structure to store item details
struct Item {
    char name[1000];
    int quantity;
    int price;
    int discount;
    long int bill;
};

// Function prototypes
void addItem(struct Item items[], int *count, long int *total);
void displayBill(struct Item items[], int count, long int total, int extraDiscount);
void saveBillToCSV(struct Item items[], int count, long int total, int extraDiscount);
void sortItems(struct Item items[], int count);

int main() 
{
    struct Item items[MAX_ITEMS];
    int count = 0, choice, extraDiscount = 0;
    long int total = 0;

    while (1) {
        // Menu Options
        printf("\n===== Billing System Menu =====\n");
        printf("1. Add Item\n");
        printf("2. Display Bill\n");
        printf("3. Save Bill to File\n");
        printf("4. Apply Extra Discount\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                addItem(items, &count, &total);
                break;
            case 2:
                displayBill(items, count, total, extraDiscount);
                break;
            case 3:
                saveBillToCSV(items, count, total, extraDiscount);
                break;
            case 4:
                printf("Enter extra discount: ");
                scanf("%d", &extraDiscount);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to add an item
void addItem(struct Item items[], int *count, long int *total) {
    if (*count >= MAX_ITEMS) {
        printf("Item limit reached!\n");
        return;
    }

    struct Item newItem;
    while(1){
    getchar();  // To consume newline character left by previous input

    printf("Enter item name (or 'x' to stop): ");
    fgets(newItem.name, 1000, stdin);
    newItem.name[strcspn(newItem.name, "\n")] = '\0';  // Remove newline

    if (strcmp(newItem.name, "x") == 0) return;  // Stop if 'x' is entered

    printf("Enter quantity: ");
    scanf("%d", &newItem.quantity);
    printf("Enter price per item: ");
    scanf("%d", &newItem.price);
    printf("Enter discount: ");
    scanf("%d", &newItem.discount);

    // Calculate bill after discount
    newItem.bill = (newItem.quantity * newItem.price) - newItem.discount;
    *total += newItem.bill;

    // Add to the list
    items[*count] = newItem;
    (*count)++;

    printf("Item added successfully!\n");
    }
}

// Function to display the bill
void displayBill(struct Item items[], int count, long int total, int extraDiscount) {
    if (count == 0) {
        printf("No items in the bill!\n");
        return;
    }

    // Sort items before displaying
    sortItems(items, count);

    printf("\n--------------------------------------BILL--------------------------------------\n");
    printf("Sl. Name                                   Quantity    Price    Discount    Bill\n");
    for (int i = 0; i < count; i++) {
        printf("%-3d %-40s %-10d %-8d %-10d %-10ld\n",
               i + 1, items[i].name, items[i].quantity, items[i].price, items[i].discount, items[i].bill);
    }
    printf("--------------------------------------------------------------------------------\n");

    printf("\nExtra Discount: %d\n", extraDiscount);
    printf("Final Total: %ld\n", total - extraDiscount);
}

// Function to save the bill to a csv file
void saveBillToCSV(struct Item items[], int count, long int total, int extraDiscount) {
    FILE *file = fopen("bill.csv", "a"); // Open file in append mode
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    // Write column headers
    fprintf(file, "Sl No,Name,Quantity,Price,Discount,Bill\n");

    // Write item details
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%d,%d,%d,%ld\n",
                i + 1, items[i].name, items[i].quantity, items[i].price, items[i].discount, items[i].bill);
    }

    // Write total & discount at the bottom
    fprintf(file, ",,,,Extra Discount,%d\n", extraDiscount);
    fprintf(file, ",,,,Final Total,%ld\n", total - extraDiscount);

    fclose(file);
    printf("Bill saved as 'bill.csv' successfully! Open it in Excel.\n");
}

// Function to sort items alphabetically by name
void sortItems(struct Item items[], int count) {
    struct Item temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(items[i].name, items[j].name) > 0) {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}