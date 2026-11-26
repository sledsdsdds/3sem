#pragma once

#include "Person.h"

/**
 * @brief Класс для представления клиента адвокатской конторы
 */
class Client : public Person
{
private:
    std::string phone;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Client();

    /**
     * @brief Конструктор с параметрами
     * @param surname Фамилия
     * @param name Имя
     * @param patronymic Отчество
     * @param id Идентификатор клиента
     * @param phone Контактный телефон
     */
    Client(const std::string& surname, const std::string& name,
        const std::string& patronymic, const std::string& id,
        const std::string& phone);

    /**
     * @brief Виртуальный деструктор по умолчанию
     */
    virtual ~Client() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Client(const Client& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Client& operator=(const Client& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Client(Client&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Client& operator=(Client&& other) noexcept;

    /**
     * @brief Получить номер телефона клиента
     * @return Константная ссылка на номер телефона
     */
    const std::string& GetPhone() const;

    /**
     * @brief Установить номер телефона клиента
     * @param phone Новый номер телефона
     */
    void SetPhone(const std::string& phone);

    /**
     * @brief Полная строковая информация о клиенте
     * @return Строка с подробной информацией
     */
    std::string ToString() const override;

    /**
     * @brief Сводная информация о клиенте
     * @return Строка со сводкой для отчетов
     */
    std::string GetSummary() const override;

    /**
     * @brief Оператор проверки равенства клиентов
     * @param other Клиент для сравнения
     * @return true, если клиенты равны, иначе false
     */
    bool operator==(const Client& other) const;

    /**
     * @brief Оператор проверки неравенства клиентов
     * @param other Клиент для сравнения
     * @return true, если клиенты не равны, иначе false
     */
    bool operator!=(const Client& other) const;
};