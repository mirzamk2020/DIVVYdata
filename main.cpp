/* main.cpp */
//
// Project: Analyzing DIVVY data
// Author: Mirza MK Baig
// Date: 3/9/2021
// 
// The program analyzes the DIVYY bike trips data and stations. It stores the stations data and bike trips data
// in dynamically allocated arrays. It does the following operations when user enters a specific command until user inputs "#".
// 1. Quick statistics (command: stats)
// 2. Summary of bike duration (command: durations)
// 3. Histogram of starting times (command: starting)
// 4. Stations near me (example command: nearme 41.87 -87.66 0.8) Lists stations by ascending order of distance near given position.
// 5. List all stations (command: stations)
// 6. Find stations (example command: find Park). Lists stations alphabetically that contains case-sensitive string in station's name. 
// 7. Find trips within timespan (example command: trips 2:00 5:00)
//
//


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


using namespace std;


struct stationInfo{
    string stationID;
    int capacity;
    double latitude;
    double longitude;
    string name;
    double distance;
    int trips;
    bool tripFound;
};
    

struct tripInfo{
    string tripID;
    string bikeID;
    string startStatID;
    string endStatID;
    int duration;
    string startTime;
    int startMins;
};


// storeStationValues
//
// Given inputStationsFile as a reference, stationInfo struct stations array and number of stations,
// the program inputs data into stationInfo struct stations array and stores in appropraite locations
// line by line. No return type.
//
void storeStationValues(ifstream& inputStationsFile, stationInfo stations[], int N){
    for (int i = 0; i < N; ++i){
        inputStationsFile >> stations[i].stationID;
        inputStationsFile >> stations[i].capacity;
        inputStationsFile >> stations[i].latitude;
        inputStationsFile >> stations[i].longitude;
        
        string name = "";
        getline(inputStationsFile, name);
        name.erase(0,1); // removes the extra space at index 0
        stations[i].name = name;
        
        // initalizing these values that will be used later in program
        stations[i].distance = 0.0;
        stations[i].trips = 0;
        stations[i].tripFound = false;
        
    }
}


//
// storeBikeTripValues
//
// Given inputBikeTripsFile as a reference, tripInfo struct trips array and number of bike trips,
// the program inputs data into tripInfo struct trips array and stores in appropraite locations
// line by line. No return type.
//
void storeBikeTripValues(ifstream& inputBikeTripsFile, tripInfo trips[], int N){
    for (int i = 0; i < N; ++i){
        inputBikeTripsFile >> trips[i].tripID;
        inputBikeTripsFile >> trips[i].bikeID;
        inputBikeTripsFile >> trips[i].startStatID;
        inputBikeTripsFile >> trips[i].endStatID;
        inputBikeTripsFile >> trips[i].duration;
        inputBikeTripsFile >> trips[i].startTime;
        
        // initalizing startMins values that will be used later in program
        trips[i].startMins = 0;
        
    }
}


//
// quickStats
//
// Given total number of stations(S), total number of bike trips(T), and stationInfo struct stations array,
// the program calculates the total bike capacity by looping through the stations array and adding to the 
// bike capacity counter. Outputs stations, trips, and total bike capacity. No return type.
void quickStats(int S, int T, stationInfo stations[]){
    int totalBikeCapacity = 0;
    for (int i = 0; i < S; ++i){
        totalBikeCapacity += stations[i].capacity;
    }
    
    cout << " stations: " << S << endl;
    cout << " trips: " << T << endl;
    cout << " total bike capacity: " << totalBikeCapacity << endl;
    
}


//
// durations
//
// Given total number of trips(T) and tripInfo struct trips array, the program
// loops through the trips array and categorizes trip into 5 categories based on the duration
// (i.e oneToTwoHours or thirtyToSixtyMins) and keeps a counter. Outputs
// the counter for the 5 categories. No return type.
//
void durations(int T, tripInfo trips[]){
    int lessThanEqualThirtyMins = 0;
    int thirtyToSixtyMins = 0;
    int oneToTwoHours = 0;
    int twoToFiveHours = 0;
    int moreThanFiveHours = 0;
    
    for(int i = 0; i < T; ++i){
        if(trips[i].duration <= 1800){ // <= 30 mins
            lessThanEqualThirtyMins++;
        } else if (trips[i].duration > 1800 && trips[i].duration <= 3600){ // 30 < duration <= 60 mins
            thirtyToSixtyMins++;
        } else if (trips[i].duration > 3600 && trips[i].duration <= 7200){ // 1 hour < duration <= 2 hours
            oneToTwoHours++;
        } else if(trips[i].duration > 7200 && trips[i].duration <= 18000){ // 2 hours < duration <= 5 hours
            twoToFiveHours++;
        } else if(trips[i].duration > 18000){ // duration > 5 hours
            moreThanFiveHours++;
        }
    }
    
    cout << " trips <= 30 mins: " << lessThanEqualThirtyMins << endl;
    cout << " trips 30..60 mins: " << thirtyToSixtyMins << endl;
    cout << " trips 1-2 hrs: " << oneToTwoHours << endl;
    cout << " trips 2-5 hrs: " << twoToFiveHours << endl;
    cout << " trips > 5 hrs: " << moreThanFiveHours << endl;
}


//
// startingTimes
//
// Given total number of trips(T) and tripInfo struct trips array, the program loops through the startTime string 
// and finds the hour. It categorizes into 1 of 24 categories and executes if-elseif statement to count how many 
// they are in each hour category. No return type.
//
void startingTimes(int T, tripInfo trips[]){
    // initializing count for 24 hours(0-23)
    int Hour0, Hour1, Hour2, Hour3, Hour4, Hour5, Hour6, Hour7, Hour8, Hour9, Hour10, Hour11, Hour12, Hour13, Hour14;
    int Hour15, Hour16, Hour17, Hour18, Hour19, Hour20, Hour21, Hour22, Hour23;

    //setting to 0
    Hour0 = Hour1 = Hour2 = Hour3 = Hour4 = Hour5 = Hour6 = Hour7 = Hour8 = Hour9 = Hour10 = Hour11 = Hour12 = Hour13 = Hour14 = 0;
    Hour15 = Hour16 = Hour17 = Hour18 = Hour19 = Hour20 = Hour21 = Hour22 = Hour23 = 0;

    for(int i = 0; i < T; ++i){
        string startTime = trips[i].startTime;
        int colonIndex = startTime.find(":");
        int hour = stoi(startTime.substr(0, colonIndex)); // convert the substring from index 0 til colonIndex to int
        
        if(hour == 0){
            Hour0++;
        } else if (hour == 1){
            Hour1++;
        } else if (hour == 2){
            Hour2++;
        } else if (hour == 3){
            Hour3++;
        } else if (hour == 4){
            Hour4++;
        } else if (hour == 5){
            Hour5++;
        } else if (hour == 6){
            Hour6++;
        } else if (hour == 7){
            Hour7++;
        } else if (hour == 8){
            Hour8++;
        } else if (hour == 9){
            Hour9++;
        } else if (hour == 10){
            Hour10++;
        } else if (hour == 11){
            Hour11++;
        } else if (hour == 12){
            Hour12++;
        } else if (hour == 13){
            Hour13++;
        } else if (hour == 14){
            Hour14++;
        } else if (hour == 15){
            Hour15++;
        } else if (hour == 16){
            Hour16++;
        } else if (hour == 17){
            Hour17++;
        } else if (hour == 18){
            Hour18++;
        } else if (hour == 19){
            Hour19++;
        } else if (hour == 20){
            Hour20++;
        } else if (hour == 21){
            Hour21++;
        } else if (hour == 22){
            Hour22++;
        } else if (hour == 23){
            Hour23++;
        }
    }
    // output results
    cout << " 0: " << Hour0 << endl;
    cout << " 1: " << Hour1 << endl;
    cout << " 2: " << Hour2 << endl;
    cout << " 3: " << Hour3 << endl;
    cout << " 4: " << Hour4 << endl;
    cout << " 5: " << Hour5 << endl;
    cout << " 6: " << Hour6 << endl;
    cout << " 7: " << Hour7 << endl;
    cout << " 8: " << Hour8 << endl;
    cout << " 9: " << Hour9 << endl;
    cout << " 10: " << Hour10 << endl;
    cout << " 11: " << Hour11 << endl;
    cout << " 12: " << Hour12 << endl;
    cout << " 13: " << Hour13 << endl;
    cout << " 14: " << Hour14 << endl;
    cout << " 15: " << Hour15 << endl;
    cout << " 16: " << Hour16 << endl;
    cout << " 17: " << Hour17 << endl;
    cout << " 18: " << Hour18 << endl;
    cout << " 19: " << Hour19 << endl;
    cout << " 20: " << Hour20 << endl;
    cout << " 21: " << Hour21 << endl;
    cout << " 22: " << Hour22 << endl;
    cout << " 23: " << Hour23 << endl;
}


//
// swapValues
//
// Given struct stationInfo a and b by reference, the program swaps the elements by using 
// a temporary variable to store one of the elements. No return type.
//
void swapValues(stationInfo& a, stationInfo& b){
    stationInfo tempA = a;
    a = b;
    b = tempA;
}


// 
// bubbleSortByDistance
//
// Given stationInfo struct stations array and total number of stations(S), bubble sort is performed
// by distance from nearest to farthest, which is an ascending order. The program does a while loop and for loop to 
// swap elements of the stations array and store if there was a swap so the while loop can execute again.
//
void bubbleSortByDistance(stationInfo stations[], int S){
    bool isSwapped = true; // initial value to start the bubble sort
    while(isSwapped){
        isSwapped = false;
        for(int i = 0; i < (S - 1); ++i){
            if(stations[i].distance > stations[i+1].distance){
                swapValues(stations[i], stations[i+1]); // swap 2 index from array
                isSwapped = true; // allows while loop to execute again since there was a swap detected
            }
        }
    }
}


//
// distBetween2Points
//
// Returns the distance in miles between 2 points (lat1, long1) and 
// (lat2, long2).  Latitudes are positive above the equator and 
// negative below; longitudes are positive heading east of Greenwich 
// and negative heading west.  Example: Chicago is (41.88, -87.63).
//
// NOTE: you may get slightly different results depending on which 
// (lat, long) pair is passed as the first parameter.
// 
// Originally written by: Prof. Hummel, U. of Illinois, Chicago, Spring 2021
// Reference: http://www8.nau.edu/cvm/latlon_formula.html
//
double distBetween2Points(double lat1, double long1, double lat2, double long2)
{
  double PI = 3.14159265;
  double earth_rad = 3963.1;  // statue miles:

  double lat1_rad = lat1 * PI / 180.0;
  double long1_rad = long1 * PI / 180.0;
  double lat2_rad = lat2 * PI / 180.0;
  double long2_rad = long2 * PI / 180.0;

  double dist = earth_rad * acos(
    (cos(lat1_rad) * cos(long1_rad) * cos(lat2_rad) * cos(long2_rad))
    +
    (cos(lat1_rad) * sin(long1_rad) * cos(lat2_rad) * sin(long2_rad))
    +
    (sin(lat1_rad) * sin(lat2_rad))
  );

  return dist;
}


//
// stationsNearMe
//
// Given stationInfo struct stations array and total number of stations(S), it gets user inputs and calulates distance
// and stores in stations array. It sorts the stations array by distance by calling bubble sort function. 
// It loops through the distances for all stations and checks if it's within the D to output it. No return type.
//
void stationsNearMe(stationInfo stations[], int S){
    // get user input of lat, long, and D
    double latitude, longitude, D;
    
    cin >> latitude;
    cin >> longitude;
    cin >> D;
    
    // store the distance in the stations array
    for(int i = 0; i < S; ++i){
        stations[i].distance = distBetween2Points(latitude, longitude, stations[i].latitude, stations[i].longitude);
    }
    
    bubbleSortByDistance(stations, S);
     
    cout << " The following stations are within " << D << " miles of (" << latitude << ", " << longitude << "):" << endl;
    int foundOneStation = 0; // to check if atleast one station is within D
    
    for(int i = 0; i < S; ++i){
        if(stations[i].distance <= D){
            foundOneStation = 1;
            cout << " station " << stations[i].stationID << " (" << stations[i].name << "): " << stations[i].distance << " miles" << endl;
        }
    }
    
    if(foundOneStation == 0){
        cout << " none found" << endl;
    }
}


//
// storeTrips
//
// Given stationInfo struct stations array, tripInfo struct trips array, total number of stations, and total number of trips,
// the program loops through items in stations and checks if trips value is 0. If it's 0, then it loops through the trips to find
// if it matches with start and/or end station id and increases trips counter. No return type.
//
void storeTrips(stationInfo stations[], tripInfo trips[], int S, int T){
    for(int i = 0; i < S; ++i){
        if(stations[i].trips == 0){ // only adding # of trips when trip is empty
            for(int k = 0; k < T; ++k){
                if(trips[k].startStatID == stations[i].stationID && trips[k].endStatID == stations[i].stationID){
                    stations[i].trips += 1; // only increasing trip by 1 for same start and end station id
                } else if (trips[k].startStatID == stations[i].stationID){
                    stations[i].trips += 1;
                } else if (trips[k].endStatID == stations[i].stationID){
                    stations[i].trips += 1;
                }
            }
        }
    }
}


// 
// bubbleSortByName
//
// Given stationInfo struct stations array and total number of stations(S), bubble sort is performed
// alphabetically, which is done in an ascending order. The program does a while loop and for loop to 
// swap elements of the stations array and store if there was a swap so the while loop can execute again.
//
void bubbleSortByName(stationInfo stations[], int S){
    bool isSwapped = true; // initial value to start the bubble sort
    while(isSwapped){
        isSwapped = false;
        for(int i = 0; i < (S - 1); ++i){
            if(stations[i].name > stations[i+1].name){
                swapValues(stations[i], stations[i+1]); // swap 2 index from array
                isSwapped = true; // allows while loop to execute again since there was a swap detected
            }
        }
    }
}


//
// listAllStations
//
// Given stationInfo struct stations array, tripInfo struct trips array, total number of stations(S), and total number of trips(T),
// calls the function storeTrips and bubbleSortByName to update the stations array. Outputs all the stations. No return type.
//
void listAllStations(stationInfo stations[], tripInfo trips[], int S, int T){
    storeTrips(stations, trips, S, T);
    
    bubbleSortByName(stations, S);
    
    // output the stations
    for(int i = 0; i < S; ++i){
        cout << stations[i].name << " (" << stations[i].stationID << ") @ ("<< stations[i].latitude << ", ";
        cout << stations[i].longitude << "), " << stations[i].capacity << " capacity, " << stations[i].trips << " trips" << endl;
    }
  
}


//
// searchTargetInStations
//
// Given stationInfo struct stations array, total number of stations(S), and a string targer, the program searches through the
// the names of stations array to find target. If it does, it increases the namesMatchCounter by 1. Returns namesMatchCounter.
//
int searchTargetInStations(stationInfo stations[], int S, string target){
    int namesMatchCounter = 0;
    string stationName; 
    size_t stationExistsInName;
    
    for(int i = 0; i < S; ++i){
        stationName = stations[i].name;
        stationExistsInName = stationName.find(target);
        
        if(stationExistsInName != string::npos){ // target exists in the name
            namesMatchCounter++;
        }
    }
    
    return namesMatchCounter;
}


//
// keyExists
//
// Given an int index, stationInfo struct stations array, and a string target,
// the program performs if condition to see if the target exists in the specific name of the station by index value given.
// If it does, returns 1. If it doesn't, returns 0.
//
int keyExists(int index, stationInfo stations[], string target){
    string stationName = stations[index].name;
    size_t stationExistsInName = stationName.find(target);
    
    if(stationExistsInName != string::npos){ // target exists in the name
            return 1; // found
        }
    
    return 0; // not found for specific index
}


//
// findStations
//
// Given stationInfo struct stations array, tripInfo struct trips array, total number of stations, and total number of trips,
// the program does bubbleSortByName and storeTrips to update the stations array. It then loops through the stations array to
// find if the targetKey string exists in station name. It then outputs either none found or the station info. No return type.
//
void findStations(stationInfo stations[], tripInfo trips[], int S, int T){
    string targetKey;
    
    cin >> targetKey;
    
    bubbleSortByName(stations, S);
    
    storeTrips(stations, trips, S, T);
    
    for(int i = 0; i < S; ++i){
        int exists = keyExists(i, stations, targetKey);
        if(exists == 1){
            cout << stations[i].name << " (" << stations[i].stationID << ") @ ("<< stations[i].latitude << ", ";
            cout << stations[i].longitude << "), " << stations[i].capacity << " capacity, " << stations[i].trips << " trips" << endl;
        }
    }
    
    // checking if no match found
    int stationFound = searchTargetInStations(stations, S, targetKey);
    if(stationFound == 0){ // no station contain targetKey string
        cout << " none found" << endl;
    }
}


//
// tripFoundAtStation
//
// Given stationInfo struct stations array, string targetStationID, and total number of stations(S),
// the program stores either true or false values in tripFound inside stations array if it matches the targetStationID. No return type.
//
void tripFoundAtStation(stationInfo stations[], string targetStationID, int S){
    for (int i = 0; i < S; ++i){
        if(stations[i].stationID == targetStationID){
            stations[i].tripFound = true;
        }
    }
}


//
// countTripsAndDuration
//
// Given stationInfo struct stations array, tripInfo struct trips array, total # of stations, total # of trips, time1Mins,
// time2Mins, trips by refernce, and duration by reference, it loops through the trips array elements and examines two cases.
// If it crosses midnight(time1Mins > time2Mins), checks if startTime is between time1 and 23:59 and 0:00 and time2. 
// Else, it sees if startMins is between time1 and time2. Updates trips and duration accordingly. No return type.
//
void countTripsAndDuration(stationInfo stations[], tripInfo trips[], int S, int T, int time1Mins, int time2Mins, int& countTrips, double& totalDuration){
    for(int j = 0; j < T; ++j){
        if(time1Mins > time2Mins){ // crosses midnight
            // looks for trip's startTime between time1Mins and 23:59 OR startTime between 0:00(0 mins) to time2Mins
            if((trips[j].startMins >= time1Mins && trips[j].startMins <= 1439) || (trips[j].startMins >= 0 && trips[j].startMins <= time2Mins)){ 
                // updates trips, duration, and calls tripFoundAtStation to store boolean true in stationInfo struct stations array
                countTrips += 1;
                totalDuration += (trips[j].duration)/(60.0); // minute conversion
                tripFoundAtStation(stations, trips[j].startStatID, S);
                
            }
        } else { // time1 < time2
            if(trips[j].startMins >= time1Mins && trips[j].startMins <= time2Mins){
                countTrips += 1;
                totalDuration += (trips[j].duration)/(60.0); // minute conversion
                tripFoundAtStation(stations, trips[j].startStatID, S);
            }
        }
    }
}


//
// tripsInTimeSpan
//
// Given stationInfo struct stations array, tripInfo struct trips array, and total # of stations, total # of trips,
// it gets userinput for time1 and time2 and converts into minutes(int). Stores time in startMins of trips array. 
// Outputs either none found or stations name, avg duration, and trips. No return type.
//
void tripsInTimeSpan(stationInfo stations[], tripInfo trips[], int S, int T){
    string time1, time2;
    
    cin >> time1;
    cin >> time2;
    
    // find time1 and time2 in minutes
    int colonIndex1 = time1.find(":");
    int colonIndex2 = time2.find(":");
    int hour1 = stoi(time1.substr(0, colonIndex1));
    int hour2 = stoi(time2.substr(0, colonIndex2));
    int minIndex1 = ++colonIndex1;
    int minIndex2 = ++colonIndex2;
    int min1 = stoi(time1.substr(minIndex1));
    int min2 = stoi(time2.substr(minIndex2));
    int Time1InMins = (60 * hour1) + min1;
    int Time2InMins = (60 * hour2) + min2;
    
    int countTrips = 0;
    double duration = 0.0;
    
    // storing time in startMins of trips array
    for(int i = 0; i < T; ++i){
        string startTime = trips[i].startTime;
        int colonIndex = startTime.find(":");
        int hour = stoi(startTime.substr(0, colonIndex));
        int minIndex = ++colonIndex;
        int min = stoi(startTime.substr(minIndex));
        trips[i].startMins = (60 * hour) + min;
    }
    
    countTripsAndDuration(stations, trips, S, T, Time1InMins, Time2InMins, countTrips, duration); // updates trips and duration vars
    
    if(countTrips > 0){
        cout << " " << countTrips << " trips found" << endl;
        cout << " avg duration: " << floor(duration/countTrips) << " minutes" << endl;
        
        bubbleSortByName(stations, S);
        cout << " stations where trip started: ";
        
        int countStations = 0; // acts as an indicator for adding comma and space if more than 1 trip exists
        for(int i = 0; i < S; ++i){
            if(stations[i].tripFound == true){
                if(countStations >= 1){ // add comma and space for more than 1 station names
                    cout << ", ";
                }
                cout << stations[i].name;
                countStations++;
            }
        }
        cout << endl;
        
    } else {
        cout << "none found" << endl;
    }
    
    // resetting the tripFound value to false after the program finishes outputting
    for (int i = 0; i < S; ++i){
        stations[i].tripFound = false;
    }
    
}


int main(){
    
    // (1) input stations and biketrips file and error check
    string biketripsFileName;
    string stationsFileName;
    
    ifstream inputBikeTripsFile;
    ifstream inputStationsFile;
    
    cout << "** Divvy Bike Data Analysis **" << endl;
    
    cout << "Please enter name of stations file> " << endl;
    cin >> stationsFileName;
    
    inputStationsFile.open(stationsFileName);
    if (!inputStationsFile.good()) { // error check stations file
        cout << "**Error: unable to open input file '" << stationsFileName << "'" << endl;
        return 0;
    }
    
    cout << "Please enter name of bike trips file> " << endl;
    cin >> biketripsFileName;
    
    inputBikeTripsFile.open(biketripsFileName);
    if (!inputBikeTripsFile.good()) { // error check biketrips file
        cout << "**Error: unable to open input file '" << biketripsFileName << "'" << endl;
        return 0;
    }
    
    // (2) inputting and storing data in two dynamically-allocated arrays
    int numOfStations;
    int numOfTrips;
    
    inputStationsFile >> numOfStations;
    inputBikeTripsFile >> numOfTrips;
    
    stationInfo* stations = new stationInfo[numOfStations];
    tripInfo* trips = new tripInfo[numOfTrips];
    
    storeStationValues(inputStationsFile, stations, numOfStations);
    storeBikeTripValues(inputBikeTripsFile, trips, numOfTrips);
    
    // closing files after storing in the two arrays
    inputStationsFile.close(); 
    inputBikeTripsFile.close();
    
    // (3) getting userCommand and executing them until they enter "#"
    string userCommand = "";
    while(userCommand != "#"){
        cout << "Enter command (# to stop)> ";
        
        cin >> userCommand;

        if (userCommand == "#") {
            break; // exits loop
        } else if (userCommand == "stats") {
            quickStats(numOfStations, numOfTrips, stations);
        } else if (userCommand == "durations") {
            durations(numOfTrips, trips);
        } else if (userCommand == "starting") {
            startingTimes(numOfTrips, trips);
        } else if (userCommand == "nearme") {
            stationsNearMe(stations, numOfStations);
        } else if (userCommand == "stations") {
            listAllStations(stations, trips, numOfStations, numOfTrips);
        } else if (userCommand == "find") {
            findStations(stations, trips, numOfStations, numOfTrips);
        } else if (userCommand == "trips") {
            tripsInTimeSpan(stations, trips, numOfStations, numOfTrips);
        } else {
            cout << "** Invalid command, try again..." << endl;
        }
    }
    cout << "** Done **" << endl;
    
    delete[] stations;
    delete[] trips;
    return 0;
    
}