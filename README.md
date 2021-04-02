# DIVVYdata

Project: Analyzing DIVVY data
Author: Mirza MK Baig
Date: 3/9/2021

The program analyzes the DIVYY bike trips data and stations. It stores the stations data and bike trips data
in dynamically allocated arrays. It does the following operations when user enters a specific command until user inputs "#".
1. Quick statistics (command: stats)
2. Summary of bike duration (command: durations)
3. Histogram of starting times (command: starting)
4. Stations near me (example command: nearme 41.87 -87.66 0.8) Lists stations by ascending order of distance near given position.
5. List all stations (command: stations)
6. Find stations (example command: find Park). Lists stations alphabetically that contains case-sensitive string in station's name. 
7. Find trips within timespan (example command: trips 2:00 5:00)

There is a sample biketrips and stations file included. The data is gathered from DIVVY bike data released by the city of Chicago.
