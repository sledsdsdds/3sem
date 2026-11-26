#pragma once

#include <string>

/**
 * @brief Абстрактный базовый класс для представления человека
 */
class Person
{
protected:
    static size_t nextId;       ///< Счётчик для автоматической генерации идентификаторов
    std::string surname;        ///< Фамилия
    std::string name;           ///< Имя
    std::string patronymic;     ///< Отчество
    std::string id;             ///< Уникальный идентификатор (ключ)

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

    /**
     * @brief Получить фамилию
     * @return Константная ссылка на фамилию
     */
    const std::string& GetSurname() const;

    /**
     * @brief Установить фамилию
     * @param surname Новая фамилия
     */
    void SetSurname(const std::string& surname);

    /**
     * @brief Получить имя
     * @return Константная ссылка на имя
     */
    const std::string& GetName() const;

    /**
     * @brief Установить имя
     * @param name Новое имя
     */
    void SetName(const std::string& name);

    /**
     * @brief Получить отчество
     * @return Константная ссылка на отчество
     */
    const std::string& GetPatronymic() const;

    /**
     * @brief Установить отчество
     * @param patronymic Новое отчество
     */
    void SetPatronymic(const std::string& patronymic);

    /**
     * @brief Получить идентификатор
     * @return Константная ссылка на идентификатор
     */
    const std::string& GetId() const;

    /**
     * @brief Установить идентификатор
     * @param id Новый идентификатор (не может быть пустым)
     */
    void SetId(const std::string& id);

    /**
     * @brief Получить полное ФИО
     * @return Строка формата "Фамилия Имя Отчество"
     */
    std::string GetFullName() const;

    /**
     * @brief Получить текущее значение счётчика идентификаторов
     * @return Значение счётчика nextId
     */
    static size_t GetNextId();

    /**
     * @brief Сбросить счётчик автоматической генерации идентификаторов
     * @param start Начальное значение счётчика (по умолчанию 0)
     */
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

    /**
     * @brief Оператор проверки на равенство
     * @param other Сравниваемый объект
     * @return true, если все поля объектов совпадают, иначе false
     */
    bool operator==(const Person& other) const;

    /**
     * @brief Оператор проверки на неравенство
     * @param other Сравниваемый объект
     * @return true, если объекты различаются, иначе false
     */
    bool operator!=(const Person& other) const;
};