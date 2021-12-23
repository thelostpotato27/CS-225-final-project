import csv
from collections import defaultdict

flight_dict = defaultdict(lambda: [0,0,0,0,0])
code_to_city = defaultdict(lambda: None) # store airport code -> city

# flight dict format: key is (city1, city2) where city1 < city2
# value is array of [number of dist/time records, dist sum, time sum, number of costs, cost sum]

# city dict format: key is city name as in our final output
# value is set of airport codes associated with that city

with open('datasets/FlightTimeDataOriginal.csv', newline='') as csvfile: # open time/distance file
    csv_reader = csv.reader(csvfile)
    next(csv_reader) # skip header
    for row in csv_reader:
        if not all(row[:-1]):
            continue
        startCity = row[1].split(',')[0] 
        endCity = row[3].split(',')[0] # strip out state names
        flightID = tuple(sorted([startCity, endCity]))
        flight_dict[flightID][0] += 1 # increase num of flights between these cities
        flight_dict[flightID][1] += float(row[5])
        flight_dict[flightID][2] += float(row[4])
        code_to_city[row[0]] = startCity
        code_to_city[row[2]] = endCity

with open('datasets/cost_data.csv', newline = '') as csvfile_cost:
    csv_reader = csv.reader(csvfile_cost)
    next(csv_reader)
    for row in csv_reader:
        if not all(row[:3]):
            continue
        if row[0] not in code_to_city:
           # print("code for " + row[0] + " not found")
            continue
        if row[1] not in code_to_city:
            #print("code for " + row[1] + " not found")
            continue
        flightID = tuple(sorted([code_to_city[row[0]], code_to_city[row[1]]]))
        flight_dict[flightID][3] += 1
        flight_dict[flightID][4] += float(row[2])

actually_used_cities = set()
edgecnt = 0

with open('Edge_Data.csv', mode = 'w', newline='') as csv_output:
    csv_writer = csv.writer(csv_output)
    csv_writer.writerow(["City1", "City2", "Distance", "Time", "Cost"])
    for flightID, flightdata in sorted(flight_dict.items()):
        if flightdata[0] == 0:
            print("no dist/time data for flights between " + str(flightID) + ", skipping")
            continue
        if flightdata[3] == 0:
            print("no cost data for flights between " + str(flightID) + ", skipping")
            continue
        row = list(flightID)
        actually_used_cities.add(row[0])
        actually_used_cities.add(row[1])
        row.append(int(round(flightdata[1]/flightdata[0])))
        row.append(int(round(flightdata[2]/flightdata[0])))
        row.append(int(round(flightdata[4]/flightdata[3])))
        csv_writer.writerow(row)
        edgecnt += 1


latlongdict = defaultdict(lambda: [0, 0, 0]) # will store city name -> coords count, lat sum, long sum

with open("datasets/airports.csv", newline = '') as csvfile_latlong:
    csv_reader = csv.reader(csvfile_latlong)
    next(csv_reader)
    for row in csv_reader:
        if row[4] in code_to_city:
            city = code_to_city[row[4]]
            if city not in actually_used_cities:
                continue
            latlongdict[city][0] += 1
            latlongdict[city][1] += float(row[6])
            latlongdict[city][2] += float(row[7])

with open("datasets/airports_manual.csv", newline = '') as csvfile_latlong_manual:
    csv_reader = csv.reader(csvfile_latlong_manual)
    next(csv_reader)
    for row in csv_reader:
            latlongdict[row[0]] = [1, float(row[1]), float(row[2])]

with open('Node_Data.csv', mode = 'w', newline='') as csv_output:
    csv_writer = csv.writer(csv_output)
    csv_writer.writerow(["City", "Latitude", "Longitude"])
    for city, latlongdata in sorted(latlongdict.items()):
        csv_writer.writerow([city, round(latlongdata[1]/latlongdata[0],3), round(latlongdata[2]/latlongdata[0],3)])

for city in actually_used_cities:
    if city not in latlongdict:
        print(city + " missing from latitude/longitude dataset")

print("Summary:")
print("Number of edges/flights found: " + str(edgecnt))
print("Number of nodes/cities found: " + str(len(actually_used_cities)))