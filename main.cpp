#include <iostream>
#include <string>
#include <vector>
#include <ctime>

// Enums
enum SeatType { NORMAL, RECLINER };
enum BookingStatus { PENDING, CONFIRMED, CANCELLED };

// Base class Person
class Person {
protected:
    int id;
    std::string name;
public:
    Person(int id, std::string name) : id(id), name(name) {}
    virtual ~Person() {}
};

// Derived classes from Person
class Actor : public Person {
public:
    Actor(int id, std::string name) : Person(id, name) {}
};

class Director : public Person {
public:
    Director(int id, std::string name) : Person(id, name) {}
};

class User : public Person {
public:
    User(int id, std::string name) : Person(id, name) {}
};

// Movie class
class Movie {
    int id;
    std::string title;
    std::time_t dateOfRelease;
    std::vector<Actor*> cast;
    Director* director;

public:
    Movie(int id, std::string title) : id(id), title(title) {}
    std::string getTitle() const { return title; }
};

// Pricing Strategy
class PricingStrategy {
protected:
    float basePrice;
public:
    PricingStrategy(float price) : basePrice(price) {}
    virtual float getPrice() = 0;
    virtual ~PricingStrategy() {}
};

class RegularPricing : public PricingStrategy {
public:
    RegularPricing() : PricingStrategy(10.0f) {}
    float getPrice() override { return basePrice; }
};

class WeekendPricing : public PricingStrategy {
public:
    WeekendPricing() : PricingStrategy(10.0f) {}
    float getPrice() override { return basePrice * 1.5f; }
};

// Seat class
class Seat {
    std::string number;
    SeatType type;
public:
    Seat(std::string number, SeatType type) : number(number), type(type) {}
    std::string getNumber() const { return number; }
    SeatType getType() const { return type; }
};

// Forward declaration
class Schedule;

// Seat Booking class
class SeatBooking {
    int id;
    Seat* seat;
    Schedule* schedule;
    PricingStrategy* pricingStrategy;
    BookingStatus status;
    User* user;
    std::time_t lockExpiryTime;

public:
    SeatBooking(int id, Seat* seat, Schedule* schedule) 
        : id(id), seat(seat), schedule(schedule), status(PENDING) {
        pricingStrategy = new RegularPricing();
    }

    bool blockSeat() {
        if (status == PENDING) {
            status = CONFIRMED;
            lockExpiryTime = std::time(nullptr) + 600; // 10 minute lock
            return true;
        }
        return false;
    }

    bool bookSeat(User* user) {
        if (status == PENDING) {
            this->user = user;
            status = CONFIRMED;
            return true;
        }
        return false;
    }

    float getPrice() { 
        return pricingStrategy->getPrice(); 
    }

    ~SeatBooking() {
        delete pricingStrategy;
    }
};

// Schedule class
class Schedule {
    int id;
    std::time_t date;
    Movie* movie;
    std::string startTime;
    std::vector<SeatBooking*> seatBookings;

public:
    Schedule(int id, Movie* movie, std::string startTime)
        : id(id), movie(movie), startTime(startTime) {}
    
    bool addSeatBooking(SeatBooking* booking) {
        seatBookings.push_back(booking);
        return true;
    }

    ~Schedule() {
        for(SeatBooking* booking : seatBookings) {
            delete booking;
        }
    }
};

// Ticket class
class Ticket {
    int id;
    Movie* movie;
    std::string startTime;
    std::time_t date;
    std::vector<Seat*> seats;
    User* user;
    float totalAmount;

public:
    Ticket(int id, Movie* movie, User* user)
        : id(id), movie(movie), user(user), totalAmount(0.0f) {}
    
    void addSeat(Seat* seat) {
        seats.push_back(seat);
    }

    void setTotalAmount(float amount) {
        totalAmount = amount;
    }

    float getTotalAmount() const {
        return totalAmount;
    }
};

int main() {
    // Create objects
    Movie* movie = new Movie(1, "Inception");
    User* user = new User(1, "John Doe");
    
    Seat* seat1 = new Seat("A1", NORMAL);
    Seat* seat2 = new Seat("A2", RECLINER);
    
    Schedule* schedule = new Schedule(1, movie, "20:00");
    
    SeatBooking* booking1 = new SeatBooking(1, seat1, schedule);
    SeatBooking* booking2 = new SeatBooking(2, seat2, schedule);
    
    // Book seats
    if (booking1->blockSeat() && booking2->blockSeat()) {
        Ticket* ticket = new Ticket(1, movie, user);
        ticket->addSeat(seat1);
        ticket->addSeat(seat2);
        
        float totalAmount = booking1->getPrice() + booking2->getPrice();
        ticket->setTotalAmount(totalAmount);
        
        std::cout << "Booking successful for movie: " << movie->getTitle() << std::endl;
        std::cout << "Total amount: $" << ticket->getTotalAmount() << std::endl;

        // Cleanup
        delete ticket;
    }
    
    // Cleanup
    delete movie;
    delete user;
    delete seat1;
    delete seat2;
    delete booking1;
    delete booking2;
    delete schedule;
    
    return 0;
}