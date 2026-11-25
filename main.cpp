#include "ModuleFactory.hpp"
#include "Station.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <utility>

#ifdef _WIN32
#include <windows.h>
#endif

const char* stateText(const Module& module)
{
    switch (module.getState())
    {
    case ModuleState::On:
        return module.isActive() ? "включён" : "выключен";
    case ModuleState::Repair:
        return "ремонт";
    case ModuleState::Emergency:
        return "авария";
    }

    return "неизвестное состояние";
}

void printModule(const Module& module)
{
    std::cout << '#' << module.getId()
              << " | " << module.getName() << " (" << module.getType() << ')'
              << " | эффективность " << module.getEfficiency() << '%'
              << " | прочность " << module.getDurability().getValue()
              << " | " << module.getEnergyConsumption().getValue() << " кВт"
              << " | вместимость " << module.getCapacity().getValue()
              << " | " << stateText(module) << '\n';
}

void printStation(const Station& station)
{
    if (station.size() == 0)
        std::cout << "Станция пуста.\n";

    for (const Module& module : station)
        printModule(module);
}

void fillStation(Station& station, const ModuleFactory& standard,
                 const ModuleFactory& advanced)
{
    station.addModule(standard.createResidentialModule("Жилой отсек"));
    station.addModule(standard.createEnergyModule("Солнечная панель"));
    station.addModule(standard.createResearchModule("Лаборатория биологии"));
    station.addModule(advanced.createResidentialModule("Медотсек"));
    station.addModule(advanced.createEnergyModule("Реактор"));
    station.addModule(advanced.createResearchModule("Лаборатория физики"));
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    try
    {
        StandardModuleFactory standard;
        AdvancedModuleFactory advanced;

        std::cout << "1. Создание станции и обход модулей\n";
        Station station(6);
        fillStation(station, standard, advanced);
        printStation(station);

        std::cout << "\n2. Глубокое копирование\n";
        Station copy(station);
        Module& copiedModule = *copy.begin();
        copiedModule.getDurability().decrease(25);
        copiedModule.getDurability().repair(5);
        copiedModule.getEnergyConsumption().increase(3);
        copiedModule.getCapacity().setValue(3);
        copiedModule.setEfficiency(60);
        copiedModule.setState(ModuleState::Repair);
        std::cout << "Оригинал: ";
        printModule(*station.begin());
        std::cout << "Копия:    ";
        printModule(copiedModule);

        Station assigned(1);
        assigned.addModule(standard.createResearchModule("Временный модуль"));
        assigned = station;
        std::cout << "После присваивания копированием: " << assigned.size() << " модулей.\n";

        std::cout << "\n3. Перемещение станции\n";
        Station moved(std::move(copy));
        std::cout << "В новой станции: " << moved.size()
                  << ", в источнике: " << copy.size() << '\n';
        printStation(copy);
        copy.addModule(standard.createResidentialModule("Новый жилой отсек"));
        std::cout << "Источник снова используется: " << copy.size() << " модуль.\n";

        assigned = std::move(moved);
        std::cout << "После присваивания перемещением: " << assigned.size()
                  << ", в источнике: " << moved.size() << '\n';

        std::cout << "\n4. Действия с модулями и сортировка\n";
        for (auto it = station.getIterator(); it.hasNext(); it.next())
            it.current().activate();

        Module& first = *station.begin();
        first.deactivate();
        printModule(first);
        first.setState(ModuleState::Emergency);
        printModule(first);
        first.moveToIndex(station, 2);
        std::cout << "После переноса первого модуля на индекс 2:\n";
        printStation(station);

        station.sortByEfficiency();
        std::cout << "После сортировки по убыванию эффективности:\n";
        printStation(station);

        std::cout << "\n5. Лимит, поиск и удаление\n";
        try
        {
            station.addModule(standard.createEnergyModule("Лишний модуль"));
        }
        catch (const std::length_error& error)
        {
            std::cout << error.what() << '\n';
        }

        const int id = station.begin()->getId();
        if (const Module* found = station.findById(id))
            std::cout << "По ID #" << id << " найден модуль: " << found->getName() << '\n';

        if (station.removeById(id))
            std::cout << "Модуль #" << id << " удалён по ID.\n";
        station.removeByIndex(0);
        std::cout << "Модуль с индексом 0 удалён. Осталось: " << station.size() << '\n';

        try
        {
            station.moveModule(0, station.size());
        }
        catch (const std::out_of_range& error)
        {
            std::cout << error.what() << '\n';
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
