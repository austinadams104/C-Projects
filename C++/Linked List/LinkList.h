#ifndef LINKLIST_H
#define LINKLIST_H

#include <memory>

template<typename T>
struct Node{
	T data;
	std::shared_ptr<Node<T>> next;
	Node(T t) : data(t), next(nullptr){}
};
template<typename T>
class List{
public:	
	List() :head(nullptr){}	
	std::shared_ptr<Node<T>> getHead(){
		return head;
	}
	void insert(T data){		
		insertAfter(data, findBefore(data));
	}
	void deleteCrap(T data){		
		deleteAfter(data, findBeforeDelete(data));		
	}
	int listSize(){
		int counter = 0;
		for (auto cur = head; cur != nullptr; cur = cur->next){
			++counter;
		}
		return counter;
	}
	//List(List& other) :data(other.data), next(copy(other.next)){}
	List(List& other){
		head = copy(other.getHead());
	}
	List& operator = (List& other){
		head = copy(other.getHead());
	}
	//List(List&&) = default;
	//List& operator = (List&&) = default;
	template<typename F>
	void forEach(F f){
		for (auto cur = head; cur != nullptr; cur = cur->next){
			f(cur->data);
		}
	}
private:
	std::shared_ptr<Node<T>> head;

	std::shared_ptr<Node<T>> findBefore(T const & value){
		auto cur = head;
		while (cur != nullptr && cur->next != nullptr){
			if (cur->next->data > value){				
				return cur;
			}
			cur = cur->next;
		}
		return cur;
	}
	void insertAfter(T const & data, std::shared_ptr<Node<T>> before){
		auto node = std::make_shared<Node<T>>(data);
		if (head == nullptr){
			head = node;
			return;
		}
		if (head->data > data){
			node->next = head;
			head = node;
			return;
		}
		if (!before) return;				
		node->next = before->next;
		before->next = node;
	}	
	std::shared_ptr<Node<T>> findBeforeDelete(T const & value){
		auto cur = head;
		while (cur != nullptr && cur->next != nullptr){
			if (cur->next->data == value){				
				return cur;
			}
			cur = cur->next;
		}
		return cur;
	}
	void deleteAfter(T const & data, std::shared_ptr<Node<T>> before){	
		if (before->next == nullptr) return;
		if (head == nullptr){			
			return;
		}
		if (head->data == data && head->next != nullptr){
			head = head->next;
			return;
		}
		if (head->data == data && head->next == nullptr){
			head = nullptr;
		}		
		auto after = before->next->next;
		before->next = after;
		deleteAfter(data, findBeforeDelete(data));
		return;
	}
	std::shared_ptr<Node<T>> copy(std::shared_ptr<Node<T>> list){
		if (!list) return nullptr;
		auto node = std::make_shared<Node<T>>(list->data);
		node->next = copy(list->next);
		return node;
	}
};
#endif
