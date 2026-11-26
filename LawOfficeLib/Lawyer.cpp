#include "Lawyer.h"
#include <utility>

Lawyer::Lawyer()
    : Person(), specialization(""), isAvailable(true)
{
}

Lawyer::Lawyer(const std::string& surname, const std::string& name,
    const std::string& patronymic, const std::string& id,
    const std::string& specialization, const bool isAvailable)
    : Person(surname, name, patronymic, id),
    specialization(specialization),
    isAvailable(isAvailable)
{
}

Lawyer::Lawyer(const Lawyer& other)
    : Person(other),
    specialization(other.specialization),
    isAvailable(other.isAvailable)
{
}

Lawyer& Lawyer::operator=(const Lawyer& other)
{
    if (this != &other)
    {
        Person::operator=(other);
        specialization = other.specialization;
        isAvailable = other.isAvailable;
    }
    return *this;
}

Lawyer::Lawyer(Lawyer&& other) noexcept
    : Person(std::move(other)),
    specialization(std::move(other.specialization)),
    isAvailable(other.isAvailable)
{
    other.isAvailable = true;
}

Lawyer& Lawyer::operator=(Lawyer&& other) noexcept
{
    if (this != &other)
    {
        Person::operator=(std::move(other));
        specialization = std::move(other.specialization);
        isAvailable = other.isAvailable;
        other.isAvailable = true;
    }
    return *this;
}

const std::string& Lawyer::GetSpecialization() const { return specialization; }
void Lawyer::SetSpecialization(const std::string& spec) { specialization = spec; }
bool Lawyer::IsAvailable() const { return isAvailable; }
void Lawyer::SetAvailable(const bool available) { isAvailable = available; }

std::string Lawyer::ToString() const
{
    std::string res = "[Адвокат] ФИО: " + GetFullName();
    if (!id.empty())
    {
        res += " (ID: " + id + ")";
    }
    res += " | Специализация: " + specialization;
    res += " | Статус: " + std::string(isAvailable ? "свободен" : "занят");
    return res;
}

std::string Lawyer::GetSummary() const
{
    std::string res = "Адвокат: " + GetFullName();
    res += " | Специализация: " + specialization;
    res += " | Статус: " + std::string(isAvailable ? "свободен" : "занят");
    return res;
}

bool Lawyer::operator==(const Lawyer& other) const
{
    return Person::operator==(other) &&
        specialization == other.specialization &&
        isAvailable == other.isAvailable;
}

bool Lawyer::operator!=(const Lawyer& other) const
{
    return !(*this == other);
}