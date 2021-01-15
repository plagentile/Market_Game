#ifndef APPLICATIONSTATUS_H
#define APPLICATIONSTATUS_H

#include<stdio.h>
/*
    This class outlines the a large portion of any errors that may be encountered in our application.
    If one is encountered, a message should be printed out of what failed
*/

class ApplicationStatus
{

public:
        enum class Status
        {
            Unchanged,
            ExitSuccessfully,
            UserClosedApplication,
            IncorrectAPIKey
        };

public:
    ApplicationStatus() = default;
    ApplicationStatus(const ApplicationStatus&) = delete;
    ApplicationStatus& operator = (const ApplicationStatus&) = delete;
    ~ApplicationStatus() = default;

    void print_Error_Message(const Status) const;

};

#endif // APPLICATIONSTATUS_H
