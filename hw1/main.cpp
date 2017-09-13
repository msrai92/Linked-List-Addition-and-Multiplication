//
//  main.cpp
//  hw1
//
//  Created by Manvir Rai on 6/8/17.
//  Copyright © 2017 Manvir Rai. All rights reserved.
//

#include <iostream>
#include "ArgumentManager.h"
#include "DoubleLinkedList.h"
#include <fstream>
int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: infinitearithmetic \"input=xyz.txt;digitsPerNode=<number>\"\n";
    }
    ArgumentManager am(argc, argv);
    std::string filename = am.get("input");
    int digitsPerNode = std::stoi(am.get("digitsPerNode"));
    std::ifstream ifs(filename.c_str());
    std::string line;


    while (getline(ifs, line)){
   
        std::string num1;
        std::string num2;
        char op;
        num1.clear();
        num2.clear();

        // replace op with space
        for (char& c : line)  //this for loop was given by kaoji
        {
            if(!isdigit(c)){
                op = c;
                c = ' ';
                break;
            }
        }
        
        std::stringstream  ss(line);    //now that operand is removed extract both numbers
        ss >> num1 >> num2;
        
    
        
        DoubleLinkedList l1(num1, digitsPerNode);  // DoubleLinkedList(const std::string& num, int digitsPerNode)
        DoubleLinkedList l2(num2, digitsPerNode);
        DoubleLinkedList l(digitsPerNode);
        
        if(op == '+'){
            l = l1+l2;                                          //if operand is + add
            std::cout << num1 << op << num2 << "="; l.Print();
        }
        
        else if(op=='*'){
            l = l1*l2;
            std::cout << num1 << op << num2 << "="; l.Print();  //if operand is * mulitply
        }
    }
 
    
        return 0;
}
