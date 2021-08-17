class FullDate {
public:
    int getYear() {
        time_t rawtime = timeClient.getEpochTime();
        struct tm* ti;
        ti = localtime(&rawtime);
        int year = ti->tm_year + 1900;

        return year;
    }

    int getMonth() {
        time_t rawtime = timeClient.getEpochTime();
        struct tm* ti;
        ti = localtime(&rawtime);
        int month = (ti->tm_mon + 1) < 10 ? 0 + (ti->tm_mon + 1) : (ti->tm_mon + 1) - 1; // Gunakan Array Nama2 Bulan...

        return month;
    }

    int getDate() {
        time_t rawtime = timeClient.getEpochTime();
        struct tm* ti;
        ti = localtime(&rawtime);
        int date = (ti->tm_mday) < 10 ? 0 + (ti->tm_mday) : (ti->tm_mday);

        return date;
    }

}fullDate;
