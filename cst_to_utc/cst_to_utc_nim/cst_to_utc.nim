import std/os
import std/strutils

# echo paramCount(), " ", paramStr(1)

# Check number of arguments
if paramCount() != 2:
  echo "Invalid arguments!"
  echo "Usage: ", paramStr(0), " <hour> <AM or PM>"
  quit()

# Set variables from arguments
var hour: int = parseInt(paramStr(1))
var day_night: string = paramStr(2)

# Check if arguments are correct
if hour > 23:
  echo "Invalid arguments! \"hour\" does not exist"
  echo "Usage: ", paramStr(0), " <hour> <AM or PM>"
  quit()

if day_night != "AM" and day_night != "PM":
  echo "Invalid arguments! Please use AM or PM"
  echo "Usage: ", paramStr(0), " <hour> <AM or PM>"
  quit()

# Convert time
if day_night == "PM":
  var new_hour: int = hour + 12
  var utc: int = new_hour + 6
  if utc > 23:
    echo utc - 24, " AM UTC the next day"
  else:
    echo utc, " PM UTC"
else:
  var utc: int = hour + 6
  if utc >= 12:
    echo utc, " PM UTC"
  else:
    echo utc, " AM UTC"
