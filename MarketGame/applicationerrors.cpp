#include "applicationerrors.h"

void ApplicationErrors::print_Error_Message(const APP_ERRORS error) const
{
    switch (error){

    case(APP_ERRORS::ExitSuccessfully):
        printf("\nProgram Exited Successfully\n");
        break;
    case(APP_ERRORS::IncorrectAPIKey):
        printf("\nAPI Key Did Not Meet Basic Authentication Criteria\n");
        break;
    case(APP_ERRORS::UserClosedApplication):
        printf("\nUser Forcibly Exited the Application\n");
        break;
    default:
        break;
    }
}
