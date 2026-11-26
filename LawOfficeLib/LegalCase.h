#pragma once

#include <string>
#include <set>
#include <map>
#include "Lawyer.h"
#include "Client.h"
#include "Service.h"

/**
 * @brief Класс для представления Дела в адвокатской конторе
 */
class LegalCase
{
private:
    static std::set<int> existingCaseNumbers;
    static std::map<int, int> caseRefCount;
    int caseNumber;
    std::string description;
    Lawyer* lawyer;
    Client* client;
    Service* service;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    LegalCase();

    /**
     * @brief Конструктор с параметрами и проверкой уникальности номера дела
     * @param caseNumber Номер дела (должен быть больше нуля)
     * @param description Содержание дела
     * @param lawyer Указатель на адвоката
     * @param client Указатель на клиента
     * @param service Указатель на оказываемую услугу
     */
    LegalCase(const int caseNumber,
        const std::string& description,
        Lawyer* lawyer,
        Client* client,
        Service* service);

    /**
     * @brief Деструктор с освобождением номера дела из реестра
     */
    ~LegalCase();

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    LegalCase(const LegalCase& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    LegalCase& operator=(const LegalCase& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    LegalCase(LegalCase&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    LegalCase& operator=(LegalCase&& other) noexcept;

    int GetCaseNumber() const;
    void SetCaseNumber(const int newCaseNumber);

    const std::string& GetDescription() const;
    void SetDescription(const std::string& description);

    Lawyer* GetLawyer() const;
    void SetLawyer(Lawyer* lawyer);

    Client* GetClient() const;
    void SetClient(Client* client);

    Service* GetService() const;
    void SetService(Service* service);

    /**
     * @brief Проверить, существует ли дело с указанным номером
     * @param number Номер дела для проверки
     * @return true, если номер уже занят, иначе false
     */
    static bool IsCaseNumberExists(const int number);

    /**
     * @brief Очистить статический реестр занятых номеров дел
     */
    static void ResetRegistry();

    /**
     * @brief Полная строковая информация о деле
     * @return Строка с описанием дела
     */
    std::string ToString() const;

    /**
     * @brief Сводная информация о деле
     * @return Краткая строка с описанием дела
     */
    std::string GetSummary() const;

    bool operator==(const LegalCase& other) const;
    bool operator!=(const LegalCase& other) const;
};