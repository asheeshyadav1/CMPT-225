/*
 * BankSimApp.cpp
 *
 * Description: This is a Bank Simulation application 
 *             that models the arrival and departure of people at a bank.
 *
 * Class Invariant: The simulation must start at time 0
 *                  and end when there are no more events to process.
 *
 * Author: Asheesh Yadav + Eeshan V
 * Last Modified: April 5, 2024
 */
#include <iostream> // standard library
#include <iomanip> // for setw(x)
#include "PriorityQueue.h" // PriorityQueue class
#include "BinaryHeap.h" // BinaryHeap class
#include "Event.h" // Event class
#include "Queue.h" // Queue class
#include "EmptyDataCollectionException.h" // for exception handling

using namespace std;// for printing

class bankSimulation {
private:
    bool isTellerFree; // Teller status
    int updatedTime; // Current time
    int totalCustomers; // Queue size
    int totalWaitTime; // Waiting time
    Queue<Event> customerQueue; // Customer queue
    PriorityQueue<Event> eventPriorityQueue; // Event queue

public:
    // Default constructor
    // Precondition: None
    // Postcondition: Creates a new bankSimulation object
    // Description: Initializes the bankSimulation object
    //Time Complexity: O(1)
    bankSimulation() : isTellerFree(true), updatedTime(0), totalCustomers(0), totalWaitTime(0) {}
    
    //Handles Arrivining Customers
    // Precondition: None
    // Postcondition: Handles the arrival of customers
    // Description: Processes the arrival of customers
    //Time Complexity: O(1)
    void handleArrival(Event arrivalEvent); 

    //Handles Departing Customers
    // Precondition: Must be atleast 1 customer
    // Postcondition: Handles the departure of customers
    // Description: Processes the departure of customers
    //Time Complexity: O(1)
    void handleDeparture(Event departureEvent); 

    //Creates Simulation
    // Precondition: None
    // Postcondition: Runs the events occured at the Bank
    // Description: Runs the Bank simulation
    //Time Complexity: O(n)
    void createSimulation(); 
};


void bankSimulation::createSimulation()
{
    try { //reads the times from the files
        int arrivalTime, transactionTime;
        while (cin >> arrivalTime >> transactionTime) 
        {
            Event newEvent(Event::ARRIVAL, arrivalTime, transactionTime);
            eventPriorityQueue.enqueue(newEvent); // Enqueue event
        }
        
        cout << "Simulation Begins" << endl;
        while (!eventPriorityQueue.isEmpty()) // Process events
        {
            Event currentEvent = eventPriorityQueue.peek();
            updatedTime = currentEvent.getTime();
            if (currentEvent.getType() == Event::ARRIVAL) {
                handleArrival(currentEvent);
            } else {
                handleDeparture(currentEvent);
            }
        }
        cout << "Simulation Ends" << endl;	
        //calc the avg wait time
        //must used casting 
        double avergaeWait = (double)totalWaitTime / (double)totalCustomers;
        // Print final stats
        cout << endl << "Final Statistics:  \n" << endl;
        cout << "\tTotal number of people processed: " << totalCustomers << endl;
        cout << "\tAverage amount of time spent waiting: " << avergaeWait << endl;
    
    } catch (EmptyDataCollectionException & err) { // Exception handling
        cout << "Error: " << err.what() << endl;   // if queue is empty
    }
}

void bankSimulation::handleArrival(Event arrivalEvent)
{
    try {
        //print arrival based on the books instructions 
        cout << "Processing an arrival event at time:  " << setw(3) << right << arrivalEvent.getTime() << endl;
        
        //inc customers waiting
        totalCustomers++;

        // Dequeue event since departure is occuring
        eventPriorityQueue.dequeue(); 

        //create event for customer
        Event customer(Event::ARRIVAL, arrivalEvent.getTime(), arrivalEvent.getLength());

        if (customerQueue.isEmpty() && isTellerFree) // If teller is free
        {
            //get departure time
            int departureTime = updatedTime + arrivalEvent.getLength();
            //create the actual event for departure
            Event newDepartureEvent(Event::DEPARTURE, departureTime, 0);
            //enqueue the event
            eventPriorityQueue.enqueue(newDepartureEvent); 
            //teller is busy
            isTellerFree = false;
        }
        else // If teller busy
        {	//make him go into the queue if the teller is busy
            customerQueue.enqueue(customer); 
        }
        //throw catch block as seen in our lectures
        //if the queue is empty
    } catch (EmptyDataCollectionException & err) {
        cout << "Error: " << err.what() << endl;
    }
}

void bankSimulation::handleDeparture(Event departureEvent)
{
    try {
        //print departure based on the books instructions
        cout << "Processing a departure event at time: " << setw(3) << right << departureEvent.getTime() << endl;

        eventPriorityQueue.dequeue(); // Dequeue event
        if (!customerQueue.isEmpty()) // If customers in queue
        {
            //get the customer
            Event customer = customerQueue.peek();

            // Enqueue customer
            customerQueue.dequeue(); 

            //get the departure time
            int departureTime = updatedTime + customer.getLength();

            //if the updated time is greater than the customer time
            if (updatedTime >customer.getTime())
                //update the time for wait
                totalWaitTime += updatedTime - customer.getTime(); 

            //create the actual event for departure
            Event newDepartureEvent = Event(Event::DEPARTURE, departureTime, 0);

            //enqueue event
            eventPriorityQueue.enqueue(newDepartureEvent); 
        }
        else
            isTellerFree = true; // Teller is free
            //throw catch block as seen in our lectures
    } catch (EmptyDataCollectionException & err) {
        cout << "Error: " << err.what() << endl;
    }
}

int main()
{
    bankSimulation bkSimul; // Create simulator
    bkSimul.createSimulation(); // Run simulation
    return 0;
}