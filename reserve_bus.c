#include <stdio.h>
#include <string.h>

char username[10][25];
int password[10];
int usercount = 0;

int loginmenu() {
    int choice;
    printf("\n========= Login Menu ===========\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // clear newline
    return choice;
}

int usermenu() {
    int choice;
    printf("\n======== User Menu ===========\n");
    printf("1. Book Ticket\n");
    printf("2. Cancel Ticket\n");
    printf("3. Check Bus Status\n");
    printf("4. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();
    return choice;
}

void registration() {
    printf("\nEnter your username: ");
    getchar(); // clear leftover newline
    fgets(username[usercount], sizeof(username[usercount]), stdin);
    username[usercount][strcspn(username[usercount], "\n")] = '\0'; // remove newline

    printf("Enter your password (number only): ");
    scanf("%d", &password[usercount]);
    getchar();

    printf("Registration successful!\n");
    usercount++;
}

void login_fun() {
    char temp_username[25];
    int temp_password;
    int found = 0;

    printf("\nEnter your username: ");
    getchar(); // clear newline
    fgets(temp_username, sizeof(temp_username), stdin);
    temp_username[strcspn(temp_username, "\n")] = '\0';

    printf("Enter your password: ");
    scanf("%d", &temp_password);
    getchar();

    for (int i = 0; i < usercount; i++) {
        if (strcmp(username[i], temp_username) == 0) {
            if (password[i] == temp_password) {
                printf("\nLogin successful! Welcome %s\n", username[i]);
                found = 1;
                int user_choice;
                do {
                    user_choice = usermenu();
                    switch (user_choice) {
                        case 1:
                            printf("Ticket booked successfully!\n");
                            break;
                        case 2:
                            printf("Ticket cancelled!\n");
                            break;
                        case 3:
                            printf("All buses are running on time.\n");
                            break;
                        case 4:
                            printf("Logged out successfully.\n");
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                } while (user_choice != 4);
                break;
            } else {
                printf("Wrong password!\n");
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Username not found!\n");
    }
}

int main() {
    int number;
    do {
        number = loginmenu();
        switch (number) {
            case 1:
                login_fun();
                break;
            case 2:
                registration();
                break;
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (number != 3);

    return 0;
}
  