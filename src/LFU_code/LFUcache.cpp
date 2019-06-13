#include<iostream>
#include<unordered_map>
#include<list>

using namespace std;

struct Node{
	int key;
	int value;
	int freq;
	list<int>::const_iterator it;
};

class LFUcache{
public:
	//构造函数
	LFUcache(int capacity): capacity_(capacity), min_freq_(0){}
	
	int get(int key){
		auto it = cache_.find(key);
		if(it == cache_.cend())	return -1;
		visit(it->second);
		return (it->second).value;
	}

	void put(int key, int value){
		if(capacity_ == 0) return;
		auto it = cache_.find(key);

		if(it != cache_.cend()){
			it->second.value = value;
			visit(it->second);
			return;
		}
		//如果cache满
		if(cache_.size() == capacity_){
			//删除最少使用频率中最久未被使用node
			const int key_should_del = freq_list[min_freq_].back();
			freq_list[min_freq_].pop_back();
			cache_.erase(key_should_del);
		}
		//添加一个node
		min_freq_ = 1;
		freq_list[min_freq_].push_front(key);
		cache_[key] = {key, value, 1, freq_list[1].cbegin()};
	}
	
private:
	unordered_map<int, Node> cache_;
	unordered_map<int, list<int>> freq_list;
	int min_freq_;
	int capacity_;
	void visit(Node& node){
		const int pre_freq = node.freq;
		const int freq = ++(node.freq);
		freq_list[pre_freq].erase(node.it);

		if(freq_list[pre_freq].empty() && pre_freq == min_freq_){
			freq_list.erase(pre_freq);
			++min_freq_;
		}
		freq_list[freq].push_front(node.key);
		node.it = freq_list[freq].cbegin();
	}

};


int main(int argc, char** argv){
	LFUcache cache = LFUcache(6);
	cache.put(1,1);
	cache.put(2,2);
	cache.get(1);
	return 0;
}
