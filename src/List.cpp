#include "List.hpp"

//CONTRUCT
List::List(){

    head = NULL;
    curr = NULL;
    tail = NULL;
    temp = NULL;    

}

void List::insertAtStart(sf::RectangleShape data){

    nodePtr n = new node;
    n->data = data;
    n->next = NULL;

    if(isEmpty()){
        head = n;
        tail = n;
    }else{
        temp = head;
        head = n;
        head->next = temp;
    }
}

int List::size(){
    int size = 0;

    if(isEmpty()){
        std::cout<<"list is null\n";
        return 0;
    }else{
        curr = head;
        while(curr->next != NULL){
            size+=1;
            curr = curr->next;
        }
    }

    return size;
}

sf::RectangleShape List::operator[](int i){
    //retrieve a node @ that position
    int index = 0;
    sf::RectangleShape none;
    if(isEmpty()){
        std::cout<<"list is empty!\n";
        return none;
    }else if(i == 0){
        return head->data;    
    }else{
        curr = head;
        while(index != i){
            curr = curr->next;    
            index++;
        }
        return curr->data;
    }
    return none;
}

bool List::isEmpty(){

    if(head == NULL){
        return true;   
    }
    return false;
}