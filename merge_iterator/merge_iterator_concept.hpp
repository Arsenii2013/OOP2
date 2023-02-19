#ifndef MERGE_ITERATOR_H_
#define MERGE_ITERATOR_H_

#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>
#include <optional>

template<std::input_iterator InputIt>
    //using const_value_t = std::add_const<typename std::iterator_traits<InputIt>::value_type>;
using value_t = std::remove_const_t<typename std::iterator_traits<InputIt>::value_type>;


namespace Concept {

    template<std::input_iterator InputIt>
    class IteratorPair final {
    private:
        //using value_t = typename std::iterator_traits<InputIt>::value_type;
        InputIt curr, end;

    public:
        IteratorPair() = default;

        IteratorPair(const InputIt &_curr, const InputIt &_end) {
            curr = _curr;
            end = _end;
        }

        IteratorPair(const std::pair<InputIt, InputIt> &p) {
            curr = p.first;
            end = p.second;
        }

        void next(){
            ++curr;
        }

        [[nodiscard]] bool is_valid() const {
            return curr != end;
        }

        [[nodiscard]] value_t<InputIt> get_value() const {
            if (!is_valid()) {
                throw std::out_of_range("Attempt to dereference end iterator");
            }
            return *curr;
        }

        bool operator==(const IteratorPair &rhs) const {
            return curr == rhs.curr &&
                   end == rhs.end;
        }

        bool operator!=(const IteratorPair &rhs) const {
            return !(rhs == *this);
        }

        bool operator<(const IteratorPair &rhs) const {
            return *curr < *rhs.curr;
        }
    };

    template<std::input_iterator InputIt, std::predicate<value_t<InputIt>, value_t<InputIt>> Compare = std::less<value_t<InputIt>>>
    class MergingIterator final {
    private:
        std::vector<IteratorPair<InputIt>> ranges;
        std::optional<value_t<InputIt>> return_value;
        Compare cmp{};

        void set_return_value(){
            if (ranges.empty()) {
                *this = MergingIterator();
                return;
            }
            auto max = std::max_element(ranges.begin(), ranges.end(),
                                        [this](IteratorPair<InputIt> x, IteratorPair<InputIt> y) {
                                            return cmp(x.get_value(), y.get_value());
                                        });
            return_value = max->get_value();
            max->next();
            if (!max->is_valid()) {
                ranges.erase(std::remove(ranges.begin(), ranges.end(), *max), ranges.end());
            }
        }
    public:
        using value_type = std::add_const_t<value_t<InputIt>>;
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using pointer = std::add_pointer_t<value_type>;
        using reference = std::add_lvalue_reference_t<value_type>;

        MergingIterator() = default;

        MergingIterator(std::initializer_list<IteratorPair<InputIt>> _ranges, Compare _cmp = Compare{}) {
            cmp = _cmp;
            std::copy_if(_ranges.begin(), _ranges.end(), std::back_inserter(ranges),
                         std::mem_fn(&IteratorPair<InputIt>::is_valid));
            set_return_value();
        }

        bool operator==(const MergingIterator &iter) const {
            return *return_value == *iter.return_value && iter.ranges == ranges;
        }

        bool operator!=(const MergingIterator &iter) const {
            return !(*this == iter);
        }

        [[nodiscard]] value_t<InputIt> operator*() const {
            if (*this == MergingIterator()) {
                throw std::out_of_range("Attempt to dereference end iterator");
            }
            return *return_value;
        }

        MergingIterator &operator++() {
            if (*this == MergingIterator()) {
                throw std::out_of_range("Attempt to increment end iterator");
            }

            set_return_value();
            return *this;
        }

        MergingIterator operator++(int) {
            MergingIterator temp = *this;
            ++*this;
            return temp;
        }

    };

}

#endif /* MERGE_ITERATOR_H_ */
