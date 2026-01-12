#include <iostream>
#include "Menu.h"
#include "Ordering.h"

int main() {

   seneca::Ordering ord("drinks.csv", "foods.csv");
   if (!ord) {
      std::cout << "Failed to open data files or the data files are corrupted!";
      return 1;
      }
   while (true) {
      seneca::Menu main_menu("Seneca Restaurant", "End Program");
      main_menu << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";
      size_t option = main_menu.select();
      if (option == 1) {
         while (true) {
            seneca::Menu sub_menu("Order Menu", "Back to main menu");
            sub_menu << "Food" << "Drink";
            size_t order_option = sub_menu.select();
            if (order_option == 1) ord.orderFood();
            else if (order_option == 2) ord.orderDrink();
            else if (order_option == 0) break;
         }
      }
      else if (option == 2) ord.printBill(std::cout);
      else if (option == 3) ord.resetBill();
      else if (option == 4) ord.listFoods();
      else if (option == 5) ord.listDrinks();
      else {
         if (ord.hasUnsavedBill()) {
            seneca::Menu confirmation_menu("You have bills that are not saved. Are you sue you want to exit?",
               "No");
            confirmation_menu << "Yes";
            size_t confirmation_option = confirmation_menu.select();
            if (confirmation_option == 1) exit(0);
            }
         else return 0;
         }
      }
}
