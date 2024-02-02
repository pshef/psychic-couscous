package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	// Check number of arguments
	if len(os.Args) != 3 {
		fmt.Println("Invalid arguments!")
		fmt.Println("Usage: ", os.Args[0], " <hour> <AM or PM>")
		os.Exit(1)
	}

	// Set variables from arguments
	hour, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("Invalid arguments! Please use a number")
		fmt.Println("Usage: ", os.Args[0], " <hour> <AM or PM>")
		os.Exit(1)
	}
	day_night := os.Args[2]

	// Check if arguments are correctly formatted
	if hour > 23 {
		fmt.Println("Invalid arguments \"hour\" does not exist.")
		fmt.Println("Usage: ", os.Args[0], " <hour> <AM or PM>")
		os.Exit(1)
	}

	if (day_night != "PM") && (day_night != "AM") {
		fmt.Println("Invalid arguments! Please use AM or PM")
		fmt.Println("Usage: ", os.Args[0], " <hour> <AM or PM>")
		os.Exit(1)
	}

	// Convert time
	if (day_night == "AM") && (hour > 12) {
		fmt.Println("Invalid arguments! Hours 13 - 23 are PM")
		fmt.Println("Usage: ", os.Args[0], " <hour> <AM or PM>")
		os.Exit(1)
	} else if (hour == 12) && (day_night == "AM") {
		fmt.Println("Invalid auments! Please use 00 for midnight")
		fmt.Println("Usage: ", os.Args[0], " <hour> <AM or PM>")
		os.Exit(1)
	} else if day_night == "PM" {
		new_hour := hour + 12
		utc := new_hour + 6
		if utc > 23 {
			fmt.Println(utc-24, " AM UTC the next day")
		} else {
			fmt.Println(utc, " PM UTC")
		}
	} else {
		utc := hour + 6
		if utc >= 12 {
			fmt.Println(utc, " PM UTC")
		} else {
			fmt.Println(utc, " AM UTC")
		}
	}
}
