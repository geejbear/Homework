
/* this file is a lesson that is designed to be read from top to bottom */


/*
 BIT FLAGS

 a set of options can be stored in a single integer.
 each bit in an integer can represent whether an option is true or false
*/


/*
 plan for this lesson

 ( 1 )
 first, an example of when you'd use bit flags, but done in a
 typical way. this makes it easier to understand the kind of case in which
 bit flags would be used.

 ( 2 )
 next, the same example but using bit flags. a back to back comparison
 makes it clear the advantages and disadvantages.
*/

// without bit flags, a set of options might typically be stored in a struct:

#include <stdbool.h>

typedef struct
{
    bool solid;     // do collision detection
    bool passive;   // doesn't attack player
    bool flies;     // not affected by gravity
    bool respawns;  // respawns if killed
    bool easy;      // appears on easy difficult
    bool medium;    // appears on medium difficulty
    bool hard;      // appears on hard difficulty
} EntityOptions;

// TODO: how many bytes is an EntityOptions struct?
// answer: 7 bytes
// the size of 'bool' might vary from computer to computer, so you should use
// code to find its size.




// for the above example, every entity would have a set of options,
// which define characteristics about different types of entities
typedef struct
{
    int x;
    int y;
    int score;
    int lives;
    EntityOptions options;
} Entity;

// TODO: how many bytes is an Entity?




// as an example of use, the 'flies' option is inspected to determine
// whether gravity should be applied to an entity
#define NUM_ENTITIES 100
void ApplyGravity(Entity *e) { } // just for the example below!

void Update(Entity entities[NUM_ENTITIES])
{
    for ( int i = 0; i < NUM_ENTITIES; i++ ) {
        
        // at this point in the code we don't know whether this entity flies
        // or not, so we have to check:
        if ( entities[i].options.flies == false ) {
            ApplyGravity(&entities[i]);
        }
    }
}




// with bit flags, one only needs 1 bit, rather than 1 byte to store a boolean
// value, but accessing each value becomes more involved.

// bit masks

#define ENTITY_FLAGS_NONE       0x00 // 00000000
#define ENTITY_FLAGS_SOLID      0x01 // 00000001
#define ENTITY_FLAGS_PASSIVE    0x02 // 00000010
#define ENTITY_FLAGS_FLIES      0x04 // 00000100
#define ENTITY_FLAGS_RESPAWNS   0x08 // 00001000
#define ENTITY_FLAGS_EASY       0x10 // 00010000
#define ENTITY_FLAGS_MEDIUM     0x20 // 00100000
#define ENTITY_FLAGS_HARD       0x40 // 01000000


// with only 7 options, and each option now only 1 bit, we can fit all of an
// entity's options into a single byte.

// an option stored in one bit is called a 'flag'

typedef struct
{
    int x;
    int y;
    int score;
    int lives;
    EntityFlags flags; // much smaller!
} Entity2;

// TODO: how many bytes is an Entity2 struct?




// however, the process of getting(1) and setting options is now more involved.

// (1) get, the opposite of set, refers to checking the value of something

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    printf("size of EntityOptions: %zu bytes\n", sizeof(EntityOptions));
    printf("size of Entity: %zu bytes\n", sizeof(Entity));
    printf("size of Entity2: %zu bytes\n", sizeof(Entity2));
    
    srand((unsigned)time(NULL));
    
    Entity2 monster; // notice it's an Entity2, not Entity!
    monster.flags = rand(); // give it some random options
    
    // TODO: check if monster has 'passive' option

    if ( monster.flags & ENTITY_FLAGS_PASSIVE ) {
        puts("moster is passive");
    }

    
    // TODO: check if monster has 'respawns' option
#if 0 // remove when ready to do this problem
    if ( ? ) {
        puts("monster will respawn");
    }
#endif
    
    return 0;
}




// with #define's instead of a named struct (EntityOptions) we lose the
// advantage of a type name

// solution one: use a typedef'd enum to store the flag constants

typedef enum
{
    ENTITY_FLAGS2_NONE      = 0x00,
    ENTITY_FLAGS2_SOLID     = 0x01,
    ENTITY_FLAGS2_PASSIVE   = 0x02,
    ENTITY_FLAGS2_FLIES     = 0x04,
    ENTITY_FLAGS2_RESPAWNS  = 0x08,
    ENTITY_FLAGS2_EASY      = 0x10,
    ENTITY_FLAGS2_MEDIUM    = 0x20,
    ENTITY_FLAGS2_HARD      = 0x40
} EntityFlags;

// here we can declare a variable of type 'EntityFlags2', however the size of
// an enum value is usually the same size as an int by default, and the space
// advantage is lost




// solution two: use #define'd values and just typedef the size of int you to
// stores the flags.

typedef char EntityFlags2;



// TODO: bonus
// what flags does an Entity2 have if the value of its flags member is 77?
