#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 100
#define MAX_ORDER_ITEMS 20
#define FILENAME "menu.txt"
#define BILLS_FOLDER "bills/"

// Structure for menu items
typedef struct {
int id;
char name[50];
float price;
char category[30];
} MenuItem;

// Structure for order items
typedef struct {
int item_id;
char name[50];
float price;
int quantity;
} OrderItem;

// Structure for order
typedef struct {
int order_id;
OrderItem items[MAX_ORDER_ITEMS];
int item_count;
float subtotal;
float gst;
float service_charge;
float total;
time_t order_time;
} Order;

MenuItem menu[MAX_ITEMS];
int menu_count = 0;

// Function prototypes
void loadMenu();
void saveMenu();
void displayMenu();
void addMenuItem();
void updateMenuItem();
void deleteMenuItem();
void takeOrder();
void generateBill(Order order);
void viewAllBills();
void displayStatistics();
float calculateGST(float amount);
float calculateServiceCharge(float amount);
void printReceipt(Order order);

int main() {
int choice;

// Create bills directory if it doesn't exist  
system("mkdir " BILLS_FOLDER " 2>nul");  
  
loadMenu();  
  
printf("=========================================\n");  
printf("    RESTAURANT BILLING MANAGEMENT SYSTEM\n");  
printf("=========================================\n");  
  
do {  
    printf("\n=== MAIN MENU ===\n");  
    printf("1. Display Menu\n");  
    printf("2. Add Menu Item\n");  
    printf("3. Update Menu Item\n");  
    printf("4. Delete Menu Item\n");  
    printf("5. Take Order\n");  
    printf("6. View All Bills\n");  
    printf("7. Display Statistics\n");  
    printf("8. Exit\n");  
    printf("Enter your choice: ");  
    scanf("%d", &choice);  
      
    switch(choice) {  
        case 1:  
            displayMenu();  
            break;  
        case 2:  
            addMenuItem();  
            break;  
        case 3:  
            updateMenuItem();  
            break;  
        case 4:  
            deleteMenuItem();  
            break;  
        case 5:  
            takeOrder();  
            break;  
        case 6:  
            viewAllBills();  
            break;  
        case 7:  
            displayStatistics();  
            break;  
        case 8:  
            saveMenu();  
            printf("Thank you for using the system!\n");  
            break;  
        default:  
            printf("Invalid choice! Please try again.\n");  
    }  
} while(choice != 8);  
  
return 0;

}

void loadMenu() {
FILE *file = fopen(FILENAME, "r");
if (file == NULL) {
printf("Menu file not found. Starting with empty menu.\n");
return;
}

menu_count = 0;  
while(fscanf(file, "%d,%49[^,],%f,%29[^\n]\n",   
            &menu[menu_count].id,   
            menu[menu_count].name,   
            &menu[menu_count].price,   
            menu[menu_count].category) != EOF) {  
    menu_count++;  
    if(menu_count >= MAX_ITEMS) break;  
}  
  
fclose(file);  
printf("Menu loaded successfully! (%d items)\n", menu_count);

}

void saveMenu() {
FILE *file = fopen(FILENAME, "w");
if (file == NULL) {
printf("Error saving menu file!\n");
return;
}

for(int i = 0; i < menu_count; i++) {  
    fprintf(file, "%d,%s,%.2f,%s\n",   
            menu[i].id,   
            menu[i].name,   
            menu[i].price,   
            menu[i].category);  
}  
  
fclose(file);  
printf("Menu saved successfully!\n");

}

void displayMenu() {
if(menu_count == 0) {
printf("No items in the menu!\n");
return;
}

printf("\n=== RESTAURANT MENU ===\n");  
printf("ID  | %-30s | %-10s | Price\n", "Item Name", "Category");  
printf("----|--------------------------------|------------|-------\n");  
  
for(int i = 0; i < menu_count; i++) {  
    printf("%-3d | %-30s | %-10s | ₹%.2f\n",   
           menu[i].id,   
           menu[i].name,   
           menu[i].category,   
           menu[i].price);  
}

}

void addMenuItem() {
if(menu_count >= MAX_ITEMS) {
printf("Menu is full! Cannot add more items.\n");
return;
}

MenuItem newItem;  
  
printf("\n=== ADD MENU ITEM ===\n");  
printf("Enter Item ID: ");  
scanf("%d", &newItem.id);  
  
// Check if ID already exists  
for(int i = 0; i < menu_count; i++) {  
    if(menu[i].id == newItem.id) {  
        printf("Item ID already exists!\n");  
        return;  
    }  
}  
  
printf("Enter Item Name: ");  
getchar(); // Clear buffer  
fgets(newItem.name, 50, stdin);  
newItem.name[strcspn(newItem.name, "\n")] = 0; // Remove newline  
  
printf("Enter Price: ");  
scanf("%f", &newItem.price);  
  
printf("Enter Category: ");  
getchar(); // Clear buffer  
fgets(newItem.category, 30, stdin);  
newItem.category[strcspn(newItem.category, "\n")] = 0; // Remove newline  
  
menu[menu_count] = newItem;  
menu_count++;  
  
printf("Item added successfully!\n");  
saveMenu();

}

void updateMenuItem() {
int id, found = 0;

printf("\n=== UPDATE MENU ITEM ===\n");  
printf("Enter Item ID to update: ");  
scanf("%d", &id);  
  
for(int i = 0; i < menu_count; i++) {  
    if(menu[i].id == id) {  
        printf("Current Name: %s\n", menu[i].name);  
        printf("Enter New Name: ");  
        getchar();  
        fgets(menu[i].name, 50, stdin);  
        menu[i].name[strcspn(menu[i].name, "\n")] = 0;  
          
        printf("Current Price: ₹%.2f\n", menu[i].price);  
        printf("Enter New Price: ");  
        scanf("%f", &menu[i].price);  
          
        printf("Current Category: %s\n", menu[i].category);  
        printf("Enter New Category: ");  
        getchar();  
        fgets(menu[i].category, 30, stdin);  
        menu[i].category[strcspn(menu[i].category, "\n")] = 0;  
          
        found = 1;  
        printf("Item updated successfully!\n");  
        saveMenu();  
        break;  
    }  
}  
  
if(!found) {  
    printf("Item with ID %d not found!\n", id);  
}

}

void deleteMenuItem() {
int id, found = 0;

printf("\n=== DELETE MENU ITEM ===\n");  
printf("Enter Item ID to delete: ");  
scanf("%d", &id);  
  
for(int i = 0; i < menu_count; i++) {  
    if(menu[i].id == id) {  
        // Shift all items after this one  
        for(int j = i; j < menu_count - 1; j++) {  
            menu[j] = menu[j + 1];  
        }  
        menu_count--;  
        found = 1;  
        printf("Item deleted successfully!\n");  
        saveMenu();  
        break;  
    }  
}  
  
if(!found) {  
    printf("Item with ID %d not found!\n", id);  
}

}

void takeOrder() {
if(menu_count == 0) {
printf("No items in menu! Please add items first.\n");
return;
}

Order order;  
order.item_count = 0;  
order.subtotal = 0;  
order.order_time = time(NULL);  
  
printf("\n=== TAKE ORDER ===\n");  
displayMenu();  
  
int choice;  
do {  
    printf("\n1. Add Item to Order\n");  
    printf("2. Finish Order\n");  
    printf("Enter choice: ");  
    scanf("%d", &choice);  
      
    if(choice == 1) {  
        if(order.item_count >= MAX_ORDER_ITEMS) {  
            printf("Order is full! Cannot add more items.\n");  
            break;  
        }  
          
        int item_id, quantity, found = 0;  
          
        printf("Enter Item ID: ");  
        scanf("%d", &item_id);  
        printf("Enter Quantity: ");  
        scanf("%d", &quantity);  
          
        // Find item in menu  
        for(int i = 0; i < menu_count; i++) {  
            if(menu[i].id == item_id) {  
                OrderItem orderItem;  
                orderItem.item_id = item_id;  
                strcpy(orderItem.name, menu[i].name);  
                orderItem.price = menu[i].price;  
                orderItem.quantity = quantity;  
                  
                order.items[order.item_count] = orderItem;  
                order.item_count++;  
                order.subtotal += (menu[i].price * quantity);  
                  
                found = 1;  
                printf("Item added to order!\n");  
                break;  
            }  
        }  
          
        if(!found) {  
            printf("Item with ID %d not found!\n", item_id);  
        }  
    }  
} while(choice != 2 && order.item_count < MAX_ORDER_ITEMS);  
  
if(order.item_count > 0) {  
    // Calculate charges  
    order.service_charge = calculateServiceCharge(order.subtotal);  
    order.gst = calculateGST(order.subtotal + order.service_charge);  
    order.total = order.subtotal + order.service_charge + order.gst;  
      
    // Generate order ID (using timestamp)  
    order.order_id = (int)order.order_time;  
      
    // Print receipt and save bill  
    printReceipt(order);  
    generateBill(order);  
} else {  
    printf("No items in order. Order cancelled.\n");  
}

}

float calculateGST(float amount) {
// 18% GST
return amount * 0.18;
}

float calculateServiceCharge(float amount) {
// 10% Service Charge
return amount * 0.10;
}

void printReceipt(Order order) {
printf("\n");
printf("=========================================\n");
printf("           RESTAURANT RECEIPT\n");
printf("=========================================\n");
printf("Order ID: %d\n", order.order_id);
printf("Date: %s", ctime(&order.order_time));
printf("-----------------------------------------\n");
printf("%-3s %-30s %-8s %-6s %-10s\n",
"Qty", "Item", "Price", "Total", "ID");
printf("-----------------------------------------\n");

for(int i = 0; i < order.item_count; i++) {  
    printf("%-3d %-30s ₹%-7.2f ₹%-5.2f %-3d\n",   
           order.items[i].quantity,  
           order.items[i].name,  
           order.items[i].price,  
           order.items[i].price * order.items[i].quantity,  
           order.items[i].item_id);  
}  
  
printf("-----------------------------------------\n");  
printf("Subtotal:                    ₹%.2f\n", order.subtotal);  
printf("Service Charge (10%%):        ₹%.2f\n", order.service_charge);  
printf("GST (18%%):                   ₹%.2f\n", order.gst);  
printf("-----------------------------------------\n");  
printf("TOTAL:                       ₹%.2f\n", order.total);  
printf("=========================================\n");  
printf("        Thank you for your visit!\n");  
printf("=========================================\n");

}

void generateBill(Order order) {
char filename[100];
sprintf(filename, BILLS_FOLDER "bill_%d.txt", order.order_id);

FILE *file = fopen(filename, "w");  
if (file == NULL) {  
    printf("Error creating bill file!\n");  
    return;  
}  
  
fprintf(file, "=========================================\n");  
fprintf(file, "           RESTAURANT BILL\n");  
fprintf(file, "=========================================\n");  
fprintf(file, "Order ID: %d\n", order.order_id);  
fprintf(file, "Date: %s", ctime(&order.order_time));  
fprintf(file, "-----------------------------------------\n");  
fprintf(file, "%-3s %-30s %-8s %-6s\n",   
       "Qty", "Item", "Price", "Total");  
fprintf(file, "-----------------------------------------\n");  
  
for(int i = 0; i < order.item_count; i++) {  
    fprintf(file, "%-3d %-30s ₹%-7.2f ₹%-5.2f\n",   
           order.items[i].quantity,  
           order.items[i].name,  
           order.items[i].price,  
           order.items[i].price * order.items[i].quantity);  
}  
  
fprintf(file, "-----------------------------------------\n");  
fprintf(file, "Subtotal:                    ₹%.2f\n", order.subtotal);  
fprintf(file, "Service Charge (10%%):        ₹%.2f\n", order.service_charge);  
fprintf(file, "GST (18%%):                   ₹%.2f\n", order.gst);  
fprintf(file, "-----------------------------------------\n");  
fprintf(file, "TOTAL:                       ₹%.2f\n", order.total);  
fprintf(file, "=========================================\n");  
  
fclose(file);  
printf("Bill saved as: %s\n", filename);

}

void viewAllBills() {
printf("\n=== VIEW ALL BILLS ===\n");
system("dir " BILLS_FOLDER " /b 2>nul");
}

void displayStatistics() {
printf("\n=== RESTAURANT STATISTICS ===\n");
printf("Total Menu Items: %d\n", menu_count);

// Count items by category  
printf("\nItems by Category:\n");  
printf("------------------\n");  
  
for(int i = 0; i < menu_count; i++) {  
    int count = 1;  
    // Check if we already counted this category  
    int already_counted = 0;  
    for(int j = 0; j < i; j++) {  
        if(strcmp(menu[i].category, menu[j].category) == 0) {  
            already_counted = 1;  
            break;  
        }  
    }  
      
    if(!already_counted) {  
        for(int j = i + 1; j < menu_count; j++) {  
            if(strcmp(menu[i].category, menu[j].category) == 0) {  
                count++;  
            }  
        }  
        printf("%-15s: %d items\n", menu[i].category, count);  
    }  
}  
  
// Price statistics  
if(menu_count > 0) {  
    float min_price = menu[0].price;  
    float max_price = menu[0].price;  
    float total_value = 0;  
      
    for(int i = 0; i < menu_count; i++) {  
        if(menu[i].price < min_price) min_price = menu[i].price;  
        if(menu[i].price > max_price) max_price = menu[i].price;  
        total_value += menu[i].price;  
    }  
      
    printf("\nPrice Statistics:\n");  
    printf("-----------------\n");  
    printf("Minimum Price: ₹%.2f\n", min_price);  
    printf("Maximum Price: ₹%.2f\n", max_price);  
    printf("Average Price: ₹%.2f\n", total_value / menu_count);  
}

}