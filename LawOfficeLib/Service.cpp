#include "Service.h"
#include <stdexcept>
#include <utility>

Service::Service()
    : name(""), serviceType(""), caseCategory(""), specialization(""), price(0.0)
{
}

Service::Service(const std::string& name, const std::string& serviceType,
    const std::string& caseCategory, const std::string& specialization,
    const double price)
    : name(name),
    serviceType(serviceType),
    caseCategory(caseCategory),
    specialization(specialization),
    price(price)
{
    if (price < 0.0)
    {
        throw std::invalid_argument("Цена услуги не может быть отрицательной");
    }
}

Service::Service(const Service& other)
    : name(other.name),
    serviceType(other.serviceType),
    caseCategory(other.caseCategory),
    specialization(other.specialization),
    price(other.price)
{
}

Service& Service::operator=(const Service& other)
{
    if (this != &other)
    {
        name = other.name;
        serviceType = other.serviceType;
        caseCategory = other.caseCategory;
        specialization = other.specialization;
        price = other.price;
    }
    return *this;
}

Service::Service(Service&& other) noexcept
    : name(std::move(other.name)),
    serviceType(std::move(other.serviceType)),
    caseCategory(std::move(other.caseCategory)),
    specialization(std::move(other.specialization)),
    price(other.price)
{
    other.price = 0.0;
}

Service& Service::operator=(Service&& other) noexcept
{
    if (this != &other)
    {
        name = std::move(other.name);
        serviceType = std::move(other.serviceType);
        caseCategory = std::move(other.caseCategory);
        specialization = std::move(other.specialization);
        price = other.price;
        other.price = 0.0;
    }
    return *this;
}

const std::string& Service::GetName() const { return name; }
void Service::SetName(const std::string& n) { name = n; }
const std::string& Service::GetServiceType() const { return serviceType; }
void Service::SetServiceType(const std::string& type) { serviceType = type; }
const std::string& Service::GetCaseCategory() const { return caseCategory; }
void Service::SetCaseCategory(const std::string& category) { caseCategory = category; }
const std::string& Service::GetSpecialization() const { return specialization; }
void Service::SetSpecialization(const std::string& spec) { specialization = spec; }
double Service::GetPrice() const { return price; }

void Service::SetPrice(const double newPrice)
{
    if (newPrice < 0.0)
    {
        throw std::invalid_argument("Цена услуги не может быть отрицательной");
    }
    price = newPrice;
}

std::string Service::ToString() const
{
    return "[" + serviceType + "] " + name +
        " | Категория: " + caseCategory +
        " | Специализация: " + specialization +
        " | Цена: " + std::to_string(static_cast<int>(price)) + " руб.";
}

bool Service::operator==(const Service& other) const
{
    return name == other.name &&
        serviceType == other.serviceType &&
        caseCategory == other.caseCategory &&
        specialization == other.specialization &&
        price == other.price;
}

bool Service::operator!=(const Service& other) const
{
    return !(*this == other);
}