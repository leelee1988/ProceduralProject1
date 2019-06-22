#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

/** @file main.cpp
 *  @brief Brief description of file.
 *  You have been hired to create software for a media player production facility that will keep track of what products are produced.
Without the software, workers on the production floor are physically producing items and having to write down what is produced in a production log book.
Management would like the production tracking to be more automated so the workers don't need to spend as much time recording what was produced, the log will be more accurate, and it will be easier to generate production reports.
 *  @author Leemarie Collet
 *  @bug No known bugs.
 */
struct catalog_struct {
    ///Vectors for ProductLine
    std::string productLineManufacturers;
    std::string productLineNames;
    std::string productLineItemTypes;
}cata;


struct production_list_struct {
    ///Vectors for Production
    std::string productionManufacturers;
    std::string productionNames;
    std::string productionItemTypes;
    std::string serialNumbers;
    int productionNumbers;
}prod_list;

struct employee_accounts_struct {
    ///Vector for Employee Account
    std::string password;
    std::string userName;
}emp;

struct employee_test_struct {
    ///Vector for Password Testing
    std::string password_temp;
    ///Vector for UserName Testing
    std::string testUserName;
}emp_test;

int display_menu_and_get_choice();

void produce_items(std::vector<production_list_struct> &, const std::vector<catalog_struct> &);

void add_new_items(std::vector<catalog_struct> &);

void produce_statistics(const std::vector<production_list_struct> &);

void create_employee_account(std::vector<employee_accounts_struct> &, std::vector<employee_test_struct> &);

bool employee_login(std::vector<employee_accounts_struct> &, std::vector<employee_test_struct> &);

int main() {

    std::vector<catalog_struct> catalog_vector;
    std::vector<production_list_struct> production_list_vector;
    std::vector<employee_accounts_struct> employee_accounts_vector;
    std::vector<employee_test_struct> employee_test_vector;

    ///Populates Vectors
    std::string line;
    //file to string and string to vector
    //catalog
    std::ifstream catalog("Catalog.csv");
    while (getline(catalog, line)) {
        std::stringstream ss(line);
        getline(ss, cata.productLineManufacturers, ',');
        getline(ss,  cata.productLineNames, ',');
        getline(ss, cata.productLineItemTypes);
        catalog_vector.push_back(cata);
    }
    catalog.close();

    //if catalog file does not exist create file and populate vector
    if(catalog_vector.size() == 0){
        std::ofstream populateCatalog("Catalog.csv");
        populateCatalog << "Microsoft,Zune,AM" << std::endl;
        populateCatalog << "Apple,iPod,AM" << std::endl;
        populateCatalog << "Sylvania,SDVD1187,VM" << std::endl;
        populateCatalog.close();
        while (getline(catalog, line)) {
            std::stringstream ss(line);
            getline(ss, cata.productLineManufacturers, ',');
            getline(ss,  cata.productLineNames, ',');
            getline(ss, cata.productLineItemTypes);
            catalog_vector.push_back(cata);
        }
        populateCatalog.close();
    }

    //file to string and string to vector
    //production list
    std::ifstream production_list("production_list.csv");
    while(getline(production_list, line)) {
        std::stringstream ss(line);
        std::string prod_num;
        getline(ss, prod_num, ',');
        prod_list.productionNumbers = std::stoi(prod_num);
        getline(ss, prod_list.productionManufacturers, ',');
        getline(ss, prod_list.productionItemTypes, ',');
        getline(ss, prod_list.productionNames, ',');
        getline(ss, prod_list.serialNumbers);
        production_list_vector.push_back(prod_list);
    }

    production_list.close();
    //file to string and string to vector
    //Employee Accounts
    std::ifstream employeeAccounts("employee_accounts.csv");
    while (getline(employeeAccounts, line)) {
        std::stringstream ss(line);
        getline(ss, emp.userName, ',');
        getline(ss, emp.password);
        employee_accounts_vector.push_back(emp);
    }
    employeeAccounts.close();


    //Welcome greeting
    std::cout << "   Production Line Tracker   " << std::endl;
    std::cout << "*****************************" << std::endl;
    std::cout << "Please log in to continue..." << std::endl;
    bool logged_in = false;

    //Initialize for menu start
    int user_menu_choice;
    bool continue_program = true;
    while (continue_program) {
        if(logged_in == false){
            //login on startup
            logged_in = employee_login(employee_accounts_vector,employee_test_vector);}
        if (logged_in == false) {
            user_menu_choice = display_menu_and_get_choice();
        }
        if (logged_in == false) {
            switch (user_menu_choice) {
                //Product Items
                case 1: {
                    produce_items(production_list_vector, catalog_vector);
                    break;
                }
                    //Add Items to Catalog
                case 2: {
                    add_new_items(catalog_vector);
                    break;
                }
                    //Display Production Statistics
                case 3: {
                    produce_statistics(production_list_vector);
                    break;
                }
                    //Create Employee Account
                case 4: {
                    create_employee_account(employee_accounts_vector, employee_test_vector);
                    break;
                }
                    //Logout or in to account
                case 5: {
                    logged_in = false;
                    std::cout << "You have been logged out" << std::endl;
                    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                    break;
                }
                    //Exit Program
                case 6: {
                    continue_program = false;
                    break;
                }
                default: {
                    std::cout << "You have entered an invalid number, please try again.\n" << std::endl;
                    break;
                }
            }
        } else {
            std::cout << "Please log in to access system..." << std::endl;
            employee_login(employee_accounts_vector,employee_test_vector);
        }
    }
}

int display_menu_and_get_choice() {
    //Menu selection prompt
    std::cout << "\n**********Menu************" << std::endl;
    std::cout << "1) Produce Items\n";
    std::cout << "2) Add New Item to Catalog\n";
    std::cout << "3) Production Statistics\n";
    std::cout << "4) Create Employee Account\n";
    std::cout << "5) Logout of Account\n";
    std::cout << "6) Exit Program\n";
    int userMenuChoice;
    std::cin >> userMenuChoice;
    return userMenuChoice;
}

void produce_items(std::vector<production_list_struct> &production_list_vector,
                   const std::vector<catalog_struct> &catalog_vector) {
    //output catalog
    std::cout << "\nChoose a Product to Produce:" << std::endl;
    std::cout << "****************************" << std::endl;
    for (int product_index = 0; product_index < catalog_vector.size(); product_index++) {
        std::cout << product_index + 1 << ". ";
        std::cout << catalog_vector[product_index].productLineManufacturers << " ";
        std::cout << catalog_vector[product_index].productLineNames << " ";
        std::cout << catalog_vector[product_index].productLineItemTypes << "\n";
    }
    //choice for production
    int userChoiceForProduct;
    std::cin >> userChoiceForProduct;
    userChoiceForProduct = userChoiceForProduct - 1;

    //output for number to produce
    std::cout << "How many would you like to Produce?:" << std::endl;
    int serialNumInput;
    std::cin >> serialNumInput;

    //get num for serial
    int countItemType = 0;
    std::string itemType = catalog_vector[userChoiceForProduct].productLineItemTypes;
    //std::cout << productionItemTypes.size() << std::endl;
    for (int i = 0; i < production_list_vector.size(); i++) {
        if (itemType == production_list_vector[i].productionItemTypes) {
            countItemType++;
        }
    }
    //create serial num and save
    int serialCount = 1;
    int prodNum = production_list_vector.size();
    //std::cout << productionManufacturers.size()<<std::endl;
    while (serialCount < serialNumInput + 1) {
        prodNum++;
        std::ofstream productionList;
        productionList.open("production_list.csv", std::ios_base::app);
        std::string manReduced = catalog_vector[userChoiceForProduct].productLineManufacturers.substr(0, 3);
        std::string serialNumber;
        productionList << prodNum << "," << catalog_vector[userChoiceForProduct].productLineManufacturers
                       << "," << catalog_vector[userChoiceForProduct].productLineItemTypes << ","
                       << catalog_vector[userChoiceForProduct].productLineNames << "," << manReduced
                       << catalog_vector[userChoiceForProduct].productLineItemTypes << std::setfill('0') << std::setw(5)
                       << countItemType + serialCount << std::endl;
        serialCount++;
    }
    int reset_vectors = production_list_vector.size();
    for(int reset_vetors_count = 0; reset_vetors_count < reset_vectors; reset_vetors_count++) {
        production_list_vector.pop_back();
    }
    std::string line;
    std::ifstream production_list("production_list.csv");
    while(getline(production_list, line)) {
        std::stringstream ss(line);
        std::string prod_num;
        getline(ss, prod_num, ',');
        prod_list.productionNumbers = std::stoi(prod_num);
        getline(ss, prod_list.productionManufacturers, ',');
        getline(ss, prod_list.productionItemTypes, ',');
        getline(ss, prod_list.productionNames, ',');
        getline(ss, prod_list.serialNumbers);
        production_list_vector.push_back(prod_list);
    }
    production_list.close();
}

void add_new_items(std::vector<catalog_struct> &catalog_vector){
    std::cout << "\nAdd Product to Cataglog" << std::endl;
    std::cout << "***********************" << std::endl;
    std::string manufacturer, prodName;
    int itemType;
    std::cout << "Enter Manufacturer:" << std::endl;
    std::cin >> manufacturer;
    std::cout << "Enter Product Name:" << std::endl;
    std::cin >> prodName;
    std::cout << "What is the Item Type:\n1. Audio\n2. Visual\n3. AudioMobile\n4. VisualMobile" << std::endl;
    std::cin >> itemType;
    std::string itemTypeCode;
    switch (itemType) {
        case 1:
            itemTypeCode = "MM";
            break;
        case 2:
            itemTypeCode = "VI";
            break;
        case 3:
            itemTypeCode = "AM";
            break;
        case 4:
            itemTypeCode = "VM";
            break;
        default:
            std::cout << "Not a valid selection\n";
            std::cout << "Setting type to 'NA'\n";
            itemTypeCode = "NA";
            break;
    }
    int catalogCount = 0;
    std::ofstream catalog;
    while (catalogCount < 1) {
        catalog.open("Catalog.csv", std::ios_base::app);
        catalog << manufacturer << "," << prodName << "," << itemTypeCode << std::endl;
        catalogCount++;
    }
    catalog.close();

    cata.productLineManufacturers = manufacturer;
    cata.productLineNames = prodName;
    cata.productLineItemTypes = itemTypeCode;
    catalog_vector.push_back(cata);
}

void produce_statistics(const std::vector<production_list_struct> &production_list_vector){
    int statisticChoice;
    std::cout << "\nChoose Statistic to Produce:" << std::endl;
    std::cout << "****************************" << std::endl;
    std::cout
            << "1. Number of each Item Type\n2. Total Items Produced\n3. Display Serials of Type\n"
               "4. Display Entire Production Log\n5. Search for Serial Number Info" << std::endl;
    std::cin >> statisticChoice;
    switch (statisticChoice) {
        case 1: {
            //Displaying number of each Item Type
            int countItemType = 0;
            std::string itemType = "MM";
            for (int i = 0; i < production_list_vector.size(); i++) {
                if (itemType == production_list_vector[i].productionItemTypes) {
                    countItemType++;
                }
            }
            std::cout << "Number of 'MM': " << countItemType << std::endl;
            //Reset for next type
            countItemType = 0;
            itemType = "VI";
            for (int i = 0; i < production_list_vector.size(); i++) {
                if (itemType == production_list_vector[i].productionItemTypes) {
                    countItemType++;
                }
            }
            std::cout << "Number of 'VI': " << countItemType << std::endl;
            //Reset for next type
            countItemType = 0;
            itemType = "AM";
            for (int i = 0; i < production_list_vector.size(); i++) {
                if (itemType == production_list_vector[i].productionItemTypes) {
                    countItemType++;
                }
            }
            std::cout << "Number of 'AM': " << countItemType << std::endl;
            //Reset for next type
            countItemType = 0;
            itemType = "VM";
            for (int i = 0; i < production_list_vector.size(); i++) {
                if (itemType == production_list_vector[i].productionItemTypes) {
                    countItemType++;
                }
            }
            std::cout << "Number of 'VM': " << countItemType << std::endl;
            //system("pause");
            break;
        }
        case 2: {
            //total items produced
            int totalItemCount = 0;
            for (totalItemCount; totalItemCount < production_list_vector.size(); totalItemCount++) {
            }
            std::cout << "Total Items Currently Produced: " << totalItemCount << std::endl;
            //system("pause");
            break;
        }
        case 3: {
            //serials of certain type
            int itemType;
            std::cout << "What is the Item Type:\n1. Audio\n2. Visual\n3. AudioMobile\n4. VisualMobile" << std::endl;
            std::cin >> itemType;
            std::string itemTypeCode;
            switch (itemType) {
                case 1:
                    itemTypeCode = "MM";
                    break;
                case 2:
                    itemTypeCode = "VI";
                    break;
                case 3:
                    itemTypeCode = "AM";
                    break;
                case 4:
                    itemTypeCode = "VM";
                    break;
                default:
                    std::cout << "Not a valid selection\n";
                    std::cout << "Setting type to 'NA'\n";
                    itemTypeCode = "NA";
                    break;
            }
            std::cout << "Serial Numbers for Type of: " << itemTypeCode << std::endl;
            int ifPrinted = 0;
            for (int outputCount = 0; outputCount < production_list_vector.size(); outputCount++) {
                if (itemTypeCode == production_list_vector[outputCount].productionItemTypes) {
                    std::cout << production_list_vector[outputCount].serialNumbers << std::endl;
                    ifPrinted++;
                }
            }
            if (ifPrinted == 0) {
                std::cout << "No Items of that Type found." << std::endl;
            }
            //system("pause");
            break;
        }
        case 4: {
            //display entire production log
            for (int outputCount = 0; outputCount < production_list_vector.size(); outputCount++) {
                std::cout << production_list_vector[outputCount].productionNumbers << ". Manufacturer: '"
                          << production_list_vector[outputCount].productionManufacturers << "' Item Type: '"
                          << production_list_vector[outputCount].productionItemTypes
                          << "' Product Name: '" << production_list_vector[outputCount].productionNames << "' Serial Number: '" <<
                          production_list_vector[outputCount].serialNumbers << "'" << std::endl;
            }
            break;
        }
        case 5: {
            //search for serial number
            std::cout << "Enter the Serial Number: \n";
            std::string serialInput;
            std::cin >> serialInput;
            int ifPrinted = 0;
            for (int serialCount = 0; serialCount < production_list_vector.size(); serialCount++) {
                if (production_list_vector[serialCount].serialNumbers == serialInput) {
                    std::cout << "Production Number: '" << production_list_vector[serialCount].productionNumbers << ".' Manufacturer: '"
                              << production_list_vector[serialCount].productionManufacturers << "' Item Type: '"
                              << production_list_vector[serialCount].productionItemTypes
                              << "' Product Name: '" << production_list_vector[serialCount].productionItemTypes << "'" << std::endl;
                    ifPrinted++;
                }
            }
            if (ifPrinted == 0) {
                std::cout << "That Serial Number Could Not Be Found." << std::endl;
            }
            break;
        }
        default:
            std::cout << "Invalid selection" << std::endl;
            break;
    }
}

void create_employee_account(std::vector<employee_accounts_struct> &employee_accounts_vector, std::vector<employee_test_struct> &employee_test_vector){
    std::cout << "Enter employee's first name:\n";
    std::string first_name;
    std::cin >> first_name;
    std::cout << "Enter employee's last name:\n";
    std::string last_name;
    std::cin >> last_name;
    std::string user_name;

    // create user name
    char user_first = first_name[0];
    std::string user_last = last_name;
    user_name = user_first + user_last;
    std::transform(user_name.begin(), user_name.end(), user_name.begin(), ::tolower);
    std::string pass;

    std::cout << "Your generated user name: " + user_name + "\n";

    //check if password entered is valid
    bool valid;
    std::cout << "Enter employee's password:\n";
    std::cout << "Must contain a number and lowercase and uppercase letters.\n";

    int count = 0;

    std::cin >> pass;
    // code to check if valid
    int uppercaseCount = 0;
    int lowercaseCount = 0;
    int digitCount = 0;
    for (count = 0; count < pass.size(); count++) {
        if (isupper(pass[count])) {
            uppercaseCount = 1;
        }
        if (islower(pass[count])) {
            lowercaseCount = 1;
        }
        if (isdigit(pass[count])) {
            digitCount = 1;
        }
    }
    if (uppercaseCount != 0 && lowercaseCount != 0 && digitCount != 0) {
        valid = true;
    } else {
        valid = false;
    }

    /// STRUCT FOR EMP ACCOUNTS AND ENCRYPT PASSWORD SORT OUT
    if (valid) {
        std::cout << "Valid Password" << std::endl;
        emp.userName = user_name;
        emp.password = pass;
        employee_accounts_vector.push_back(emp);

        /// save both to file
        emp_test.testUserName = user_name;
        emp_test.password_temp = pass;
        employee_test_vector.push_back(emp_test);
        std::string encrypt_pass = employee_test_vector[0].password_temp;
        employee_test_vector.pop_back();
        std::string end_pass;
        for (int count = 0; count < encrypt_pass.size(); count++) {
            char first_char = encrypt_pass[count];
            first_char += 3;
            char new_first_char = first_char;
            end_pass += new_first_char;
        }
        emp.password = end_pass;
        employee_accounts_vector.push_back(emp);

        std::ofstream employee_accounts;
        employee_accounts.open("employee_accounts.csv", std::ios_base::app);
        employee_accounts << emp.userName << "," << emp.password << std::endl;
        employee_accounts.close();
    } else {
        std::cout << "Invalid Password" << std::endl;
    }
}

bool employee_login(std::vector<employee_accounts_struct> &employee_accounts_vector, std::vector<employee_test_struct> &employee_test_vector){
    std::string userName_temp;
    std::cout << "Enter Username: " << std::endl;
    std::cin >> userName_temp;
    emp_test.testUserName = userName_temp;

    bool user_found = false;
    bool logged_in = false;

    for (int count = 0; count < employee_accounts_vector.size(); count++) {
        if (userName_temp == employee_accounts_vector[count].userName) {

            std::cout << "Enter Password: " << std::endl;
            std::string test_pass;
            std::cin >> test_pass;
            emp_test.password_temp = test_pass;
            employee_test_vector.push_back(emp_test);

            ///create encyrption for test pass
            std::string encrypt_pass = employee_test_vector[0].password_temp;
            employee_test_vector.pop_back();
            std::string end_pass;
            for (int encrypt_count = 0; encrypt_count < encrypt_pass.length(); encrypt_count++) {
                char first_char = encrypt_pass[encrypt_count];
                first_char += 3;
                char new_first_char = first_char;
                end_pass += new_first_char;
            }
            user_found = true;
            ///loop for user-password testcase

            if (end_pass == employee_accounts_vector[count].password) {
                std::cout << "Login Success: " << std::endl;
                logged_in = true;
                break;
            } else {
                std::cout << "Incorrect Password!" << std::endl;
                break;
            }
        }
    }
    if (user_found == false) {
        std::cout << "User was not found!" << std::endl;
    }

    return logged_in;
}
