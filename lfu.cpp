#include<bits/stdc++.h>
using namespace std;

class LFUCache {
    int capacity;
    int minFreq;
    unordered_map<int,pair<int,int>> keyVal;
    unordered_map<int,list<int>> freqList;
    unordered_map<int,list<int>::iterator> pos;
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minFreq = 0;
    }
    
    int get(int key) {
        if(keyVal.find(key) == keyVal.end())
            return -1;
        freqList[keyVal[key].second].erase(pos[key]);
        keyVal[key].second++;
        freqList[keyVal[key].second].push_back(key);
        pos[key] = --freqList[keyVal[key].second].end();
        if(freqList[minFreq].empty())
            minFreq++;
        return keyVal[key].first;
    }
    
    void put(int key, int value) {
        if(!capacity)
            return;
        if(keyVal.find(key) != keyVal.end()) {
            keyVal[key].first = value;
            freqList[keyVal[key].second].erase(pos[key]);
            keyVal[key].second++;
            freqList[keyVal[key].second].push_back(key);
            pos[key] = --freqList[keyVal[key].second].end();
            if(freqList[minFreq].empty())
                minFreq++;
            return;
        }
        if(keyVal.size() == capacity) {
            int delKey = freqList[minFreq].front();
            keyVal.erase(delKey);
            pos.erase(delKey);
            freqList[minFreq].pop_front();
        }
        keyVal[key] = {value,1};
        freqList[1].push_back(key);
        pos[key] = --freqList[1].end();
        minFreq = 1;
    }
};

vector<int> getKeyAndValue(string s){
    vector<int> res;
    stringstream ss(s);
    string word;
    while (ss >> word) {
        if (isdigit(word[0])) {
            res.push_back(stoi(word));
        }
    }
    return res;
}

vector<int> implementLFU(int cacheSize, vector<string> queries){
    vector<int> ans;
    LFUCache cache=LFUCache(cacheSize);
    for (const auto& str : queries) {
        vector<int> keyValue=getKeyAndValue(str);
        if(str[0]=='P'){
            cache.put(keyValue[0], keyValue[1]);
        }else{
            ans.push_back(cache.get(keyValue[0]));
        }
    }
    return ans;
}
