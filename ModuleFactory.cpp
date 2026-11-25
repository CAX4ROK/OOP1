#include "ModuleFactory.hpp"

std::unique_ptr<Module> StandardModuleFactory::createResidentialModule(const std::string& name) const
{
    return std::make_unique<CrewCabin>(name);
}

std::unique_ptr<Module> StandardModuleFactory::createEnergyModule(const std::string& name) const
{
    return std::make_unique<SolarModule>(name);
}

std::unique_ptr<Module> StandardModuleFactory::createResearchModule(const std::string& name) const
{
    return std::make_unique<BiologyLab>(name);
}

std::unique_ptr<Module> AdvancedModuleFactory::createResidentialModule(const std::string& name) const
{
    return std::make_unique<MedicalCabin>(name);
}

std::unique_ptr<Module> AdvancedModuleFactory::createEnergyModule(const std::string& name) const
{
    return std::make_unique<ReactorModule>(name);
}

std::unique_ptr<Module> AdvancedModuleFactory::createResearchModule(const std::string& name) const
{
    return std::make_unique<PhysicsLab>(name);
}
