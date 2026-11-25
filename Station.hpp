#pragma once

#include "Module.hpp"

#include <iterator>
#include <stdexcept>
#include <vector>

template <typename VectorIterator, typename ModuleType>
class StationIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Module;
    using difference_type = std::ptrdiff_t;
    using pointer = ModuleType*;
    using reference = ModuleType&;

    StationIterator() = default;

    StationIterator(VectorIterator current, VectorIterator end)
        : current_(current), end_(end)
    {
    }

    bool hasNext() const
    {
        return current_ != end_;
    }

    reference current() const
    {
        if (!hasNext())
            throw std::out_of_range("Итератор достиг конца станции");

        return **current_;
    }

    void next()
    {
        if (hasNext())
            ++current_;
    }

    reference operator*() const
    {
        return current();
    }

    pointer operator->() const
    {
        return &current();
    }

    StationIterator& operator++()
    {
        next();
        return *this;
    }

    StationIterator operator++(int)
    {
        StationIterator previous = *this;
        next();
        return previous;
    }

    bool operator==(const StationIterator& other) const
    {
        return current_ == other.current_;
    }

    bool operator!=(const StationIterator& other) const
    {
        return !(*this == other);
    }

private:
    friend class Station;

    VectorIterator current_{};
    VectorIterator end_{};
};

class Station
{
private:
    using ModuleList = std::vector<std::unique_ptr<Module>>;

    ModuleList modules_;
    std::size_t maxModules_;

public:
    using Iterator = StationIterator<ModuleList::iterator, Module>;
    using ConstIterator = StationIterator<ModuleList::const_iterator, const Module>;

    explicit Station(std::size_t maxModules);
    Station(const Station& other);
    Station& operator=(const Station& other);
    Station(Station&& other) noexcept;
    Station& operator=(Station&& other) noexcept;
    ~Station() = default;

    std::size_t size() const noexcept;
    void addModule(std::unique_ptr<Module> module);
    bool removeById(int id);
    void removeByIndex(std::size_t index);
    Module* findById(int id) noexcept;
    const Module* findById(int id) const noexcept;
    void moveModule(std::size_t fromIndex, std::size_t toIndex);
    void sortByEfficiency();

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    Iterator getIterator() noexcept;
    ConstIterator getIterator() const noexcept;
};
