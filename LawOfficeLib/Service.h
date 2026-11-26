#pragma once

#include <string>

/**
 * @brief Класс для представления юридической услуги
 */
class Service
{
private:
    std::string name;
    std::string serviceType;
    std::string caseCategory;
    std::string specialization;
    double price;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Service();

    /**
     * @brief Конструктор с параметрами
     * @param name Название услуги
     * @param serviceType Вид услуги ("Консультация", "Ведение дела в суде")
     * @param caseCategory Категория дела ("Гражданские", "Уголовные")
     * @param specialization Требуемая специализация адвоката
     * @param price Стоимость услуги в рублях
     */
    Service(const std::string& name, const std::string& serviceType,
        const std::string& caseCategory, const std::string& specialization,
        const double price);

    /**
     * @brief Деструктор по умолчанию
     */
    ~Service() = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Service(const Service& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Service& operator=(const Service& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Service(Service&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Service& operator=(Service&& other) noexcept;

    const std::string& GetName() const;
    void SetName(const std::string& name);

    const std::string& GetServiceType() const;
    void SetServiceType(const std::string& serviceType);

    const std::string& GetCaseCategory() const;
    void SetCaseCategory(const std::string& caseCategory);

    const std::string& GetSpecialization() const;
    void SetSpecialization(const std::string& specialization);

    double GetPrice() const;
    void SetPrice(const double price);

    /**
     * @brief Строковое представление услуги
     * @return Строка с подробным описанием услуги и цены
     */
    std::string ToString() const;

    /**
     * @brief Оператор проверки равенства услуг
     * @param other Услуга для сравнения
     * @return true, если услуги равны, иначе false
     */
    bool operator==(const Service& other) const;

    /**
     * @brief Оператор проверки неравенства услуг
     * @param other Услуга для сравнения
     * @return true, если услуги не равны, иначе false
     */
    bool operator!=(const Service& other) const;
};