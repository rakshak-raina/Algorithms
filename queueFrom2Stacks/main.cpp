#include <iostream>
#include<bits/stdc++.h>

using namespace std;

stack<int> first;
stack<int> second;
vector<int> arr;

int deQueue(){
    if(first.empty())
    {
        return false;
    }
    
    while(first.size()!=1){
        second.push(first.top());
        first.pop();
    }
    first.pop();
    
    while(second.size()){
        first.push(second.top());
        second.pop();
    }
    
    return true;
}

int enQueue(int in){
    first.push(in);
    return true;
}

ostream & operator<<(ostream & os, stack<int> my_stack) 
{
    while(!my_stack.empty()) 
    {
        os << my_stack.top() << " ";
        my_stack.pop();
    }
    return os; 
}

void show(){
    std::cout << first << std::endl;
}

int main() {
    enQueue(10);
    enQueue(20);
    enQueue(30);
    show();
    deQueue();
    show();
    enQueue(40);
    show();
    deQueue();
    deQueue();
    deQueue();
    deQueue();
    show();
    
	return 0;
}