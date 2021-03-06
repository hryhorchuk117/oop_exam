//
// Created by ivan on 08.06.20.
//

#ifndef OOP_EXAM_MAP_HPP
#define OOP_EXAM_MAP_HPP

#include <cassert>
#include "../Set/Set.hpp"

template <typename Tkey, typename Tvalue>
struct Pair {
    Tkey key;
    Tvalue value;
};

template <typename Tkey, typename Tvalue>
bool operator <(Pair<Tkey, Tvalue> left, Pair<Tkey, Tvalue> right) {
    return left.key < right.key;
}

template <typename Tkey, typename Tvalue>
bool operator ==(Pair<Tkey, Tvalue> left, Pair<Tkey, Tvalue> right) {
    return left.key == right.key;
}

template <typename Tkey, typename Tvalue>
bool operator >(Pair<Tkey, Tvalue> left, Pair<Tkey, Tvalue> right) {
    return left.key > right.key;
}



template <typename Tkey, typename Tvalue, template <typename, class> class Container, typename Comparator=Comp<Pair<Tkey, Tvalue>>>
class Map {
public:
    using Tset = Set<Container<Pair<Tkey, Tvalue>,Comparator>>;

    void insert(Tkey key, Tvalue value) {
        if (count(key))
            erase(key);
        set.insert({key, value});
    }

    Tvalue getValue(Tkey key) {
        auto temp = set.search({key, Tvalue()});
        assert(temp != nullptr && "Key must be exist");
        return temp->value().value;
    }

    bool count(Tkey key) {
        return set.count({key, Tvalue()});
    }

    void erase(Tkey key) {
        set.erase({key, Tvalue()});
    }

    std::vector <Tkey> keys() {
        auto elements = set._elements();
        std::vector <Tkey> result;
        for (auto i : elements) {
            result.push_back(i.key);
        }
        return result;
    }

    std::vector <Tvalue> values() {
        auto elements = set._elements();
        std::vector <Tvalue> result;
        for (auto i : elements) {
            result.push_back(i.value);
        }
        return result;
    }

    std::vector <std::pair<Tkey, Tvalue>> pairs() {
        auto elements = set._elements();
        std::vector <std::pair<Tkey, Tvalue>> result;
        for (auto i : elements) {
            result.push_back({i.key,i.value});
        }
        return result;
    }

private:
    Tset set;
};


#endif //OOP_EXAM_MAP_HPP
