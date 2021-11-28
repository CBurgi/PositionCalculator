#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define USERNUM 10
#define NAMELENGTH 20

int usernum;
char file_name[100];
FILE *input_file;

typedef struct user_t{
    double lat;
    double lon;
    double alt;
    double time;
    char name[NAMELENGTH];

}user;
user temp_user, our_user, other_users[USERNUM], closest_user;

typedef struct diff_t{
    double posdif;
    char name[NAMELENGTH];
}diff;
diff user_diffs[USERNUM] = {{4, "posd"}, {5.0, "tes"}}, closest_user_diff = {2, "nam"};

user scan_user(int num, double lat, double lon, double alt, double time, char name[]){
    printf("%s\n", user_diffs[1].posdif);

    printf("scan_user\n");
    //takes lat, lon, alt, time, and name[] values and returns 1 user struct
    if (num == -1){
        our_user.lat = lat;
        our_user.lon = lon;
        our_user.alt = alt;
        our_user.time = time;
        strcpy(our_user.name, name);

        puts(our_user.name);
        printf("%d\n", our_user.time);
    }else{
        other_users[num].lat = lat;
        other_users[num].lon = lon;
        other_users[num].alt = alt;
        other_users[num].time = time;
        strcpy(other_users[num].name, name);

        puts(other_users[num].name);
        printf("%d\n", other_users[num].time);
    }

}

int assign_user(){
    printf("assign_user\n");
    double lat, lon, alt, time;
    char name[NAMELENGTH];

    //uses scan_user to assign our_user and other_users[]
    printf("Which file contains all the other users?\n");
    scanf("%s", &file_name);
    input_file = fopen(file_name, "r");
    if (input_file == NULL){
        printf("Can't open file");
        exit(1);
    }

    int i, n;
    fscanf(input_file, "%d", &n);
    
    for(i=0; i<n; i++){
        fscanf(input_file, "%d", &lat);
        fscanf(input_file, "%d", &lon);
        fscanf(input_file, "%d", &alt);
        fscanf(input_file, "%d", &time);
        fscanf(input_file, "%s", &name);

        scan_user(i, lat, lon, alt, time, name);
    }

    printf("Please enter the user's latitude\n");
    scanf("%d", &lat);
    printf("Please enter the user's longditude\n");
    scanf("%d", &lon);
    printf("Please enter the user's altitude\n");
    scanf("%d", &alt);
    printf("Please enter the time in nanoseconds\n");
    scanf("%d", &time);
    printf("Please enter the user's name\n");
    scanf("%s", &name);

    scan_user(-1, lat, lon, alt, time, name);

    return n;
}

void calc_user_diff(user our_user, user other_users[], diff user_diffs[], int n){
    printf("calc_user_diff\n");
    //takes 2 user_t structs and returns the difference in their distances
    int i;
    for(i=0; i<n; i++){
        strcpy(user_diffs[i].name, other_users[i].name);
        user_diffs[i].posdif = sqrt(pow(other_users[i].lat - our_user.lat, 2) + pow(other_users[i].lon - our_user.lon, 2) - pow(other_users[i].alt - our_user.alt, 2));
        puts(user_diffs[i].name);
        printf("%d\n", user_diffs[i].posdif);
    }
}

void find_closest_user(diff user_diffs[], user other_users[], int n){
    printf("find_closest_user\n");
    //loops through the user_diffs and returns the smallest one
    closest_user_diff = user_diffs[0];
    
    int i;
    for(i=0; i<n; i++){
        if(user_diffs[i].posdif < closest_user_diff.posdif){
            closest_user_diff = user_diffs[i];
            closest_user = other_users[i];
            puts(closest_user.name);
        }
    }
}

int main(){
    closest_user_diff.posdif = 3;
    printf("%d\n", closest_user_diff.posdif);

    return 0;

    usernum = assign_user();
    printf("%s %d %s %d\n", other_users[1].name, other_users[1].lat, our_user.name, our_user.lat);
    calc_user_diff(our_user, other_users, user_diffs, usernum);
    find_closest_user(user_diffs, other_users, usernum);
    printf("%s %d\n",user_diffs[1].name, user_diffs[1].posdif);
    printf("The closest user is %s. ", closest_user.name);
    printf("Their position was %d lat, %d long, and %d alt at %d nanoseconds.", closest_user.lat, closest_user.lon, closest_user.alt, closest_user.time);


    fclose(input_file);
    return 0;
}
