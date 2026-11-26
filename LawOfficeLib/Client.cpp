#include "Client.h"
#include <utility>

Client::Client()
    : Person(), phone("")
{
}

Client::Client(const std::string& surname, const std::string& name,
    const std::string& patronymic, const std::string& id,
    const std::string& phone)
    : Person(surname, name, patronymic, id), phone(phone)
{
}

Client::Client(const Client& other)
    : Person(other), phone(other.phone)
{
}

Client& Client::operator=(const Client& other)
{
    if (this != &other)
    {
        Person::operator=(other);
        phone = other.phone;
    }
    return *this;
}

Client::Client(Client&& other) noexcept
    : Person(std::move(other)), phone(std::move(other.phone))
{
}

Client& Client::operator=(Client&& other) noexcept
{
    if (this != &other)
    {
        Person::operator=(std::move(other));
        phone = std::move(other.phone);
    }
    return *this;
}

const std::string& Client::GetPhone() const { return phone; }
void Client::SetPhone(const std::string& ph) { phone = ph; }

std::string Client::ToString() const
{
    std::string res = "[Клиент] ФИО: " + GetFullName();
    if (!id.empty())
    {
        res += " (ID: " + id + ")";
    }
    res += " | Телефон: " + (phone.empty() ? "не указан" : phone);
    return res;
}

std::string Client::GetSummary() const
{
    std::string res = "Клиент: " + GetFullName();
    res += " | Тел.: " + (phone.empty() ? "--" : phone);
    return res;
}

bool Client::operator==(const Client& other) const
{
    return Person::operator==(other) && phone == other.phone;
}

bool Client::operator!=(const Client& other) const
{
    return !(*this == other);
}