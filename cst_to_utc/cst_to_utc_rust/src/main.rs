use std::env;
use std::process::exit;

fn main() {
    // Collects arguments
    let args: Vec<String> = env::args().collect();

    // Checks number of arguments
    if args.len() != 3 {
        println!("Invalid arguments!");
        println!(">> {} <hour> <AM or PM>", args[0]);
        exit(1);
    };

    // Sets hour argument and verifies if it's valid
    let hour: i32 = args[1].as_str().trim().parse().expect("Not a number");
    if (0..24).contains(&hour) {
    } else {
        panic!(
            "Invalid arguments! \"hour\" does not exist.\n\
            >> Usage: {} <hour> <AM or PM>",
            args[0]
        );
    };

    // Sets AM/PM argument and verifies if it's valid
    let day_night: &str = args[2].as_str();
    if (day_night.eq("PM")) || (day_night.eq("AM")) {
    } else {
        panic!(
            "Invalid arguments! Please use AM or PM.\n\
            >> Usage: {} <hour> <AM or PM>",
            args[0]
        );
    };

    // Converts the time
    if day_night == "PM" {
        let new_hour = hour + 12;
        let utc = new_hour + 6;
        if utc > 23 {
            println!("{} AM UTC the next day", utc - 24)
        } else {
            println!("{} PM UTC", utc)
        };
    } else {
        let utc = hour + 6;
        if utc >= 12 {
            println!("{} PM UTC", utc)
        } else {
            println!("{} AM UTC", utc)
        }
    };
}
