#include "applicationstatus.h"

void ApplicationStatus::print_Error_Message(const Status error) const
{
    switch (error){

    case(Status::ExitSuccessfully):
        printf("\nProgram Exited Successfully\n");
        break;
    case(Status::IncorrectAPIKey):
        printf("\nAPI Key Did Not Meet Basic Authentication Criteria\n");
        break;
    case(Status::UserClosedApplication):
        printf("\nUser Forcibly Exited the Application\n");
        break;
    default:
        break;
    }
}
