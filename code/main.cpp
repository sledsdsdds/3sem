#include <windows.h>
#include <iostream>
#include <vector>
#include "Person.h"
#include "Lawyer.h"
#include "Client.h"
#include "Service.h"
#include "LegalCase.h"
#include "LawOffice.h"

/**
 * @brief Точка входа в демонстрационную программу
 * @return 0 при успешном завершении программы
 */
int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Service srv1("Консультация по разводу", "Консультация", "Гражданские", "Семейные", 3000.0);
    Service srv2("Раздел имущества в суде", "Ведение дела в суде", "Гражданские", "Семейные", 35000.0);
    Service srv3("Защита по делу об убийстве", "Ведение дела в суде", "Уголовные", "Убийства", 120000.0);
    Service srv4("Жилищный спор", "Консультация", "Гражданские", "Жилищные", 2500.0);

    Lawyer law1("Иванов", "Иван", "Иванович", "LAW-001", "Семейные");
    Lawyer law2("Смирнова", "Елена", "Сергеевна", "LAW-002", "Семейные");
    Lawyer law3("Кузнецов", "Павел", "Алексеевич", "LAW-003", "Убийства");

    Client cl1("Петров", "Петр", "Петрович", "CL-1001", "+7 (916) 111-22-33");
    Client cl2("Сидорова", "Анна", "Владимировна", "CL-1002", "+7 (926) 444-55-66");

    // Коллекция базового типа, заполненная объектами-наследниками
    std::vector<Person*> people = { &law1, &cl1, &law2, &cl2, &law3 };
    for (const auto* personPtr : people)
    {
        std::cout << personPtr->ToString() << "\n";
    }
    std::cout << "\n";

    LawOffice office("Адвокатская контора «Право и Закон»", "г. Москва, ул. Тверская, д. 10");
    office.AddService(&srv1);
    office.AddService(&srv2);
    office.AddService(&srv3);
    office.AddService(&srv4);

    office.AddLawyer(&law1);
    office.AddLawyer(&law2);
    office.AddLawyer(&law3);

    office.AddClient(&cl1);
    office.AddClient(&cl2);

    LegalCase* case1 = office.OpenCase("Раздел совместно нажитой квартиры", &law1, &cl1, &srv2);
    office.OpenCase("Защита обвиняемого в суде первой инстанции", &law3, &cl2, &srv3);

    std::cout << "ЗАДАНИЕ 1\n";
    std::cout << office.GetServicesSummary() << "\n";

    std::cout << "ЗАДАНИЕ 2\n";
    std::cout << office.GetClientsByServiceInfo("Раздел имущества в суде") << "\n";

    std::cout << "ЗАДАНИЕ 3\n";
    std::cout << office.GetAvailableLawyersByServiceInfo("Раздел имущества в суде") << "\n";

    std::cout << "ЗАДАНИЕ 4\n";
    std::cout << office.GetCaseDescriptionInfo(case1->GetCaseNumber()) << "\n";

    return 0;
}