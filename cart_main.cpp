#include <bits/stdc++.h>
#include "./data_model.h"

vector<Product> allProducts = {
    Product(1, "Apple", 30),
    Product(5, "Mango", 16),
    Product(3, "Guava", 26),
    Product(2, "Banana", 10),
    Product(4, "Strawberry", 20),
    Product(6, "Watermelon", 15),
    Product(7, "Sapodilla", 12),
    Product(8, "Kiwi", 40),
};

Product *chooseProduct()
{
    // Display the list of products
    cout << "_ _ _ _ _ _ _ _ _ _" << endl;
    cout << endl;
    string ProductList;
    for (auto product : allProducts)
    {
        ProductList.append(product.getDisplayName());
    }
    cout << ProductList;

    cout << "_ _ _ _ _ _ _ _ _ _" << endl;
    cout << endl;
    cout << "Select an item ?" << endl;
    string ch;
    cin >> ch;
    string choice = ch;
    choice[0] = toupper(choice[0]);

    // use linear search
    for (int i = 0; i < allProducts.size(); i++)
    {
        if (allProducts[i].getShortName() == choice)
        {
            return &allProducts[i]; // returns address of the product
        }
    }
    // else
    cout << "Sorry, Product not found!" << endl
         << endl;
    return NULL;
}

bool checkout(Cart &cart)
{
    if (cart.isEmpty())
    {
        cout << "Your Cart is empty!" << endl;
        return false;
    }

    int total = cart.getTotal();
    cout << "* Select the Payment method : ";
    cout << "(P)ay in Cash   |   (D)ebit/(C)redit card" << endl;
    char mode;
    cin >> mode;
    if (mode == 'p')
    {
        cout << endl
             << "Enter Amount : ";
        int paid;
        cin >> paid;

        if (paid >= total)
        {
            cout << "Change : " << paid - total << endl;
            cout << "Thank You for Shopping!" << endl;
            return true;
        }

        else
        {
            cout << "Not Enough Cash!" << endl;
            cout << "Try Again!" << endl
                 << endl;
            return false;
        }
    }

    else if (mode == 'd' or mode == 'c')
    {
        string number;
        cout << endl
             << "Enter your Card Number : ";
        cin >> number;
        if (number.size() < 16 or number.size() > 16)
        {
            cout << "Card type not Accepted!" << endl;
            cout << "Try Again!" << endl;
            return false;
        }
        int cvv;
        cout << "Enter your 3-digit CVV Number : ";
        cin >> cvv;
        cout << endl
             << "        Do you want to make a Payment : (Y)es  |   (N)o" << endl;
        cout << "        ";
        char response;
        cin >> response;
        if (response == 'y')
        {
            cout << endl
                 << "        Your Payment is Successful!" << endl;
            cout << "        Thank You for Shopping!" << endl
                 << endl;
            return true;
        }
        if (response == 'n')
        {
            cout << endl
                 << "        Try Again!" << endl
                 << endl;
            return false;
        }
    }
}

int main()
{
    cout << endl;
    cout << "                                                   <---------------------- SHOPPING CART ---------------------->                      " << endl;
    cout << endl;
    cout << "* Please write your Name : ";
    string name;
    cin >> name;
    string yourName = name;
    yourName[0] = toupper(yourName[0]);

    cout << "Welcome "
         << "\"" << yourName << "\"" << endl;
    cout << "_ _ _ _ _ _ _ _ _ _" << endl;
    cout << endl;

    char action;
    Cart cart;
    while (true)
    {
        cout << "* " << yourName << ","
             << " Please select an Action -> (A)dd item, (R)emove item, (V)iew cart, (C)heckout" << endl;
        cin >> action;

        if (action == 'a')
        {
            // Todo: Add to Cart
            // View All Products + Choose Product + Add to the Cart
            cout << "Available Products for " << yourName << endl;
            Product *product = chooseProduct();
            if (product != NULL)
            {
                cout << product->getName() << " is added to the Cart." << endl
                     << endl;
                // todo:
                cart.addProduct(*product); // to convert back pointer(product) into object
            }
        }

        else if (action == 'r')
        {
            if (cart.isEmpty())
            {
                cout << "You cannot remove anything as cart is empty!" << endl
                     << endl;
                return 0;
            }
            cout << "Q) Select which Item you want to remove from the Cart? " << endl;
            Product *product = chooseProduct();
            if (product != NULL)
            {
                if (!cart.removeSingleProduct(*product))
                {
                    cout << "This item is already not there in the Cart!" << endl
                         << endl;
                }
                else
                {
                    if (cart.checkProduct(*product))
                    {
                        cout << "This item is already not there in the Cart!" << endl
                             << endl;
                        if (cart.isEmpty())
                        {
                            cout << "Your Cart is empty now." << endl
                                 << endl;
                        }
                    }
                    else
                    {
                        cout << product->getName() << " is removed from the Cart." << endl;
                        // todo:
                        cart.removeProduct(*product); // to convert back pointer(product) into object
                        cout << endl
                             << "Your Cart has now following items - " << endl;
                        cout << cart.viewCart();
                        cout << "_ _ _ _ _ _ _ _ _ _" << endl;
                    }
                }
            }
        }

        else if (action == 'v')
        {
            if (cart.isEmpty())
            {
                cout << "Your Cart is empty!" << endl
                     << endl;
                return 0;
            }
            // View the cart
            cout << "_ _ _ _ _ _ _ _ _ _" << endl;
            cout << cart.viewCart();
            cout << "_ _ _ _ _ _ _ _ _ _" << endl;
        }

        else if (action == 'c')
        {
            // checkout
            cart.viewCart();
            if (checkout(cart))
            {
                break;
            }
        }

        else
        {
            cout << "Sorry, it is not a Valid Action!" << endl;
            cout << "Try Again!" << endl
                 << endl;
        }
    }
}
