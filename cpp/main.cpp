#include <iostream>
#include <string>
#include <vector>
#include <memory>

// =====================
// Base class: Ride
// =====================
class Ride {
protected:
    std::string rideID;
    std::string pickupLocation;
    std::string dropoffLocation;
    double distance; // in miles

public:
    Ride(const std::string& id,
         const std::string& pickup,
         const std::string& dropoff,
         double distanceMiles)
        : rideID(id),
          pickupLocation(pickup),
          dropoffLocation(dropoff),
          distance(distanceMiles) {}

    virtual ~Ride() = default;

    virtual double calculateFare() const = 0; // pure virtual → polymorphism

    virtual void rideDetails() const {
        std::cout << "Ride ID: " << rideID << "\n"
                  << "Pickup: " << pickupLocation << "\n"
                  << "Dropoff: " << dropoffLocation << "\n"
                  << "Distance: " << distance << " miles\n";
    }
};

// =====================
// Derived class: StandardRide
// =====================
class StandardRide : public Ride {
    double baseFarePerMile;

public:
    StandardRide(const std::string& id,
                 const std::string& pickup,
                 const std::string& dropoff,
                 double distanceMiles,
                 double ratePerMile = 1.5)
        : Ride(id, pickup, dropoff, distanceMiles),
          baseFarePerMile(ratePerMile) {}

    double calculateFare() const override {
        return distance * baseFarePerMile;
    }

    void rideDetails() const override {
        std::cout << "=== Standard Ride ===\n";
        Ride::rideDetails();
        std::cout << "Fare: $" << calculateFare() << "\n\n";
    }
};

// =====================
// Derived class: PremiumRide
// =====================
class PremiumRide : public Ride {
    double baseFarePerMile;
    double premiumMultiplier;

public:
    PremiumRide(const std::string& id,
                const std::string& pickup,
                const std::string& dropoff,
                double distanceMiles,
                double ratePerMile = 2.0,
                double multiplier = 1.5)
        : Ride(id, pickup, dropoff, distanceMiles),
          baseFarePerMile(ratePerMile),
          premiumMultiplier(multiplier) {}

    double calculateFare() const override {
        return distance * baseFarePerMile * premiumMultiplier;
    }

    void rideDetails() const override {
        std::cout << "=== Premium Ride ===\n";
        Ride::rideDetails();
        std::cout << "Fare: $" << calculateFare() << "\n\n";
    }
};

// =====================
// Driver class
// =====================
class Driver {
    std::string driverID;
    std::string name;
    double rating;
    std::vector<std::shared_ptr<Ride>> assignedRides; // encapsulated

public:
    Driver(const std::string& id,
           const std::string& driverName,
           double driverRating)
        : driverID(id),
          name(driverName),
          rating(driverRating) {}

    void addRide(const std::shared_ptr<Ride>& ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        std::cout << "Driver ID: " << driverID << "\n"
                  << "Name: " << name << "\n"
                  << "Rating: " << rating << "\n"
                  << "Total Rides: " << assignedRides.size() << "\n\n";
    }

    void listAssignedRides() const {
        std::cout << "Rides assigned to " << name << ":\n";
        for (const auto& ride : assignedRides) {
            ride->rideDetails(); // polymorphic call
        }
    }
};

// =====================
// Rider class
// =====================
class Rider {
    std::string riderID;
    std::string name;
    std::vector<std::shared_ptr<Ride>> requestedRides; // encapsulated

public:
    Rider(const std::string& id,
          const std::string& riderName)
        : riderID(id),
          name(riderName) {}

    void requestRide(const std::shared_ptr<Ride>& ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        std::cout << "Ride history for rider " << name << ":\n";
        for (const auto& ride : requestedRides) {
            ride->rideDetails(); // polymorphic call
        }
    }
};

// =====================
// Demo main()
// =====================
int main() {
    // Create rides of different types
    std::shared_ptr<Ride> ride1 =
        std::make_shared<StandardRide>("R1", "Downtown", "Airport", 10.0);
    std::shared_ptr<Ride> ride2 =
        std::make_shared<PremiumRide>("R2", "Mall", "Hotel", 5.0);
    std::shared_ptr<Ride> ride3 =
        std::make_shared<StandardRide>("R3", "University", "Station", 3.5);

    // Put rides in a polymorphic collection
    std::vector<std::shared_ptr<Ride>> allRides = {ride1, ride2, ride3};

    std::cout << "=== Polymorphic Ride List ===\n";
    for (const auto& ride : allRides) {
        ride->rideDetails();           // virtual dispatch
        std::cout << "Computed fare: $"
                  << ride->calculateFare() << "\n\n";
    }

    // Create driver and rider
    Driver driver("D1", "Alex Johnson", 4.9);
    Rider rider("U1", "Sanya Kamra");

    // Assign rides
    driver.addRide(ride1);
    driver.addRide(ride2);

    rider.requestRide(ride1);
    rider.requestRide(ride3);

    std::cout << "\n=== Driver Info ===\n";
    driver.getDriverInfo();
    driver.listAssignedRides();

    std::cout << "\n=== Rider Info ===\n";
    rider.viewRides();

    return 0;
}
