#pragma once

#include <string>
#include <vector>
#include "Lawyer.h"
#include "Client.h"
#include "Service.h"
#include "LegalCase.h"

/**
 * @brief Класс для управления адвокатской конторой
 */
class LawOffice
{
private:
    std::string name;
    std::string address;
    std::vector<Service*> services;
    std::vector<Lawyer*> lawyers;
    std::vector<Client*> clients;
    std::vector<LegalCase*> cases;
    int nextCaseNumber;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    LawOffice();

    /**
     * @brief Конструктор с параметрами
     * @param name Название конторы
     * @param address Адрес конторы
     */
    LawOffice(const std::string& name, const std::string& address);

    /**
     * @brief Деструктор по умолчанию
     */
    ~LawOffice() = default;

    LawOffice(const LawOffice& other);
    LawOffice& operator=(const LawOffice& other);
    LawOffice(LawOffice&& other) noexcept;
    LawOffice& operator=(LawOffice&& other) noexcept;

    const std::string& GetName() const;
    void SetName(const std::string& name);

    const std::string& GetAddress() const;
    void SetAddress(const std::string& address);

    void AddService(Service* service);
    void AddLawyer(Lawyer* lawyer);
    void AddClient(Client* client);

    /**
     * @brief Завести новое дело в конторе
     * @param description Содержание дела
     * @param lawyer Адвокат (отмечается как занятый)
     * @param client Клиент
     * @param service Оказываемая услуга
     * @return Указатель на созданное дело
     */
    LegalCase* OpenCase(const std::string& description,
        Lawyer* lawyer,
        Client* client,
        Service* service);

    Service* FindServiceByName(const std::string& serviceName) const;
    LegalCase* FindCaseByNumber(const int caseNumber) const;
    std::vector<Client*> FindClientsByService(const std::string& serviceName) const;
    std::vector<Lawyer*> FindAvailableLawyersByService(const std::string& serviceName) const;

    /**
     * @brief Задание 1: Получить список предоставляемых услуг и их цену
     * @return Отформатированная строка со списком услуг
     */
    std::string GetServicesSummary() const;

    /**
     * @brief Задание 2: Получить список клиентов, обращавшихся за данной услугой
     * @param serviceName Название услуги
     * @return Отформатированная строка со списком клиентов
     */
    std::string GetClientsByServiceInfo(const std::string& serviceName) const;

    /**
     * @brief Задание 3: Получить список свободных адвокатов по выбранной услуге
     * @param serviceName Название услуги
     * @return Отформатированная строка со списком свободных адвокатов
     */
    std::string GetAvailableLawyersByServiceInfo(const std::string& serviceName) const;

    /**
     * @brief Задание 4: Получить содержание дела по его номеру
     * @param caseNumber Номер дела
     * @return Строка с описанием дела или сообщением, что дело не найдено
     */
    std::string GetCaseDescriptionInfo(const int caseNumber) const;

    size_t GetServiceCount() const;
    size_t GetLawyerCount() const;
    size_t GetClientCount() const;
    size_t GetCaseCount() const;
};