#include <iostream>
#include <vector>
#include <string>
#include <cstring> 
#include <cstdlib>

// g++ chal.cpp -o chal -no-pie -z lazy

struct schedule{
    char title[0x16];
    std::string content;
};

int SCHEDULE_STATUS = 0;
schedule* sched = nullptr;

void init_proc(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    std::cin.rdbuf()->pubsetbuf(nullptr, 0);
    std::cout.rdbuf()->pubsetbuf(nullptr, 0);
    
    puts("+======= alpha ========+");
    puts("| Band schedule system |");
    puts("+======================+");
    
}

void debug_backdoor(){
    puts("[!] Welcome, debug mode has opened...");
    system("/bin/sh");
}

void menu(){
    puts("+======================+");
    puts("| (1) create schedule  |");
    puts("| (2) edit title       |");
    puts("| (3) edit content     |");
    puts("| (4) show schedule    |");
    puts("+======================+");
    printf("< MyGO @ ScheduleManager $ > ");
}

int get_choice(){
    int choice;
    scanf("%d", &choice);
    return choice;
}

void create(){
    if(SCHEDULE_STATUS == 0){
        sched = new(std::nothrow) schedule;
        if (sched == nullptr) {
            puts("[x] Memory allocation failed!");
            exit(0);
        }
        
        puts("MyGO @ sched title > ");
        std::cin >> sched->title;
        puts("MyGO @ sched content > ");
        std::cin >> sched->content;
        
        SCHEDULE_STATUS = 1;

        puts("[!] Create Success !!!");
    } else {
        puts("[x] Your schedule have been created");
        return;
    }
}

void edit_title(){
    if (SCHEDULE_STATUS == 1){
        puts("MyGO @ sched title > ");
        std::cin >> sched->title;
        puts("[!] Edit Success");
    } else {
        puts("[x] Schdule Not Found ... ");
        return;
    } 
}

void edit_content(){
    if (SCHEDULE_STATUS == 1){
        puts("MyGO @ sched content > ");
        std::cin >> sched->content;
        puts("[!] Edit Success");
    } else {
        puts("[x] Schdule Not Found ... ");
        return;
    } 
}

void show(){
    if (SCHEDULE_STATUS == 1){
        std::cout << "===== Schedule =====" << std::endl;
        std::cout << "MyGO @ Title : " << sched -> title << std::endl;
        std::cout << "MyGO @ Content : " << sched -> content << std::endl;
        std::cout << "====================" << std::endl;
    } else {
        puts("[x] Schdule Not Found ... ");
        return;
    }
}

void login(){
    char username[0x10];  
    char password[0x10]; 
    
    printf("Username > ");
    scanf("%15s", username);

    printf("Password > ");
    scanf("%15s", password);
    
    if (strcmp(username, "MyGO!!!!!") == 0 && strcmp(password, "TomorinIsCute") == 0){
        puts("\033[34m");
        puts("=========================================");
        puts("                  ____    _____      ");  
        puts(" /'\\_/`\\         /\\  _`\\ /\\  __`\\    ");  
        puts("/\\      \\  __  __\\ \\ \\L\\_\\ \\ \\/\\ \\   ");  
        puts("\\ \\ \\__\\ \\/\\ \\/\\ \\\\ \\ \\L_L\\ \\ \\ \\ \\  ");  
        puts(" \\ \\ \\_/\\ \\ \\ \\_\\ \\\\ \\ \\/, \\ \\ \\_\\ \\ ");  
        puts("  \\ \\_\\\\ \\_\\/`____ \\\\ \\____/\\ \\_____\\");  
        puts("   \\/_/ \\/_/`/___/> \\\\/___/  \\/_____/");  
        puts("               /\\___/                 ");  
        puts("               \\/__/                  ");  
        puts("=========================================");
        puts("\033[0m");
        puts("[!] This is a system that can manage your band schedule.");
        return;
    } else {
        puts("[x] Verify Failed");
        exit(0);
    }
}

int main()
{
    init_proc();
    
    int choice;
    int index;
    
    login();
    
    while(1){
        menu();
        choice = get_choice();
        if (choice == 1){
            create();
        } else if (choice == 2){
            edit_title();
        } else if (choice == 3){
            edit_content();
        } else if (choice == 4){
            show();
        } else {
            break;
        }
        
    }
    return 0;
}
