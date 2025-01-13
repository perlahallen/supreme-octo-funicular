#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>

class Candidate {
public:
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    std::string eventName;
    double eventScore;

    Candidate() = default;

    Candidate(std::string firstName, std::string lastName, std::string dateOfBirth, std::string eventName, double eventScore)
        : firstName(std::move(firstName)), lastName(std::move(lastName)), dateOfBirth(std::move(dateOfBirth)), eventName(std::move(eventName)), eventScore(eventScore) {}

    friend std::ostream& operator<<(std::ostream& os, const Candidate& candidate) {
        os << candidate.firstName << " " << candidate.lastName
           << " | Event: " << candidate.eventName
           << " | Score: " << candidate.eventScore;
        return os;
    }
};

class MarathonRegistration {
private:
    std::vector<Candidate> candidates;
    bool isRegistrationOpen;

public:
    MarathonRegistration() : isRegistrationOpen(true) {}

    void registerCandidate(std::string firstName, std::string lastName, std::string dateOfBirth, std::string eventName, double eventParameter) {
        if (!isRegistrationOpen) {
            throw std::runtime_error("Registration is closed. No more candidates can be registered.");
        }

        double eventScore;
        if (eventName == "Sprint") {
            eventScore = eventParameter <= 10 ? 9.0 : 12.0;
        } else if (eventName == "Cross") {
            eventScore = eventParameter <= 30 ? 9.0 : 12.0;
        } else if (eventName == "Semi-marathon" || eventName == "Marathon") {
            eventScore = eventParameter > 50 ? 9.0 : 12.0;
        } else {
            throw std::invalid_argument("Invalid event type provided.");
        }

        candidates.emplace_back(std::move(firstName), std::move(lastName), std::move(dateOfBirth), std::move(eventName), eventScore);
    }

    void closeRegistration() {
        isRegistrationOpen = false;
    }

    std::vector<Candidate> getAcceptedCandidates() {
        if (isRegistrationOpen) {
            throw std::runtime_error("Registration is still open. Close it to finalize the candidate list.");
        }

        std::ranges::sort(candidates, [](const Candidate& a, const Candidate& b) {
            return a.eventScore > b.eventScore;
        });

        if (candidates.size() > 500) {
            candidates.resize(500);
        }

        return candidates;
    }
};

int main() {
    try {
        MarathonRegistration marathonRegistration;

        marathonRegistration.registerCandidate("Muhammet", "Atamuradov", "1990-03-15", "Sprint", 9);
        marathonRegistration.registerCandidate("Guller", "Tashliyeva", "1992-08-22", "Cross", 25);
        marathonRegistration.registerCandidate("Kenan", "Akgayev", "1988-11-05", "Marathon", 60);
        marathonRegistration.registerCandidate("Ahat", "Berdiyev", "1995-06-18", "Semi-marathon", 55);

        marathonRegistration.closeRegistration();

        std::vector<Candidate> acceptedCandidates = marathonRegistration.getAcceptedCandidates();
        std::cout << "Accepted Candidates:\n";
        for (const auto& candidate : acceptedCandidates) {
            std::cout << candidate << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}