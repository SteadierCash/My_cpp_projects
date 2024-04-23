#include "job_tracker_functions.h"

using namespace std;

int main(){   
    welcome();
    string current_user = "test";

    if (start_screen(current_user) == 2){
        return 0;
    }

    user_screen(current_user);

    return 0;
}






