
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Constant Seats var
#define SEATS 24
// Name length of 50 chars (Will sanity check inputs later for edge cases)
#define NAME_LEN 50

struct seat {
    int seatID;
    int assigned;  // 0 = empty, 1 = assigned
    char lastName[NAME_LEN];
    char firstName[NAME_LEN];
};

typedef struct seat Seat;

/* Function prototypes */
void intialize(Seat flight[]);
void flightMenu(Seat flight[], const char flightName[]);
void showEmptyCount(Seat flight[]);
void showEmptySeats(Seat flight[]);
void showAlphabeticalList(Seat flight[]);
void assignSeat(Seat flight[]);
void deleteSeat(Seat flight[]);
void clearInput(void);
int readInteger(const char *prompt, int min, int max);
int comparePassengers(const void *a, const void *b);

/* Initialize all 24 seats */
void intialize(Seat flight[])
{
    for (int i = 0; i < SEATS; i++) {
        flight[i].seatID = i + 1;
        flight[i].assigned = 0;
        flight[i].lastName[0] = '\0';
        flight[i].firstName[0] = '\0';
    }
}

/* Clear remaining characters from input */
void clearInput(void)
{
    int ch;
    // Go thru input and clear it out
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

/* Read an integer safely */
int readInteger(const char *prompt, int min, int max)
{
    int value;

    while (1) {
        printf("%s", prompt);

        if (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInput();
            continue;
        }

        clearInput();

        if (value >= min && value <= max) {
            return value;
        }

        printf("Enter a number from %d to %d.\n", min, max);
    }
}


/* Display the number of empty seats */
void showEmptyCount(Seat flight[])
{
    int count = 0;
    for (int i = 0; i < SEATS; i++) {
        if (flight[i].assigned == 0) {
            count++;
        }
    }

    printf("\nEmpty seats: %d out of %d\n", count, SEATS);
}

/* Display the IDs of empty seats */
void showEmptySeats(Seat flight[])
{
    // Flag to trigger a 'no empty seats' notification in case all seats are occupied
    int found = 0;

    printf("\nEmpty seat IDs:\n");
    for (int i = 0; i < SEATS; i++) {
        if (flight[i].assigned == 0) {
            printf("%d ", flight[i].seatID);
            found = 1;
        }
    }
    if (!found) {
        printf("All seats filled");
    }

    printf("\n");
}


/* Display assigned passengers alphabetically */

void showAlphabeticalList(Seat flight[])
{
    Seat passengers[SEATS];
    Seat temp;
    int count = 0;

    // Copy assigned passengers into a temporary array 
    for (int i = 0; i < SEATS; i++) {
        if (flight[i].assigned == 1) {
            passengers[count] = flight[i];
            count++;
        }
    }

    // Check whether there are any passengers 
    if (count == 0) {
        printf("\nNo passengers are assigned to this flight.\n");
        return;
    }

    // Sort alphabetically by last name, then first name 
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {

            int result = strcmp(passengers[j].lastName,
                                passengers[j + 1].lastName);

            if (result == 0) {
                result = strcmp(passengers[j].firstName,
                                passengers[j + 1].firstName);
            }

            if (result > 0) {
                temp = passengers[j];
                passengers[j] = passengers[j + 1];
                passengers[j + 1] = temp;
            }
        }
    }

    /* Display the sorted passenger list */
    printf("\n%-10s %-20s %-20s\n",
           "Seat ID", "Last Name", "First Name");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10d %-20s %-20s\n",
               passengers[i].seatID,
               passengers[i].lastName,
               passengers[i].firstName);
    }
}


/* Read a nonempty name, allowing cancellation
I was lowkey having issues with scanf so I used fgets instead after looking online */
int readName(const char *prompt, char name[], size_t size)
{
    while (1) {
        printf("%s", prompt);

        if (fgets(name, size, stdin) == NULL) {
            return 0;
        }

        if (strchr(name, '\n') == NULL) {
            clearInput();
            printf("Name is too long. Try again.\n");
            continue;
        }

        name[strcspn(name, "\n")] = '\0';

        if (strcmp(name, "0") == 0) {
            return 0;
        }

        if (name[0] == '\0') {
            printf("Name cannot be empty. Enter 0 to cancel.\n");
            continue;
        }

        return 1;
    }
}

/* Assign a passenger to a seat */
void assignSeat(Seat flight[])
{
    int seatID;
    char first[NAME_LEN];
    char last[NAME_LEN];

    showEmptySeats(flight);

    seatID = readInteger(
        "\nEnter seat ID to assign (1-24), or 0 to cancel: ",
        0, SEATS);

    if (seatID <= 0) {
        printf("Assignment cancelled.\n");
        return;
    }

    if (flight[seatID - 1].assigned == 1) {
        printf("Seat %d is already assigned.\n", seatID);
        return;
    }

    printf("Enter 0 at either name prompt to cancel.\n");

    if (!readName("Enter passenger first name: ",
                  first, sizeof(first))) {
        printf("Assignment cancelled.\n");
        return;
    }

    if (!readName("Enter passenger last name: ",
                  last, sizeof(last))) {
        printf("Assignment cancelled.\n");
        return;
    }

    flight[seatID - 1].assigned = 1;
    strcpy(flight[seatID - 1].firstName, first);
    strcpy(flight[seatID - 1].lastName, last);

    printf("Seat %d successfully assigned to %s %s.\n",
           seatID, first, last);
}

/* Delete an existing seat assignment */
void deleteSeat(Seat flight[])
{
    int seatID;

    seatID = readInteger(
        "\nEnter seat ID to delete (1-24), or 0 to cancel: ",
        0, SEATS);

    if (seatID <= 0) {
        printf("Deletion cancelled.\n");
        return;
    }

    printf("Passenger: %s %s (Seat %d)\n",
           flight[seatID - 1].firstName,
           flight[seatID - 1].lastName,
           seatID);

    printf("Delete this assignment? (y/n): ");

    char answer[20];

    if (fgets(answer, sizeof(answer), stdin) == NULL) {
        return;
    }

    if (tolower((unsigned char)answer[0]) != 'y') {
        printf("Deletion cancelled.\n");
        return;
    }

    flight[seatID - 1].assigned = 0;
    flight[seatID - 1].firstName[0] = '\0';
    flight[seatID - 1].lastName[0] = '\0';

    printf("Seat %d assignment deleted successfully.\n", seatID);
}

/* Second-level menu for a selected flight */
void flightMenu(Seat flight[], const char flightName[])
{
    int choice;

    do {
        printf("\n===== %s =====\n", flightName);
        printf("a) Show number of empty seats\n");
        printf("b) Show list of empty seats\n");
        printf("c) Show alphabetical list of seats\n");
        printf("d) Assign a customer to a seat\n");
        printf("e) Delete a seat assignment\n");
        printf("f) Return to Main Menu\n");

        printf("Select an option: ");

        char input[100];

        if (fgets(input, sizeof(input), stdin) == NULL) {
            return;
        }

        choice = tolower((unsigned char)input[0]);

        switch (choice) {
            case 'a':
                showEmptyCount(flight);
                break;

            case 'b':
                showEmptySeats(flight);
                break;

            case 'c':
                showAlphabeticalList(flight);
                break;

            case 'd':
                assignSeat(flight);
                break;

            case 'e':
                deleteSeat(flight);
                break;

            case 'f':
                printf("Returning to Main Menu...\n");
                break;

            default:
                printf("Invalid option. Please choose a-f.\n");
        }

    } while (choice != 'f');
}

/* Main program */
int main(void)
{
    Seat outbound[SEATS];
    Seat inbound[SEATS];
    char choice;

    intialize(outbound);
    intialize(inbound);

    do {
        printf("\n===== COLOSSUS AIRLINES =====\n");
        printf("a) Outbound Flight\n");
        printf("b) Inbound Flight\n");
        printf("c) Quit\n");
        printf("Select an option: ");

        char input[100];

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        choice = tolower((unsigned char)input[0]);

        switch (choice) {
            case 'a':
                flightMenu(outbound, "Outbound Flight");
                break;

            case 'b':
                flightMenu(inbound, "Inbound Flight");
                break;

            case 'c':
                printf("Thank you for using Colossus Airlines!\n");
                break;

            default:
                printf("Invalid option. Please choose a, b, or c.\n");
        }

    } while (choice != 'c');

    return 0;
}
