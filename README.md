# Movie Booking System

This C++ program implements a simplified movie booking system with features like user management, movie scheduling, seat booking, and ticket generation. The design leverages object-oriented programming principles and design patterns to ensure scalability and maintainability.

---

## Features

### 1. User Management

- Supports different types of users: **Actors**, **Directors**, and **Regular Users**.
- Users are derived from a common base class `Person` to ensure code reuse and extensibility.

### 2. Movie Management

- `Movie` class stores movie details such as title and release date.
- Each movie can have a cast of `Actor` objects and a `Director`.

### 3. Schedule Management

- The `Schedule` class allows movies to be scheduled with specific start times.
- Seat bookings are associated with a schedule.

### 4. Seat Booking

- Users can book seats for a scheduled movie.
- Two types of seats are available: **Normal** and **Recliner**.
- Seat bookings follow a lifecycle: **PENDING**, **CONFIRMED**, or **CANCELLED**.
- Booked seats are temporarily locked to prevent double booking.

### 5. Ticket Generation

- `Ticket` class generates tickets for booked seats.
- Tickets store information about the movie, user, seats, and the total price.

### 6. Pricing Strategies

- Dynamic pricing based on scheduling:
  - `RegularPricing`: Default pricing.
  - `WeekendPricing`: Higher pricing on weekends.
- Easily extendable with additional pricing strategies.

---

## Design Patterns Used

### 1. **Strategy Pattern**

- Pricing strategies (`RegularPricing` and `WeekendPricing`) implement a common interface `PricingStrategy`, allowing dynamic selection of pricing logic.

### 2. **State Pattern**

- The program uses state pattern effectively to manage seat states.

### 3. **Composite Pattern**

- Tickets aggregate multiple seats and their pricing, demonstrating how smaller components can form a larger entity.

---

## Code Structure

### Core Classes

1. **Person**

   - Base class for `Actor`, `Director`, and `User`.

2. **Movie**

   - Stores details about a movie and its cast.

3. **Schedule**

   - Manages movie schedules and associated bookings.

4. **SeatBooking**

   - Handles seat bookings, including locking and confirmation.

5. **Ticket**
   - Generates tickets for booked seats.

### Supporting Classes

1. **PricingStrategy**

   - Base class for implementing different pricing algorithms.

2. **Seat**
   - Represents individual seats with unique numbers and types.

---

## Example Usage

1. Create a movie and user:

   ```cpp
   Movie* movie = new Movie(1, "Inception");
   User* user = new User(1, "John Doe");
   ```

2. Create seats and schedule:

   ```cpp
   Seat* seat1 = new Seat("A1", NORMAL);
   Seat* seat2 = new Seat("A2", RECLINER);
   Schedule* schedule = new Schedule(1, movie, "20:00");
   ```

3. Book seats and generate a ticket:

   ```cpp
   SeatBooking* booking1 = new SeatBooking(1, seat1, schedule);
   SeatBooking* booking2 = new SeatBooking(2, seat2, schedule);

   if (booking1->blockSeat() && booking2->blockSeat()) {
       Ticket* ticket = new Ticket(1, movie, user);
       ticket->addSeat(seat1);
       ticket->addSeat(seat2);
       ticket->setTotalAmount(booking1->getPrice() + booking2->getPrice());

       std::cout << "Booking successful for movie: " << movie->getTitle() << std::endl;
       std::cout << "Total amount: $" << ticket->getTotalAmount() << std::endl;

       delete ticket;
   }
   ```

4. Cleanup:
   ```cpp
   delete movie;
   delete user;
   delete seat1;
   delete seat2;
   delete booking1;
   delete booking2;
   delete schedule;
   ```

---

## How to Extend

- **New Seat Types:** Add new seat types to the `SeatType` enum and handle them in the `Seat` and `PricingStrategy` classes.
- **Additional Pricing Strategies:** Derive new classes from `PricingStrategy` to implement custom pricing logic.
- **Enhanced User Roles:** Extend the `Person` class to add new user types like `Admin` or `Manager`.
