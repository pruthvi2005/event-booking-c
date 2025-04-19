#include<stdio.h>
#include<string.h>

// Structure to store event details
struct Event {
    char name[50];
    char date[20];
    char time[20];
    char venue[50];
    char organizer[50];
};

// Functions declaration
void bookEvent();
void viewBookings();
void cancelBooking();

int main() {
    int choice;
    while(1) {
      printf("\n welcome to Dr.T.Thimmaiah Institute of Technology to event booking system\n");
        printf("\nCollege Event Booking System\n");
        printf("1. Book an Event\n");
        printf("2. View All Bookings\n");
        printf("3. Cancel a Booking\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: bookEvent(); break;
            case 2: viewBookings(); break;
            case 3: cancelBooking(); break;
            case 4: printf("Exiting..."); return 0;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

// Add function definitions here based on your requirements

void bookEvent() {
    // Function to void bookEvent() {
    struct Event e;
    FILE *file = fopen("events.txt", "a"); // Open file in append mode
    
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Event Name: ");
    scanf(" %[^\n]", e.name); // Read input with spaces
    printf("Enter Date (DD-MM-YYYY): ");
    scanf(" %[^\n]", e.date);
    printf("Enter Time (HH:MM): ");
    scanf(" %[^\n]", e.time);
    printf("Enter Venue: ");
    scanf(" %[^\n]", e.venue);
    printf("Enter Organizer Name: ");
    scanf(" %[^\n]", e.organizer);

    fprintf(file, "%s|%s|%s|%s|%s\n", e.name, e.date, e.time, e.venue, e.organizer);
    printf("Event booked successfully!\n");

    fclose(file); // Close file
}


void viewBookings() {
  struct Event e;
  FILE *file = fopen("events.txt", "r"); // Open file in read mode
  
  if (file == NULL) {
      printf("No bookings found! Please ensure the file exists and contains valid data.\n");
      return;
  }

  printf("\nList of Events:\n");
  printf("---------------------------------------------------\n");
  
  while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", e.name, e.date, e.time, e.venue, e.organizer) != EOF) {
      printf("Event Name: %s\nDate: %s\nTime: %s\nVenue: %s\nOrganizer: %s\n", e.name, e.date, e.time, e.venue, e.organizer);
      printf("---------------------------------------------------\n");
  }

  fclose(file); // Close file
}

void cancelBooking() {
  struct Event e;
  char targetName[50];
  int found = 0;

  FILE *file = fopen("events.txt", "r");
  FILE *tempFile = fopen("temp.txt", "w");

  if (file == NULL || tempFile == NULL) {
      printf("Error opening file!\n");
      return;
  }

  printf("Enter the name of the event to cancel: ");
  scanf(" %[^\n]", targetName);

  while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", e.name, e.date, e.time, e.venue, e.organizer) != EOF) {
      if (strcmp(e.name, targetName) == 0) {
          found = 1;
          printf("Event '%s' canceled successfully!\n", e.name);
      } else {
          fprintf(tempFile, "%s|%s|%s|%s|%s\n", e.name, e.date, e.time, e.venue, e.organizer);
      }
  }

  fclose(file);
  fclose(tempFile);

  remove("events.txt"); // Delete original file
  rename("temp.txt", "events.txt"); // Rename temp file to original

  if (!found) {
      printf("No event found with the name '%s'.\n", targetName);
  }
}
