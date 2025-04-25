#include <iostream>
#include <vector>
#include <string>
#include <cstring> 
#include <csignal>

// g++ chal.cpp -o chal -s

#define SCHEDULE_MAX 4
#define SCHEDULE_SIZE schedule.capacity()

std::vector<std::string> schedule;

void timeout_handler(int signum) {
    std::cerr << "Time out !\n";
    _exit(1);  
}


void init_proc(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    std::cin.rdbuf()->pubsetbuf(nullptr, 0);
    std::cout.rdbuf()->pubsetbuf(nullptr, 0);

    signal(SIGALRM, timeout_handler); 
    alarm(60);
    
    puts("+======== beta ========+");
    puts("| Band schedule system |");
    puts("+======================+");
    
}

void menu(){
    puts("+======================+");
    puts("| (1) add schedule     |");
    puts("| (2) edit schedule    |");
    puts("| (3) delete schedule  |");
    puts("| (4) Show schedule    |");
    puts("+======================+");
    printf("< MyGO @ ScheduleManager $ > ");
}

int get_choice(){
    int choice;
    scanf("%d", &choice);
    return choice;
}

std::string get_string(){
    std::string MSG;
    printf("Input item > ");
    std::cin.ignore();
    std::getline(std::cin, MSG);
    
    return MSG;
}


void add_scedule(){
    if(SCHEDULE_SIZE > SCHEDULE_MAX){
        puts("[!] schedule is full. Don't let Tomorin so tired...");
        return;
    }
    schedule.emplace_back(get_string());
    
    puts("[+] add success!");
    return;
}


void edit_schedule(int index){
    
    if(index > SCHEDULE_SIZE || index < 0){
        puts("[x] schedule is not exist");
        return;
    }
    
    std::cin.ignore();
    printf("Edit item > ");
    std::getline(std::cin, schedule[index]);
    
    puts("[+] Edit success!");
    return;
}

void delete_schedule(int index){
    if(index > SCHEDULE_SIZE || index < 0){
        puts("[x] schedule is not exist");
        return;
    }
    
    schedule.erase(schedule.begin() + index);
    puts("[-] delete success!");
    return;
}

void show_schedule(int index){
    if(index > SCHEDULE_SIZE || index < 0){
        puts("[x] schedule is not exist");
        return;
    }
    
    std::cout << "Index [" << index << "] is " << schedule[index] << std::endl;
    return;
}

int get_index(){
    int index;
    printf("Index > ");
    scanf("%d", &index);
    
    return index;
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
    int ops_cnt = 0 ;
    
    login();
    
    while(1){
        menu();
        choice = get_choice();
        ops_cnt++;
        if (ops_cnt < 12) {
            if(choice == 1){
                add_scedule();
                
            } else if (choice != 2 && choice != 3 && choice != 4) {
                printf("[!] Thanks ~ ");
                break;
            } else {
                index = get_index();
                if (choice == 2){
                    edit_schedule(index);
                    
                } else if (choice == 3){
                    delete_schedule(index);
                    
                } else if (choice == 4){
                    show_schedule(index);
                
                }
            }
        } else {
            exit(0);
        }
    }
    return 0;
}
