//
// Created by sescer on 10.11.22.
//

#ifndef UNTITLED2_SAVED_HPP
#define UNTITLED2_SAVED_HPP
//
// Created by sescer on 24.10.22.
//

#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP
#include <functional>
#include <vector>
#include <algorithm>
#include <memory>
#include <optional>
#include <random>

constexpr inline int max_level = 4;
constexpr inline float p = 0.5F;

template <typename Key, typename Value, typename Alloc = std::allocator<std::pair<const Key,Value> > >
class Node final{
    using value_type = std::pair<const Key, Value>;
    using value_ptr = std::add_pointer_t<std::pair<const Key, Value>>;
    using link_type = std::add_pointer_t<Node<Key, Value, Alloc>>;

    std::vector<link_type> links;

    value_ptr value;
    Alloc alloc;
    //Key key;
    //Value value;
public:
    //Node() == NIL node
    Node() = default;
    Node& operator=(const Node&) = default;

    //Node(std::vector<link_type>&& li) : links(std::forward(li)) {}
    Node(const std::vector<link_type>& li) : links(li) {}

    Node(Key&& _key, Value&& _value, Alloc&& _alloc, std::vector<link_type>&& li) :
            alloc(std::forward(_alloc)), links(std::forward(li)){
        value = alloc.allocate(1);
        new(value) value_type{std::forward(_key), std::forward(_value)};
    }

    Node(const Key& _key, const Value& _value, const Alloc& _alloc, const std::vector<link_type>& li) :
            alloc(_alloc), links(li){
        value = alloc.allocate(1);
        new(value) value_type{_key, _value};
    }

    Node(const Key& _key, const Value& _value, const Alloc& _alloc, const Node* parent, std::size_t lvl) :
            alloc(_alloc){
        value = alloc.allocate(1);
        new(value) value_type{_key, _value};

        Node* Current = parent->next(0);
        links.push_back(Current);
        for(size_t Counter = 1; Counter <= lvl; Counter++){
            Current = next(Counter);
            Next.AddLast(Current);
        }
        Current=Previous;
        for(size_t Counter=0; Counter<=InLevel; Counter++)
            if(Current=PreviousOnLevel(Counter))
                Current->Next[Counter]=this;
    }

    ~Node() {
        value->~value_type();
        alloc.deallocate(value, 1);
    }

    [[nodiscard]] value_type& get_value(){
        if(!value){
            throw std::runtime_error("attemp to get value from NIL node");
        }
        return *value;
    }

    operator bool() const{
        return value != nullptr;
    }

    bool operator==(const Node &rhs) const {
        return links == rhs.links &&
               value == rhs.value;
    }

    bool operator!=(const Node &rhs) const {
        return !(rhs == *this);
    }

    std::add_pointer_t<Node>& next(std::size_t n){
        if(n > links.size()){
            throw std::runtime_error("attemp to get node bigger than max_level");
        }

        return links[n];
    }
};

template<typename SkipList>
class Iterator final{
    Node<typename SkipList::key, typename SkipList::value, typename SkipList::_alloc> value;
public:
    Iterator(Node<typename SkipList::key, typename SkipList::value, typename SkipList::_alloc>& _value){
        value = _value;
    }

    Iterator& operator++() {
        value = *value.links[0];
        return this;
    }

    Iterator operator++(int) {
        Iterator temp = *this;
        ++*this;
        return temp;
    }

    bool operator==(const Iterator &rhs) const {
        return value == rhs.value;
    }

    bool operator!=(const Iterator &rhs) const {
        return !(rhs == *this);
    }

    SkipList::value_type& operator*(){
        if(!value){
            throw std::runtime_error("attemp to dereference end iterator");
        }
        return value.get_value();
    }
};

/*template <typename Key,
        typename Value,
        typename Alloc = std::allocator<std::pair<const Key,Value> > >
const Node<Key, Value, Alloc> NIL();*/

template <typename Key,
        typename Value,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<std::pair<const Key,Value> > >
class SkipList final{
    //Node<Key, Value, Alloc> head{std::vector<link_type>(max_level, new Node<Key, Value, Alloc>())};
    Node<Key, Value, Alloc> head{std::vector<link_type>(max_level)};
    //std::array<Node<Key, Value, Alloc>, max_level> heads;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::geometric_distribution<std::size_t> random{p};
    Compare cmp;
    Alloc alloc;

    std::size_t _size;
    std::size_t level;

    std::size_t random_level(){
        std::size_t ret = random(gen) + 1;
        return ret > max_level ? max_level : ret;
    }

    Node* find(Key key){
        Node* prev = &head;
        Node* curr = head.next(max_level);
        for(std::size_t i = max_level; i>=0; i--){
            while(curr && cmp(key, curr->get_value().first)){
                prev = curr;
                curr = curr->next(i);
            }
            if(!i)
                break;
            curr = prev;
        };
        return prev;
    }

public:
    using key = Key;
    using value = Value;
    using compare = Compare;
    using _alloc = Alloc;
    using iterator = Iterator<SkipList>;
    using const_iterator = Iterator<SkipList> ;
    using value_type = std::pair<const Key, Value>;
    using value_ptr = std::add_pointer_t<std::pair<const Key, Value>>;
    using link_type = std::add_pointer_t<Node<Key, Value, Alloc>>;

    /*
    skip_list();
    explicit skip_list(const Compare &comp, const Alloc &a = Alloc());
    skip_list(const skip_list &another);

    skip_list &operator=(const skip_list &another);*/

    iterator begin(){
        return *head.next(0);
    }
    const_iterator begin() const{
        return *head.next(0);
    }

    iterator end(){
        return {};
    }

    const_iterator end() const{
        return {};
    }

    bool empty() const{
        return head;
    }

    std::size_t size() const{
        return _size;
    }

    Value &operator[](const Key &key){
        auto return_value = &head;
        for(int i = level; i >= 0; i--){
            while(return_value->next(i) && cmp(return_value->next(i)->get_value().first, key)){
                return_value = return_value->next(i);
            }
        }

        return_value = return_value->next(0);
        if(return_value == nullptr || cmp(return_value->get_value().first, key) || cmp(key, return_value->get_value().first)){
            throw std::runtime_error("this key not in list");
        }
        return return_value->get_value().second;
    }

    Value &at(const Key &key){
        return *this[key];
    }
    //const Value &at(const Key &key);*/

    /*
    iterator insert(const value_type & _value){
        std::vector<link_type> update(max_level);
        //auto x = &head;
        auto x = head;
        for(int i = level; i >= 0; i--){
            while(x->next(i) && cmp(x->next(i)->get_value().first, _value.first)){
                x = x->next(i);
            }
            update[i] = x;
        }
        //x = x->next(0);
        if(x->next(0) && *x->next(0) && x->next(0)->get_value().first == _value.first){
            x->next(0)->get_value().second = _value.second;
        }else{
            auto lvl = random_level();
            //std::size_t lvl = max_level;
            if(lvl > level){
                for(int i = level + 1; i <= lvl; i++){
                    update[i] = &head;
                }
                level = lvl;
            }
            x->next(0) = new Node<Key, Value, Alloc>(_value.first, _value.second, alloc, std::vector<link_type>(lvl));

            for(std::size_t i = 0; i < lvl; i++){
                x->next(0)->next(i);
                x->next(0)->next(i) = update[i]->next(i);
                update[i]->next(i) = x->next(0);
            }
        }
        return *x;
    }*/

    /*iterator insert(const value_type & _value){
        std::vector<Node<Key, Value, Alloc>> update(max_level);
        //auto x = &head;
        auto x = head;
        for(int i = level; i >= 0; i--){
            while(x.next(i) && cmp(x.next(i)->get_value().first, _value.first)){
                x = *x.next(i);
            }
            update[i] = x;
        }
        //x = x->next(0);
        if(x.next(0) && *x.next(0) && x.next(0)->get_value().first == _value.first){
            x.next(0)->get_value().second = _value.second;
        }else{
            auto lvl = random_level();
            //std::size_t lvl = max_level;
            if(lvl > level){
                for(int i = level + 1; i <= lvl; i++){
                    update[i] = head;
                }
                level = lvl;
            }
            x.next(0) = new Node<Key, Value, Alloc>(_value.first, _value.second, alloc, std::vector<link_type>(lvl));

            for(std::size_t i = 0; i < lvl; i++){
                x.next(0)->next(i);
                x.next(0)->next(i) = update[i].next(i);
                update[i].next(i) = x.next(0);
            }
        }
        return x;
    }*/

    iterator insert(const value_type & _value){
        Node* to_place = find(_value.first);
        Node* next = to_place->next(0);
        return x;
    }

    void erase(iterator position);
    std::size_t erase(const Key &key);
    void erase(iterator first, iterator last);

    void swap(SkipList &another);
    void clear();

    iterator find(const Key &key);
    const_iterator find(const Key &key) const;
};

/*
template <typename K, typename V, typename C, typename A>
inline bool operator==(const skip_list<K,V,C,A> &x, const skip_list<K,V,C,A> &y) {
    // ....
}

template <typename K, typename V, typename C, typename A>
inline bool operator!=(const skip_list<K,V,C,A> &x, const skip_list<K,V,C,A> &y) {
    // ....
}
*/
#endif //UNTITLED2_SKIP_LIST_HPP

#endif //UNTITLED2_SAVED_HPP
