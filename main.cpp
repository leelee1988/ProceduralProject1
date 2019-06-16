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
int displayMenuAndChooseChoice();

void
produceItems(std::vector<std::string> &, std::vector<std::string> &, std::vector<std::string> &, std::vector<int> &,
             std::vector<std::string> &, std::vector<std::string> &, std::vector<std::string> &,
             std::vector<std::string> &);

void resetAndRepopulateVectors(std::vector<std::string> &, std::vector<std::string> &, std::vector<std::string> &,
                               std::vector<int> &,
                               std::vector<std::string> &, std::vector<std::string> &, std::vector<std::string> &,
                               std::vector<std::string> &);

void addNewItems(std::vector<std::string> &, std::vector<std::string> &, std::vector<std::string> &);

int main() {
    ///********* Vectors for ProductLine*********
    std::vector<std::string> productLineManufacturers;
    std::vector<std::string> productLineNames;
    std::vector<std::string> productLineItemTypes;

    ///********* Vectors for Production*********
    std::vector<std::string> productionManufacturers;
    std::vector<std::string> productionNames;
    std::vector<std::string> productionItemTypes;
    std::vector<std::string> serialNumbers;
    std::vector<int> productionNumbers;

    //code for the catalog
    std::string line;
    std::ifstream catalog("Catalog.csv");
    std::string manufacturer;
    std::string prodName;
    std::string itemTypeCode;
    while (getline(catalog, line)) {
        std::stringstream ss(line);
        getline(ss, manufacturer, ',');
        getline(ss, prodName, ',');
        getline(ss, itemTypeCode);
        productLineManufacturers.push_back(manufacturer);
        productLineNames.push_back(prodName);
        productLineItemTypes.push_back(itemTypeCode);
    }
    catalog.close();

    //code for Production list
    int prodNum;
    std::string prodNumString;
    std::string serialNum;
    std::ifstream productList("production_list.csv");
    while (getline(productList, line)) {
        std::stringstream ss(line);
        getline(ss, prodNumString, ',');
        prodNum = std::stoi(prodNumString);
        getline(ss, manufacturer, ',');
        getline(ss, itemTypeCode, ',');
        getline(ss, prodName, ',');
        getline(ss, serialNum, ',');
        productionNumbers.push_back(prodNum);
        productionManufacturers.push_back(manufacturer);
        productionItemTypes.push_back(itemTypeCode);
        productionNames.push_back(prodName);
        serialNumbers.push_back(serialNum);
    }
    productList.close();

    // this is to repopulate the vectors
    resetAndRepopulateVectors(productLineManufacturers, productLineNames, productLineItemTypes, productionNumbers,
                              productionManufacturers, productionNames, productionItemTypes, serialNumbers);

    //Welcome greeting for our production line tracker
    std::cout << "Production Line Tracker\n" << std::endl;

    //Starts menu
    int userChoice;
    bool continueProgram = true;
    while (continueProgram) {
        userChoice = displayMenuAndChooseChoice();
        if (userChoice == 1) {
            produceItems(productLineManufacturers, productLineNames, productLineItemTypes, productionNumbers,
                         productionManufacturers, productionNames, productionItemTypes, serialNumbers);
            resetAndRepopulateVectors(productLineManufacturers, productLineNames, productLineItemTypes,
                                      productionNumbers,
                                      productionManufacturers, productionNames, productionItemTypes, serialNumbers);
        } else if (userChoice == 2) {
            addNewItems(productLineManufacturers, productLineNames, productLineItemTypes);
            resetAndRepopulateVectors(productLineManufacturers, productLineNames, productLineItemTypes,
                                      productionNumbers,
                                      productionManufacturers, productionNames, productionItemTypes, serialNumbers);
        } else if (userChoice == 3) {
            //count;
            //statistics();
        } else if (userChoice == 4) {
            //employeeAccount();
        } else if (userChoice == 5) {
            //createAccount();
        } else if (userChoice == 6) {
            continueProgram = false;
        } else {
            std::cout << "You have entered an invalid number, please try again.\n\n" << std::endl;
        }
    }
    return 0;
}

int displayMenuAndChooseChoice() {
    //Menu selection prompt
    std::cout << "\n**********Menu************" << std::endl;
    std::cout << "1) Produce Items\n";
    std::cout << "2) Add New Items\n";
    std::cout << "3) Production Statistics\n";
    std::cout << "4) Employee Account\n";
    std::cout << "5) Add Employee Account\n";
    std::cout << "6) Exit Program\n";
    int userChoice;
    std::cin >> userChoice;
    return userChoice;
}

void produceItems(std::vector<std::string> &productLineManufacturers, std::vector<std::string> &productLineNames,
                  std::vector<std::string> &productLineItemTypes,
                  std::vector<int> &productionNumbers, std::vector<std::string> &productionManufacturers,
                  std::vector<std::string> &productionNames, std::vector<std::string> &productionItemTypes,
                  std::vector<std::string> &serialNumbers) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //this outputs the catalog
    std::cout << "\nChoose a Product to Produce:" << std::endl;
    std::cout << "****************************" << std::endl;
    for (int product_index = 0; product_index < productLineManufacturers.size(); product_index++) {
        std::cout << product_index + 1 << ". ";
        std::cout << productLineManufacturers[product_index] << " ";
        std::cout << productLineNames[product_index] << " ";
        std::cout << productLineItemTypes[product_index] << "\n";
    }

    //choice for production
    int userChoiceForProduct;
    std::cin >> userChoiceForProduct;
    userChoiceForProduct = userChoiceForProduct - 1;

    //output for number of items wanted to produce
    std::cout << "How many would you like to Produce?:" << std::endl;
    int serialNumInput;
    std::cin >> serialNumInput;

    //get num for serial
    int countItemType = 0;
    std::string itemType = productLineItemTypes[userChoiceForProduct];
    //std::cout << productionItemTypes.size() << std::endl;
    for (int i = 0; i < productionItemTypes.size(); i++) {
        if (itemType == productionItemTypes[i]) {
            countItemType++;
        }
    }

//creates serial number and saves it
    int serialCount = 1;
    int prodNum = productionNumbers.size();
    //std::cout << productionManufacturers.size()<<std::endl;
    while (serialCount < serialNumInput + 1) {
        prodNum++;
        std::ofstream productionList;
        productionList.open("production_list.csv", std::ios_base::app);
        std::string manReduced = productLineManufacturers[userChoiceForProduct].substr(0, 3);
        std::string serialNumber;
        productionList << prodNum << "," << productLineManufacturers[userChoiceForProduct]
                       << "," << productLineItemTypes[userChoiceForProduct] << ","
                       << productLineNames[userChoiceForProduct] << "," << manReduced
                       << productLineItemTypes[userChoiceForProduct] << std::setfill('0') << std::setw(5)
                       << countItemType + serialCount << std::endl;
        serialCount++;
    }

}

void resetAndRepopulateVectors(std::vector<std::string> &productLineManufacturers,
                               std::vector<std::string> &productLineNames,
                               std::vector<std::string> &productLineItemTypes,
                               std::vector<int> &productionNumbers, std::vector<std::string> &productionManufacturers,
                               std::vector<std::string> &productionNames, std::vector<std::string> &productionItemTypes,
                               std::vector<std::string> &serialNumbers) {

    while (0 < productLineItemTypes.size()) {
        productLineManufacturers.pop_back();
        productLineNames.pop_back();
        productLineItemTypes.pop_back();
    }

    while (0 < productionNumbers.size()) {
        productionNumbers.pop_back();
        productionManufacturers.pop_back();
        productionItemTypes.pop_back();
        productionNames.pop_back();
        serialNumbers.pop_back();
    }

    std::string line;
    //catalog
    std::ifstream catalog("Catalog.csv");
    std::string manufacturer;
    std::string prodName;
    std::string itemTypeCode;
    while (getline(catalog, line)) {
        std::stringstream ss(line);
        getline(ss, manufacturer, ',');
        getline(ss, prodName, ',');
        getline(ss, itemTypeCode);
        productLineManufacturers.push_back(manufacturer);
        productLineNames.push_back(prodName);
        productLineItemTypes.push_back(itemTypeCode);

    }
    catalog.close();

    //production list
    int prodNum;
    std::string prodNumString;
    std::string serialNum;
    std::ifstream productionList("production_list.csv");
    while (getline(productionList, line)) {
        std::stringstream ss(line);
        getline(ss, prodNumString, ',');
        prodNum = std::stoi(prodNumString);
        getline(ss, manufacturer, ',');
        getline(ss, itemTypeCode, ',');
        getline(ss, prodName, ',');
        getline(ss, serialNum);
        productionNumbers.push_back(prodNum);
        productionManufacturers.push_back(manufacturer);
        productionItemTypes.push_back(itemTypeCode);
        productionNames.push_back(prodName);
        serialNumbers.push_back(serialNum);
    }
}

void addNewItems(std::vector<std::string> &productLineManufacturers,
                 std::vector<std::string> &productLineNames, std::vector<std::string> &productLineItemTypes) {
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
    while (catalogCount < 1) {
        std::ofstream catalog;
        catalog.open("Catalog.csv", std::ios_base::app);
        catalog << manufacturer << "," << prodName << "," << itemTypeCode << std::endl;
        catalogCount++;
    }
}
