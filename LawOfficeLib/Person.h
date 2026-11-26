#pragma once

#include <string>

/**
 * @brief Абстрактный базовый класс для представления человека
 */
class Person
{
protected:
    static size_t nextId;
    std::string surname;
    std::string name;
    std::string patronymic;
    std::string id;

public:
    /**
     * @brief Конструктор по умолчанию с автоматической генерацией ключа
     */
    Person();

    /**
     * @brief Конструктор с параметрами
     * @param surname Фамилия
     * @param name Имя
     * @param patronymic Отчество
     * @param id Идентификатор (ключ)
     */
    Person(const std::string& surname, const std::string& name,
        const std::string& patronymic, const std::string& id);

    /**
     * @brief Виртуальный деструктор по умолчанию
     */
    virtual ~Person() = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Person(const Person& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Person& operator=(const Person& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Person(Person&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Person& operator=(Person&& other) noexcept;

    const std::string& GetSurname() const;
    void SetSurname(const std::string& surname);

    const std::string& GetName() const;
    void SetName(const std::string& name);

    const std::string& GetPatronymic() const;
    void SetPatronymic(const std::string& patronymic);

    const std::string& GetId() const;
    void SetId(const std::string& id);

    /**
     * @brief Получить полное ФИО
     * @return Строка формата "Фамилия Имя Отчество"
     */
    std::string GetFullName() const;

    static size_t GetNextId();
    static void ResetNextId(const size_t start = 0);

    /**
     * @brief Чисто виртуальный метод строкового представления объекта
     * @return Строка с информацией о человеке
     */
    virtual std::string ToString() const = 0;

    /**
     * @brief Чисто виртуальный метод получения сводной информации
     * @return Строка со сводкой
     */
    virtual std::string GetSummary() const = 0;

    bool operator==(const Person& other) const;
    bool operator!=(const Person& other) const;
};