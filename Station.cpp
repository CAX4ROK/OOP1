#include "Station.hpp"

#include <algorithm>
#include <utility>

Station::Station(std::size_t maxModules)
    : maxModules_(maxModules)
{
    if (maxModules == 0)
        throw std::invalid_argument("Станция должна вмещать хотя бы один модуль");
}

Station::Station(const Station& other)
    : maxModules_(other.maxModules_)
{
    modules_.reserve(other.size());
    for (const Module& module : other)
        modules_.push_back(module.clone());
}

Station& Station::operator=(const Station& other)
{
    if (this != &other)
    {
        Station copy(other);
        *this = std::move(copy);
    }

    return *this;
}

Station::Station(Station&& other) noexcept
    : modules_(std::move(other.modules_)), maxModules_(other.maxModules_)
{
    other.modules_.clear();
}

Station& Station::operator=(Station&& other) noexcept
{
    if (this != &other)
    {
        modules_ = std::move(other.modules_);
        maxModules_ = other.maxModules_;
        other.modules_.clear();
    }

    return *this;
}

std::size_t Station::size() const noexcept
{
    return modules_.size();
}

void Station::addModule(std::unique_ptr<Module> module)
{
    if (!module)
        throw std::invalid_argument("Пустой указатель нельзя добавить на станцию");
    if (size() >= maxModules_)
        throw std::length_error("На станции нет свободных мест");

    modules_.push_back(std::move(module));
}

bool Station::removeById(int id)
{
    for (std::size_t index = 0; index < size(); ++index)
    {
        if (modules_[index]->getId() == id)
        {
            removeByIndex(index);
            return true;
        }
    }

    return false;
}

void Station::removeByIndex(std::size_t index)
{
    if (index >= size())
        throw std::out_of_range("Индекс модуля вне станции");

    modules_.erase(modules_.begin() + static_cast<std::ptrdiff_t>(index));
}

Module* Station::findById(int id) noexcept
{
    for (Module& module : *this)
    {
        if (module.getId() == id)
            return &module;
    }

    return nullptr;
}

const Module* Station::findById(int id) const noexcept
{
    for (const Module& module : *this)
    {
        if (module.getId() == id)
            return &module;
    }

    return nullptr;
}

void Station::moveModule(std::size_t fromIndex, std::size_t toIndex)
{
    if (fromIndex >= size() || toIndex >= size())
        throw std::out_of_range("Индекс перемещения вне станции");

    auto from = modules_.begin() + static_cast<std::ptrdiff_t>(fromIndex);
    auto to = modules_.begin() + static_cast<std::ptrdiff_t>(toIndex);
    if (from < to)
        std::rotate(from, from + 1, to + 1);
    else if (from > to)
        std::rotate(to, from, from + 1);
}

void Station::sortByEfficiency()
{
    for (std::size_t remaining = size(); remaining > 1; --remaining)
    {
        bool swapped = false;
        auto left = begin();
        auto right = left;
        ++right;

        for (std::size_t i = 1; i < remaining; ++i)
        {
            if (left->getEfficiency() < right->getEfficiency())
            {
                std::iter_swap(left.current_, right.current_);
                swapped = true;
            }

            ++left;
            ++right;
        }

        if (!swapped)
            break;
    }
}

Station::Iterator Station::begin() noexcept
{
    return {modules_.begin(), modules_.end()};
}

Station::Iterator Station::end() noexcept
{
    return {modules_.end(), modules_.end()};
}

Station::ConstIterator Station::begin() const noexcept
{
    return {modules_.cbegin(), modules_.cend()};
}

Station::ConstIterator Station::end() const noexcept
{
    return {modules_.cend(), modules_.cend()};
}

Station::Iterator Station::getIterator() noexcept
{
    return begin();
}

Station::ConstIterator Station::getIterator() const noexcept
{
    return begin();
}
