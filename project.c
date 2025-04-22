#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_PRODUCTS 1000
#define MAX_SUPPLIERS 100
#define MAX_ORDERS 500
#define MAX_USERS 50
#define MAX_STRING 100

// Structure definitions
typedef struct {
    int id;
    char name[MAX_STRING];
    float price;
    int quantity;
    char category[MAX_STRING];
    int supplier_id;
    char last_updated[MAX_STRING];
} Product;

typedef struct {
    int id;
    char name[MAX_STRING];
    char contact_person[MAX_STRING];
    char phone[MAX_STRING];
    char email[MAX_STRING];
    char address[MAX_STRING];
} Supplier;

typedef struct {
    int id;
    int product_id;
    int quantity;
    float total_price;
    char order_date[MAX_STRING];
    char status[MAX_STRING];
} Order;

typedef struct {
    int id;
    char username[MAX_STRING];
    char password[MAX_STRING];
    char role[MAX_STRING];
} User;

// Global variables
Product products[MAX_PRODUCTS];
Supplier suppliers[MAX_SUPPLIERS];
Order orders[MAX_ORDERS];
User users[MAX_USERS];
int product_count = 0;
int supplier_count = 0;
int order_count = 0;
int user_count = 0;
User current_user;

// Function prototypes
void initialize_system(void);
int login(void);
void main_menu(void);
void product_menu(void);
void supplier_menu(void);
void order_menu(void);
void reports_menu(void);
void user_menu(void);

// Product functions
void add_product(void);
void update_product(void);
void delete_product(void);
void list_products(void);
void search_product(void);
int find_product(int id);

// Supplier functions
void add_supplier(void);
void update_supplier(void);
void delete_supplier(void);
void list_suppliers(void);
int find_supplier(int id);

// Order functions
void create_order(void);
void update_order_status(void);
void list_orders(void);
void generate_order_report(void);

// User functions
void add_user(void);
void change_password(void);
void list_users(void);

// Utility functions
void save_data(void);
void load_data(void);
void get_current_time(char* time_str);
int generate_id(char* type);
void clear_screen(void);

int main() {
    initialize_system();
    load_data();

    while (1) {
        if (login()) {
            main_menu();
        } else {
            printf("\nLogin failed. Please try again.\n");
        }
    }

    return 0;
}

void initialize_system(void) {
    system("cls");
    // Add default admin user if no users exist
    if (user_count == 0) {
        User admin = {1, "admin", "admin123", "admin"};
        users[user_count++] = admin;
        save_data();
    }
}

int login(void) {
    char username[MAX_STRING];
    char password[MAX_STRING];

    printf("\n=== Inventory Management System Login ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            current_user = users[i];
            return 1;
        }
    }
    return 0;
}

void main_menu(void) {
    system("cls");
    int choice;

    while (1) {
        clear_screen();
        printf("\n=== Main Menu ===\n");
        printf("1. Product Management\n");
        printf("2. Supplier Management\n");
        printf("3. Order Management\n");
        printf("4. Reports\n");
        printf("5. User Management\n");
        printf("6. Save and Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: product_menu(); break;
            case 2: supplier_menu(); break;
            case 3: order_menu(); break;
            case 4: reports_menu(); break;
            case 5:
                if (strcmp(current_user.role, "admin") == 0) {
                    user_menu();
                } else {
                    printf("\nAccess denied. Admin rights required.\n");
                }
                break;
            case 6:
                save_data();
                exit(0);
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void product_menu(void) {
    system("cls");
    int choice;

    while (1) {
        printf("\n=== Product Management ===\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. List Products\n");
        printf("5. Search Product\n");
        printf("6. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_product(); break;
            case 2: update_product(); break;
            case 3: delete_product(); break;
            case 4: list_products(); break;
            case 5: search_product(); break;
            case 6: return;
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void supplier_menu(void) {
    system("cls");
    int choice;

    while (1) {
        printf("\n=== Supplier Management ===\n");
        printf("1. Add Supplier\n");
        printf("2. Update Supplier\n");
        printf("3. Delete Supplier\n");
        printf("4. List Suppliers\n");
        printf("5. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_supplier(); break;
            case 2: update_supplier(); break;
            case 3: delete_supplier(); break;
            case 4: list_suppliers(); break;
            case 5: return;
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void add_product(void) {
    system("cls");
    if (product_count >= MAX_PRODUCTS) {
        printf("\nMaximum product limit reached.\n");
        return;
    }

    Product p;
    p.id = generate_id("product");

    printf("\nEnter product details:\n");
    printf("Name: ");
    scanf(" %[^\n]s", p.name);
    printf("Price: ");
    scanf("%f", &p.price);
    printf("Quantity: ");
    scanf("%d", &p.quantity);
    printf("Category: ");
    scanf(" %[^\n]s", p.category);

    list_suppliers();
    printf("Supplier ID: ");
    scanf("%d", &p.supplier_id);

    get_current_time(p.last_updated);

    products[product_count++] = p;
    printf("\nProduct added successfully.\n");
    save_data();
}

void list_products(void) {
    system("cls");
    if (product_count == 0) {
        printf("\nNo products found.\n");
        return;
    }

    printf("\n=== Product List ===\n");
    printf("ID\tName\tPrice\tQuantity\tCategory\tSupplier ID\tLast Updated\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < product_count; i++) {
        printf("%d\t%s\t%.2f\t%d\t\t%s\t\t%d\t\t%s\n",
               products[i].id,
               products[i].name,
               products[i].price,
               products[i].quantity,
               products[i].category,
               products[i].supplier_id,
               products[i].last_updated);
    }
}

void add_supplier(void) {
    system("cls");
    if (supplier_count >= MAX_SUPPLIERS) {
        printf("\nMaximum supplier limit reached.\n");
        return;
    }

    Supplier s;
    s.id = generate_id("supplier");

    printf("\nEnter supplier details:\n");
    printf("Name: ");
    scanf(" %[^\n]s", s.name);
    printf("Contact Person: ");
    scanf(" %[^\n]s", s.contact_person);
    printf("Phone: ");
    scanf(" %[^\n]s", s.phone);
    printf("Email: ");
    scanf(" %[^\n]s", s.email);
    printf("Address: ");
    scanf(" %[^\n]s", s.address);

    suppliers[supplier_count++] = s;
    printf("\nSupplier added successfully.\n");
    save_data();
}

void list_suppliers(void) {
    system("cls");
    if (supplier_count == 0) {
        printf("\nNo suppliers found.\n");
        return;
    }

    printf("\n=== Supplier List ===\n");
    printf("ID\tName\tContact Person\tPhone\tEmail\tAddress\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < supplier_count; i++) {
        printf("%d\t%s\t%s\t%s\t%s\t%s\n",
               suppliers[i].id,
               suppliers[i].name,
               suppliers[i].contact_person,
               suppliers[i].phone,
               suppliers[i].email,
               suppliers[i].address);
    }
}

void save_data(void) {
    system("cls");
    FILE *fp;

    // Save products
    fp = fopen("products.dat", "wb");
    if (fp != NULL) {
        fwrite(&product_count, sizeof(int), 1, fp);
        fwrite(products, sizeof(Product), product_count, fp);
        fclose(fp);
    }

    // Save suppliers
    fp = fopen("suppliers.dat", "wb");
    if (fp != NULL) {
        fwrite(&supplier_count, sizeof(int), 1, fp);
        fwrite(suppliers, sizeof(Supplier), supplier_count, fp);
        fclose(fp);
    }

    // Save orders
    fp = fopen("orders.dat", "wb");
    if (fp != NULL) {
        fwrite(&order_count, sizeof(int), 1, fp);
        fwrite(orders, sizeof(Order), order_count, fp);
        fclose(fp);
    }

    // Save users
    fp = fopen("users.dat", "wb");
    if (fp != NULL) {
        fwrite(&user_count, sizeof(int), 1, fp);
        fwrite(users, sizeof(User), user_count, fp);
        fclose(fp);
    }
}

void load_data(void) {
    system("cls");
    FILE *fp;

    // Load products
    fp = fopen("products.dat", "rb");
    if (fp != NULL) {
        fread(&product_count, sizeof(int), 1, fp);
        fread(products, sizeof(Product), product_count, fp);
        fclose(fp);
    }

    // Load suppliers
    fp = fopen("suppliers.dat", "rb");
    if (fp != NULL) {
        fread(&supplier_count, sizeof(int), 1, fp);
        fread(suppliers, sizeof(Supplier), supplier_count, fp);
        fclose(fp);
    }

    // Load orders
    fp = fopen("orders.dat", "rb");
    if (fp != NULL) {
        fread(&order_count, sizeof(int), 1, fp);
        fread(orders, sizeof(Order), order_count, fp);
        fclose(fp);
    }

    // Load users
    fp = fopen("users.dat", "rb");
    if (fp != NULL) {
        fread(&user_count, sizeof(int), 1, fp);
        fread(users, sizeof(User), user_count, fp);
        fclose(fp);
    }
}

void get_current_time(char* time_str) {
    system("cls");
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(time_str, MAX_STRING, "%Y-%m-%d %H:%M:%S", t);
}

int generate_id(char* type) {
    if (strcmp(type, "product") == 0) {
        return product_count + 1;
    } else if (strcmp(type, "supplier") == 0) {
        return supplier_count + 1;
    } else if (strcmp(type, "order") == 0) {
        return order_count + 1;
    } else if (strcmp(type, "user") == 0) {
        return user_count + 1;
    }
    return 0;
}

void clear_screen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void update_product(void) {
    system("cls");
    int id;
    printf("\nEnter product ID to update: ");
    scanf("%d", &id);

    int index = find_product(id);
    if (index == -1) {
        printf("\nProduct not found.\n");
        return;
    }

    printf("\nCurrent product details:\n");
    printf("Name: %s\n", products[index].name);
    printf("Price: %.2f\n", products[index].price);
    printf("Quantity: %d\n", products[index].quantity);
    printf("Category: %s\n", products[index].category);

    printf("\nEnter new details (press enter to keep current):\n");
    char input[MAX_STRING];

    printf("Name: ");
    getchar();
    fgets(input, MAX_STRING, stdin);
    if (input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(products[index].name, input);
    }

    printf("Price: ");
    fgets(input, MAX_STRING, stdin);
    if (input[0] != '\n') {
        products[index].price = atof(input);
    }

    printf("Quantity: ");
    fgets(input, MAX_STRING, stdin);
    if (input[0] != '\n') {
        products[index].quantity = atoi(input);
    }

    printf("Category: ");
    fgets(input, MAX_STRING, stdin);
    if (input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(products[index].category, input);
    }

    get_current_time(products[index].last_updated);
    printf("\nProduct updated successfully.\n");
    save_data();
}

void delete_product(void) {
    system("cls");
    int id;
    printf("\nEnter product ID to delete: ");
    scanf("%d", &id);

    int index = find_product(id);
    if (index == -1) {
        printf("\nProduct not found.\n");
        return;
    }

    for (int i = index; i < product_count - 1; i++) {
        products[i] = products[i + 1];
    }
    product_count--;

    printf("\nProduct deleted successfully.\n");
    save_data();
}

void search_product(void) {
    system("cls");
    char search_term[MAX_STRING];
    printf("\nEnter search term: ");
    getchar();
    fgets(search_term, MAX_STRING, stdin);
    search_term[strcspn(search_term, "\n")] = 0;

    printf("\nSearch results:\n");
    printf("ID\tName\tPrice\tQuantity\tCategory\tSupplier ID\tLast Updated\n");
    printf("--------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < product_count; i++) {
        if (strstr(products[i].name, search_term) || strstr(products[i].category, search_term)) {
            printf("%d\t%s\t%.2f\t%d\t\t%s\t\t%d\t\t%s\n",
                   products[i].id,
                   products[i].name,
                   products[i].price,
                   products[i].quantity,
                   products[i].category,
                   products[i].supplier_id,
                   products[i].last_updated);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo products found matching '%s'\n", search_term);
    }
}

void update_supplier(void) {
    system("cls");
    int id;
    printf("\nEnter supplier ID to update: ");
    scanf("%d", &id);

    int index = find_supplier(id);
    if (index == -1) {
        printf("\nSupplier not found.\n");
        return;
    }

    printf("\nCurrent supplier details:\n");
    printf("Name: %s\n", suppliers[index].name);
    printf("Contact Person: %s\n", suppliers[index].contact_person);
    printf("Phone: %s\n", suppliers[index].phone);
    printf("Email: %s\n", suppliers[index].email);
    printf("Address: %s\n", suppliers[index].address);

    printf("\nEnter new details (press enter to keep current):\n");
    char input[MAX_STRING];

    printf("Name: ");
    getchar();
    fgets(input, MAX_STRING, stdin);
    if (input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(suppliers[index].name, input);
    }

    printf("Contact Person: ");
    fgets(input, MAX_STRING, stdin);
    if (input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(suppliers[index].contact_person, input);
    }

    printf("Phone: ");
    fgets(input, MAX_STRING, stdin);
    if (input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(suppliers[index].phone, input);
    }

    printf("Email: ");
    fgets(input, MAX_STRING, stdin);
    if (input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(suppliers[index].email, input);
    }

    printf("Address: ");
    fgets(input, MAX_STRING, stdin);
    if (input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(suppliers[index].address, input);
    }

    printf("\nSupplier updated successfully.\n");
    save_data();
}

void delete_supplier(void) {
    system("cls");
    int id;
    printf("\nEnter supplier ID to delete: ");
    scanf("%d", &id);

    int index = find_supplier(id);
    if (index == -1) {
        printf("\nSupplier not found.\n");
        return;
    }

    for (int i = index; i < supplier_count - 1; i++) {
        suppliers[i] = suppliers[i + 1];
    }
    supplier_count--;

    printf("\nSupplier deleted successfully.\n");
    save_data();
}

int find_product(int id) {
    for (int i = 0; i < product_count; i++) {
        if (products[i].id == id) {
            return i;
        }
    }
    return -1;
}

int find_supplier(int id) {
    for (int i = 0; i < supplier_count; i++) {
        if (suppliers[i].id == id) {
            return i;
        }
    }
    return -1;
}

void order_menu(void) {
    system("cls");
    int choice;

    while (1) {
        printf("\n=== Order Management ===\n");
        printf("1. Create Order\n");
        printf("2. Update Order Status\n");
        printf("3. List Orders\n");
        printf("4. Generate Order Report\n");
        printf("5. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_order(); break;
            case 2: update_order_status(); break;
            case 3: list_orders(); break;
            case 4: generate_order_report(); break;
            case 5: return;
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void create_order(void) {
    system("cls");
    if (order_count >= MAX_ORDERS) {
        printf("\nMaximum order limit reached.\n");
        return;
    }

    Order o;
    o.id = generate_id("order");

    list_products();
    printf("\nEnter product ID: ");
    scanf("%d", &o.product_id);

    int product_index = find_product(o.product_id);
    if (product_index == -1) {
        printf("\nProduct not found.\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &o.quantity);

    if (o.quantity > products[product_index].quantity) {
        printf("\nInsufficient stock.\n");
        return;
    }

    o.total_price = products[product_index].price * o.quantity;
    products[product_index].quantity -= o.quantity;

    get_current_time(o.order_date);
    strcpy(o.status, "Pending");

    orders[order_count++] = o;
    printf("\nOrder created successfully. Total price: %.2f\n", o.total_price);
    save_data();
}

void update_order_status(void) {
    system("cls");
    int id;
    printf("\nEnter order ID to update: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < order_count; i++) {
        if (orders[i].id == id) {
            printf("\nCurrent status: %s\n", orders[i].status);
            printf("Enter new status (Pending/Processing/Completed/Cancelled): ");
            scanf("%s", orders[i].status);
            printf("\nOrder status updated successfully.\n");
            found = 1;
            save_data();
            break;
        }
    }

    if (!found) {
        printf("\nOrder not found.\n");
    }
}

void list_orders(void) {
    system("cls");
    if (order_count == 0) {
        printf("\nNo orders found.\n");
        return;
    }

    printf("\n=== Order List ===\n");
    printf("ID\tProduct ID\tQuantity\tTotal Price\tOrder Date\tStatus\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < order_count; i++) {
        printf("%d\t%d\t\t%d\t\t%.2f\t\t%s\t%s\n",
               orders[i].id,
               orders[i].product_id,
               orders[i].quantity,
               orders[i].total_price,
               orders[i].order_date,
               orders[i].status);
    }
}

void generate_order_report(void) {
    system("cls");
    float total_revenue = 0;
    int total_orders = 0;
    int pending_orders = 0;

    for (int i = 0; i < order_count; i++) {
        total_revenue += orders[i].total_price;
        total_orders++;
        if (strcmp(orders[i].status, "Pending") == 0) {
            pending_orders++;
        }
    }

    printf("\n=== Order Report ===\n");
    printf("Total Orders: %d\n", total_orders);
    printf("Pending Orders: %d\n", pending_orders);
    printf("Total Revenue: %.2f\n", total_revenue);
    printf("Average Order Value: %.2f\n", total_orders > 0 ? total_revenue / total_orders : 0);
}

void reports_menu(void) {
    system("cls");
    int choice;

    while (1) {
        printf("\n=== Reports ===\n");
        printf("1. Product Stock Report\n");
        printf("2. Order Report\n");
        printf("3. Revenue Report\n");
        printf("4. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n=== Product Stock Report ===\n");
                list_products();
                break;
            case 2:
                generate_order_report();
                break;
            case 3:
                printf("\n=== Revenue Report ===\n");
                float total_revenue = 0;
                for (int i = 0; i < order_count; i++) {
                    if (strcmp(orders[i].status, "Completed") == 0) {
                        total_revenue += orders[i].total_price;
                    }
                }
                printf("Total Revenue from Completed Orders: %.2f\n", total_revenue);
                break;
            case 4:
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void user_menu(void) {
    system("cls");
    int choice;

    while (1) {
        printf("\n=== User Management ===\n");
        printf("1. Add User\n");
        printf("2. List Users\n");
        printf("3. Change Password\n");
        printf("4. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_user(); break;
            case 2: list_users(); break;
            case 3: change_password(); break;
            case 4: return;
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void add_user(void) {
    system("cls");
    if (user_count >= MAX_USERS) {
        printf("\nMaximum user limit reached.\n");
        return;
    }

    User u;
    u.id = generate_id("user");

    printf("\nEnter user details:\n");
    printf("Username: ");
    scanf("%s", u.username);
    printf("Password: ");
    scanf("%s", u.password);
    printf("Role (admin/user): ");
    scanf("%s", u.role);

    users[user_count++] = u;
    printf("\nUser added successfully.\n");
    save_data();
}

void list_users(void) {
    system("cls");
    if (user_count == 0) {
        printf("\nNo users found.\n");
        return;
    }

    printf("\n=== User List ===\n");
    printf("ID\tUsername\tRole\n");
    printf("------------------------\n");

    for (int i = 0; i < user_count; i++) {
        printf("%d\t%s\t\t%s\n",
               users[i].id,
               users[i].username,
               users[i].role);
    }
}

void change_password(void) {
    system("cls");
    char old_password[MAX_STRING];
    char new_password[MAX_STRING];

    printf("\nEnter old password: ");
    scanf("%s", old_password);

    if (strcmp(current_user.password, old_password) != 0) {
        printf("\nIncorrect password.\n");
        return;
    }

    printf("Enter new password: ");
    scanf("%s", new_password);

    for (int i = 0; i < user_count; i++) {
        if (users[i].id == current_user.id) {
            strcpy(users[i].password, new_password);
            strcpy(current_user.password, new_password);
            printf("\nPassword changed successfully.\n");
            save_data();
            return;
        }
    }
}
