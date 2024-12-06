#include <iostream>
#include <string>
#include <ctime>

class Ticket {
protected:
    double price;
    std::string eventDate;

public:
    Ticket(double p, const std::string& date) : price(p), eventDate(date) {}

    virtual bool validate() const {
        time_t now = time(0);
        tm* localTime = localtime(&now);

        char currentDate[11];
        strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", localTime);

        return eventDate >= currentDate;
    }

    virtual void display() const {
        std::cout << "Price: $" << price << ", Event Date: " << eventDate;
        if (validate()) {
            std::cout << " (Valid)\n";
        } else {
            std::cout << " (Expired)\n";
        }
    }
};

class ConcertTicket : public Ticket {
private:
    std::string seatNumber;

public:
    ConcertTicket(double p, const std::string& date, const std::string& seat)
        : Ticket(p, date), seatNumber(seat) {}

    void reserveSeat() const {
        std::cout << "Seat " << seatNumber << " has been reserved.\n";
    }

    void display() const override {
        Ticket::display();
        std::cout << "Seat Number: " << seatNumber << std::endl;
    }
};

int main() {
    Ticket ticket1(50.0, "2024-12-31");
    ConcertTicket concertTicket1(120.0, "2024-12-15", "A12");

    std::cout << "Ticket Info:\n";
    ticket1.display();

    std::cout << "\nConcert Ticket Info:\n";
    concertTicket1.display();

    std::cout << "\nReserving seat for concert ticket:\n";
    concertTicket1.reserveSeat();

    return 0;
}
