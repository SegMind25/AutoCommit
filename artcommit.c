#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 🔧 Configure your GitHub name & email
const char* GIT_EMAIL = "modistotube2004@gmail.com";
const char* GIT_NAME  = "Bekkali";

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int month, int year) {
    const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) return 29;
    return days[month - 1];
}

int main() {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    int target_year = tm_now->tm_year + 1900 - 1; // previous year

    // Set Git identity (optional but safe)
    system("git config user.email \"modistotube2004@gmail.com\"");
    system("git config user.name \"Bekkali\"");

    const char* logfile = "log.txt";
    FILE* f;

    for (int month = 1; month <= 12; month++) {
        int days = days_in_month(month, target_year);
        for (int day = 1; day <= days; day++) {
            char date_str[11];
            snprintf(date_str, sizeof(date_str), "%04d-%02d-%02d", target_year, month, day);

            // Append one line to the same file
            f = fopen(logfile, "a");
            if (f) {
                fprintf(f, "Commit on %s\n", date_str);
                fclose(f);
            }

            // Stage the file
            system("git add log.txt");

            // Commit with historical date (noon)
            char cmd[256];
            snprintf(cmd, sizeof(cmd),
                     "git commit --date=\"%s 12:00:00\" -m \"Daily log: %s\"",
                     date_str, date_str);
            system(cmd);
        }
    }

    printf("✅ Done! All 365 (or 366) commits added to log.txt for year %d.\n", target_year);
    printf("🚀 Run: git push origin main\n");
    return 0;
}
