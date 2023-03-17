// It is an Command line app------------->

// product, item and cart class

#include <bits/stdc++.h>
using namespace std;

class Item; // Forward declaration of class Item for friend class
class Cart; // Forward declaration of class Cart for friend class

class Product
{
    string name;
    int price;

public:
    int id;
    Product() {}

    Product(int u_id, string name, int price) // constructor to add new product
    {
        id = u_id;

        this->name = name;
        this->price = price;
    }
    string getDisplayName()
    {
        return name + " : Rs" + to_string(price) + "\n";
    }

    string getName()
    {
        return name;
    }

    string getShortName()
    {
        return name.substr(0, 1); // e.g. it gives --> 'A' for Apple
    }

    friend class Item; // now item class can access private data members of this class i.e. price, name and id.
    friend class Cart; // now cart class can access private data members of this class i.e. price, name and id.
};

class Item
{
    Product product;
    int quantity;

public:
    Item() {}

    Item(Product p, int q) : product(p), quantity(q) {} // constructor using a initialization list.

    int getItemPrice()
    {
        return quantity * product.price;
    }

    string getItemInfo()
    {
        return to_string(quantity) + " x " + product.name + " = Rs" + to_string(quantity * product.price) + "\n";
    }

    friend class Cart;
};

// collection of an items
class Cart
{
    // Todo

    unordered_map<int, Item> items; // map has id and item
public:
    void addProduct(Product product)
    {
        if (items.count(product.id) == 0) // so, add it now in map for the first time
        {
            Item newItem(product, 1);
            items[product.id] = newItem;
        }
        else
            items[product.id].quantity += 1;
    }

    void removeProduct(Product product)
    {
        if (items.count(product.id) != 0) // so, remove it now from the map
        {
            if (items[product.id].quantity > 0)
                items[product.id].quantity -= 1;
        }
    }

    bool removeSingleProduct(Product product)
    {
        if (items.count(product.id) == 0) // means, product is not present in the map
        {
            return false;
        }
        return true;
    }

    bool checkProduct(Product product)
    {
        if (items[product.id].quantity == 0) // so don't show this product in the cart now.
            return true;
        return false;
    }

    int getTotal()
    {
        // Todo
        int total = 0; // how much we have to pay for an item
        for (auto itemPair : items)
        {
            auto item = itemPair.second;  // to get an item from a map
            total += item.getItemPrice(); // e.g. 2kg mangoes * Rs16 = 32 and 3kg Watermelons * Rs15 = 45 .........so it will return 45 + 32 = 77
        }
        return total;
    }

    string viewCart()
    {
        if (items.empty())
        {
            return "Cart is Empty";
        }

        string itemizedList;
        int cart_total = getTotal(); // total of all the items in a cart

        for (auto itemPair : items)
        {
            auto item = itemPair.second; // to get an item from a map
            if (item.quantity == 0)
                continue;
            else
                itemizedList.append(item.getItemInfo());
        }

        return itemizedList + "\n Total Amount : Rs" + to_string(cart_total) + "\n";
    }

    bool isEmpty()
    {
        return items.empty();
    }
};
