#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mainMenu();
void registerUser();
int loginUser(char uname[]);
void userMenu(char uname[]);
void bookTicket(char uname[]);
void cancelTicket();
void showBuses();
void logoutReport(char uname[]);
void systemReport();
void printLine();
void wait();

int maxUsers = 20;
int maxBuses = 5;


int busNo[5] = {101, 102, 103, 104, 105};
char fromCity[5][20] = {"Delhi", "Lucknow", "Mumbai", "Chennai", "Kolkata"};
char toCity[5][20] = {"Bihar", "Kanpur", "Pune", "Nagla", "Patna"};
float fare[5] = {500, 450, 600, 700, 550};
int totalSeats[5] = {40, 40, 40, 40, 40};
int availableSeats[5] = {40, 40, 40, 40, 40};


char usernames[20][50];
char passwords[20][30];
int userCount = 0;

float totalRevenue = 0.0;
float userBaseFare = 0.0, userGST = 0.0, userTotal = 0.0;


int bookedBusNo[10];
int bookedSeats[10];
float bookedTotal[10];
int bookedCount = 0;

int main() {
    mainMenu();
    return 0;
}

void printLine() {
    printf("--------------------------------------------------\n");
}

void wait() {
    printf("\nPress ENTER to continue...");
    while (getchar() != '\n'); 
}

void mainMenu() {
    int choice;
    while (1) {
        system("cls"); 
        printLine();
        printf("      BUS RESERVATION SYSTEM\n");
        printLine();
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printLine();
        printf("Enter choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2: {
                char uname[50];
                if (loginUser(uname))
                    userMenu(uname);
                break;
            }
            case 3:
                systemReport();
                exit(0);
            default:
                printf("\nInvalid choice!\n");
                wait();
        }
    }
}

void registerUser() {
    system("cls");
    printLine();
    printf("USER REGISTRATION\n");
    printLine();

    if (userCount >= maxUsers) {
        printf("Registration limit reached!\n");
        wait();
        return;
    }

    printf("Enter full name: ");
    fgets(usernames[userCount], 50, stdin);
    usernames[userCount][strcspn(usernames[userCount], "\n")] = '\0';

    printf("Enter password: ");
    fgets(passwords[userCount], 30, stdin);
    passwords[userCount][strcspn(passwords[userCount], "\n")] = '\0';

    userCount++;
    printf("\nRegistration Successful!\n");
    wait();
}

int loginUser(char uname[]) {
    system("cls");
    char pass[30];
    printLine();
    printf("USER LOGIN\n");
    printLine();

    printf("Enter full name: ");
    fgets(uname, 50, stdin);
    uname[strcspn(uname, "\n")] = '\0';

    printf("Enter password: ");
    fgets(pass, 30, stdin);
    pass[strcspn(pass, "\n")] = '\0';

    for (int i = 0; i < userCount; i++) {
        if (strcmp(uname, usernames[i]) == 0 && strcmp(pass, passwords[i]) == 0) {
            printf("\nWelcome, %s!\n", uname);
            wait();
            return 1;
        }
    }

    printf("\nInvalid username or password!\n");
    wait();
    return 0;
}

void userMenu(char uname[]) {
    int choice;
    userBaseFare = userGST = userTotal = 0.0;
    bookedCount = 0;

    while (1) {
        system("cls");
        printLine();
        printf("USER MENU - %s\n", uname);
        printLine();
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. Check Bus Status\n");
        printf("4. Logout (Show Report)\n");
        printLine();
        printf("Enter choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                bookTicket(uname);
                break;
            case 2:
                cancelTicket();
                break;
            case 3:
                showBuses();
                break;
            case 4:
                logoutReport(uname);
                printf("\nLogged out successfully!\n");
                wait();
                return;
            default:
                printf("\nInvalid choice!\n");
                wait();
        }
    }
}

void showBuses() {
    system("cls");
    printLine();
    printf("AVAILABLE BUSES\n");
    printLine();
    printf("BusNo  From\t   To\t     Fare\tSeats Left\n");
    printLine();

    for (int i = 0; i < maxBuses; i++) {
        printf("%d\t%-10s %-10s %.2f\t%d\n",
               busNo[i], fromCity[i], toCity[i], fare[i], availableSeats[i]);
    }
    wait();
}

void bookTicket(char uname[]) {
    int bno, seats;
    float base, gst, total;

    showBuses();
    printf("\nEnter Bus Number to Book: ");
    scanf("%d", &bno);
    printf("Enter Number of Seats: ");
    scanf("%d", &seats);
    while (getchar() != '\n');

    for (int i = 0; i < maxBuses; i++) {
        if (busNo[i] == bno) {
            if (seats > 0 && availableSeats[i] >= seats) {
                base = fare[i] * seats;
                gst = base * 0.18;
                total = base + gst;

                availableSeats[i] -= seats;
                userBaseFare += base;
                userGST += gst;
                userTotal += total;
                totalRevenue += total;

                bookedBusNo[bookedCount] = bno;
                bookedSeats[bookedCount] = seats;
                bookedTotal[bookedCount] = total;
                bookedCount++;

                printf("\nBooking Successful!\n");
                printf("Bus %d: %s to %s\n", busNo[i], fromCity[i], toCity[i]);
                printf("Seats: %d | Base: %.2f | GST: %.2f | Total: %.2f\n",
                       seats, base, gst, total);
                wait();
                return;
            } else {
                printf("\nNot enough seats available!\n");
                wait();
                return;
            }
        }
    }

    printf("\nInvalid Bus Number!\n");
    wait();
}

void cancelTicket() {
    int bno, seats;

    showBuses();
    printf("\nEnter Bus Number to Cancel: ");
    scanf("%d", &bno);
    printf("Enter Number of Seats to Cancel: ");
    scanf("%d", &seats);
    while (getchar() != '\n');

    for (int i = 0; i < maxBuses; i++) {
        if (busNo[i] == bno) {
            if (availableSeats[i] + seats <= totalSeats[i]) {
                availableSeats[i] += seats;
                printf("\n%d Seats Cancelled Successfully!\n", seats);
                wait();
                return;
            } else {
                printf("\nInvalid seat count!\n");
                wait();
                return;
            }
        }
    }

    printf("\nBus not found!\n");
    wait();
}

void logoutReport(char uname[]) {
    system("cls");
    printLine();
    printf("USER LOGOUT REPORT\n");
    printLine();
    printf("User Name: %s\n", uname);
    printLine();
    printf("BusNo | Seats | Total Fare (With GST)\n");
    printLine();

    if (bookedCount == 0) {
        printf("No bookings done.\n");
    } else {
        for (int i = 0; i < bookedCount; i++) {
            printf("%5d | %5d | %.2f\n", bookedBusNo[i], bookedSeats[i], bookedTotal[i]);
        }
    }

    printLine();
    printf("Total Base Fare: %.2f\n", userBaseFare);
    printf("GST (18%%): %.2f\n", userGST);
    printf("Grand Total: %.2f\n", userTotal);
    printLine();
}

void systemReport() {
    system("cls");
    printLine();
    printf("SYSTEM FINAL REPORT\n");
    printLine();
    printf("Total Users Registered: %d\n", userCount);
    printf("Total Revenue (With GST): %.2f\n", totalRevenue);
    printLine();
}
