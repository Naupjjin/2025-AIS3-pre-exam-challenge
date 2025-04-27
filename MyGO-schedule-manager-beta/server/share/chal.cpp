#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <csignal>

#define SCHEDULE_MAX 4

class ScheduleManager {
private:
    std::vector<std::string> schedule;
    int ops_cnt = 0;

    static void timeout_handler(int signum) {
        std::cerr << "Time out!\n";
        _exit(1);
    }

    void init_proc() {
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

    void menu() {
        puts("+======================+");
        puts("| (1) add schedule     |");
        puts("| (2) edit schedule    |");
        puts("| (3) delete schedule  |");
        puts("| (4) show schedule    |");
        puts("+======================+");
        printf("< MyGO @ ScheduleManager $ > ");
    }

    int get_choice() {
        int choice;
        scanf("%d", &choice);
        return choice;
    }

    std::string get_string(const char* prompt) {
        std::string input;
        printf("%s", prompt);
        std::cin.ignore();
        std::getline(std::cin, input);
        return input;
    }

    int get_index() {
        int index;
        printf("Index > ");
        scanf("%d", &index);
        return index;
    }

    void login() {
        char username[0x10];
        char password[0x10];

        printf("Username > ");
        scanf("%15s", username);

        printf("Password > ");
        scanf("%15s", password);

        if (strcmp(username, "MyGO!!!!!") == 0 && strcmp(password, "TomorinIsCute") == 0) {
            puts("\033[34m");
            puts("=========================================");
            puts("                  ____    _____      ");
            puts(" /'\\_/\\         /\\  _\\ /\\  __\\    ");
            puts("/\\      \\  __  __\\ \\ \\L\\_\\ \\ \\/\\ \\   ");
            puts("\\ \\ \\__\\ \\/\\ \\/\\ \\\\ \\ \\L_L\\ \\ \\ \\ \\  ");
            puts(" \\ \\ \\_/\\ \\ \\ \\_\\ \\\\ \\ \\/, \\ \\ \\_\\ \\ ");
            puts("  \\ \\_\\\\ \\_\\/____ \\\\ \\____/\\ \\_____\\");
            puts("   \\/_/ \\/_//___/> \\\\/___/  \\/_____/");
            puts("               /\\___/                 ");
            puts("               \\/__/                  ");
            puts("=========================================");
            puts("\033[0m");
            puts("[!] This is a system that can manage your band schedule.");
        } else {
            puts("[x] Verify Failed");
            exit(0);
        }
    }

public:
    ScheduleManager() {
        init_proc();
        login();
    }

    void add_schedule() {
        if (schedule.capacity() >= SCHEDULE_MAX) {
            puts("[!] Schedule is full. Don't let Tomorin so tired...");
            return;
        }
        schedule.emplace_back(get_string("Input item > "));
        puts("[+] Add success!");
    }

    void edit_schedule(int index) {
        if (index < 0 || index >= (int)schedule.capacity()) {
            puts("[x] Schedule does not exist");
            return;
        }
        std::cin.ignore();
        printf("Edit item > ");
        std::getline(std::cin, schedule[index]);
        puts("[+] Edit success!");
    }

    void delete_schedule(int index) {
        if (index < 0 || index >= (int)schedule.capacity()) {
            puts("[x] Schedule does not exist");
            return;
        }
        schedule.erase(schedule.begin() + index);
        puts("[-] Delete success!");
    }

    void show_schedule(int index) {
        if (index < 0 || index >= (int)schedule.capacity()) {
            puts("[x] Schedule does not exist");
            return;
        }
        std::cout << "Index [" << index << "] is " << schedule[index] << std::endl;
    }

    void run() {
        while (true) {
            menu();
            int choice = get_choice();
            ops_cnt++;
            if (ops_cnt >= 12) {
                puts("[x] Too many operations!");
                exit(0);
            }

            switch (choice) {
                case 1:
                    add_schedule();
                    break;
                case 2:
                    edit_schedule(get_index());
                    break;
                case 3:
                    delete_schedule(get_index());
                    break;
                case 4:
                    show_schedule(get_index());
                    break;
                default:
                    printf("[!] Thanks ~ ");
                    return;
            }
        }
    }
};

int main() {
    ScheduleManager manager;
    manager.run();
    return 0;
}