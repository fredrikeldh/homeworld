/*=============================================================================
    Name    : statscript.h
    Purpose : Definitions for statscript.c (Static Scripting Utilities)

    Created 6/24/1997 by gshaw
    Copyright Relic Entertainment, Inc.  All rights reserved.
=============================================================================*/

#ifndef ___STATSCRIPT_H
#define ___STATSCRIPT_H

#include "ObjTypes.h"
#include "Types.h"

/*=============================================================================
    Types:
=============================================================================*/

typedef void (*setVarCback)(const char *directory,char *field,void *dataToFillIn);

typedef struct
{
    const char *name;
    setVarCback setVarCB;
    void * offset1;     // should really be 1 offset, but I can't get rid of this strange compiler error
    void * offset2;
} scriptStructEntry;

typedef struct
{
    const char *name;
    setVarCback setVarCB;
    void *dataPtr;
} scriptEntry;

///////DATA!!!!
extern char globalScriptFileName[50];  //file name of file loaded in a script callback function


/*=============================================================================
    Macros
=============================================================================*/

// for filling in scriptEntry
#define makeEntry(var,callback)  { strdollar(var), callback, &(var) }
#define END_SCRIPT_STRUCT_ENTRY  { NULL, NULL, 0, 0 }
#define END_SCRIPT_ENTRY         { NULL, NULL, NULL }

/*=============================================================================
    Functions:
=============================================================================*/

struct StaticInfoHealthGuidanceShipDerelict;
struct ShipStaticInfo;

void RemoveCommasFromString(char *field);
void StripTrailingSpaces(char *value);

void scriptSetRGBCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetRGBACB(const char *directory,char *field,void *dataToFillIn);
void scriptSetReal32CB(const char *directory,char *field,void *dataToFillIn);
void scriptSetReal32CB_ARRAY(const char *directory,char *field,void *dataToFillIn);
void scriptSetReal32SqrCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetSbyteCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetUbyteCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetSwordCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetUwordCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetSdwordCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetUdwordCB(const char *directory,char *field,void *dataToFillIn);
bool scriptStringToBool(char *boolString);
void scriptSetBool8(const char *directory,char *field,void *dataToFillIn);
void scriptSetBool(const char *directory,char *field,void *dataToFillIn);
void scriptSetBitUdword(const char *directory,char *field,void *dataToFillIn);
void scriptSetBitUword(const char *directory,char *field,void *dataToFillIn);
void scriptSetStringCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetStringPtrCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetCosAngCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetCosAngSqrCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetCosAngCB_ARRAY(const char *directory,char *field,void *dataToFillIn);
void scriptSetSinAngCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetTanAngCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetAngCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetGunTypeCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetGunSoundTypeCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetBulletTypeCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetShipClassCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetShipRaceCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetShipTypeCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetVectorCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetLWToHWMonkeyVectorCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetFormationCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetTacticsCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetSalvagePointCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetSalvageStatCB(const char *directory,char *field,void *dataToFillIn);
void scriptSetSalvageStatics(const char *directory,const char *filename,struct StaticInfoHealthGuidanceShipDerelict *statinfo);
void scriptSetDockOverideStatics(const char *directory,const char *filename,struct ShipStaticInfo *shipstatinfo);

void scriptSetStruct(const char *directory,const char *filename,scriptStructEntry info[],ubyte *structureToFillIn);
void scriptSet(const char *directory,const char *filename,scriptEntry info[]);
void scriptSetFileSystem(const char *directory,const char *filename,scriptEntry info[]);
void scriptSetGunStatics(const char *directory,const char *filename,struct ShipStaticInfo *shipstatinfo);
void scriptSetNAVLightStatics(const char *directory,const char *filename,struct ShipStaticInfo *shipstatinfo);
void scriptSetDockStatics(const char *directory,const char *filename,struct ShipStaticInfo *statinfo);
struct SphereStaticInfo *scriptSetSphereStaticInfo(const char *directory,const char *filename);
void scriptSetShipGroupSizeCB(const char *directory, char *field, void *dataToFillIn);
void scriptSetShipProbCB(const char *directory, char *field, void *dataToFillIn);
void scriptSetHyperspaceCostCB(const char *directory, char *field, void *dataToFillIn);
void scriptSetSpecialDoorOffsetCB(const char *directory, char *field, void *dataToFillIn);
void scriptSetBlobPropertyOverlap(const char *directory,char *field,void *dataToFillIn);
void scriptSetBlobBiggestRadius(const char *directory,char *field,void *dataToFillIn);

// sets all tweakable global variables in game
void scriptSetTweakableGlobals(void);

void mgGameTypeScriptInit();

#ifdef HW_BUILD_FOR_DEBUGGING
void CheckValidTacticsClass(TacticsType tactic,ShipClass shipclass,char *field);
#endif

#endif

