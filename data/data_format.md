### Data format
Our edge data is in Edge_Data.csv, and has the following columns:
- "City1" and "City2" are the names of cities on either end of each flight.
- We treat flights as non-directed, so we should not have both a flight from Austin->Houston and Houston->Austin. Having either order is fine though.
- Distance is the flight distance in miles, rounded to the nearest mile.
- Time is the flight time in minutes, rounded to the nearest minute.
- Cost is the flight cost in USD, rounded to the nearest dollar.

Our Node data is in Node_Data.csv, and has the following columns:
- "Name" is the name of a city.
- "Latitude" is its latitude as a floating point number. Negative means south, positive means north.
- "Longitude" is its longitude as a floating point number. Negative means west, positive means east.

Every city that is a destination or origin city of a flight in the edge data file should have a corresponding row in the node data file.
Cities should have their first letter capitalized and every other letter lowercase for searching functionality to work properly.
The graph specified by the node and edge files should be a completely connected graph with just 1 component.