#include "LinkList.h"
#include <iostream>

template<typename T>
void print(T t){
	std::cout << t << std::endl;
}

int main(){
	List<double> linkList;	
	linkList.insert(2.9);
	linkList.insert(3.7);
	linkList.insert(3.5);
	linkList.insert(3.7);
	linkList.insert(3.2);
	linkList.insert(4);
	linkList.insert(-8.5);
	linkList.insert(1.1);
	linkList.forEach(print<double>);
	//linkList.print();
	/*std::cout << std::endl << linkList.listSize() << std::endl;
	List<int> newList(linkList);
	newList.print();*/
	linkList.deleteCrap(3.7);
	linkList.forEach(print<double>);
	//linkList.print();
	//linkList.deleteCrap(2);
	//linkList.print();

	//linkList.forEach(print);
	/*List<int> linkList;
	linkList.insertNode(5,);
	linkList.foreach(print);*/
}