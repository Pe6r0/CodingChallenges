#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <type_traits>
#include <iterator>
#include <vector>
#include <iostream>
#include <bitset>
#include <memory>
#include <unordered_map>

//todo add template

class LRUCache
{
    struct DoubleLinkedList
    {
        DoubleLinkedList* parent = nullptr;
        DoubleLinkedList* child = nullptr;
        double value  = 0.0;
        std::string key;
    };

public:
    double get(std::string name)
    {
        auto i = _storage.find(name);
        if (i == _storage.end())
        {
            throw (std::invalid_argument("name not present"));
        }
        //update order
        makeFirst(i->second);
        return i->second.value;
    }

    void set(std::string name, double value)
    {
        if (_storage.size() >= 5) //todo add template
        {
            removeLast();
        }
        DoubleLinkedList node;
        node.key = name;
        node.value = value;
        _storage[name] = node; //check for repeat
        makeFirst(_storage[name]);
        if (_last == nullptr)
        {
            _last = &_storage[name];
        }
    }

private:
    void makeFirst(DoubleLinkedList& node)
    {
        if (&node == _root)
        {
            return;
        }
        if (_last == &node)
        {
            _last = node.parent;
        }
        if (node.parent != nullptr)
        {
            node.parent->child = node.child;
            node.parent = nullptr;
        }
        if (_root != nullptr)
        {
            node.child = _root;
            _root->parent = &node;
        }
        _root = &node;
    }

    void removeLast()
    {
        if (_last == nullptr)
        {
            return;
        }

        if (_root == _last)
        {
            _storage.clear();
            _root = nullptr;
            _last = nullptr;
            return;
        }
        auto key = _last->key;
        _last->parent->child = nullptr;
        _last = _last->parent;
        _storage.erase(key);
    }
    DoubleLinkedList* _root = nullptr;
    DoubleLinkedList* _last = nullptr;
    std::unordered_map<std::string, DoubleLinkedList> _storage;
};

int main()
{
    LRUCache cache;
    cache.set("test0", 0.1);
    cache.set("test1", 0.2);
    cache.set("test2", 0.3);
    cache.set("test3", 0.4);
    cache.set("test4", 0.5);
    cache.get("test0");
    cache.set("test5", 0.6);
    return 0;
}
