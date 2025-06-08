#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
void check_card(int a[]){
    for(int i=0;i<5;i++){
        printf("%d  ",a[i]);
    }
    printf("\n\n");
}
int main() {
    printf("\n============== start ==============\n");
    int hand_card_Num=0;
    bool draw_Finish=false;
    int hand_Card[5]={0,0,0,0,0};
    int rand_Card=0,card_Type=0,card_Number=0,Card=0;
    srand(time(NULL));
    do{
        do{

            rand_Card=rand()%52;
            card_Type=rand_Card/13;
            card_Number=rand_Card%13+1;
            Card=(card_Number<<2)+card_Type;
            draw_Finish=false;
            for(int i=0;i<hand_card_Num;i++){
                if(hand_Card[i]==Card){
                    draw_Finish=true;
                    break;
                }
            }
        }while(draw_Finish==true);
        hand_Card[hand_card_Num]=Card;
        hand_card_Num++;
    }while(hand_card_Num<5);
    printf("check draw card.\n");
    check_card(hand_Card);


    int sort_max_value=hand_Card[0];
    for(int i=0;i<5;i++){
        for(int k=0;k<4;k++){
            if(hand_Card[k]>hand_Card[k+1]){
                sort_max_value=hand_Card[k];
                hand_Card[k]=hand_Card[k+1];
                hand_Card[k+1]=sort_max_value;
            }
        }

    }
    printf("check bubble sort.\n");
    check_card(hand_Card);
/*-----------------------------------------------------*/
/*-----------------check card colar--------------------*/
    printf("check card colar.\n");
    char* hand_card_Type[5];
    int hand_card_Number[5]={0,0,0,0,0};
    for (int i=0;i<5;i++){
        switch (hand_Card[i]&3)
        {
        case 0:
            hand_card_Type[i]="Spades";
            break;
        case 1:
            hand_card_Type[i]="Diamond";
            break;
        case 2:
            hand_card_Type[i]="Heart";
            break;
        case 3:
            hand_card_Type[i]="Club";
            break;
    
        default:
            break;
        }
        hand_card_Number[i]=hand_Card[i]>>2;
        switch (hand_card_Number[i])
        {
        case 1:
            printf("%s A  ",hand_card_Type[i]);
            break;
        case 11:
            printf("%s J  ",hand_card_Type[i]);
            break;
        case 12:
            printf("%s Q  ",hand_card_Type[i]);
            break;
        case 13:
            printf("%s K  ",hand_card_Type[i]);
            break;
        default:
            printf("%s %d  ",hand_card_Type[i],hand_card_Number[i]);
            break;
        }

    }
/*-----------------------------------------------------*/
/*---------------------Flush---------------------------*/
    printf("\n\n");
    bool Flush=false;
    for(int i=1;i<5;i++){
        if (hand_card_Type[0]!=hand_card_Type[i]){
            Flush=false;
            break;
        }
        else{
            Flush=true;
        }
    }
    if(Flush){
        printf("Flush\n");
    }
    else{
        printf("No Flush\n");
    }
/*-----------------------------------------------------*/
/*--------------------Straight-------------------------*/
    bool straight=true;
    for(int i=0;i<4;i++){
        if(hand_card_Number[i]!=hand_card_Number[i+1]+1){
            straight=false;
        }
    }
    if(straight){
        printf("Straight\n");
    }
    else{
        printf("No Straight\n");
    }
/*-----------------------------------------------------*/
/*--------------------Full House-----------------------*/
    bool Full_house = false;
    if ((hand_card_Number[0] == hand_card_Number[1] && hand_card_Number[1] == hand_card_Number[2]) &&
        (hand_card_Number[3] == hand_card_Number[4])) {
        Full_house = true;
    }
    else if ((hand_card_Number[2] == hand_card_Number[3] && hand_card_Number[3] == hand_card_Number[4]) &&
            (hand_card_Number[0] == hand_card_Number[1])) {
        Full_house = true;
    }
    else {
        Full_house = false;
    }

    if (Full_house) {
        printf("Full house\n");
    }
    else {
        printf("No Full house\n");
    }
/*-----------------------------------------------------*/
/*--------------------Four of a kind-------------------*/
    bool Four_of_kind=false;
    if((hand_card_Number[0]==hand_card_Number[3])||(hand_card_Number[1]==hand_card_Number[4])){
        Four_of_kind=true;
    }
    else{
        Four_of_kind=false;
    }
    if (Four_of_kind) {
        printf("Four of kind\n");
    }
    else {
        printf("No Four of kind\n");
    }
/*-----------------------------------------------------*/
/*--------------------pair-----------------------------*/
    bool pair_con=false;
    int pair_num=0;
    for(int i=0;i<4;i++){
        if((hand_card_Number[i]==hand_card_Number[i+1])&&!pair_con){
            pair_con=true;
            pair_num++;
        }
        else{
            pair_con=false;
        }
     }
    if (pair_num) {
        printf("%d Pair\n",pair_num);
    }
    else {
        printf("No Pair\n");
    }
    printf("\n=============== end ===============\n");
}
