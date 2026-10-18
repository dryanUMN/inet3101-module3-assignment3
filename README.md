# INET 3101 Module 3 Assignment 3
Source Code for Module 3 Assignment 3

## Program Description
This program manages seat assignments by allowing users to view empty seats, list assigned passengers alphabetically, assign passengers to seats, and delete existing assignments.

## Struct and menu Design 
It uses a structure named Seat to represent an individual seat.

The structure contains four fields:
seatID: The seat number, from 1 to 24.
assigned: An assignment status marker (0 for empty, 1 for assigned).
lastName: The passenger's last name.
firstName: The passenger's first name.

Two separate arrays store the seat information for each flight:
Seat outbound[SEATS];
Seat inbound[SEATS];

The initializeSeats() function initializes all seats as empty and assigns seat IDs from 1 through 24. Uses 2 seperate arrays so that changes to one flight do not affect the other.

Menu is a Basic 2 level text interface.
First menu contains flight selection options, second menu contains options for viewing or editing seat assignment of that flight

## Input Stream and Buffer Analysis

Uses a for loop and getchar() in the clearInput() function to clear the input stream out when input is not validated.
scanf() is used when reading input ints
ended up using fgets() for reading input text because it handles the newline character better between inputs

The buffer clear with clearInput() works with scanf after reading int inputs by clearing the new line character, so that the left over new line char doesn't interfere with the next input.

## AI test harness

Prompt used to generate the test_input.txt file is below: 

using the attached solution.c file, follow the instructions in brackets below and create a test batch file

[AI Harness Generation: Prompt an AI to construct a comprehensive batch test script file named test_input.txt. The test file must simulate automated rapid menu navigation and edge cases, including:
- Attempting to assign an already occupied seat.
- Entering names with spaces or exceeding string buffer limits.
- Attempting to delete an unassigned seat.
- Aborting an entry midway through choice `d` or `e`.
- Invalid menu selections at both menu levels.
]

This test file pointed out the intial flaws in my input buffer handling that I since fixed after a bit of troubleshooting.
It also helped me clean up the menu formatting, as the output file was noticeably hard to read lol.