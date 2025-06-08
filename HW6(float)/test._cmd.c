#include <stdio.h>
#include <string.h>
static void login(void *p) {
    printf("[login] Command received: %s\n", (char *)p);
}

static void hello(void *p) {
    printf("[hello] Hello there! You typed: %s\n", (char *)p);
}

static void goodbye(void *p) {
    printf("[goodbye] Goodbye! You typed: %s\n", (char *)p);
}

static void cls(void *p) {
    printf("[cls] Clearing screen... (simulated)\n");
}

static void EXIT(void *p) {
    printf("[EXIT] Exiting program...\n");
}


// 命令表資料結構
typedef struct {
    const char *cmdname;
    void (*f)(void *);
} CmdTBL;

// 命令清單表
static CmdTBL CT[] = {
    {"CMD1", hello},
    {"CMD2", goodbye},
    {"cls", cls},
    {"EXIT", EXIT},
    {"Hello!", login},
    {NULL, NULL}
};

int cmdInterpreter(char *cmd) {
    char c = 0x00;
    int i,k;
    for (int i = 0; cmd[i] && cmd[i] != ' '; i++);
    if (cmd[i] == ' ') {
        cmd[i] = 0x00;  
    }
    // 比對命令表
    for (int k = 0; CT[k].cmdname != NULL; k++) {
        if (!strcmp(cmd, CT[k].cmdname)) {
            cmd[i] = c;  // 還原空白字元
            CT[k].f(cmd);  // 呼叫對應的命令函式
            return 1;
        }
    }

    return 0;  
}
int main(int argc, char* argv[]) {
    int i;

    printf("[argc=%d]\n", argc);
    for (i = 0; i < argc; i++) {
        printf("[%d] %s\n", i, argv[i]);
    }
    char input[256];
    while (1) {
        printf("\n> ");
        fgets(input, sizeof(input), stdin);//
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) continue;

        if (!cmdInterpreter(input)) {
            printf("Unknown command: %s\n", input);
        }
        if (!strcmp(input, "EXIT"))
            break;
    }

    return 0;
}


