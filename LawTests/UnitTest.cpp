#include "CppUnitTest.h"

#include <string>
#include <stdexcept>

#include "Person.h"
#include "Lawyer.h"
#include "Client.h"
#include "Service.h"
#include "LegalCase.h"
#include "LawOffice.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(PersonTests)
    {
    public:
        /**
         * @brief Проверка конструкторов, валидации ID и правила пяти Person
         */
        TEST_METHOD(PersonBasicAndValidation_Test)
        {
            Person p("Иванов", "Иван", "Иванович", "ID-1");
            Assert::AreEqual(std::string("Иванов Иван Иванович"), p.GetFullName());

            Assert::ExpectException<std::invalid_argument>([]() {
                Person bad("Иванов", "Иван", "Иванович", "   ");
                });

            Person copy(p);
            Assert::IsTrue(p == copy);

            Person moved(std::move(copy));
            Assert::AreEqual(std::string("Иванов"), moved.GetSurname());
        }
    };

    TEST_CLASS(LawyerAndClientTests)
    {
    public:
        /**
         * @brief Проверка полиморфизма Lawyer и Client через базовый класс Person
         */
        TEST_METHOD(Polymorphism_Test)
        {
            Lawyer law("Иванов", "И.", "И.", "L-1", "Семейные");
            Client cl("Петров", "П.", "П.", "C-1", "+7-900-111");

            Person* p1 = &law;
            Person* p2 = &cl;

            Assert::IsTrue(p1->ToString().find("Семейные") != std::string::npos);
            Assert::IsTrue(p2->ToString().find("+7-900-111") != std::string::npos);
        }
    };

    TEST_CLASS(LegalCaseTests)
    {
    public:
        /**
         * @brief Проверка уникальности номера дела и валидации
         */
        TEST_METHOD(CaseNumberValidation_Test)
        {
            LegalCase::ResetRegistry();
            Lawyer law("Иванов", "И.", "И.", "L-1", "Семейные");
            Client cl("Петров", "П.", "П.", "C-1", "+7");
            Service srv("Развод", "Консультация", "Гражданские", "Семейные", 3000.0);

            Assert::ExpectException<std::invalid_argument>([&]() {
                LegalCase bad(0, "Описание", &law, &cl, &srv);
                });

            LegalCase c1(101, "Описание 1", &law, &cl, &srv);
            Assert::ExpectException<std::invalid_argument>([&]() {
                LegalCase dup(101, "Дубликат", &law, &cl, &srv);
                });
        }
    };

    TEST_CLASS(LawOfficeTests)
    {
    public:
        /**
         * @brief Проверка всех 4 заданий варианта «Контора адвоката»
         */
        TEST_METHOD(AllTasks_Test)
        {
            LegalCase::ResetRegistry();
            LawOffice office("Контора №1", "ул. Мира, 1");

            Service srv("Раздел имущества", "Ведение дела в суде", "Гражданские", "Семейные", 35000.0);
            Lawyer law1("Иванов", "Иван", "Иванович", "L-1", "Семейные");
            Lawyer law2("Смирнова", "Елена", "Сергеевна", "L-2", "Семейные");
            Client cl("Петров", "Петр", "Петрович", "C-1", "+7-916-111");

            office.AddService(&srv);
            office.AddLawyer(&law1);
            office.AddLawyer(&law2);
            office.AddClient(&cl);

            LegalCase* c = office.OpenCase("Раздел квартиры", &law1, &cl, &srv);

            // Задание 1: список услуг и цена
            std::string servicesInfo = office.GetServicesSummary();
            Assert::IsTrue(servicesInfo.find("Раздел имущества") != std::string::npos);
            Assert::IsTrue(servicesInfo.find("35000") != std::string::npos);

            // Задание 2: клиенты по услуге
            std::string clientsInfo = office.GetClientsByServiceInfo("Раздел имущества");
            Assert::IsTrue(clientsInfo.find("Петров Петр Петрович") != std::string::npos);

            // Задание 3: свободные адвокаты по услуге (law1 занят, свободна law2)
            std::string lawyersInfo = office.GetAvailableLawyersByServiceInfo("Раздел имущества");
            Assert::IsTrue(lawyersInfo.find("Смирнова Елена Сергеевна") != std::string::npos);
            Assert::IsTrue(lawyersInfo.find("Иванов Иван Иванович") == std::string::npos);

            // Задание 4: содержание дела по номеру
            std::string caseInfo = office.GetCaseDescriptionInfo(c->GetCaseNumber());
            Assert::IsTrue(caseInfo.find("Раздел квартиры") != std::string::npos);
            Assert::IsTrue(office.GetCaseDescriptionInfo(999).find("не найдено") != std::string::npos);
        }
    };
}