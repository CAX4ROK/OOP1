#include "Attributes.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>

Durability::Durability(int value)
{
    setValue(value);
}

int Durability::getValue() const noexcept
{
    return value_;
}

void Durability::setValue(int value)
{
    if (value < 0 || value > 100)
        throw std::invalid_argument("Прочность должна быть от 0 до 100");

    value_ = value;
}

void Durability::decrease(int amount)
{
    if (amount < 0)
        throw std::invalid_argument("Урон должен быть неотрицательным");

    value_ -= std::min(amount, value_);
}

void Durability::repair(int amount)
{
    if (amount < 0)
        throw std::invalid_argument("Объём ремонта должен быть неотрицательным");

    value_ += std::min(amount, 100 - value_);
}

EnergyConsumption::EnergyConsumption(int value)
{
    setValue(value);
}

int EnergyConsumption::getValue() const noexcept
{
    return value_;
}

void EnergyConsumption::setValue(int value)
{
    if (value < 0)
        throw std::invalid_argument("Энергопотребление должно быть неотрицательным");

    value_ = value;
}

void EnergyConsumption::increase(int amount)
{
    if (amount < 0)
        throw std::invalid_argument("Прибавка должна быть неотрицательной");
    if (amount > std::numeric_limits<int>::max() - value_)
        throw std::overflow_error("Слишком большое энергопотребление");

    value_ += amount;
}

void EnergyConsumption::decrease(int amount)
{
    if (amount < 0)
        throw std::invalid_argument("Уменьшение должно быть неотрицательным");

    value_ -= std::min(amount, value_);
}

Capacity::Capacity(int value)
{
    setValue(value);
}

int Capacity::getValue() const noexcept
{
    return value_;
}

void Capacity::setValue(int value)
{
    if (value < 0)
        throw std::invalid_argument("Вместимость должна быть неотрицательной");

    value_ = value;
}
