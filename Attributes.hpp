#pragma once

class Durability
{
public:
    explicit Durability(int value);

    int getValue() const noexcept;
    void setValue(int value);
    void decrease(int amount);
    void repair(int amount);

private:
    int value_;
};

class EnergyConsumption
{
public:
    explicit EnergyConsumption(int value);

    int getValue() const noexcept;
    void setValue(int value);
    void increase(int amount);
    void decrease(int amount);

private:
    int value_;
};

class Capacity
{
public:
    explicit Capacity(int value);

    int getValue() const noexcept;
    void setValue(int value);

private:
    int value_;
};
