#!/usr/bin/python3

import sys

# Check inputs
if len(sys.argv) != 3:
    print("Missing arguments!")
    print("Usage: cstToUtc.py <hour> <AM or PM>")
    exit()

# Set variables from inputs
hour = int(sys.argv[1])
dayNight = str(sys.argv[2])

# Check if arguments are correct
if not isinstance(hour, int) or hour > 23:
    print("Invalid arguments! \"Hour\" does not exist.")
    print("Usage: cstToUtc.py <hour> <AM or PM>")
    exit()

if dayNight != "PM" and dayNight != "AM":
    print("Invalid arguments! Please use AM or PM.")
    print("Usage: cstToUtc.py <hour> <Am or PM>")
    exit()

# Convert time 
if dayNight == str("PM"):
    NewHour = int(hour) + 12
    UTC = NewHour + 6
    if UTC > 23:
        print(f"{UTC - 24} AM UTC the next day")
    else:
        print(f"{UTC} PM UTC")
else:
    UTC = int(hour) + 6
    if UTC >= 12:
        print(f"{UTC} PM UTC")
    else:
        print(f"{UTC} AM UTC")
