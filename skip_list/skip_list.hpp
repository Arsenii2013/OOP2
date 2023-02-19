#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP
#include <functional>
#include <vector>
#include <algorithm>
#include <memory>
#include <optional>
#include <random>

#include "iterator.hpp"

template <typename Key,
        typename Value,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<std::pair<const Key,Value> > >
class SkipList final{
public:
    using node_type = Node<Key, Value, Alloc>;
    using link_type = std::shared_ptr<node_type>;
    using iterator = Iterator<SkipList>;
    using const_iterator = std::add_const_t<Iterator<SkipList>> ;
    using value_type = std::pair<const Key, Value>;
    using value_ptr = std::add_pointer_t<std::pair<const Key, Value>>;
private:
    // типизовать уровни и индексы
    // рвзнести зоны ответственности
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::geometric_distribution<size_t> random{p};
    Compare cmp;
    Alloc alloc;

    link_type head{std::make_shared<node_type>(std::vector<link_type>(max_level))};
    std::size_t _size{};
    size_t level{};
    size_t random_level(){
        size_t ret = size_t(random(gen) + 1);
        return ret > max_level ? max_level : ret;
    }
public:
    SkipList() = default;
    explicit SkipList(const Compare &comp, const Alloc &a = Alloc()) noexcept: alloc(a), cmp(comp){};

    SkipList(const SkipList &another): alloc(another.alloc), cmp(another.cmp){
        for(auto it = another.begin(); it != another.end(); it++){
            insert(*it);
        }
    }

    SkipList &operator=(const SkipList &another){
        clear();
        alloc = another.alloc;
        cmp = another.cmp;
        for(auto it = another.begin(); it != another.end(); it++){
            insert(*it);
        }
        return *this;
    }

    ~SkipList(){
        clear();
    }

    iterator begin() noexcept{
        return head->next(1);
    }
    const_iterator begin() const noexcept{
        return head->next(1);
    }

    iterator end() noexcept{
        return {};
    }

    const_iterator end() const noexcept{
        return {};
    }

    bool empty() const noexcept{
        return _size == 0;
    }

    std::size_t size() const noexcept{
        return _size;
    }

    Value &operator[](const Key &key){
        return find(key)->second;
    }

    Value &at(const Key &key){
        return (*this)[key];
    }
    const Value &at(const Key &key) const{
        return (*this)[key];
    }

    iterator insert(const value_type & _value){
        std::vector<link_type> update(max_level);
        auto x = head;
        for(size_t i = level; i >= size_t(1); --i){
            while(x->next(i) && cmp(x->next(i)->get_value().first, _value.first)){
                x = x->next(i);
            }
            update[i - size_t(1)] = x;

        }
        if(x->next(1) && x->next(1)->get_value().first == _value.first){
            x->next(1)->get_value().second = _value.second;
        }else{
            //auto lvl = random_level();
            size_t lvl = max_level;
            if(lvl > level){
                for(size_t i = level + size_t(1); i <= lvl; i++){
                    update[i - size_t(1)] = head;
                }
                level = lvl;
            }
            auto placed = std::make_shared<node_type>(_value.first, _value.second, alloc, std::vector<link_type>(lvl));

            for(size_t i = size_t(1); i <= lvl; i++){
                placed->next(i) = update[i - size_t(1)]->next(i);
                update[i - size_t(1)]->next(i) = placed;
            }
            _size++;
        }
        return x->next(1);
    }

    void erase(iterator position){
        erase(position->first);
    }

    std::size_t erase(const Key &key){
        std::vector<link_type> update(max_level);
        //auto x = &head;
        auto x = head;
        for(std::size_t i = level; i >= 1; i--){
            while(x->next(i) && cmp(x->next(i)->get_value().first, key)){
                x = x->next(i);
            }
            update[i - 1] = x;

        }
        x = x->next(1);

        if(!x || x->get_value().first != key){
            throw std::runtime_error("this key not in list");
        }

        for(size_t i = size_t(1); i <= level; i++){
            if(update[i - size_t(1)]->next(i) != x){
                break;
            }
            update[i - size_t(1)]->next(i) = x->next(i);
        }

        _size--;
        for(; level > size_t(1) && head->next(level); level--);

        return 0;
    }
    void erase(iterator first, iterator last){
        for(; first != last; erase(first), first++);
    }

    void swap(SkipList &another){
        auto tmp = std::move(another);
        another = std::move(*this);
        *this = std::move(tmp);
    }

    void clear(){
        head = std::allocate_shared<node_type>(alloc, std::vector<link_type>(max_level));
        level = 0;
        _size = 0;
    }

    iterator find(const Key &key){
        auto return_value = head;

        for(int i = level; i >= 1; i--){
            while(return_value->next(i) && cmp(return_value->next(i)->get_value().first, key)){
                return_value = return_value->next(i);
            }
        }

        return_value = return_value->next(1);
        if(!return_value || cmp(return_value->get_value().first, key) || cmp(key, return_value->get_value().first)){
            throw std::runtime_error("this key not in list");
        }
        return return_value;
    }

    const_iterator find(const Key &key) const{
        auto return_value = head;
        for(int i = level; i >= 1; i--){
            while(return_value->next(i) && cmp(return_value->next(i)->get_value().first, key)){
                return_value = return_value->next(i);
            }
        }

        return_value = return_value->next(1);
        if(!return_value || cmp(return_value->get_value().first, key) || cmp(key, return_value->get_value().first)){
            throw std::runtime_error("this key not in list");
        }
        return return_value;
    }

    inline bool operator==(const SkipList &rhs) noexcept{
        return alloc == rhs.alloc && cmp == rhs.cmp && std::equal(begin(), end(), rhs.begin(), rhs.end());
    }

    inline bool operator!=(const SkipList &rhs) noexcept{
        return !(*this == rhs);
    }
};


#endif //UNTITLED2_SKIP_LIST_HPP
