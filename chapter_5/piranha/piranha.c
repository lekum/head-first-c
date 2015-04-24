#include <stdio.h>
#include <string.h>

struct fish
{
    const char *name;
    char species[20];
    int teeth;
    int age;
};

void catalog(struct fish *f)
{
    printf("%s is a %s with %i teeth. He is %i.\n",
           f->name,
           f->species,
           f->teeth,
           f->age
          ); 
}

void set_teeth(struct fish *f, int teeth)
{	
	f->teeth = teeth; 
}


void set_species(struct fish *f, const char *species)
{
	strcpy(f->species, species);
}

int main()
{
    struct fish snappy = {"Snappy", "Piranha", 69, 4};
    catalog(&snappy);
    set_teeth(&snappy, 13);
    catalog(&snappy);
    set_species(&snappy, "Shark");
    catalog(&snappy);
    return 0;
}
