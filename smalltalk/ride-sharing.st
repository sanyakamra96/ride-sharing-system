"Ride class"
Object subclass: #Ride
    instanceVariableNames: 'rideID pickupLocation dropoffLocation distance'
    classVariableNames: ''
    package: 'RideSharing'.

Ride >> rideID: anId pickup: pickup dropoff: dropoff distance: miles
    rideID := anId.
    pickupLocation := pickup.
    dropoffLocation := dropoff.
    distance := miles.

Ride >> calculateFare
    "Abstract method – subclasses must override"
    self subclassResponsibility.

Ride >> rideDetails
    ^ String streamContents: [ :s |
        s
            nextPutAll: 'Ride ID: '; nextPutAll: rideID; cr;
            nextPutAll: 'Pickup: '; nextPutAll: pickupLocation; cr;
            nextPutAll: 'Dropoff: '; nextPutAll: dropoffLocation; cr;
            nextPutAll: 'Distance: '; print: distance; nextPutAll: ' miles'; cr ].


"StandardRide"
Ride subclass: #StandardRide
    instanceVariableNames: 'baseFarePerMile'
    classVariableNames: ''
    package: 'RideSharing'.

StandardRide >> baseFarePerMile: aNumber
    baseFarePerMile := aNumber.

StandardRide >> calculateFare
    ^ distance * baseFarePerMile.

StandardRide >> rideDetails
    ^ String streamContents: [ :s |
        s nextPutAll: '=== Standard Ride ==='; cr.
        s nextPutAll: super rideDetails; cr.
        s nextPutAll: 'Fare: $'; print: self calculateFare; cr ].


"PremiumRide"
Ride subclass: #PremiumRide
    instanceVariableNames: 'baseFarePerMile premiumMultiplier'
    classVariableNames: ''
    package: 'RideSharing'.

PremiumRide >> baseFarePerMile: aNumber multiplier: mult
    baseFarePerMile := aNumber.
    premiumMultiplier := mult.

PremiumRide >> calculateFare
    ^ distance * baseFarePerMile * premiumMultiplier.

PremiumRide >> rideDetails
    ^ String streamContents: [ :s |
        s nextPutAll: '=== Premium Ride ==='; cr.
        s nextPutAll: super rideDetails; cr.
        s nextPutAll: 'Fare: $'; print: self calculateFare; cr ].


"Driver class"
Object subclass: #Driver
    instanceVariableNames: 'driverID name rating assignedRides'
    classVariableNames: ''
    package: 'RideSharing'.

Driver >> initialize
    super initialize.
    assignedRides := OrderedCollection new.

Driver >> driverID: anId name: aName rating: aRating
    driverID := anId.
    name := aName.
    rating := aRating.

Driver >> addRide: aRide
    assignedRides add: aRide.

Driver >> driverInfo
    ^ String streamContents: [:s |
        s nextPutAll: 'Driver ID: '; nextPutAll: driverID; cr;
        s nextPutAll: 'Name: '; nextPutAll: name; cr;
        s nextPutAll: 'Rating: '; print: rating; cr;
        s nextPutAll: 'Total rides: '; print: assignedRides size; cr ].

Driver >> listAssignedRides
    assignedRides do: [:ride |
        Transcript show: ride rideDetails; cr ].


"Rider class"
Object subclass: #Rider
    instanceVariableNames: 'riderID name requestedRides'
    classVariableNames: ''
    package: 'RideSharing'.

Rider >> initialize
    super initialize.
    requestedRides := OrderedCollection new.

Rider >> riderID: anId name: aName
    riderID := anId.
    name := aName.

Rider >> requestRide: aRide
    requestedRides add: aRide.

Rider >> viewRides
    requestedRides do: [:ride |
        Transcript show: ride rideDetails; cr ].


"Demo script to show polymorphism"
| ride1 ride2 ride3 rides driver rider |
ride1 := StandardRide new.
ride1 rideID: 'R1' pickup: 'Downtown' dropoff: 'Airport' distance: 10.
ride1 baseFarePerMile: 1.5.

ride2 := PremiumRide new.
ride2 rideID: 'R2' pickup: 'Mall' dropoff: 'Hotel' distance: 5.
ride2 baseFarePerMile: 2.0 multiplier: 1.5.

ride3 := StandardRide new.
ride3 rideID: 'R3' pickup: 'University' dropoff: 'Station' distance: 3.5.
ride3 baseFarePerMile: 1.5.

rides := { ride1. ride2. ride3 }.

Transcript clear.
Transcript show: '=== Polymorphic Ride List (Smalltalk) ==='; cr.
rides do: [:r |
    Transcript show: r rideDetails; cr.
    Transcript show: 'Computed fare: $'; show: r calculateFare; cr; cr ].

driver := Driver new.
driver driverID: 'D1' name: 'Alex Johnson' rating: 4.9.
driver addRide: ride1.
driver addRide: ride2.

rider := Rider new.
rider riderID: 'U1' name: 'Sanya Kamra'.
rider requestRide: ride1.
rider requestRide: ride3.

Transcript show: driver driverInfo; cr.
driver listAssignedRides.

Transcript show: 'Ride history for rider '; show: 'Sanya Kamra'; cr.
rider viewRides.

