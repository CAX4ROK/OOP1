#include "Module.hpp"
#include "Station.hpp"

#include <limits>
#include <stdexcept>

int Module::nextId_ = 1;

int Module::generateId()
{
    if (nextId_ == std::numeric_limits<int>::max())
        throw std::overflow_error("Закончились идентификаторы модулей");

    return nextId_++;
}

Module::Module(const std::string& name, int efficiency, int durability,
               int energyConsumption, int capacity)
    : id_(generateId()),
      name_(name),
      durability_(durability),
      energyConsumption_(energyConsumption),
      capacity_(capacity)
{
    setEfficiency(efficiency);
}

Module::Module(const Module& other)
    : id_(generateId()),
      name_(other.name_),
      efficiency_(other.efficiency_),
      state_(other.state_),
      active_(other.active_),
      durability_(other.durability_),
      energyConsumption_(other.energyConsumption_),
      capacity_(other.capacity_)
{
}

int Module::getId() const noexcept
{
    return id_;
}

const std::string& Module::getName() const noexcept
{
    return name_;
}

int Module::getEfficiency() const noexcept
{
    return efficiency_;
}

void Module::setEfficiency(int efficiency)
{
    if (efficiency < 0 || efficiency > 100)
        throw std::invalid_argument("Эффективность должна быть от 0 до 100");

    efficiency_ = efficiency;
}

Durability& Module::getDurability() noexcept
{
    return durability_;
}

const Durability& Module::getDurability() const noexcept
{
    return durability_;
}

EnergyConsumption& Module::getEnergyConsumption() noexcept
{
    return energyConsumption_;
}

const EnergyConsumption& Module::getEnergyConsumption() const noexcept
{
    return energyConsumption_;
}

Capacity& Module::getCapacity() noexcept
{
    return capacity_;
}

const Capacity& Module::getCapacity() const noexcept
{
    return capacity_;
}

bool Module::isActive() const noexcept
{
    return active_;
}

ModuleState Module::getState() const noexcept
{
    return state_;
}

void Module::activate() noexcept
{
    setState(ModuleState::On);
}

void Module::deactivate() noexcept
{
    active_ = false;
}

void Module::setState(ModuleState state) noexcept
{
    state_ = state;
    active_ = (state == ModuleState::On);
}

void Module::moveToIndex(Station& station, std::size_t toIndex)
{
    std::size_t fromIndex = 0;
    for (Module& module : station)
    {
        if (&module == this)
        {
            station.moveModule(fromIndex, toIndex);
            return;
        }
        ++fromIndex;
    }

    throw std::invalid_argument("Модуль отсутствует на указанной станции");
}

CrewCabin::CrewCabin(const std::string& name)
    : ResidentialModule(name, 75, 100, 15, 4)
{
}

std::unique_ptr<Module> CrewCabin::clone() const
{
    return std::make_unique<CrewCabin>(*this);
}

std::string CrewCabin::getType() const
{
    return "CrewCabin";
}

MedicalCabin::MedicalCabin(const std::string& name)
    : ResidentialModule(name, 90, 100, 25, 2)
{
}

std::unique_ptr<Module> MedicalCabin::clone() const
{
    return std::make_unique<MedicalCabin>(*this);
}

std::string MedicalCabin::getType() const
{
    return "MedicalCabin";
}

SolarModule::SolarModule(const std::string& name)
    : EnergyModule(name, 85, 100, 5, 30)
{
}

std::unique_ptr<Module> SolarModule::clone() const
{
    return std::make_unique<SolarModule>(*this);
}

std::string SolarModule::getType() const
{
    return "SolarModule";
}

ReactorModule::ReactorModule(const std::string& name)
    : EnergyModule(name, 98, 100, 12, 60)
{
}

std::unique_ptr<Module> ReactorModule::clone() const
{
    return std::make_unique<ReactorModule>(*this);
}

std::string ReactorModule::getType() const
{
    return "ReactorModule";
}

BiologyLab::BiologyLab(const std::string& name)
    : ResearchModule(name, 80, 100, 30, 20)
{
}

std::unique_ptr<Module> BiologyLab::clone() const
{
    return std::make_unique<BiologyLab>(*this);
}

std::string BiologyLab::getType() const
{
    return "BiologyLab";
}

PhysicsLab::PhysicsLab(const std::string& name)
    : ResearchModule(name, 94, 100, 40, 12)
{
}

std::unique_ptr<Module> PhysicsLab::clone() const
{
    return std::make_unique<PhysicsLab>(*this);
}

std::string PhysicsLab::getType() const
{
    return "PhysicsLab";
}
