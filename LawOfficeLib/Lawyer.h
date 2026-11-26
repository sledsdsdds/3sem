#pragma once

#include "Person.h"

/**
 * @brief Класс для представления адвоката конторы
 */
class Lawyer : public Person
{
private:
    std::string specialization;
    bool isAvailable;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Lawyer();

    /**
     * @brief Конструктор с параметрами
     * @param surname Фамилия
     * @param name Имя
     * @param patronymic Отчество
     * @param id Идентификатор адвоката
     * @param specialization Специализация (жилищные, семейные, убийства и т.д.)
     * @param isAvailable Статус доступности (true — свободен, false — занят)
     */
    Lawyer(const std::string& surname, const std::string& name,
        const std::string& patronymic, const std::string& id,
        const std::string& specialization, const bool isAvailable = true);

    /**
     * @brief Виртуальный деструктор по умолчанию
     */
    virtual ~Lawyer() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Lawyer(const Lawyer& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Lawyer& operator=(const Lawyer& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Lawyer(Lawyer&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Lawyer& operator=(Lawyer&& other) noexcept;

    /**
     * @brief Получить специализацию адвоката
     * @return Константная ссылка на строку специализации
     */
    const std::string& GetSpecialization() const;

    /**
     * @brief Установить специализацию адвоката
     * @param specialization Новая специализация
     */
    void SetSpecialization(const std::string& specialization);

    /**
     * @brief Проверить, свободен ли адвокат
     * @return true, если адвокат свободен, иначе false
     */
    bool IsAvailable() const;

    /**
     * @brief Установить статус доступности адвоката
     * @param available Новый статус доступности
     */
    void SetAvailable(const bool available);

    /**
     * @brief Полная строковая информация об адвокате
     * @return Строка с подробной информацией
     */
    std::string ToString() const override;

    /**
     * @brief Сводная информация об адвокате
     * @return Строка со сводкой для отчетов
     */
    std::string GetSummary() const override;

    /**
     * @brief Оператор проверки равенства адвокатов
     * @param other Адвокат для сравнения
     * @return true, если адвокаты равны, иначе false
     */
    bool operator==(const Lawyer& other) const;

    /**
     * @brief Оператор проверки неравенства адвокатов
     * @param other Адвокат для сравнения
     * @return true, если адвокаты не равны, иначе false
     */
    bool operator!=(const Lawyer& other) const;
};