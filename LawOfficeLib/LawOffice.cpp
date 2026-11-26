#include "LawOffice.h"
#include <algorithm>
#include <utility>

LawOffice::LawOffice()
    : name(""), address(""), nextCaseNumber(1)
{
}

LawOffice::LawOffice(const std::string& name, const std::string& address)
    : name(name), address(address), nextCaseNumber(1)
{
}

LawOffice::LawOffice(const LawOffice& other)
    : name(other.name),
    address(other.address),
    services(other.services),
    lawyers(other.lawyers),
    clients(other.clients),
    cases(other.cases),
    nextCaseNumber(other.nextCaseNumber)
{
}

LawOffice& LawOffice::operator=(const LawOffice& other)
{
    if (this != &other)
    {
        name = other.name;
        address = other.address;
        services = other.services;
        lawyers = other.lawyers;
        clients = other.clients;
        cases = other.cases;
        nextCaseNumber = other.nextCaseNumber;
    }
    return *this;
}

LawOffice::LawOffice(LawOffice&& other) noexcept
    : name(std::move(other.name)),
    address(std::move(other.address)),
    services(std::move(other.services)),
    lawyers(std::move(other.lawyers)),
    clients(std::move(other.clients)),
    cases(std::move(other.cases)),
    nextCaseNumber(other.nextCaseNumber)
{
    other.nextCaseNumber = 1;
}

LawOffice& LawOffice::operator=(LawOffice&& other) noexcept
{
    if (this != &other)
    {
        name = std::move(other.name);
        address = std::move(other.address);
        services = std::move(other.services);
        lawyers = std::move(other.lawyers);
        clients = std::move(other.clients);
        cases = std::move(other.cases);
        nextCaseNumber = other.nextCaseNumber;
        other.nextCaseNumber = 1;
    }
    return *this;
}

const std::string& LawOffice::GetName() const { return name; }
void LawOffice::SetName(const std::string& n) { name = n; }
const std::string& LawOffice::GetAddress() const { return address; }
void LawOffice::SetAddress(const std::string& addr) { address = addr; }

void LawOffice::AddService(Service* service)
{
    if (service) services.push_back(service);
}

void LawOffice::AddLawyer(Lawyer* lawyer)
{
    if (lawyer) lawyers.push_back(lawyer);
}

void LawOffice::AddClient(Client* client)
{
    if (client) clients.push_back(client);
}

LegalCase* LawOffice::OpenCase(const std::string& description,
    Lawyer* lawyer,
    Client* client,
    Service* service)
{
    while (LegalCase::IsCaseNumberExists(nextCaseNumber))
    {
        nextCaseNumber++;
    }
    const int number = nextCaseNumber++;
    if (lawyer)
    {
        lawyer->SetAvailable(false);
    }
    LegalCase* legalCase = new LegalCase(number, description, lawyer, client, service);
    cases.push_back(legalCase);
    return legalCase;
}

Service* LawOffice::FindServiceByName(const std::string& serviceName) const
{
    for (const auto& s : services)
    {
        if (s && s->GetName() == serviceName) return s;
    }
    return nullptr;
}

LegalCase* LawOffice::FindCaseByNumber(const int caseNumber) const
{
    for (const auto& c : cases)
    {
        if (c && c->GetCaseNumber() == caseNumber) return c;
    }
    return nullptr;
}

std::vector<Client*> LawOffice::FindClientsByService(const std::string& serviceName) const
{
    std::vector<Client*> result;
    for (const auto& c : cases)
    {
        if (c && c->GetService() && c->GetService()->GetName() == serviceName && c->GetClient())
        {
            if (std::find(result.begin(), result.end(), c->GetClient()) == result.end())
            {
                result.push_back(c->GetClient());
            }
        }
    }
    return result;
}

std::vector<Lawyer*> LawOffice::FindAvailableLawyersByService(const std::string& serviceName) const
{
    std::vector<Lawyer*> result;
    const Service* targetService = FindServiceByName(serviceName);
    if (!targetService) return result;

    for (const auto& l : lawyers)
    {
        if (l && l->IsAvailable() && l->GetSpecialization() == targetService->GetSpecialization())
        {
            result.push_back(l);
        }
    }
    return result;
}

std::string LawOffice::GetServicesSummary() const
{
    std::string res = "=== Список предоставляемых услуг и их цена ===\n";
    if (!name.empty()) res += "Контора: " + name + "\n";
    if (!address.empty()) res += "Адрес: " + address + "\n";
    res += "Всего услуг: " + std::to_string(services.size()) + "\n";
    res += "--------------------------------------------------\n";

    if (services.empty())
    {
        res += "Список услуг пуст.\n";
        return res;
    }

    int idx = 1;
    for (const auto& s : services)
    {
        if (s) res += std::to_string(idx++) + ". " + s->ToString() + "\n";
    }
    return res;
}

std::string LawOffice::GetClientsByServiceInfo(const std::string& serviceName) const
{
    std::string res = "=== Клиенты, обращавшиеся за услугой \"" + serviceName + "\" ===\n";
    const auto found = FindClientsByService(serviceName);
    if (found.empty())
    {
        res += "Клиентов по данной услуге не найдено.\n";
        return res;
    }

    int idx = 1;
    for (const auto& c : found)
    {
        res += std::to_string(idx++) + ". " + c->GetSummary() + "\n";
    }
    return res;
}

std::string LawOffice::GetAvailableLawyersByServiceInfo(const std::string& serviceName) const
{
    std::string res = "=== Свободные адвокаты по услуге \"" + serviceName + "\" ===\n";
    const auto found = FindAvailableLawyersByService(serviceName);
    if (found.empty())
    {
        res += "Свободных адвокатов по данной услуге нет.\n";
        return res;
    }

    int idx = 1;
    for (const auto& l : found)
    {
        res += std::to_string(idx++) + ". " + l->GetSummary() + "\n";
    }
    return res;
}

std::string LawOffice::GetCaseDescriptionInfo(const int caseNumber) const
{
    const auto legalCase = FindCaseByNumber(caseNumber);
    if (!legalCase)
    {
        return "Дело №" + std::to_string(caseNumber) + " не найдено.\n";
    }
    return legalCase->ToString() + "\n";
}

size_t LawOffice::GetServiceCount() const { return services.size(); }
size_t LawOffice::GetLawyerCount() const { return lawyers.size(); }
size_t LawOffice::GetClientCount() const { return clients.size(); }
size_t LawOffice::GetCaseCount() const { return cases.size(); }