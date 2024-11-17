#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SCHEDULE 20
#define NAME_SIZE 50
#define TIME_SIZE 6
#define MEMO_SIZE 100

typedef struct{
    char name[NAME_SIZE];
    char start_time[TIME_SIZE];
    char end_time[TIME_SIZE];
    char memo[MEMO_SIZE];
}Schedule;
typedef struct{
    Schedule schedules[MAX_SCHEDULE];
    int schedule_count;
}Day;
typedef struct{
    Day days[31];
}Month;
typedef struct{
    Month months[12];
}Calendar;

void print_menu(void);
void print_line(void);
void print_plan(Calendar cal, int month, int day, int index);

void getCalDateAndName(int*, int*, char*);
void copy_schedule(Schedule *, Schedule *);
int days_in_month(int month);
int find_schedule(Calendar *calendar, int month, int day, char *schedule_name, int *index);

int isLeapYear(int year);
int getDaysInMonth(int year, int month);
int getStartDayOfMonth(int year, int month);
void printCalendar(int year, int month);

void add_schedule(Calendar *, int, int, char[]);
void delete_schedule(Calendar *calendar, int month, int day, char schedule_name[]);
void modify_schedule(Calendar *calendar, int month, int day, char schedule_name[]);

int main()
{
    Calendar calendar;
    memset(&calendar, 0, sizeof(Calendar));

    /* hard-coding
     * calendar.months[11-1].days[17-1].schedule_count++;
     * strcpy(calendar.months[11-1].days[17-1].schedules[0].name, "Drinking");
     * strncpy(calendar.months[11-1].days[17-1].schedules[0].start_time, "18:00", TIME_SIZE);
     * strncpy(calendar.months[11-1].days[17-1].schedules[0].end_time, "23:59", TIME_SIZE);
     * strcpy(calendar.months[11-1].days[17-1].schedules[0].memo, "friends");
     */
    
    printf("Starting the calendar program");

    int choice, index;
    int year=2024, month, day;
    char name[NAME_SIZE];
    while(1)
    {
        print_menu();
        scanf("%d", &choice);
        getchar();
        print_line();

        switch (choice)
        {
        case 1:
            getCalDateAndName(&month, &day, name);
            add_schedule(&calendar, month, day, name);
            break;
        case 2:
            getCalDateAndName(&month, &day, name);
            delete_schedule(&calendar, month, day, name);
            break;
        case 3:
            getCalDateAndName(&month, &day, name);
            modify_schedule(&calendar, month, day, name);
            break;
        case 4:
            printf("Input the month (1-12): ");
            scanf("%d", &month);
            getchar();

            if (month >= 1 && month <= 12) {
                printCalendar(year, month);
            }
            break;
        case 5:
            getCalDateAndName(&month, &day, name);
            if(find_schedule(&calendar, month, day, name, &index))
                print_plan(calendar, month, day, index);
            break;
        case 6:
            printf("Terminating the program\n");
            exit(1);
            break;
        default:
            printf("Wrong number, Type again\n\n");
            continue;
        }
    }
}

void print_menu(void)
{
    printf("\n\n");
    print_line();
    printf("\tCalendar Program\n");
    print_line();
    printf("1. Add schedule\n");
    printf("2. Remove schedule\n");
    printf("3. Modify schedule\n");
    printf("4. Show all plans in calendar\n");
    printf("5. Search for a schedule\n");
    printf("6. Exit the program\n");
    print_line();
    printf("Enter the number >> ");
}
void print_line(void)
{
    printf("--------------------------------\n");
}
void print_plan(Calendar cal, int month, int day, int index)
{
    Schedule schedule=cal.months[month-1].days[day-1].schedules[index];
    print_line();
    printf("Plan Name:\t\t%s\n", schedule.name);
    printf("Plan start-time:\t%s\n", schedule.start_time);
    printf("Plan end-time:\t\t%s\n", schedule.end_time);
    printf("Plan memo:\t\t%s\n", schedule.memo);
    print_line();
}

void getCalDateAndName(int *month, int *day, char* name)
{
    while(1)
    {
        printf("Input the month(1~12) >> ");
        scanf("%d", month);
        getchar();

        printf("Input the day(1~%d) >> ", days_in_month(*month));
        scanf("%d", day);
        getchar();

        if(*month<1||*month>12||*day<1||*day>days_in_month(*month))
        {
            printf("Invalid date, Type again\n");
            continue;
        }
        else
        {
            printf("Input the name >> ");
            fgets(name, NAME_SIZE, stdin);
            name[strlen(name)-1]='\0';
            break;
        }
    }
}
void copy_schedule(Schedule *schedule1, Schedule *schedule2)
{
    // memset(schedule1, 0, sizeof(Schedule)); // Initialize schedule

    strcpy(schedule1->name, schedule2->name);
    strcpy(schedule1->start_time, schedule2->start_time);
    strcpy(schedule1->end_time, schedule2->end_time);
    strcpy(schedule1->memo, schedule2->memo);
}
int days_in_month(int month){
    const int days_in_month[]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days_in_month[month-1];
}
int find_schedule(Calendar *calendar, int month, int day, char *schedule_name, int *index)
{
    for(int i=0;i<calendar->months[month-1].days[day-1].schedule_count;i++)
        if(strcmp(schedule_name, calendar->months[month-1].days[day-1].schedules[i].name)==0)
        {
            *index=i;
            return 1;
        }
    
    printf("\nThe schedule does not exist");
    return 0;
}

int isLeapYear(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        return 1;
    else
        return 0;
}
int getDaysInMonth(int year, int month) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year))
        return 29;
    else
        return daysInMonth[month - 1];
}
int getStartDayOfMonth(int year, int month) {
    int day = 1;
    static int dayOfWeek[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + dayOfWeek[month - 1] + day) % 7;
}
void printCalendar(int year, int month) {
    char* monthName[] = { " Jan", " Feb", " Mar", " Apr", " May", " Jun",
                         " Jul", " Aug", " Sep", " Oct", " Nob", " Dec" };
    int days = getDaysInMonth(year, month);
    int startDay = getStartDayOfMonth(year, month);

    printf("---------------------------");
    printf("\n%11s%s\n", " ", monthName[month - 1]);
    printf("---------------------------\n");
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    for (int i = 0; i < startDay; i++) {
        printf("%3s ", " ");
    }

    for (int day = 1; day <= days; day++) {
        printf("%3d ", day);

        if ((day + startDay) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void add_schedule(Calendar *calendar, int month, int day, char name[])
{
    char ch='y';
    Day *current=&calendar->months[month-1].days[day-1];
    if(current->schedule_count>0)
    {
        printf("Schedules already exist for %d/%d\n", month, day);
        printf("Do you want to add more? [Y/N]: ");
        scanf("%c", &ch);
        getchar();
    }

    if(ch=='n'||ch=='N')
    {
        printf("\nGo back to the menu");
        return;
    }

    if(current->schedule_count>=MAX_SCHEDULE)
    {
        printf("\nCannot add more schedules");
        return;
    }

    Schedule new;
    strcpy(new.name, name);

    printf("\nEnter start-time: ");
    scanf("%s", new.start_time);
    getchar();

    printf("Enter end-time: ");
    scanf("%s", new.end_time);
    getchar();

    printf("Enter memo: ");
    fgets(new.memo, MEMO_SIZE, stdin);
    new.memo[strlen(new.memo)-1]='\0';

    copy_schedule(&current->schedules[current->schedule_count++], &new);

    printf("\nSchedule added successfully");

    return;
}
void delete_schedule(Calendar *calendar, int month, int day, char schedule_name[]){
    // check if the plan exists
    int index;
    if(find_schedule(calendar, month, day, schedule_name, &index))
    {
        for(int i=index;i<calendar->months[month-1].days[day-1].schedule_count-1;i++)
        {
            copy_schedule(&calendar->months[month-1].days[day-1].schedules[i], &calendar->months[month-1].days[day-1].schedules[i+1]);
        }
        calendar->months[month-1].days[day-1].schedule_count--;
        printf("\nThe schedule has been removed");
    }

    return;
}
void modify_schedule(Calendar *calendar, int month, int day, char schedule_name[])
{
    int index;
    if(find_schedule(calendar, month, day, schedule_name, &index))
    {
        printf("\nWhat do you want to modify?\n");
        printf("1. Schedule name\n");
        printf("2. Schedule date\n");
        printf("3. Schedule time\n");
        printf("4. Schedule memo\n");
        printf("Enter your choice (1-4): ");

        int choice;
        scanf("%d", &choice);
        getchar();
        switch(choice)
        {
            case 1:
                printf("\nEnter new schedule name: ");
                memset(calendar->months[month-1].days[day-1].schedules[index].name, 0, NAME_SIZE);
                fgets(calendar->months[month-1].days[day-1].schedules[index].name, NAME_SIZE, stdin);
                calendar->months[month-1].days[day-1].schedules[index].name[strlen(calendar->months[month-1].days[day-1].schedules[index].name)-1]='\0';
                break;
            case 2:
                int new_month, new_day;

                printf("\nEnter new month (1-12): ");
                scanf("%d", &new_month);
                getchar();

                printf("Enter new day (1-%d): ", days_in_month(new_month));
                scanf("%d", &new_day);
                getchar();

                Schedule sch;
                int i=calendar->months[new_month-1].days[new_day-1].schedule_count++;
                copy_schedule(&sch, &calendar->months[month-1].days[day-1].schedules[index]);
                copy_schedule(&calendar->months[new_month-1].days[new_day-1].schedules[i], &sch);
                delete_schedule(calendar, month, day, schedule_name);
                break;
            case 3:
                memset(calendar->months[month-1].days[day-1].schedules[index].start_time, 0, TIME_SIZE);
                memset(calendar->months[month-1].days[day-1].schedules[index].end_time, 0, TIME_SIZE);

                printf("Enter start-time (HH:MM): ");
                scanf("%s", calendar->months[month-1].days[day-1].schedules[index].start_time);
                getchar();

                printf("Enter end-time (HH:MM): ");
                scanf("%s", calendar->months[month-1].days[day-1].schedules[index].end_time);
                getchar();
                break;
            case 4:
                memset(calendar->months[month-1].days[day-1].schedules[index].memo, 0, MEMO_SIZE);

                printf("Enter the new memo: ");
                fgets(calendar->months[month-1].days[day-1].schedules[index].memo, MEMO_SIZE, stdin);
                calendar->months[month-1].days[day-1].schedules[index].memo[strlen(calendar->months[month-1].days[day-1].schedules[index].memo)-1]='\0';
                break;
            default:
                printf("Invalid choice\n");
                return;
        }
        printf("\nSchedule updated");
    }
}
