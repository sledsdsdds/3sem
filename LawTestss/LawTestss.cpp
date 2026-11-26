#include "pch.h"
#include "CppUnitTest.h"

#include <vector>
#include <string>
#include <stdexcept>
#include <utility>
#include <type_traits>

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
         * @brief Проверка, что Person является абстрактным классом, а базовые методы работают через наследников
         */
        TEST_METHOD(AbstractBaseAndGetters_Test)
        {
            Assert::IsTrue(std::is_abstract<Person>::value);

            Client c1;
            Assert::IsTrue(c1.GetSurname().empty());
            Assert::IsFalse(c1.GetId().empty());

            Lawyer law("Иванов", "Иван", "Иванович", "ID-1", "Семейные");
            Person* personPtr = &law;

            Assert::AreEqual(std::string("Иванов"), personPtr->GetSurname());
            Assert::AreEqual(std::string("Иван"), personPtr->GetName());
            Assert::AreEqual(std::string("Иванович"), personPtr->GetPatronymic());
            Assert::AreEqual(std::string("ID-1"), personPtr->GetId());
            Assert::AreEqual(std::string("Иванов Иван Иванович"), personPtr->GetFullName());

            personPtr->SetSurname("Петров");
            personPtr->SetName("Петр");
            personPtr->SetId("NEW-ID");
            Assert::AreEqual(std::string("Петров"), personPtr->GetSurname());
            Assert::AreEqual(std::string("Петр"), personPtr->GetName());
            Assert::AreEqual(std::string("NEW-ID"), personPtr->GetId());
        }

        /**
         * @brief Проверка валидации ID (id не может быть пустым)
         */
        TEST_METHOD(IdValidation_Test)
        {
            Assert::ExpectException<std::invalid_argument>([]() {
                Client c("Иванов", "Иван", "Иванович", "", "+7-900-111");
                });

            Assert::ExpectException<std::invalid_argument>([]() {
                Lawyer l("Иванов", "Иван", "Иванович", "   ", "Семейные");
                });

            Client c;
            Person* personPtr = &c;
            Assert::ExpectException<std::invalid_argument>([&]() {
                personPtr->SetId("");
                });
        }
    };

    TEST_CLASS(LawyerTests)
    {
    public:
        /**
         * @brief Проверка создания адвоката, наследования и полиморфизма
         */
        TEST_METHOD(LawyerAndPolymorphism_Test)
        {
            Lawyer law("Иванов", "Иван", "Иванович", "LAW-1", "Семейные");

            Assert::AreEqual(std::string("Семейные"), law.GetSpecialization());
            Assert::IsTrue(law.IsAvailable());

            law.SetAvailable(false);
            Assert::IsFalse(law.IsAvailable());

            Person* person = &law;
            Assert::IsTrue(person->ToString().find("Семейные") != std::string::npos);
            Assert::IsTrue(law.GetSummary().find("Иванов") != std::string::npos);
        }

        /**
         * @brief Проверка правила пяти для Lawyer
         */
        TEST_METHOD(RuleOfFive_Test)
        {
            Lawyer l1("Иванов", "И.", "И.", "L-1", "Жилищные", true);
            Lawyer copy(l1);
            Assert::IsTrue(l1 == copy);

            Lawyer assigned;
            assigned = l1;
            Assert::IsTrue(l1 == assigned);

            Lawyer moved(std::move(copy));
            Assert::AreEqual(std::string("Жилищные"), moved.GetSpecialization());

            Lawyer moveAssigned;
            moveAssigned = std::move(assigned);
            Assert::AreEqual(std::string("Жилищные"), moveAssigned.GetSpecialization());
        }
    };

    TEST_CLASS(ClientTests)
    {
    public:
        /**
         * @brief Проверка создания клиента, наследования и полиморфизма
         */
        TEST_METHOD(ClientAndPolymorphism_Test)
        {
            Client cl("Петров", "Петр", "Петрович", "CL-1", "+7-916-111-22-33");

            Assert::AreEqual(std::string("+7-916-111-22-33"), cl.GetPhone());

            Person* person = &cl;
            Assert::IsTrue(person->ToString().find("+7-916-111-22-33") != std::string::npos);
            Assert::IsTrue(cl.GetSummary().find("Петров") != std::string::npos);
        }

        /**
         * @brief Проверка правила пяти для Client
         */
        TEST_METHOD(RuleOfFive_Test)
        {
            Client c1("Петров", "П.", "П.", "C-1", "+7-900-000");
            Client copy(c1);
            Assert::IsTrue(c1 == copy);

            Client assigned;
            assigned = c1;
            Assert::IsTrue(c1 == assigned);

            Client moved(std::move(copy));
            Assert::AreEqual(std::string("+7-900-000"), moved.GetPhone());

            Client moveAssigned;
            moveAssigned = std::move(assigned);
            Assert::AreEqual(std::string("+7-900-000"), moveAssigned.GetPhone());
        }
    };

    TEST_CLASS(ServiceTests)
    {
    public:
        /**
         * @brief Проверка конструкторов, валидации цены и правила пяти Service
         */
        TEST_METHOD(ServiceValidationAndRuleOfFive_Test)
        {
            Service s1("Консультация", "Консультация", "Гражданские", "Семейные", 3000.0);
            Assert::AreEqual(std::string("Консультация"), s1.GetName());
            Assert::AreEqual(3000.0, s1.GetPrice());
            Assert::IsTrue(s1.ToString().find("3000") != std::string::npos);

            Assert::ExpectException<std::invalid_argument>([]() {
                Service bad("Услуга", "Консультация", "Гражданские", "Семейные", -500.0);
                });

            Assert::ExpectException<std::invalid_argument>([&]() {
                s1.SetPrice(-10.0);
                });

            Service copy(s1);
            Assert::IsTrue(s1 == copy);

            Service moved(std::move(copy));
            Assert::AreEqual(std::string("Семейные"), moved.GetSpecialization());
        }
    };

    TEST_CLASS(LegalCaseTests)
    {
    public:
        /**
         * @brief Проверка создания дела и валидации уникальности номера
         */
        TEST_METHOD(CaseValidationAndUniqueness_Test)
        {
            LegalCase::ResetRegistry();
            Lawyer law("Иванов", "И.", "И.", "L-1", "Семейные");
            Client cl("Петров", "П.", "П.", "C-1", "+7-999-111");
            Service srv("Развод", "Консультация", "Гражданские", "Семейные", 3000.0);

            Assert::ExpectException<std::invalid_argument>([&]() {
                LegalCase badZero(0, "Описание", &law, &cl, &srv);
                });

            Assert::ExpectException<std::invalid_argument>([&]() {
                LegalCase badNegative(-3, "Описание", &law, &cl, &srv);
                });

            LegalCase c1(101, "Расторжение брака", &law, &cl, &srv);
            Assert::AreEqual(101, c1.GetCaseNumber());
            Assert::AreEqual(std::string("Расторжение брака"), c1.GetDescription());
            Assert::IsTrue(c1.GetLawyer() == &law);
            Assert::IsTrue(c1.GetClient() == &cl);
            Assert::IsTrue(c1.GetService() == &srv);

            Assert::ExpectException<std::invalid_argument>([&]() {
                LegalCase duplicate(101, "Дубликат номера", &law, &cl, &srv);
                });
        }

        /**
         * @brief Проверка правила пяти для LegalCase
         */
        TEST_METHOD(RuleOfFive_Test)
        {
            LegalCase::ResetRegistry();
            Lawyer law("Иванов", "И.", "И.", "L-1", "Семейные");
            Client cl("Петров", "П.", "П.", "C-1", "+7");
            Service srv("Развод", "Консультация", "Гражданские", "Семейные", 3000.0);

            LegalCase c1(201, "Раздел имущества", &law, &cl, &srv);
            LegalCase copy(c1);
            Assert::IsTrue(c1 == copy);

            LegalCase assigned;
            assigned = c1;
            Assert::IsTrue(c1 == assigned);

            LegalCase moved(std::move(copy));
            Assert::AreEqual(201, moved.GetCaseNumber());

            LegalCase moveAssigned;
            moveAssigned = std::move(assigned);
            Assert::AreEqual(201, moveAssigned.GetCaseNumber());
        }
    };

    TEST_CLASS(LawOfficeTests)
    {
    public:
        /**
         * @brief Проверка добавления и поиска сущностей в конторе
         */
        TEST_METHOD(AddAndFind_Test)
        {
            LawOffice office("Контора «Право и Закон»", "ул. Тверская, 10");
            Assert::AreEqual(std::string("Контора «Право и Закон»"), office.GetName());

            Service srv("Жилищный спор", "Консультация", "Гражданские", "Жилищные", 2500.0);
            Lawyer law("Иванов", "И.", "И.", "L1", "Жилищные");
            Client cl("Петров", "П.", "П.", "C1", "+7-900-111");

            office.AddService(&srv);
            office.AddLawyer(&law);
            office.AddClient(&cl);

            Assert::AreEqual(static_cast<size_t>(1), office.GetServiceCount());
            Assert::AreEqual(static_cast<size_t>(1), office.GetLawyerCount());
            Assert::AreEqual(static_cast<size_t>(1), office.GetClientCount());
            Assert::IsTrue(office.FindServiceByName("Жилищный спор") == &srv);
        }

        /**
         * @brief Проверка Задания 1: список предоставляемых услуг и их цена
         */
        TEST_METHOD(Task1_ServicesSummary_Test)
        {
            LawOffice office("Контора № 1", "ул. Мира, 5");
            Assert::IsTrue(office.GetServicesSummary().find("Список услуг пуст") != std::string::npos);

            Service srv("Раздел имущества в суде", "Ведение дела в суде", "Гражданские", "Семейные", 35000.0);
            office.AddService(&srv);

            std::string summary = office.GetServicesSummary();
            Assert::IsTrue(summary.find("Всего услуг: 1") != std::string::npos);
            Assert::IsTrue(summary.find("Раздел имущества в суде") != std::string::npos);
            Assert::IsTrue(summary.find("35000") != std::string::npos);
        }

        /**
         * @brief Проверка Задания 2: список клиентов, обращавшихся за данной услугой
         */
        TEST_METHOD(Task2_ClientsByService_Test)
        {
            LegalCase::ResetRegistry();
            LawOffice office;
            Service srv("Раздел имущества в суде", "Ведение дела в суде", "Гражданские", "Семейные", 35000.0);
            Lawyer law("Иванов", "Иван", "Иванович", "L1", "Семейные");
            Client cl("Петров", "Петр", "Петрович", "C1", "+7-916-111");

            office.AddService(&srv);
            office.AddLawyer(&law);
            office.AddClient(&cl);
            office.OpenCase("Раздел квартиры", &law, &cl, &srv);

            std::string info = office.GetClientsByServiceInfo("Раздел имущества в суде");
            Assert::IsTrue(info.find("Петров Петр Петрович") != std::string::npos);
            Assert::IsTrue(office.GetClientsByServiceInfo("Несуществующая услуга").find("не найдено") != std::string::npos);
        }

        /**
         * @brief Проверка Задания 3: список свободных адвокатов по выбранной услуге
         */
        TEST_METHOD(Task3_AvailableLawyersByService_Test)
        {
            LegalCase::ResetRegistry();
            LawOffice office;
            Service srv("Раздел имущества в суде", "Ведение дела в суде", "Гражданские", "Семейные", 35000.0);
            Lawyer law1("Иванов", "Иван", "Иванович", "L1", "Семейные");
            Lawyer law2("Смирнова", "Елена", "Сергеевна", "L2", "Семейные");
            Client cl("Петров", "Петр", "Петрович", "C1", "+7-916-111");

            office.AddService(&srv);
            office.AddLawyer(&law1);
            office.AddLawyer(&law2);
            office.AddClient(&cl);

            office.OpenCase("Раздел квартиры", &law1, &cl, &srv);

            std::string lawyersInfo = office.GetAvailableLawyersByServiceInfo("Раздел имущества в суде");
            Assert::IsTrue(lawyersInfo.find("Смирнова Елена Сергеевна") != std::string::npos);
            Assert::IsTrue(lawyersInfo.find("Иванов Иван Иванович") == std::string::npos);
        }

        /**
         * @brief Проверка Задания 4: содержание Дела по его номеру
         */
        TEST_METHOD(Task4_CaseDescription_Test)
        {
            LegalCase::ResetRegistry();
            LawOffice office;
            Service srv("Защита в суде", "Ведение дела в суде", "Уголовные", "Убийства", 120000.0);
            Lawyer law("Кузнецов", "Павел", "Алексеевич", "L3", "Убийства");
            Client cl("Сидорова", "Анна", "Владимировна", "C2", "+7-926-444");

            office.AddService(&srv);
            office.AddLawyer(&law);
            office.AddClient(&cl);

            LegalCase* createdCase = office.OpenCase("Защита обвиняемого в суде первой инстанции", &law, &cl, &srv);
            Assert::IsTrue(createdCase->GetCaseNumber() > 0);
            Assert::IsTrue(office.FindCaseByNumber(createdCase->GetCaseNumber()) == createdCase);

            std::string caseInfo = office.GetCaseDescriptionInfo(createdCase->GetCaseNumber());
            Assert::IsTrue(caseInfo.find("Защита обвиняемого в суде первой инстанции") != std::string::npos);
            Assert::IsTrue(caseInfo.find("Кузнецов Павел Алексеевич") != std::string::npos);

            Assert::IsTrue(office.GetCaseDescriptionInfo(9999).find("не найдено") != std::string::npos);
        }
    };
}