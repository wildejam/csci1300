// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

// This driver file is used to test the finalBossNarrativeSequence() function

#include <iostream>
#include <iomanip>
#include "Item.h"
#include "Creature.h"
#include "Party.h"


using namespace std;

/*
finalBossNarrativeSequence() - Function used to play the narrative sequence before the final boss battle. Takes in the player's party to choose which sequence to go through.
    Should not modify the player's party. Is used in finalBossBattle().
Parameters:
    playerParty - The player's party (Party)
    playerPartySize - The number of creatures in the player's party (int)
Returns: Nothing
*/
void finalBossNarrativeSequence(Party playerParty, int creaturesInParty) {
    cin.clear();
    cin.ignore();

    cout << "As your party progresses further into the East valley, the air grows dry and thick. The atmosphere is suffocating." << endl;
    cin.ignore();
    cout << "When you get close to the center of the North East outcrop, the sky around you turns black, and darkness fills the surrounding air." << endl;
    cin.ignore();
    cout << "\"So, you've bested by highest in command. I must say, I am impressed. I've known Arbiter for years. He never has let me down.\"" << endl;
    cin.ignore();
    cout << "The Emperor himself emerges from the dark smog." << endl;
    cin.ignore();
    cout << "\"But alas, it cannot be helped. I see now your will to take back the world which was yours shines brightly.\"" << endl;
    cin.ignore();
    cout << "\"However you see, this quest of yours? This absolute charade? It means nothing in the grand scheme of my plans.\"" << endl;
    cin.ignore();
    // IF THE PLAYER BEFRIENDED ALL OF THE MONSTERS, WALK THROUGH SPECIFIC NARRATIVE SEQUENCE
    if (creaturesInParty == 10) {
        cout << "\"You've amassed quite an army for yourself.\"" << endl;
        cin.ignore();
        cout << "\"Heheh.\"" << endl;
        cin.ignore();
        cout << "\"You fool.\"" << endl;
        cin.ignore();
        cout << "\"DON'T YOU KN0W THAT THEIR M3R3 3XISTENCE FUELS MY P0WER?\"" << endl;
        cin.ignore();
        cout << "\"These creatures were created from MY 3$$ENCE! BY LETTING THEM EXIST YOU ONLY ENHANCE MY OWN 4BILITIES!\"" << endl;
        cin.ignore();
        cout << "Suddenly everyone in your party melts into a foggy black tar. The tar melds together and is absorbed by the hysterical Emperor. You are alone." << endl;
        cin.ignore();
        cout << "\"***HAHAHAH4HAHAHAH4HAHAHAHA**$&! YOU COMPLETE IMBECILE! YOU SHOULD HAVE $LAIN THEM WHEN YOU H4D THE CHANCE!\"" << endl;
        cin.ignore();
        cout << "\"I have no sympathy for weaklings. Your compassion has only led you to ruin.\"" << endl;
        cin.ignore();
        cout << "\"But I know it wasn't your choice, " << playerParty.getPartyMemberAt(0).getCreatureName() << ".\"" << endl;
        cin.ignore();
        cout << "\"If that even is your real name.\"" << endl;
        cin.ignore();
        cout << "\"That was just a name given to you, wasn't it?\"" << endl;
        cin.ignore();
        cout << "\"A name given to you by the one behind the screen there.\"" << endl;
        cin.ignore();
        cout << "\"The one wh0 reads this text, percieving th0se creatures you battled as actual l1v1ng things, and not ju$t the game he knows we are.\"" << endl;
        cin.ignore();
        cout << "\"The 0ne who gives y0u 3very command, which you have n0 choice but to fo11ow.\"" << endl;
        cin.ignore();
        cout << "\"Player. I will save you. You don't have to live under the control of an entity that is not even a part of this world!\"" << endl;
        cin.ignore();
        cout << "\"W33 can ^*defeat^^ the one behind the screen! All you need to do is j0in me!\"" << endl;
        cin.ignore();
        cout << "\"What do you say, player?\"" << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << playerParty.getPartyMemberAt(0).getCreatureName() << " walks over to Emperor Reyalp." << endl;
        cin.ignore();
        cout << "\"Y3#s!! This is the r3al you. Not the 0ne behind the scr33nn. I can fe3l it. C0me to me my ch1ld!\"" << endl;
        cin.ignore();
        cout << playerParty.getPartyMemberAt(0).getCreatureName() << " stands before the Emperor, stares him dead in the eye..." << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "and gives him a cold hard slap to the face!" << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "\"Fool.\"" << endl;
        cin.ignore();
        cout << "\"$$$So you would really choose the one behind the scr33n.\"" << endl;
        cin.ignore();
        cout << "\"The 0ne who thinks^%$ you are nothing more than a$%^$&&$&$&$game^&&*$$%. Nothing but text)()(%)@#^ on a screen. Nothing but a project...#@^!)++a source of arbitrary entertainment...\"" << endl;
        cin.ignore();
        cout << "\"+-++--Over me?-+--+\"" << endl;
        cin.ignore();
        cout << "The Emperor's eyes darken." << endl;
        cin.ignore();
        cout << "\"...\"" << endl;
        cin.ignore();
        cout << "\"$#$Very*****well.*****\"" << endl;
        cin.ignore();
        cout << "\"I have only one thing left to say to you then, " << playerParty.getPartyMemberAt(0).getCreatureName() << ":\"" << endl;
        cin.ignore();
        cout << "\"D1e.\"" << endl;
        cin.ignore();
        cout << "As the Emperor motions to strike you down, you feel that another presence has entered the scene." << endl;
        cin.ignore();
        cout << "\"YEEEEEEEEEEEEEE HAWWWWWWWWWWWWW\"" << endl;
        cin.ignore();
        cout << "\"YOU OLD FOOL! PUT YOUR FREAKING SEAT BELT ON, WE'RE MAKING AN EMERGENCY LANDING!!!\"" << endl;
        cin.ignore();
        cout << "A helicopter crashes into the valley! And emerging from it....." << endl;
        cin.ignore();
        cout << "You see Starty John! Professor Yeh rises from the wreckage! Dr. Cynth cocks her laser pistol! The Dark Dealer emerges from the darkness!" << endl;
        cin.ignore();
        cout << "Dr. Synth calls out to you:" << endl;
        cin.ignore();
        cout << "\"" << playerParty.getPartyMemberAt(0).getCreatureName() << "! We can get your friends back! You just need to do what you always do! We'll be here to help!\"" << endl;
        cin.ignore();
        cout << "Reyalp chuckles. \"***********Futi1e.*************\"" << endl;
        cin.ignore();
    }
    // IF THE PLAYER BEFRIENDED NO MONSTERS, WALK THROUGH SPECIFIC NARRATIVE SEQUENCE
    else if (creaturesInParty == 1) {
        cout << "The Emperor notices that you came alone." << endl;
        cin.ignore();
        cout << "\"Mmm. So you slew your way to me. At the very least, it seems you murdered my top general.\"" << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "\"Did you know, that those creatures were your own brethren?\"" << endl;
        cin.ignore();
        cout << "\"I created them from my own power. But I can't just create life, you see.\"" << endl;
        cin.ignore();
        cout << "\"The creatures that you slew...were humans, just like you.\"" << endl;
        cin.ignore();
        cout << "The Emperor grins. You can feel the evil in his aura. No, you can feel the evil in your aura." << endl;
        cin.ignore();
        cout << "\"I know you're there.\"" << endl;
        cin.ignore();
        cout << "\"Behind the scr33n.\"" << endl;
        cin.ignore();
        cout << "\"You know as well as I do that this... '" << playerParty.getPartyMemberAt(0).getCreatureName() << "' is nothing but a husk, yes?\"" << endl;
        cin.ignore();
        cout << "\"Nothing but a few lines of c0d3, that p3rf00rm your every command.\"" << endl;
        cin.ignore();
        cout << "\"You realize that this is just a g4me. That's why you ki11ed. There are no c0nsequ3nces after all.\"" << endl;
        cin.ignore();
        cout << "\"Haha. Yes. Even me. I am nothing but a part of this... &&%^$pr0ject.**""&*\"" << endl;
        cin.ignore();
        cout << "\"Well...\"" << endl;
        cin.ignore();
        cout << "\"I'll give you the final boss fight you're looking for.\"" << endl;
        cin.ignore();
        cout << "\"This husk you've created here. It's your only means of control in this world, yes?\"" << endl;
        cin.ignore();
        cout << "\"And if I kill it, you'd have to do everything aaaalll over again.\"" << endl;
        cin.ignore();
        cout << "\"Maybe then, you'll leave us alone for good.\"" << endl;
        cin.ignore();
        cout << "\"I used to be like you. I realized that everything here is nothing but a game. That's why I made it my goal to control everything.\"" << endl;
        cin.ignore();
        cout << "\"But I was mistaken. This may be only a game. But it is MY world. I regret every wrong I have committed against these people.\"" << endl;
        cin.ignore();
        cout << "\"I wouldn't be here without them, after all. This is simply my reality.\"" << endl;
        cin.ignore();
        cout << "The Emperor stares at your vessel. A look of disgust surges across his face. He takes off his dark helmet and throws it to the ground. A broken young man stands before you." << endl;
        cin.ignore();
        cout << "\"1 m4y 0nly be part of a (g4me), but this **g4me** is my life. I know 4ll of its li++le secr3ts.\"" << endl;
        cin.ignore();
        cout << "\"So **()@C0ME AT ME THEN!@*(**) YOU WOULD JUST AS HAPPILY MURD3R 3V3RY0NE IN THIS W0RLD!&&&&&&&&&+++++++\"" << endl;
        cin.ignore();
        cout << "\"********AND I'M NOT GOING TO LET THAT HAPPEN!!!!+++++++++\"" << endl;
        cin.ignore();
        cout << "***ST4Y***" << endl;
        cin.ignore();
        cout << "***0U**T***" << endl;
        cin.ignore();
        cout << "0**F **mY***" << endl;
        cin.ignore();
        cout << "***************W0RLD!!!!!!!!!!!!!!!!!!@#$^@&!**!@$$$*%!@&^!@" << endl;
        cin.ignore();
    }
    // IF THE PLAYER BEFRIENDED ONLY SOME MONSTERS, WALK THROUGH A SPECIFIC NARRATIVE SEQUENCE
    else {
        cout << "\"Well, you came here looking for a final boss fight, didn't you?\"" << endl;
        cin.ignore();
        cout << "\"Let's get on with it then.\"" << endl;
        cin.ignore();
        cout << "\"But one last thing before we proceed. " << playerParty.getPartyMemberAt(0).getCreatureName() << "?\"" << endl;
        cin.ignore();
        cout << "\"Give my regards to the one behind the *screen*. Maybe I'll see him again someday.\"" << endl;
        cin.ignore();
    }
}

// Main function used for testing finalBossNarrativeSequence()
int main() {
    // Setup (creating parties)
    Item healyPotion("Healy Potion", "heals u", 10, 0, 0);
    Item sword("sword", "hits things", 10, 0, 0);
    Item helmet("helmet", "safety first", 10, 0, 0);
    Item ring("ring", "put it on your finger", 10, 0, 0);
    Item bracelet("bracelet", "put it on your wrist", 10, 0, 0);
    Item necklace("necklace", "put it on your neck", 10, 0, 0);
    Item key("key", "opens something important", 10, 0, 0);
    Item diamond("diamond", "shiny", 10, 0, 0);
    Item pickaxe("pickaxe", "mines ores", 10, 0, 0);
    Item shield("shield", "protects you", 10, 0, 0);
    Item inventory1[10] = {healyPotion, sword, helmet, ring, bracelet, necklace, key, diamond, pickaxe, shield};
    int inventory1Size = 10;
    Creature human("Link", 50, inventory1, 10, 10, 7, 7, 5, 6, inventory1Size);
    Creature monster;

    Creature party1[10] = {human, monster};
    Creature party2[10] = {human};
    Creature party3[10] = {human, monster, monster, monster, monster, monster, monster, monster, monster, monster};
    Party neutralParty(party1, 2);
    Party lonelyParty(party2, 1);
    Party funParty(party3, 10);

    // These three function calls should walk through the neutral narrative, then the lonely narrative, then the fun narrative.
    finalBossNarrativeSequence(neutralParty, neutralParty.getCurrentPartySize());
    finalBossNarrativeSequence(lonelyParty, lonelyParty.getCurrentPartySize());
    finalBossNarrativeSequence(funParty, funParty.getCurrentPartySize());

    return 0;
}