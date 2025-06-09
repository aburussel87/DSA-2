#include "inventory.h"
#include <bits/stdc++.h>

vector<string> splitter(const string &s, char delimiter)
{
    vector<string> tokens;
    istringstream ss(s);
    string token;
    while (getline(ss, token, delimiter))
    {
        if (!token.empty())
        {
            if (token.front() == '"')
            {
                token = token.substr(1, token.length() - 2);
            }
            tokens.push_back(token);
        }
    }
    return tokens;
}

int main()
{
    ofstream outfile("output.txt");
    ifstream infile("input.txt");
    INVENTORY myInventory;
    if(!outfile.is_open()){
        cout<<"Error opening file!"<<endl;
        return 1;
    }
    if (!infile.is_open())
    {
        cout << "Error opening file!"<<endl;
        return 1;
    }

    string line;
    vector<string> orders;
    while (getline(infile, line))
    {
        orders = splitter(line, ' ');
        if (orders[0] == "AI")
        {
            myInventory.AddItem(outfile, orders[1], orders[2], orders[3]);
        }
        else if (orders[0] == "BI")
        {
            myInventory.BuyItem(outfile,orders[1], orders[2]);
        }
        else if (orders[0] == "CI")
        {
            myInventory.CheckItem(outfile,orders[1]);
        }
        else if (orders[0] == "Clr")
        {
            myInventory.ClearInventory(outfile);
        }
        else if (orders[0] == "S")
        {
            myInventory.InventorySize(outfile);
        }
        else if (orders[0] == "Em")
        {
            myInventory.Empty(outfile);
        }
        else if (orders[0] == "Itr")
        {
            myInventory.ListInventory(outfile);
        }
        else
        {
            cout << "Enter valid command\n";
        }
    }

    infile.close();
    return 0;
}
