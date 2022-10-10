#include "inc/application.hpp"
#include <unistd.h>
int main(void)
{
    Application application;
    application.Init();
    application.Run();
   
    return 0;
}
