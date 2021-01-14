#ifndef APPLICATIONERRORS_H
#define APPLICATIONERRORS_H

#include<stdio.h>
/*
    This class outlines the a large portion of any errors that may be encountered in our application.
    If one is encountered, a message should be printed out of what failed
*/

class ApplicationErrors
{

public:
        enum class APP_ERRORS
        {
            ExitSuccessfully,
            UserClosedApplication,
            IncorrectAPIKey
        };

public:
    ApplicationErrors() = default;
    ApplicationErrors(const ApplicationErrors&) = delete;
    ApplicationErrors& operator = (const ApplicationErrors&) = delete;
    ~ApplicationErrors() = default;

    void print_Error_Message(const APP_ERRORS) const;

};

#endif // APPLICATIONERRORS_H
