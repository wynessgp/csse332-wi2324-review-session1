#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void drawAXmasTree() {
    printf("      .     .  .      +     .      .          .\n");
    printf(" .       .      .     #       .           .\n");
    printf("    .      .         ###            .      .      .\n");
    printf("  .      .   '#:. .:##'##:. .:#'  .      .\n");
    printf("      .      . '####'###'####'  .\n");
    printf("   .     '#:.    .:#'###'#:.    .:#'  .        .       .\n");
    printf(".           '#########'#########'        .        .\n");
    printf("    .    '#:.  '####'###'####'  .:#'   .       .\n");
    printf(" .     .  '#######''##'##''#######'                  .\n");
    printf("            .'##'#####'#####'##'           .      .\n");
    printf(".   '#:. ...  .:##'###'###'##:.  ... .:#'     .\n");
    printf("  .     '#######'##'#####'##'#######'      .     .\n");
    printf(".    .     '#####''#######''#####'    .      .\n");
    printf("        .     '      000      '    .     .\n");
    printf("   .         .   .   000     .        .       .\n");
    printf(".. .. ..............O000O........................ .....\n");
}

int main() {
    printf("\nThe elf by the christmas tree suddenly turns to you.\n");
    printf("It appears as if you're the person who was getting the present after all!\n");
    sleep(2);
    printf("What's inside?\n\n");
    sleep(5);
    printf("Unfortunately, there's only immense disappointment inside.\n");
    printf("There's just a note saying that your OS exam is on Friday. What a load of crap that is!\n\n");
    sleep(5);
    printf("Maybe you should just take it back to the store...\n\n");
    sleep(5);
    printf("Happy holidays, everyone. Hopefully this exam isn't too bad.\n"); 
    printf("If I don't see you again before break, enjoy your break!\n\n");
    sleep(5);
    printf("Oh, by the way, here's some ASCII art of a 'christmas' tree.\n\n");
    printf("You might want to increase the window size of your terminal. I'll give you a couple seconds.\n");
    sleep(5);

    // TAKEN FROM https://www.asciiart.eu/holiday-and-events/christmas/trees
    drawAXmasTree();
}