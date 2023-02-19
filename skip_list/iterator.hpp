#ifndef UNTITLED2_ITERATOR_HPP
#define UNTITLED2_ITERATOR_HPP
#include "skip_list.hpp"
#include "node.hpp"

template<typename SkipList>
class Iterator final{
    typename SkipList::link_type value;
public:
    using difference_type =	std::ptrdiff_t;
    using value_type = typename SkipList::value_type;
    using pointer = std::add_pointer_t<value_type>;
    using reference = std::add_lvalue_reference_t<value_type>;
    using iterator_category = std::forward_iterator_tag;

    Iterator() = default;

    Iterator(typename SkipList::link_type _value) noexcept{
        value = _value;
    }

    Iterator& operator++() {
        if(!value){
            throw std::runtime_error("attept to dereference end iterator");
        }
        value = value->next();
        return *this;
    }

    Iterator operator++(int){
        Iterator temp = *this;
        ++*this;
        return temp;
    }

    Iterator& operator--() {
        if(!value){
            throw std::runtime_error("attept to dereference end iterator");
        }
        value = value->previous();
        return *this;
    }

    Iterator operator--(int){
        Iterator temp = *this;
        ++*this;
        return temp;
    }

    Iterator& operator+=(int inc) {
        if(!value){
            throw std::runtime_error("attept to dereference end iterator");
        }

        value = value->next(size_t(inc));
        return *this;
    }

    Iterator operator+(int inc) {
        if(!value){
            throw std::runtime_error("attept to dereference end iterator");
        }

        return value->next(size_t(inc));
    }

    Iterator operator-(int dec) {
        if(!value){
            throw std::runtime_error("attept to dereference end iterator");
        }

        return value->previous(size_t(dec));
    }

    bool operator==(const Iterator &rhs) const noexcept{
        return value == rhs.value;
    }

    bool operator!=(const Iterator &rhs) const noexcept{
        return !(rhs == *this);
    }

    std::add_lvalue_reference_t<typename SkipList::value_type> operator*(){
        if(!value){
            throw std::runtime_error("attemp to dereference end iterator");
        }
        return value->get_value();
    }

    std::add_pointer_t<typename SkipList::value_type> operator->(){
        if(!value){
            throw std::runtime_error("attemp to dereference end iterator");
        }
        return &(value->get_value());
    }

    std::add_lvalue_reference_t<std::add_const<typename SkipList::value_type>> operator*() const{
        if(!value){
            throw std::runtime_error("attemp to dereference end iterator");
        }
        return value->get_value();
    }

    std::add_const_t<typename SkipList::value_type> operator->() const{
        if(!value){
            throw std::runtime_error("attemp to dereference end iterator");
        }
        return value->get_value();
    }
};

#endif //UNTITLED2_ITERATOR_HPP
