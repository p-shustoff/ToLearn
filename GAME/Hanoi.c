#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 256

int top_rod(int *rod) {
    int top = *(rod);     // Top is what is first on the adress
    if (top == 0) {       // If that element == 0 then go deeper
       top =*(rod+1);
       if (top == 0)
            top =*(rod+2);
    }
    return top;
}

int height(int *rod) {    // Function operates the same way as above, but decreases the height if zero element is on the way
    int element = *(rod);
    int height = 3;
    if (element == 0) {
        height -= 1;
        element = *(rod+1);
        if (element == 0) {
            height -= 1;
            element = *(rod+2);
            if ( element == 0)
                height -= 1;
        }
    }
    return height;
}

void move(int *rod_one, int *rod_another) {
    int top_one = top_rod(rod_one);
    int top_two = top_rod(rod_another);
    int height_one = height(rod_one);
    int height_two = height(rod_another);
    if (height_one) {
        if ( (top_one < top_two) || top_two == 0) {
            rod_another[3 - (height_two + 1)] = rod_one[3 - height_one];
            rod_one[3 - height_one] = 0;
        }
        else
            printf("Cannot place the bigger disc above smaller\n");
    }
    else
        printf("Error, the rod is empty!\n");
}
int state(int *rod) {
    int state = 0;
    int height_rod = height(rod);
    switch (height_rod) {
        case 3:
            state = 1;
            break;
        case 2:
            if (rod[1] == 2)
                state = 2;
            else if (rod[1] == 1 && rod[2] == 2)
                state = 3;
            else if (rod[1] == 1 && rod[2] == 3)
                state = 4;
            else
                printf("Error");
            break;
        case 1:
            if (rod[2] == 1)
                state = 5;
            else if (rod[2] == 2)
                state = 6;
            else if (rod[2] == 3)
                state = 7;
            else
                printf("Error");
            break;
        case 0:
             break;
        default:
            printf("Error");
            break;
    }
    return state;
}

void printer(int state_1, int state_2, int state_3) {
     char filename[12] = {'0' + state_1, '0' + state_2, '0' + state_3, 0};
     char ext[5] = ".txt";
     strcat(filename, ext);
     // printf("%s\n", filename);
     FILE *file;
     char arr[N];
     char path[80] = "./vars/";
     strcat(path, filename);
     path[51] = 0;
     //  printf("%s\n", path);
     file = fopen(path, "r");
     while (fgets(arr, N, file) != NULL)
         printf("%s", arr);
     putchar(10);
     fclose(file);
}

int main() {
    int rod_first[3] = {1, 2, 3};
    int rod_second[3] = {0, 0, 0};
    int rod_third[3] = {0, 0, 0};     // Initializing the rods
    printf("Please play Hanoi game and move all the discs from rod 1 to rod 2\n");
    int high_second = height(rod_second);
    while (high_second != 3) {
        int choice_1 = 0;
        int choice_2 = 0;
        system("clear");
        int state1 = state(rod_first);
        int state2 = state(rod_second);
        int state3 = state(rod_third);
        printer(state1, state2, state3);
        printf("Chose the rod from which to take disc: ");
        scanf("%d", &choice_1);
        switch (choice_1) {
            case 1:
                if(height(rod_first)) {
                    printf("Chose the rod to which: ");
                    scanf("%d", &choice_2);
                    if (choice_2 == 2)
                        move(rod_first, rod_second);
                    else if (choice_2 == 3)
                        move(rod_first, rod_third);
                    else
                        printf("Cannot move to that rod\n");
                }
                else
                    printf("Cannot take from empty rod\n");
                break;

            case 2:
                if (height(rod_second)) {
                    printf("Chose the rod to which: ");
                    scanf("%d", &choice_2);
                    if (choice_2 == 1)
                        move(rod_second, rod_first);
                    else if (choice_2 == 3)
                        move(rod_second, rod_third);
                    else
                        printf("Cannot move to that rod\n");
                }
                else
                    printf("Cannot take from empty rod\n");
                break;

            case 3:
                if (height(rod_third)) {
                    printf("Chose the rod to which: ");
                    scanf("%d", &choice_2);
                    if (choice_2 == 1)
                        move(rod_third, rod_first);
                    else if (choice_2 == 2)
                        move(rod_third, rod_second);
                    else
                        printf("Cannot move to that rod\n");
                }
                else
                    printf("Cannot take from empty rod\n");
                break;

            default:
                printf("This rod does not exist. Or wrong input entered\n");
        }
        high_second = height(rod_second);
    }
    printer(state(rod_first), state(rod_second), state(rod_third));
    printf("Sucess! You won the game!!!\n");
    return 0;
   }
