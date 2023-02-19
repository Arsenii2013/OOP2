//
// Created by sescer on 02.12.22.
//

#ifndef UNTITLED2_NODE_HPP
#define UNTITLED2_NODE_HPP
#include <functional>
#include <vector>
#include <algorithm>
#include <memory>
#include <optional>
#include <random>

constexpr inline size_t max_level = size_t(4);
constexpr inline float p = 0.5F;

template <typename Key, typename Value, typename Alloc = std::allocator<std::pair<const Key,Value> > >
class Node final{
    using value_type = std::pair<const Key, Value>;
    using value_ptr = std::shared_ptr<std::pair<const Key, Value>>;
    using link_type = std::shared_ptr<Node<Key, Value, Alloc>>;

    link_type prev;
    std::vector<link_type> links{};

    value_ptr value{};
    Alloc alloc{};
public:
    Node() = default;
    Node& operator=(const Node&) = default;

    //Node(const std::initializer_list<link_type>& li) noexcept : links(li) {}
    //Node(const std::vector<link_type>& li) noexcept : links(li) {}

    Node(Key&& _key, Value&& _value, link_type&& _prev, size_t _lvl, const Alloc& _alloc = Alloc()) :
            alloc(_alloc), value(std::allocate_shared<value_type>(alloc, _key, _value)), prev(std::move(prev)){
        size_t lvl(_lvl);
        link_type Current = _prev->next(size_t(0));
        links.push_back(Current);
        for(size_t Counter = 1; Counter <= lvl; Counter++){
            Current = next(size_t(Counter));
            links.push_back(Current);
        }
        Current = prev;
        for(size_t Counter = 0; Counter <= lvl; Counter++)
            if(Current = previous(size_t(Counter)))
                Current->next(size_t(Counter)) = this;
    }

    Node(const Key& _key, const Value& _value, const link_type& prev, std::vector<link_type>&& li = {}, const Alloc& _alloc = Alloc()) :
            alloc(_alloc), links(li), value(std::allocate_shared<value_type>(alloc, _key, _value)){}

    [[nodiscard]] value_type& get_value(){
        if(value == nullptr){
            throw std::runtime_error("attemp to get value from empty node");
        }
        return *value;
    }

    operator bool() const noexcept{
        return value != nullptr;
    }

    bool operator==(const Node &rhs) const noexcept {
        if(value == nullptr || rhs.value == nullptr){
            if(value != rhs.value){
                return false;
            }
        }else{
            if(*value != *rhs.value){
                return false;
            }
        }
        return links == rhs.links;
    }

    bool operator!=(const Node &rhs) const noexcept {
        return !(rhs == *this);
    }



    link_type& previous(){
        return prev;
    }

    link_type& previous(size_t n_l){
        auto current = prev;
        for(; current && current->links.size() < n_l; current = current->prev);
        return current;
    }



    link_type& next(){
        return links[0];
    }

    link_type& next(size_t n_l){
        std::size_t n(n_l);
        if(n > links.size()){
            throw std::runtime_error("attemp to get node bigger than max_level");
        }

        return links[n - 1];
    }


};
#endif //UNTITLED2_NODE_HPP
