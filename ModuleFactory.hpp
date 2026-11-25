#pragma once

#include "Module.hpp"

class ModuleFactory
{
public:
    virtual ~ModuleFactory() = default;

    virtual std::unique_ptr<Module> createResidentialModule(const std::string& name) const = 0;
    virtual std::unique_ptr<Module> createEnergyModule(const std::string& name) const = 0;
    virtual std::unique_ptr<Module> createResearchModule(const std::string& name) const = 0;
};

class StandardModuleFactory : public ModuleFactory
{
public:
    std::unique_ptr<Module> createResidentialModule(const std::string& name) const override;
    std::unique_ptr<Module> createEnergyModule(const std::string& name) const override;
    std::unique_ptr<Module> createResearchModule(const std::string& name) const override;
};

class AdvancedModuleFactory : public ModuleFactory
{
public:
    std::unique_ptr<Module> createResidentialModule(const std::string& name) const override;
    std::unique_ptr<Module> createEnergyModule(const std::string& name) const override;
    std::unique_ptr<Module> createResearchModule(const std::string& name) const override;
};
