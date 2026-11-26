#include "LegalCase.h"
#include <utility>
#include <stdexcept>

std::set<int> LegalCase::existingCaseNumbers;
std::map<int, int> LegalCase::caseRefCount;

LegalCase::LegalCase()
    : caseNumber(0), description(""), lawyer(nullptr), client(nullptr), service(nullptr)
{
}

LegalCase::LegalCase(const int caseNumber,
    const std::string& description,
    Lawyer* lawyer,
    Client* client,
    Service* service)
    : caseNumber(caseNumber),
    description(description),
    lawyer(lawyer),
    client(client),
    service(service)
{
    if (this->caseNumber <= 0)
    {
        throw std::invalid_argument("Номер дела должен быть больше нуля");
    }
    if (existingCaseNumbers.find(this->caseNumber) != existingCaseNumbers.end())
    {
        throw std::invalid_argument("Дело с номером " + std::to_string(this->caseNumber) + " уже существует");
    }
    existingCaseNumbers.insert(this->caseNumber);
    caseRefCount[this->caseNumber] = 1;
}

LegalCase::~LegalCase()
{
    if (caseNumber > 0)
    {
        auto it = caseRefCount.find(caseNumber);
        if (it != caseRefCount.end() && --it->second <= 0)
        {
            caseRefCount.erase(it);
            existingCaseNumbers.erase(caseNumber);
        }
    }
}

LegalCase::LegalCase(const LegalCase& other)
    : caseNumber(other.caseNumber),
    description(other.description),
    lawyer(other.lawyer),
    client(other.client),
    service(other.service)
{
    if (caseNumber > 0)
    {
        caseRefCount[caseNumber]++;
    }
}

LegalCase& LegalCase::operator=(const LegalCase& other)
{
    if (this != &other)
    {
        if (caseNumber > 0)
        {
            auto it = caseRefCount.find(caseNumber);
            if (it != caseRefCount.end() && --it->second <= 0)
            {
                caseRefCount.erase(it);
                existingCaseNumbers.erase(caseNumber);
            }
        }

        caseNumber = other.caseNumber;
        description = other.description;
        lawyer = other.lawyer;
        client = other.client;
        service = other.service;

        if (caseNumber > 0)
        {
            caseRefCount[caseNumber]++;
        }
    }
    return *this;
}

LegalCase::LegalCase(LegalCase&& other) noexcept
    : caseNumber(other.caseNumber),
    description(std::move(other.description)),
    lawyer(other.lawyer),
    client(other.client),
    service(other.service)
{
    other.caseNumber = 0;
    other.lawyer = nullptr;
    other.client = nullptr;
    other.service = nullptr;
}

LegalCase& LegalCase::operator=(LegalCase&& other) noexcept
{
    if (this != &other)
    {
        if (caseNumber > 0)
        {
            auto it = caseRefCount.find(caseNumber);
            if (it != caseRefCount.end() && --it->second <= 0)
            {
                caseRefCount.erase(it);
                existingCaseNumbers.erase(caseNumber);
            }
        }

        caseNumber = other.caseNumber;
        description = std::move(other.description);
        lawyer = other.lawyer;
        client = other.client;
        service = other.service;

        other.caseNumber = 0;
        other.lawyer = nullptr;
        other.client = nullptr;
        other.service = nullptr;
    }
    return *this;
}

int LegalCase::GetCaseNumber() const { return caseNumber; }

void LegalCase::SetCaseNumber(const int newCaseNumber)
{
    if (newCaseNumber <= 0)
    {
        throw std::invalid_argument("Номер дела должен быть больше нуля");
    }
    if (newCaseNumber != caseNumber && existingCaseNumbers.find(newCaseNumber) != existingCaseNumbers.end())
    {
        throw std::invalid_argument("Дело с номером " + std::to_string(newCaseNumber) + " уже существует");
    }
    if (caseNumber > 0)
    {
        auto it = caseRefCount.find(caseNumber);
        if (it != caseRefCount.end() && --it->second <= 0)
        {
            caseRefCount.erase(it);
            existingCaseNumbers.erase(caseNumber);
        }
    }
    caseNumber = newCaseNumber;
    existingCaseNumbers.insert(caseNumber);
    caseRefCount[caseNumber] = 1;
}

const std::string& LegalCase::GetDescription() const { return description; }
void LegalCase::SetDescription(const std::string& desc) { description = desc; }
Lawyer* LegalCase::GetLawyer() const { return lawyer; }
void LegalCase::SetLawyer(Lawyer* l) { lawyer = l; }
Client* LegalCase::GetClient() const { return client; }
void LegalCase::SetClient(Client* c) { client = c; }
Service* LegalCase::GetService() const { return service; }
void LegalCase::SetService(Service* s) { service = s; }

bool LegalCase::IsCaseNumberExists(const int number)
{
    return existingCaseNumbers.find(number) != existingCaseNumbers.end();
}

void LegalCase::ResetRegistry()
{
    existingCaseNumbers.clear();
    caseRefCount.clear();
}

std::string LegalCase::ToString() const
{
    std::string res = "Дело №" + std::to_string(caseNumber) + ":\n";
    res += "  Содержание: " + description + "\n";
    res += "  Услуга: " + (service ? service->GetName() : "не указана") + "\n";
    res += "  Клиент: " + (client ? client->GetFullName() : "не указан") + "\n";
    res += "  Адвокат: " + (lawyer ? lawyer->GetFullName() + " (" + lawyer->GetSpecialization() + ")" : "не указан");
    return res;
}

std::string LegalCase::GetSummary() const
{
    std::string res = "Дело №" + std::to_string(caseNumber) + " | " + description;
    if (client) res += " | Клиент: " + client->GetFullName();
    if (lawyer) res += " | Адвокат: " + lawyer->GetFullName();
    return res;
}

bool LegalCase::operator==(const LegalCase& other) const
{
    return caseNumber == other.caseNumber &&
        description == other.description &&
        lawyer == other.lawyer &&
        client == other.client &&
        service == other.service;
}

bool LegalCase::operator!=(const LegalCase& other) const
{
    return !(*this == other);
}