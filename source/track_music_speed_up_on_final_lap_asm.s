#include <ppc-asm.h>

.global track_music_speed_up_on_final_lap_hook1
.global track_music_speed_up_on_final_lap_hook1_end
.global track_music_speed_up_on_final_lap_hook2
.global track_music_speed_up_on_final_lap_hook2_end
.global track_music_speed_up_on_final_lap_hook3
.global track_music_speed_up_on_final_lap_hook3_end
.global track_music_speed_up_on_final_lap_hook4
.global track_music_speed_up_on_final_lap_hook4_end
.global track_music_speed_up_on_final_lap_hook5
.global track_music_speed_up_on_final_lap_hook5_end

#original code by Melg, MrBean and CLF78
#https://mariokartwii.com/showthread.php?tid=1948

track_music_speed_up_on_final_lap_hook1:

lis r12, myGlobalVarPtr@ha
lwz r12, myGlobalVarPtr@l (r12)
lbz r12, 0xD (r12)
cmpwi cr1, r12, 1
bne cr1, end_1

#r3 = RaceInfoPlayer[LocalPlayer0], r5 = RACEINFO, r29 = PlayerHolder->PlayerArray[LocalPlayer0 ID]->PlayerPointers->Field 0x1C, r31 = MaxLap of LocalPlayer0

#cr1 = CR bit used later in the function to swap (or not) to the _F version of the brstm

cmpwi cr1, r31, 1    #Check if currentLap>1 (if it's first lap then no laps have been stored in RaceInfo)
beq- cr1, end_1

lis r4, RACEDATA@ha
lwz r4, RACEDATA@l (r4)
lbz r4, 0xb8d (r4) #LapCount
cmplw cr1, r4, r31 #If MaxLap = LapCount, we are on final lap
bne+ cr1, end_1

lwz r4, 0x14 (r5)  #RaceInfo->TimerManager
addi r4, r4, 0x4   #Align with the minutes

lwz r3, 0x3C (r3)  #RaceInfoPlayer[Me]->lapFinishTimes Array
subi r5, r31, 2    #First position of that array gets stored on the transition from lap 1 to 2 (ie MaxLap = 2=
mulli r5, r5, 0xC  #Each array element is 0xC long

add r5, r3, r5     #Get the correct array element depending on the lap

subi r3, sp, 10    #Buffer for the function

lis r12, SubtractTimers@h      #Calculates the time elapsed since the player last crossed the line
ori r12, r12, SubtractTimers@l
mtctr r12
bctrl

subi r3, sp, 10
lhz r4, 0x4 (r3)  #Minutes elapsed
cmpwi cr1, r4, 0  #End if 1m or more
bgt- cr1, end_1

lbz r4, 0x6 (r3)  #Seconds elapsed
cmpwi cr1, r4, 5  #Only execute the speedup for the first 5s
bgt+ cr1, end_1



lwz r3, 0x5C (r29) #0x809C2898 -> Field 0x5BC which gets stored when PlayerHolder gets constructed on loading.
lwz r3, 0x34 (r3)
lwz r3, 0x4 (r3)

#lbz r4, -0x72 (r3) #SpeedupFlag, initially byte 0x3E of the BRSTM
lis r12, myGlobalVarPtr@ha
lwz r12, myGlobalVarPtr@l (r12)
lbz r4, 0xE (r12)
cmpwi cr1, r4, 1   #If it's 1, skip the speedup
beq- cr1, end_1
lwz r4, -0xB4 (r3)
addi r4, r4, 0x68D #Additive speedup
stw r4, -0xB4 (r3)

end_1:
lbz r0, 0xDB (r29) #Default

.long 0
.long 0
track_music_speed_up_on_final_lap_hook1_end:

track_music_speed_up_on_final_lap_hook2:

cmplw r31, r0

#Changes the BRSAR sound ID arg that the game will use for the lap jingle. Before this ASM, there is a "compare current lap with lap count", hence the bne+
li r4, 0xda  #If on final lap, play the normal lap jingle
bne+ end_2
li r4, 0x74  #Else, play the normal lap jingle
end_2:

.long 0
.long 0
track_music_speed_up_on_final_lap_hook2_end:

track_music_speed_up_on_final_lap_hook3:

#The game has already checked that it has correctly loaded the BRSTM Header.

#r29 points to the BRSTM header
lwz r3, 0x74(sp)            #Pointer to a structure where a bunch of music related settings are stored, including volume and speed
lbz r0, 0x3F(r29)           #Get the volume byte

cmpwi r0, 0                 #If the byte hasn't been changed, return
beq+ end_3

stw r0, 0x44(r29)           #Store values in the stack, free space as BRSTM headers are only 0x40 bytes
li r0, 0x7F
stw r0, 0x48(r29)

psq_l f1, 0x44(r29), 0, 4  #Reload floats using paired singles
ps_merge11 f2, f1, f1      #Move f1 ps1 to f2
fdivs f1, f1, f2
stfs f1, -0x5C(r3)


end_3:
lwz r3, 0(r30)             #Original instruction default
lbz r0, 0x3E (r29)
#stb r0, -0x72 (r3)
lis r12, myGlobalVarPtr@ha
lwz r12, myGlobalVarPtr@l (r12)
stb r0, 0xE (r12)
lwz r3, 0 (r30)       #Default

.long 0
.long 0
track_music_speed_up_on_final_lap_hook3_end:

track_music_speed_up_on_final_lap_hook4:

lis r12, myGlobalVarPtr@ha
lwz r12, myGlobalVarPtr@l (r12)
lbz r12, 0xD (r12)
cmpwi cr1, r12, 1
bne cr1, default_behave
li r11, 2
cmplw r12, r11
default_behave:

.long 0
.long 0

track_music_speed_up_on_final_lap_hook4_end:

track_music_speed_up_on_final_lap_hook5:

lis r3, trackMusicSpeedUpPatch4PlusCLwzAddr@ha
lwz r3, trackMusicSpeedUpPatch4PlusCLwzAddr@l (r3)

.long 0
.long 0

track_music_speed_up_on_final_lap_hook5_end: