#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef union {
    struct {
        unsigned hand_card_Type : 2;
        unsigned hand_card_Number : 7;
    };
    unsigned char c;
} PKCARD;

int N = 13;

void deal_cards(int n, PKCARD *PK) {
    int hand_card_Num = 0;
    bool draw_Finish = false;
    int rand_Card = 0, card_Type = 0, card_Number = 0, Card = 0;

    do {
        do {
            rand_Card = rand() % 52;
            card_Type = rand_Card / 13;
            card_Number = rand_Card % 13 + 1;
            Card = (card_Number << 2) + card_Type;
            draw_Finish = false;
            for (int i = 0; i < hand_card_Num; i++) {
                if (PK[i].c == Card) {
                    draw_Finish = true;
                    break;
                }
            }
        } while (draw_Finish);
        PK[hand_card_Num].hand_card_Number = card_Number;
        PK[hand_card_Num].hand_card_Type = card_Type;
        hand_card_Num++;
    } while (hand_card_Num < N);
}

void sort_cards(PKCARD *PK, int N) {
    PKCARD temp;
    for (int i = 0; i < N-1; i++) {
        for (int k = 0; k < N - 1; k++) {
            if (PK[k].c > PK[k + 1].c) {
                temp = PK[k];
                PK[k] = PK[k + 1];
                PK[k + 1] = temp;
            }
        }
    }
}

void sort_cards_colar(PKCARD *PK, int N) {
    PKCARD temp;
    for (int i = 0; i < N - 1; i++) {
        for (int k = 0; k < N - 1 - i; k++) {
            if (PK[k].hand_card_Type > PK[k + 1].hand_card_Type || 
                (PK[k].hand_card_Type == PK[k + 1].hand_card_Type &&
                 PK[k].hand_card_Number > PK[k + 1].hand_card_Number)) {
                temp = PK[k];
                PK[k] = PK[k + 1];
                PK[k + 1] = temp;
            }
        }
    }
}


void sort_cards_number(PKCARD *PK, int N) {
    int newN = 1;
    for (int i = 1; i < N; i++) {
        if (PK[i].hand_card_Number != PK[newN - 1].hand_card_Number) {
            PK[newN++] = PK[i];
        }
    }
}
void print_cards(PKCARD *PK, int N) {
    const char* suits[] = {"Spades", "Diamond", "Heart", "Club"};
    for (int i = 0; i < N; i++) {
        const char* suit = suits[PK[i].hand_card_Type];
        int number = PK[i].hand_card_Number;
        switch (number) {
            case 1:  printf("%s A  ", suit); break;
            case 11: printf("%s J  ", suit); break;
            case 12: printf("%s Q  ", suit); break;
            case 13: printf("%s K  ", suit); break;
            default: printf("%s %d  ", suit, number); break;
        }
    }
    printf("\n\n");
}


bool check_Straight(PKCARD *PK, int start){
    char straight=1;
    for(int i=start;i<start+4;i++){
        if(PK[i+1].hand_card_Number!=PK[i].hand_card_Number+1){
            straight=0;
        }
    }
    return straight;
};

bool check_Flush(PKCARD *PK, int start) {
    for (int i = 1; i < 5; i++) {
        if (PK[start].hand_card_Type != PK[start + i].hand_card_Type)
            return false;
    }
    return true;
}

bool check_Quads(PKCARD *PK, int i){
    int Four_of_kind=0;
    if((PK[i].hand_card_Number==PK[i+3].hand_card_Number)){
        Four_of_kind=1;
    }
    else{
        Four_of_kind=0;
    }
    return Four_of_kind;
};

bool  check_Pairs(PKCARD *PK, int i){
    bool pair=false;
    if((PK[i].hand_card_Number==PK[i+1].hand_card_Number)){
        pair=1;
    }
    return pair;
};

bool check_Trips(PKCARD *PK, int i){
    bool Trip = false;
    if ((PK[i].hand_card_Number == PK[i+1].hand_card_Number && PK[i+1].hand_card_Number == PK[i+2].hand_card_Number)) {
        Trip = true;
    }
    else {
        Trip = false;
    }
    return Trip;
};

int main() {
    int N=13;
    PKCARD PK[N];
    srand(time(NULL));
    deal_cards(N, PK);
    sort_cards(PK, N);
    printf("Check card sort:\n");
    print_cards(PK, N);

    int Trips=0;
    for(int i=0;i<N-2;i++){
        if(check_Trips(PK,i)){
            Trips++;
        }
    }

    int Pairs=0;
    for(int i=0;i<N-1;i++){
        if(check_Pairs(PK,i)){
            Pairs++;
        }
    }

    if(Trips>2){
        printf("Full House\n");
    }
    else if(Trips==1&&Pairs>2){
        printf("Full House\n");
    }
    else{
        printf("No Full House\n");
    }

    
    if(Pairs){
        printf("%d Pairs\n",Pairs);
    }
    else{
        printf("No pairs\n");
    }

    bool Four_Kind=false;
    for(int i=0;i<N-3;i++){
        if(check_Quads(PK,i)){
            Four_Kind=true;
        }
    }
    if(Four_Kind){
        printf("Four of Kind\n");
    }
    else{
        printf("No Four of Kind\n");
    }

    sort_cards_colar(PK,N);
    bool Flush=false;
    for(int i=0;i<N-4;i++){
        if(check_Flush(PK, i)){
            Flush=true;
        }
    }
    if(Flush){
        printf("Flush\n");
    }
    else{
        printf("No Flush\n");
    }

    bool Straight_Flush=false;
    for(int i=0;i<N-4;i++){
        if(check_Straight(PK,i)&&PK[i].hand_card_Type==PK[i+4].hand_card_Type){
            Straight_Flush=true;
        }
    }
    if(Straight_Flush){
        printf("Straight Flush\n");
    }
    else{
        printf("No Straight Flush\n");
    }

    sort_cards_number(PK,N);
    bool straight=false;
    for(int i=0;i<N-4;i++){
        if(check_Straight(PK,i)){
            straight=true;
        }
    }
    if(!straight){
        printf("No Straight\n");
    }
    else{
        printf("Straight\n");
    }
    printf("\n");
    return 0;
}
