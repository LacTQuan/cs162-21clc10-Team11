bool Check_Regis_Time(Registration_Session S) {
    time_t now = time(0);
    tm* t = localtime(&now);
    int year = t->tm_year + 1900, mon = t->tm_mon + 1, day = t->tm_mday,
    hour = t->tm_hour, minute = t->tm_min;
    if (year != S.start.year) return 0;
    if (mon < S.start.month || mon > S.end.month) return 0;
    if (mon == S.start.month) {
        if (day < S.start.date) return 0;    // check day
        if (day == S.start.date) {
            if (hour < S.start.hour) return 0;// check hour
            if (hour == S.start.hour) {
                if (minute < S.start.minute) return 0;// check minute
            }
        }
    }
    if (mon == S.end.month) {
        if (day > S.end.date) return 0;    // check day
        if (day == S.end.date) {
            if (hour > S.end.hour) return 0;// check hour
            if (hour == S.end.hour) {
                if (minute > S.end.minute) return 0;// check minute
            }
        }
    }
    return 1;
}