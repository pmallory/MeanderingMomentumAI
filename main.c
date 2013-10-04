#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "myLib.h"

void drawNPCs();
void drawPlayer();
void update();

NPC npcs[NPC_COUNT];
PLAYER player;

int main() {
   
    REG_DISPCTL = MODE3 | BG2_ENABLE;
   
    // Step 1: initialize npcs
    int i;
    for (i=0; i<NPC_COUNT; i++) {
        npcs[i].row = rand()%(160-15);
        npcs[i].col = rand()%(240+15);
        npcs[i].race = rand()%2;
        npcs[i].ai_state = IDLE;
        //Use the ternary operator to set the NPCs size based on race
        npcs[i].size = npcs[i].race == GIANT ? 10 : 1;
        
        //Momentum is the tendency for the NPC to keep moving in the same direction
        npcs[i].row_momentum = rand()%3-1; //random choice of -1, 0, 1
        npcs[i].col_momentum = rand()%3-1;
    }
        
    //initialize player
    player.col = 50;
    player.row = 50;
    player.size = 3;
    
    while(1) {
        //check for key presses
        key_poll();
        
        //erase old positions
        drawNPCs(True);
        drawPlayer(True);
        
        //update and draw in new position
        update();
        drawNPCs(False);
        drawPlayer(False);
        
        waitForVBlank();
    }
}

//erase if erase==True
void drawNPCs(int erase) {
    u16 color;
    if (erase)
        color = BLACK;
    else
        color = BLUE;
    
    int i;
    for (i=0; i<NPC_COUNT; i++) {
        drawRect(npcs[i].row, npcs[i].col, npcs[i].size, npcs[i].size, color);
    }
}

//erase if erase==True
void drawPlayer(int erase) {
    u16 color;
    if (erase)
        color = BLACK;
    else
        color = RED;
    
    drawRect(player.row, player.col, player.size, player.size, color);
}

void update() {
    
    //update NPC positions
    int i;
    for (i=0; i<NPC_COUNT; i++) {
        
        //calculate the "manhattan distance" this NPC is from the player
        // note: the abs() function is provided my stdlib.h
        int distance = abs(npcs[i].row - player.row) + abs(npcs[i].col - player.col);
        
        //Determine what ai_state we should be in
        if (npcs[i].race == GIANT && distance < 100) //if we're a giant close to the player, chase!
            npcs[i].ai_state = ATTRACT;
        else if (npcs[i].race == PYGMY && distance < 100)//if we're a pygmy close to the player, run away!
            npcs[i].ai_state = REPEL;
        else 
            npcs[i].ai_state = IDLE; //otherwise just meander about
           
        //NOTE: how to get a percent based probability:
        // if (rand()%100<10) {...} => executes 10% of the time
                
        if (npcs[i].ai_state == IDLE && rand()%100<10) { //10% chance of taking a step when in the idle state
            
            if (rand()%100 < 10) { 
                // This if statement executes with a 10% chance
                // so 10% of time time the NPC will choose a new momentum
                // instead of continuing on in the same direction
                npcs[i].col_momentum = rand()%3-1;
                npcs[i].row_momentum = rand()%3-1;
            }
            
            //Move in the direction of the npc's momementum
            npcs[i].col += npcs[i].col_momentum;
            npcs[i].row += npcs[i].row_momentum;
            
        } else if (npcs[i].ai_state == ATTRACT ) {
            //NOTE: we could have used a switch statement to handle AI states
            // instead of else ifs.
            
            //The goal here is to move towards the player in either the
            //horizontal or vertical direction
            if (rand()%2) { //1 in 2 chance of moving vertically
                //move towards the player vertically
                if (npcs[i].row < player.row)
                    npcs[i].row++;
                else if (npcs[i].row > player.row)
                    npcs[i].row--;
            } else { //1 in 2 chance of moving horizontally
                //move towards the player horizontally
                if (npcs[i].col < player.col)
                    npcs[i].col++;
                else if (npcs[i].col > player.col)
                    npcs[i].col--;
            }
        } else if (npcs[i].ai_state == REPEL) {
            //The goal here is to move away from the player in either the
            //horizontal or vertical direction. same as ATTRACT but in the
            //opposite direction
            if (rand()%2) {
                if (npcs[i].row < player.row)
                    npcs[i].row--;
                else if (npcs[i].row > player.row)
                    npcs[i].row++;
            } else {
                if (npcs[i].col < player.col)
                    npcs[i].col--;
                else if (npcs[i].col > player.col)
                    npcs[i].col++;
            }
        }
        
    //Kep this agent on the screen!
    if (npcs[i].row < 0)
        npcs[i].row = 0;
    if (npcs[i].col < 0)
        npcs[i].col = 0;
    if (npcs[i].row > 159-npcs[i].size)
        npcs[i].row = 159-npcs[i].size;
    if (npcs[i].col > 239-npcs[i].size)
        npcs[i].col = 239-npcs[i].size;
    } //end of update NPC position
    
    //Update player position
    if (key_held(BUTTON_UP) && player.row > 0) {
        player.row--;
    } else if (key_held(BUTTON_DOWN) && player.row < 159-player.size) {
        player.row++;
    } else if (key_held(BUTTON_LEFT) && player.col > 0) {
        player.col--;
    } else if (key_held(BUTTON_RIGHT) && player.col+player.size < 239) {
        player.col++;
    }
}
