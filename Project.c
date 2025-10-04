#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Movie {
    char title[50];
    int release_year;
    char genre[50];
    float rating;
};

void add_movie(FILE *f) {
    struct Movie M;
    printf("Enter movie title: ");
    scanf(" %[^\n]", M.title);
    printf("Enter release year: ");
    scanf("%d", &M.release_year);
    printf("Enter genre: ");
    scanf(" %[^\n]", M.genre);
    printf("Enter rating: ");
    scanf("%f", &M.rating);
    fprintf(f, "%s,%d,%s,%.2f\n", M.title, M.release_year, M.genre, M.rating);
    printf("Movie '%s' added successfully.\n", M.title);
}

void display_movie(FILE *f) {
    rewind(f);
    struct Movie movies[100];
    int count = 0;

    while (fscanf(f, "%49[^,],%d,%49[^,],%f\n", movies[count].title,
				&movies[count].release_year, movies[count].genre, &movies[count].rating) == 4) {
        count++;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (movies[j].rating < movies[j + 1].rating) {
                struct Movie temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }

	printf("\n");
    printf("\tTop 5 movies based on rating:\n");
	printf("\t\n");
    printf("\tMovie   : Title , Year , Genre , Rating\n");
    printf("\t------------------------------------------------------\n");
    for (int i = 0; i < count && i < 5; i++) {
        printf("\tMovie %d : %s,%d,%s,%.2f\n",i+1, movies[i].title, movies[i].release_year, movies[i].genre, movies[i].rating);
        printf("\t------------------------------------------------------\n");
    }
}

void search_movie_by_genre(FILE *f) {
    char genre[50];
    struct Movie m;
    int found = 0;
    rewind(f);
    
	printf("\tEnter genre to search: ");
    scanf(" %[^\n]", genre);
    printf("\n");
    printf("\t\tMovies in genre : '%s':\n", genre);
    printf("\n");
    printf("\t\tTitle , Year , Genre , Rating\n");
    printf("\t\t------------------------------------------------------\n");
    while (fscanf(f, "%49[^,],%d,%49[^,],%f\n", m.title, &m.release_year, m.genre, &m.rating) == 4) {
        if (strcmp(m.genre, genre) == 0) {
            printf("\t\t%s,%d,%s,%.2f\n", m.title, m.release_year, m.genre, m.rating);
    		printf("\t\t------------------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No movies in genre '%s' found.\n", genre);
    }
}

void search_movie_by_year(FILE *f) {
    int release_year;
    struct Movie m;
    int found = 0;
    rewind(f);
    
	printf("\tEnter release year to search: ");
    scanf("%d", &release_year);
    printf("\n");
	printf("\t\tMovies released in %d:\n", release_year);
	printf("\n");
    printf("\t\tTitle , Year , Genre , Rating\n");
	printf("\t\t------------------------------------------------------\n");
    while (fscanf(f, "%49[^,],%d,%49[^,],%f\n", m.title, &m.release_year, m.genre, &m.rating) == 4) {
        if (m.release_year == release_year) {
            printf("\t\t%s,%d,%s,%.2f\n", m.title, m.release_year, m.genre, m.rating);
            printf("\t\t------------------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No movies released in %d found.\n", release_year);
    }
}

void book_ticket(FILE *f) {
    char title[50];
    struct Movie m;
    int found = 0;
    rewind(f); 
    printf("Enter the title of the movie to book tickets: ");
    scanf(" %[^\n]", title);
    while (fscanf(f, "%49[^,],%d,%49[^,],%f\n", m.title, &m.release_year, m.genre, &m.rating) == 4) {
        if (strcmp(m.title, title) == 0) {
        	printf("\n");
            printf("\tMovie Details : Title : %s , Release Year : %d , Genre : %s , Rating : %.2f\n",m.title,m.release_year,m.genre, m.rating);
            found = 1;
            break;
        }
    }
	if (!found) {
        printf("Movie '%s' not found.\n", title);
    } else {
        char name[50], card_id[20], password[20];
        int num_tickets, x,i;
        float total_amount = 0.0 , remise = 0.0;
        int choice, s = 0, ticket_less_18, ticket_student, ticket_adult;
		printf("\n");
        printf("\t----------------Tarif-----------------\n");
        printf("\tTicket For less than 18 years old: $13\n");
		printf("\tTicket For Students : $15\n");
		printf("\tTicket For Adults  : $17\n");
        printf("\t--------------------------------------\n");
        printf("\t(If you buy 5 tickets, You benefit from a Super Cinema Ticket with a 10%% discount on the total amount.)\n");   
		printf("\n");
        printf("Do you like to get a ticket (Yes/Not) : \n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
				printf("Enter the number of tickets for less than 18 years old: ");
                scanf("%d", &ticket_less_18);
                printf("Enter the number of tickets for students: ");
                scanf("%d", &ticket_student);
                printf("Enter the number of tickets for adults: ");
                scanf("%d", &ticket_adult);
				num_tickets = ticket_less_18 + ticket_student + ticket_adult; 
                while (!(num_tickets > 0 && num_tickets <= 5)) { 
                    printf("Invalid number of tickets. You cannot purchase more than 5 Tichets. Try Again.\n");
                    printf("Enter the number of tickets for less than 18 years old: ");
                    scanf("%d", &ticket_less_18);
                    printf("Enter the number of tickets for students: ");
                    scanf("%d", &ticket_student);
                    printf("Enter the number of tickets for adults: ");
                    scanf("%d", &ticket_adult);
                    num_tickets = ticket_less_18 + ticket_student + ticket_adult; 
                }
                total_amount = ticket_less_18 * 13.0 + ticket_student * 15.0 + ticket_adult * 17.0;
                if (num_tickets == 5) { 
                    total_amount *= 0.9;
                    remise = total_amount * 0.1; 
                }

                FILE *file = fopen("Ticket.txt", "w");
                if (file == NULL) {
                    printf("Error opening file!\n");
                    exit(1);
                }
            	srand(time(NULL));    
                time_t now;
                time(&now);
                struct tm *local = localtime(&now);
                char jour[3], mois[3], annee[5], heure[3], minute[3], seconde[3];
                strftime(jour, 3, "%d", local);
                strftime(mois, 3, "%m", local);
                strftime(annee, 5, "%Y", local);
                strftime(heure, 3, "%H", local);
                strftime(minute, 3, "%M", local);
                strftime(seconde, 3, "%S", local);
                if (num_tickets == 5 ){
                	fprintf(file, "            Super Ticket Cinema         \n");
				}
				else {
					fprintf(file, "               Tickets Cinema         \n");

				}
                fprintf(file, "**********************************************\n");
                fprintf(file, "                  ROOM : %d                   \n", rand() % 10 + 1);
                int random_room = rand() % 100 + 1;
                i=0;
                while (i<num_tickets ) {
                	fprintf(file, "                 Place D-%d              \n", random_room + i);
                    i++;
                }
                fprintf(file, "**********************************************\n");
                fprintf(file, "          Movie Name : %s          \n", m.title);
                fprintf(file, "**********************************************\n");
                fprintf(file, "        Number of ticket = %d tickets \n", num_tickets);
                fprintf(file, "          %d * Tickets <18 ans = $%d\n", ticket_less_18, ticket_less_18 * 13);
                fprintf(file, "          %d * Tickets Students= $%d\n", ticket_student, ticket_student * 15);
                fprintf(file, "          %d * Tickets Adults  = $%d\n", ticket_adult, ticket_adult * 17);
                if (num_tickets == 5) {
                fprintf(file,"       Discount under total   = $%.2f \n" , remise);    
                    fprintf(file, "  Total Amount (After  discount) = $%.2f \n", total_amount);
                } else {
                    fprintf(file, "      Total amount            : $%.2f \n", total_amount);
                }
                fprintf(file, "TICKET Printed on : %s/%s/%s %s:%s    %d \n", jour, mois, annee, heure, minute ,rand() % 100 + 1); //
                fprintf(file, "\n");
                fprintf(file, "KEEP YOUR TICKET UNTIL THE END OF THE SESSION!\n");
                fprintf(file, "     TICKET NOT RETURNED OR EXCHANGED       \n");
                fprintf(file, "**********************************************\n");
                fprintf(file, "              ***GOOD SESSION***          \n");
				fclose(file);
                printf("Ticket printed successfully\n"); //
                system("notepad Ticket.txt");
                break;
			case 2:
                fclose(f);
                exit(0);
            default:
                printf("Invalid choice. Exiting.\n");
                fclose(f);
                exit(1);
        }
    }
}

int main() {
    FILE *Mov;
    Mov = fopen("Movie.txt", "a+");
    int  choice;
    if (Mov == NULL) {
        printf("Error in opening file!\n");
        exit(1);
    }
    printf("\n------------------------------------------------------------------\n");
    printf("\n\t\t     Welcome to Movie Store \n");
    printf("\n------------------------------------------------------------------\n");
	do {
        printf("\n----------------------------Menu----------------------------------\n");
        printf("\n");
        printf("1. Add a Movie :");
        printf("\t2. Display top 5 movies based on rating :\n");
        printf("3. Search movie :");
        printf("\t4. Book Ticket :\n");
        printf("5. Exit\n");
        printf("------------------------------------------------------------------\n");
        printf("\n");
        printf("Enter your choice (1 - 5): ");
        scanf("%d", &choice);
		switch (choice) {
            case 1:
                add_movie(Mov);
                break;
            case 2:
                display_movie(Mov);
                break;
            case 3: {
                int search_choice;
                printf("\n\t Choose search criteria:\n");
                printf("\n\t 1. Search by genre\n");
                printf("\n\t 2. Search by release year\n");
                printf("\n\tEnter your choice : ");
                scanf("%d", &search_choice);

                switch (search_choice) {
                    case 1:
                        search_movie_by_genre(Mov);
                        break;
                    case 2:
                        search_movie_by_year(Mov);
                        break;
                    default:
                        printf("Invalid choice.\n");
                }
            } break;
            case 4:
                book_ticket(Mov);
                break;
            case 5:
                fclose(Mov);
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);
	return 0;
}
