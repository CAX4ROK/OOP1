#pragma once

#include "Attributes.hpp"

#include <cstddef>
#include <memory>
#include <string>

class Station;

enum class ModuleState
{
    On,
    Repair,
    Emergency
};

class Module
{
public:
    virtual ~Module() = default;

    virtual std::unique_ptr<Module> clone() const = 0;
    virtual std::string getType() const = 0;

    int getId() const noexcept;
    const std::string& getName() const noexcept;
    int getEfficiency() const noexcept;
    void setEfficiency(int efficiency);

    Durability& getDurability() noexcept;
    const Durability& getDurability() const noexcept;
    EnergyConsumption& getEnergyConsumption() noexcept;
    const EnergyConsumption& getEnergyConsumption() const noexcept;
    Capacity& getCapacity() noexcept;
    const Capacity& getCapacity() const noexcept;

    bool isActive() const noexcept;
    ModuleState getState() const noexcept;
    void activate() noexcept;
    void deactivate() noexcept;
    void setState(ModuleState state) noexcept;
    void moveToIndex(Station& station, std::size_t toIndex);

protected:
    Module(const std::string& name, int efficiency, int durability,
           int energyConsumption, int capacity);
    Module(const Module& other);
    Module& operator=(const Module& other) = delete;

private:
    static int nextId_;
    static int generateId();

    int id_;
    std::string name_;
    int efficiency_ = 0;
    ModuleState state_ = ModuleState::On;
    bool active_ = false;
    Durability durability_;
    EnergyConsumption energyConsumption_;
    Capacity capacity_;
};

class ResidentialModule : public Module
{
protected:
    using Module::Module;
};

class EnergyModule : public Module
{
protected:
    using Module::Module;
};

class ResearchModule : public Module
{
protected:
    using Module::Module;
};

class CrewCabin : public ResidentialModule
{
public:
    explicit CrewCabin(const std::string& name);
    std::unique_ptr<Module> clone() const override;
    std::string getType() const override;
};

class MedicalCabin : public ResidentialModule
{
public:
    explicit MedicalCabin(const std::string& name);
    std::unique_ptr<Module> clone() const override;
    std::string getType() const override;
};

class SolarModule : public EnergyModule
{
public:
    explicit SolarModule(const std::string& name);
    std::unique_ptr<Module> clone() const override;
    std::string getType() const override;
};

class ReactorModule : public EnergyModule
{
public:
    explicit ReactorModule(const std::string& name);
    std::unique_ptr<Module> clone() const override;
    std::string getType() const override;
};

class BiologyLab : public ResearchModule
{
public:
    explicit BiologyLab(const std::string& name);
    std::unique_ptr<Module> clone() const override;
    std::string getType() const override;
};

class PhysicsLab : public ResearchModule
{
public:
    explicit PhysicsLab(const std::string& name);
    std::unique_ptr<Module> clone() const override;
    std::string getType() const override;
};
