#include <stdio.h>

typedef struct
{
    unsigned int first_visit:1;
    unsigned int come_again:1;
    unsigned int fingers_lost:4;
    unsigned int shark_attack:1;
    unsigned int days_a_week:3;
} survey;

void display_survey(survey surv)
{
    printf("Size of survey: %li\n", sizeof(surv));
    printf("First visit: %s\n", surv.first_visit?"YES":"NO");
    printf("Will come again?: %s\n", surv.come_again?"YES":"NO");
    printf("Fingers lost: %i\n", surv.fingers_lost);
    printf("Attacked by a shark?: %s\n", surv.shark_attack?"YES":"NO");
    printf("How many days a week?: %i\n", surv.days_a_week);
}

int main()
{
    survey survey_1 = {.first_visit=1};
    display_survey(survey_1);
    survey survey_2 = {.first_visit=0,
                       .come_again=1,
                       .fingers_lost=8,
                       .shark_attack=1,
                       .days_a_week=4
                      };
    display_survey(survey_2);
    return 0;
}
