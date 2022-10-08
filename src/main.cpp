#include "inc/application.hpp"
#include "inc/MenuState.hpp"
#include "inc/Screen.hpp"
#include <unistd.h>
int main(void)
{
    Application application;
    application.Init();
    application.Run();
   
    return 0;
}
