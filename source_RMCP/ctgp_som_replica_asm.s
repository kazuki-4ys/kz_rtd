#include <ppc-asm.h>

.macro pushStack
    stwu sp, -0x80 (sp)#124 + パディング
    mflr r0
    stw r0, 0x84 (sp)
    stmw r3, 8 (sp)
.endm

.macro popStack
    lmw r3, 8 (sp)
    lwz r0, 0x84 (sp)
    mtlr r0
    addi sp, sp, 0x80
.endm

.global get_ctgp_som_replica_patch1
.global get_ctgp_som_replica_patch1_end
.global get_ctgp_som_replica_patch2
.global get_ctgp_som_replica_patch2_end
.global get_ctgp_som_replica_patch3
.global get_ctgp_som_replica_patch3_end
.global get_ctgp_som_replica_patch4
.global get_ctgp_som_replica_patch4_end


get_ctgp_som_replica_patch1_end:
    mflr r12
    b get_ctgp_som_replica_patch1_end_b
get_ctgp_som_replica_patch1:
    mflr r12
bl blTrickCommonEnd
ctgp_som_replica_patch1:

#by stebler
#https://mariokartwii.com/showthread.php?tid=1730


lwz r5, 0x4 (r3)

cmpwi r5, 0xc # grand prix
beq increment

cmpwi r5, 0xe # 1 player offline vs
beq increment

cmpwi r5, 0x12 # 1 player battle
beq increment

cmpwi r5, 0x40 # 1 player ww/regional vs
beq increment

cmpwi r5, 0x42 # 1 player friend room vs
beq increment

b end1

increment:
addi r4, r4, 0x1

end1:
mr r5, r4 # original instruction

.long 0
get_ctgp_som_replica_patch1_end_b:
    bl blTrickCommonEnd

get_ctgp_som_replica_patch2_end:
    mflr r12
    b get_ctgp_som_replica_patch2_end_b
get_ctgp_som_replica_patch2:
    mflr r12
bl blTrickCommonEnd
ctgp_som_replica_patch2:

#by stebler
#https://mariokartwii.com/showthread.php?tid=1730

rlwinm. r0, r16, 0x0, 19, 19 # original instruction
bne end2

lwz r3, 0x4 (r15)

cmpwi r3, 0xc # grand prix
beq invert

cmpwi r3, 0xe # 1 player offline vs
beq invert

cmpwi r3, 0x12 # 1 player battle
beq invert

cmpwi r3, 0x40 # 1 player ww/regional vs
beq invert

cmpwi r3, 0x42 # 1 player friend room vs

invert:
crnot 4 * cr0 + eq, 4 * cr0 + eq

end2:

.long 0
get_ctgp_som_replica_patch2_end_b:
    bl blTrickCommonEnd

get_ctgp_som_replica_patch3_end:
    mflr r12
    b get_ctgp_som_replica_patch3_end_b
get_ctgp_som_replica_patch3:
    mflr r12
bl blTrickCommonEnd
ctgp_som_replica_patch3:

#replace ghost cannot save message to ctgp som control
    pushStack
    mr r14, r3
    bl get_data0
    mr r4, r3
    bl get_data1
    mr r5, r3
    bl get_data2
    mr r6, r3
    bl get_data3
    mr r7, r3
    mr r3, r14
	lis r12, ControlLoader__Load@h
    ori r12, r12, ControlLoader__Load@l#必要な引数を設定してこれを呼び出すことでメッセージの変わりにスピメのbrctrをロード
    mtlr r12
    blrl
    lwz r14, 0 (r14) #UILayoutControlへのポインタをr14へ格納
    lis r12, 0x8000
    lwz r12, 0xCC0 (r12)
    stw r14, 8 (r12)
	b end3

#bl trickにより文字列などの配列データ取得

get_data0:
    mflr r12
    bl blTrickCommonEnd
    .string "game_image"
    .balign 4

get_data1:
    mflr r12
    bl blTrickCommonEnd
    .string "speedometer"
    .balign 4

get_data2:
    mflr r12
    bl blTrickCommonEnd
    .string "CtrlSpeedometer_1_0"
    .balign 4

get_data3:
    mflr r12
    bl blTrickCommonEnd
    .long 0
    .long 0

end3:
    popStack
    .long 0
get_ctgp_som_replica_patch3_end_b:
    bl blTrickCommonEnd

get_ctgp_som_replica_patch4_end:
    mflr r12
    b get_ctgp_som_replica_patch4_end_b
get_ctgp_som_replica_patch4:
    mflr r12
bl blTrickCommonEnd
ctgp_som_replica_patch4:


.set region, 'P'

.if (region == 'P')
    .set ptr_raceData, 0x809bd728
    .set ptr_menuData, 0x809c1e38
    .set swprintf, 0x80017814
    .set LayoutUIControl__setMessageAll, 0x8063ddb4
    .set ControlLoader__Load, 0x805c2c60
.elseif (region == 'E')
    .set ptr_raceData, 0x809b8f68
    .set ptr_menuData, 0x809bd508
    .set swprintf, 0x80016cb4
    .set LayoutUIControl__setMessageAll, 0x8060c994
    .set ControlLoader__Load, 0x805ba2cc
.elseif (region == 'J')
    .set ptr_raceData, 0x809bc788
    .set ptr_menuData, 0x809c0e98
    .set swprintf, 0x80017738
    .set LayoutUIControl__setMessageAll, 0x8063d420
    .set ControlLoader__Load, 0x805c25e0
.elseif (region == 'K')
    .set ptr_raceData, 0x809abd68
    .set ptr_menuData, 0x809b0478
    .set swprintf, 0x8001787c
    .set LayoutUIControl__setMessageAll, 0x8062c0cc
    .set ControlLoader__Load, 0x805b0cc4
.else
        .err
.endif

#original code by stebler
#https://mariokartwii.com/showthread.php?tid=1730

    lwz r3, 0x0 (r29)
    lwz r3, 0x0 (r3)
    lbz r3, 0x10 (r3)


    # get the player index from the first hud slot
    lis r4, ptr_raceData@ha
    lwz r4, ptr_raceData@l (r4)
    lbz r4, 0xb84 (r4)
    ## if they don't match, the speedometer will not be updated
    cmpw r3, r4
    bne end4
    
    # check if a single player gameplay screen is active
    lis r3, ptr_menuData@ha
    lwz r3, ptr_menuData@l (r3)
    lwz r3, 0x0 (r3)
    
    lwz r28, 0x38 (r3) # grand prix
    cmpwi r28, 0x0
    bne found
    
    lwz r28, 0x3c (r3) # time trial
    cmpwi r28, 0x0
    bne found
    
    lwz r28, 0x40 (r3) # 1 player offline vs
    cmpwi r28, 0x0
    bne found
    
    lwz r28, 0x50 (r3) # 1 player battle
    cmpwi r28, 0x0
    bne found
    
    lwz r28, 0x108 (r3) # 1 player ww/regional vs
    cmpwi r28, 0x0
    bne found
    
    lwz r28, 0x110 (r3) # 1 player friend room vs
    cmpwi r28, 0x0
    bne found
    
    b end4
    
    found:
    lfs f1, 0x20 (r29) #f1はスピード

    fabs f1, f1 #f1の絶対値をf1に格納

    bl format

    .string16 "%.2f"
    .balign 4

    format:
    addi sp, sp, -0x28 #16文字分のバッファとswprintfが使う8バイト分をスタックメモリから確保
    crset 4 * cr1 + eq #???swprintfなどの可変個引数を持つ関数だと必要？らしい？

    mflr r5

    #myGlobalVarPtr->somDigitで小数点以下の桁数を指定できるように改変
    lis r4, 0x8000
    lwz r4, 0xCC0 (r4)
    lbz r4, 0xC (r4)
    addi r4, r4, 0x30
    sth r4, 4 (r5)

    li r4, 0x10 #出力先のバッファサイズに16文字分を指定
    addi r3, sp, 8
    lis r12, swprintf@h
    ori r12, r12, swprintf@l
    mtlr r12
    blrl

    addi r4, sp, 8
    mr r6, r4

    pushStack

#スピード値をデジタル表記にするためのループ
    change_to_degital_loop:
    lhz r3, 0x0 (r4)
    cmpwi r3, 0x0
    beq change_to_degital_loop_out

    cmpwi r3, 0x2d
    bne not_a_dash
    li r3, 0x246d

    not_a_dash:
    cmpwi r3, 0x2e
    bne not_a_dot
    li r3, 0x246b

    not_a_dot:
    subi r5, r3, 0x30
    cmplwi r5, 0x9
    bgt not_a_digit
    addi r3, r5, 0x2460

    not_a_digit:
    sth r3, 0x0 (r4)
    addi r4, r4, 0x1
    b change_to_degital_loop

change_to_degital_loop_out:

    mr r4, r6
    li r5, 0
    lis r3, 0x8000
    lwz r3, 0xCC0 (r3)
    lwz r3, 8 (r3)
    cmpwi r3, 0
    beq skip_set_message

    li r6, 0
    stb r6, 0x80 (r3) #LayoutUIControlをみえるようにする

    lis r12, LayoutUIControl__setMessageAll@h
    ori r12, r12, LayoutUIControl__setMessageAll@l
    mtlr r12
    blrl
    #他のコードでLayoutUIControl__setMessageAllの機能を拡張されているため、r5が0ならconst whcar_t*型の文字列r4を直接適用させられる
    #詳しくはhttps://mariokartwii.com/showthread.php?tid=1730参照

    skip_set_message:
    
    popStack

    addi sp, sp, 0x28


end4:
    lwz r31, 0x7c (sp) # original instruction
    .long 0

get_ctgp_som_replica_patch4_end_b:
    bl blTrickCommonEnd