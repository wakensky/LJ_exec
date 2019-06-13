#include<iostream>
#include<unordered_map>
#include<list>
#include"gtest/gtest.h"
using namespace std;

class LRUcache{

public:
	LRUcache(int capacity){
		capacity_ = capacity;
	}	//构造函数创建容量为capacity的cache；

	//暴露如下两个接口
	//get(int key) 查询key是否存在cache中
	//put(int key, int value)将k-v对放入cache中
	
	int get(int key){
		const auto it = m_.find(key); //O(1)时间返回hash table中的（key）；

		//如果key不存在，那么查询失败
		if(it == m_.cend()) return -1;

		//如果存在那么要将该值从list中的任意位置移动到首部
		cache_.splice(cache_.begin(), cache_, it->second);
		return it->second->second; //并且返回其值
	}

	void put(int key, int value){
		const auto it = m_.find(key);

		//如果key已经在hash table中，那么要对value进行更新,并且移动到首部
		if(it != m_.cend()){
			it->second->second = value;
			cache_.splice(cache_.begin(), cache_, it->second);
			return;
		}
		//如果key不在且已经达到capacity，要删除最末尾的k-v对
		if(cache_.size() == capacity_){
			const auto& node = cache_.back();
			m_.erase(node.first);
			cache_.pop_back();
		}
		//以上情况均不是则将此k-v插入到cache最前端,经过上述步骤，一定有剩余容量
		cache_.emplace_front(key,value);
		m_[key] = cache_.begin();
	}
	
	void print_cache(){
		for(list<pair<int,int>>::iterator it = cache_.begin(); it != cache_.end(); it++){
			cout << it->first << " : " << it->second << endl;
		}
	}
private:
	int capacity_;
	list<pair<int,int>> cache_;
	unordered_map<int, list<pair<int,int>>::iterator> m_;
};
int main(int argc, char** argv){
	LRUcache l = LRUcache(6);
	l.put(3,2);
	l.put(6,7);
	l.put(1,1);
	l.put(2,3);
	l.get(2);
	l.get(3);
	l.print_cache();
	return 0;
}
