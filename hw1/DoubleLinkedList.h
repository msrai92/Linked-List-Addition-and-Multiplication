//
//  DoubleLinkedList.h
//  hw1
//
//  Created by Manvir Rai on 6/8/17.
//  Copyright © 2017 Manvir Rai. All rights reserved.
//

#ifndef DoubleLinkedList_h
#define DoubleLinkedList_h
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
// DoubleLinkedList.h
struct Node {
    long long num;
    Node* prev;
    Node* next;
};

class DoubleLinkedList {
public:
    DoubleLinkedList();   // default construct
    DoubleLinkedList(int digitsPerNode); //constructor with one parameter
    ~DoubleLinkedList();  // deconstruct
    DoubleLinkedList(const std::string& num, int digitsPerNode); // user defined construct
    //DoubleLinkedList(int digitsPerNode);
    DoubleLinkedList(const DoubleLinkedList& list);  // copy construct
    DoubleLinkedList& operator = (const DoubleLinkedList& list);  // assignment consturct
public:
    //mandatory
    DoubleLinkedList operator + (const DoubleLinkedList& list) const;
    // l = l1 + l2
    DoubleLinkedList operator * (const DoubleLinkedList& list) const;
    
    // optional
    DoubleLinkedList operator - (const DoubleLinkedList& list) const;
    // 10% extra
    DoubleLinkedList operator / (const DoubleLinkedList& list) const;
    // 20% extra
    DoubleLinkedList Sqrt(const DoubleLinkedList& list) const;
public:
    const Node* GetHead() const; //returns
    const Node* GetTail() const; //returns tail
    void Append(Node* node);    //add node to end of list
    void addToFront(Node* node); //add node to front of list
    void Print() const; //print linked list
    void setCount(int x); //set number of nodes
    void DestroyList();   //destroy list and deallocate memory
    int getDigitsPerNode(); //return digits per node
private:
    Node* head;
    Node* tail;
    void copyList(const DoubleLinkedList& list); //function that copys linked lists
    long long m_digitsPerNode;  //number of digits per node
    long long remainder; // for / operator
    float decimal;  // for sqrt()  7 valid digits.
    int count; //counter for the number of nodes we have
};

DoubleLinkedList::DoubleLinkedList(){
    head = NULL;
    tail = NULL;
    m_digitsPerNode = 0;
    
}

DoubleLinkedList::~DoubleLinkedList(){
    Node *temp; //pointer to deallocate the momory
    //occupied by the node
    
    while(head!=NULL)   //while there are nodes in the list
    {
        temp = head; //set temp to the current node
        head = head->next;  //advance head to the next node
        delete temp;
    }
    tail = NULL; //initialize tail to NULL; head has already
    //been set to NULL by the while loop
    count = 0;
    
}

void DoubleLinkedList::DestroyList(){
    Node *temp; //pointer to deallocate the momory
    //occupied by the node
    
    while(head!=NULL)   //while there are nodes in the list
    {
        temp = head;        //set temp to the current node
        head = head->next;  //advance head to the next node
        delete temp;
    }
    tail = NULL; //initialize tail to NULL; head has already
    //been set to NULL by the while loop
    count = 0;
}
DoubleLinkedList::DoubleLinkedList(int digitsPerNode){
    m_digitsPerNode = digitsPerNode;
    head = NULL;
    tail = NULL;
    
}

DoubleLinkedList::DoubleLinkedList(const std::string& num, int digitsPerNode){
    
    //whenever user defined constructor is called we need to make sure list is empty
    //so call deconstructor or empty the list
    head = NULL;
    tail = NULL;
    m_digitsPerNode = digitsPerNode;
    std::string number = num;
    int numDigitRemoved=0;
    int characterPos=0; // where we are in the string num
    std::string newNum; // new num is going to hold the numbers we take from the original passed as arugement
    int j = number.length() % digitsPerNode;// remainder to determine how many digits to put in first node
    
    Node *newNode;
    if (j!=0){
        //append j number of digits from number string
        //and assign to first node of list
        for(int k=0; k<j; k++){
            newNum+=number[k];
            numDigitRemoved++;
            characterPos = k;
        }
        newNode = new Node;
        long long a = std::stoi(newNum);
        newNode->num = a;
        newNode->prev = NULL;
        Append(newNode);
        count++;
    }
    if(j == 0){
        //make my first node if there is no remainder
        //take the number of digits per node
        newNum.clear();
        for(int k=0; k<digitsPerNode; k++){
            newNum+=number[k];
            numDigitRemoved++;
            characterPos=k;
        }
        
        newNode = new Node;
        long long b = std::stoi(newNum);
        newNode->num = b;
        newNode->prev = NULL;
        Append(newNode);
        count++;
    }
    while (numDigitRemoved!= number.length()){
        //making the rest of the nodes
        //if j =0 or for remaining characters of number string append nodes to list
        //for the remaining characters in number string with size digitsPerNode for
        // each node
        newNum.clear(); //clear newNum
        for(int k=0; k<digitsPerNode; k++){
            newNum+=number[characterPos+1];
            numDigitRemoved++;
            characterPos++;
        }
        newNode = new Node;
        long long c = std::stoi(newNum);
        newNode->num = c;
        Append(newNode);
        count++;
    }
    
    tail->next = NULL;
    
}

void DoubleLinkedList::Append(Node* node){
    
    if(head==NULL)
    {
        head = node;        // if head is NULL make both head and tail point to
        head->prev = NULL;  // the new node
        tail = node;
        
    }
    else if(head!=NULL){
        node->prev =tail; //our node previous point to node before
        tail->next = node; // tail point to our new node
        // to connect tail node to new node
        tail = node;       // make tail point to the last node
    }
    
}

void DoubleLinkedList::addToFront(Node* node)
{
    if(tail == NULL)
    {
        head = node;        //if head is null make tail and head
        tail = node;        //point to new node
    }
    else if(tail!=NULL){
        node->next = head;  // make node next point to head
        head->prev = node;  // make heads prev point to node
        head = node;        // head points to node and becomes firt
    }                       // node in the list
}

void DoubleLinkedList::copyList(const DoubleLinkedList& list){
    
    Node *nwNode; //pointer to create a node
    Node *current; //pointer to traverse the list
    
    if(head != NULL) //if the list is nonempty, make it empty
    {
        DestroyList();
    }
    
    if (list.head == NULL) //if other list is empty set head and tail to null and count to 0
    {
        head = NULL;
        tail = NULL;
        count = 0;
    }
    else
    {
        current = list.head; //current points to the list to be copied
        
        count = list.count;
        
        //copy the first node
        head = new Node; //create the node
        head->num = current->num; //copy the num
        head->prev = NULL; //set the link
        tail = head;  // make tail point to the first node
        current = current->next; //make next point to the next node
        
        //copy the rest of the list
        while(current!=NULL)
        {
            nwNode = new Node;          // create a node
            nwNode->num = current->num; // copy the info
            nwNode->prev = tail;        //we connect node to the previous node (or first node)
            tail->next = nwNode;        //then we make the previous node (or first node) point to the next node
            tail = nwNode;              //then we make tail point to our new node
            current = current->next;    // we go the next node in the list passed as an arguement to get info from it
        }
        tail->next = NULL; //once the while loop end the list is done
        //we make next in last node point to NULL
    }
    
}

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& list)
{
    head = NULL; //set head equal to null
    copyList(list); // call copy list
}

DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& list){
    
    if(this!=&list)
    {
        copyList(list); // call copy list
    }
    
    return *this;
}
int DoubleLinkedList::getDigitsPerNode(){
    return m_digitsPerNode;
}

void DoubleLinkedList::Print() const
{
    Node *current; //pointer to traverse the list
    long long digitsNode; //store the digits per node
    std::string str; //string to store all the numbers
    std::string number; //string to add leading zeros to
    current = head;
    digitsNode = m_digitsPerNode;
    while(current!=NULL)
    {
        number = std::to_string(current->num); //convert num in node to string
        if(current!=head){                     //we do not want to add leading zeros to first node
            if(number.length()<digitsNode){    //if the number in node is not same size as digits per node
                int k = number.length();       //go through for loop adding leading zeros to fill node
                
                int numOfZeros = m_digitsPerNode-k; //store the number of zeros to fill node
                for(int i = 0; i<numOfZeros; i++){
                    number = "0" + number; //for loop to add zeros to a string
                }
                str+=number; //add the zeros to string
            }
            else{
                str+=number; //if node is filled add to string then
            }
        }
        else{
            str+=number; //if current is the head or first node add to string
        }
        current = current->next;        //move to next node
    }
    std::cout << str << std::endl;      //print the string
    
}
void DoubleLinkedList::setCount(int x){ //set the number of nodes
    count = x;
}

DoubleLinkedList DoubleLinkedList::operator+(const DoubleLinkedList& list) const
{
    DoubleLinkedList result(m_digitsPerNode); //make a linked list to store the added numbers
    Node *p1 = this->tail;  //make p1 point to tail of one list
    Node *p2 = list.tail;   //make p2 point to other list
    int numberofNodes;      //to keep track of how many nodes we make
    long long n1;           //store p1 number
    long long n2;           //store p2 number
    long long n;            //store n1 + n2
    long long base = pow(10, m_digitsPerNode);  //used to get remainder and right amount of digits per node
  
    long long carry=0;  //used to keep track of carry and initialize to zero
    while(p1!=NULL || p2!=NULL){ //a while loop for while either list is not empty
        if(p1 == NULL){
            n1 = 0; //if node is empty set value of n to 0
        }
        else{
            n1 = p1->num; //otherwise set n1 to num in node
        }
        if(p2 == NULL){
            n2 = 0; //if node is empty set value of n to 0
        }
        else{
            n2 = p2->num; //otherwise set n2 to num in node
        }
        n = n1 + n2 + carry; //add n1, n2, and carry
        
        Node *pNewNode = new Node(); //create a new node
        pNewNode->num = n%base; //set the number in node / n%base gives the correct amount of digits
                                //that node should hold
        
        result.addToFront(pNewNode);  //add node to the front
        numberofNodes++;
        carry = n/base; // n/base gives the carry if there is a carry otherwise gives 0
        
        if(p1!=NULL){
            p1=p1->prev;  //if p1 is not null then go to previous node
        }
        if(p2!=NULL){
            p2=p2->prev;  //if p2 is not null then go to previous node
        }
    }
    if(p1==NULL && p2 == NULL){                 //if p1 and p2 are null and carry is not zero
        if(carry !=0){                          //we take the carry and add it to the front of the
            Node *pnewNode = new Node();        //linked list
            pnewNode->num = carry;
            result.addToFront(pnewNode);
            numberofNodes++;
        }
    }
    result.setCount(numberofNodes);

    return result;
}

DoubleLinkedList DoubleLinkedList::operator*(const DoubleLinkedList& list) const{
    DoubleLinkedList Result(m_digitsPerNode);   //create a linked list to add mulitiplied numbers
    Node *p1 = this->tail;  //assign p1 to the tail of one node
    Node *p2 = list.tail;   //assign p2 to the tail of other linked list
    int numberofNodes;      //number of nodes we make
    long long characterPos=0;   //used to keep track of what postition in the string we are
    long long numDigitsRemoved=0;   //how many digits were removed
    std::string newNum;
    long long n1;
    long long n2;
    long long n;
    long long base = pow(10, m_digitsPerNode);
    long long carry = 0;
    long long numOfZeros=0;
    std::string numZeros;
    
    while(p2!=NULL){
        DoubleLinkedList Multiply(m_digitsPerNode); //create a new list to keep adding every node multiplication
        
        while(p1!=NULL){    //while p1 is not null loop through linked list
            n1 =p1->num;    //store p1 num into n1
            n2 =p2->num;    //store p2 num into n2
            n = n1*n2+carry;    //mulitply n1 and n2 then add carry
            Node *p3;       //create a pointer to store n into
            p3 = new Node();    //create a new node
            p3->num = n%base;   //use n%base to store correct amount of digits into p3
            Multiply.addToFront(p3);    //add node to from of mulitply
            carry = n/base;     //find carry
            p1 = p1->prev;      //make p1 to point to previous to multiply every node by p2 node num
        }
        
        if(carry!=0){
            Node *pnewNode = new Node();    //if there is still carry we add to front of list
            pnewNode->num = carry;
            Multiply.addToFront(pnewNode);
            numberofNodes++;
            carry =0;
        }
        p1 = this->tail;    //set p1 back to tail so rest of nodes in p2 can multiply
    
        numOfZeros++;
    
        if(numOfZeros>1){                           //add the zeros to right of mulitplication
            for(int i=0; i<numOfZeros-1; i++){      //multiply 2 nodes add one zero, 3 add two and so on
                numZeros+="0";
            }
        }
        while(numDigitsRemoved!=numZeros.length()){ //loop through numOfZeros string to add
            for(int k=0; k<m_digitsPerNode; k++){   // to the end of linked list
                newNum+=numZeros[characterPos];
                
                
                characterPos++;
            }
            numDigitsRemoved++;
            Node *p4;
            p4 = new Node();
            
            long long d = std::stoi(newNum);
            p4->num = d;
            Multiply.Append(p4);
        }
        p2 = p2->prev;                  //go to the previous node to continue multiplication
        Result = Result + Multiply;     //add multiply to result
    }
    return Result;
}






#endif /* DoubleLinkedList_h */
















