#ifndef ___KAS_H
#define ___KAS_H

#include "AIUtilities.h"
#include "ShipSelect.h"
#include "Vector.h"

// run-time scoping for variables, timers, etc.
enum {
    KAS_SCOPE_MISSION,
    KAS_SCOPE_FSM,
    KAS_SCOPE_STATE};

typedef void (*KASInitFunction) (void);
typedef void (*KASWatchFunction) (void);

//  these have corresponding #defines in kas2c.h
#define KAS_MISSION_NAME_MAX_LENGTH 47
#define KAS_FSM_NAME_MAX_LENGTH 47
#define KAS_STATE_NAME_MAX_LENGTH 47

//  user variables for SHIPS
#define KASSELECTION_ALLOC_INCREMENT 16
#define KASSELECTION_MAX_LABEL_LENGTH 47
typedef struct {
    char label[KASSELECTION_MAX_LABEL_LENGTH+1];
    GrowSelection shipList;
} KasSelection;

//
//  labelled entities in mission layout file
//
#define KAS_MAX_LABEL_LENGTH 47
#define KAS_LABELLED_ENTITY_ALLOC_INCREMENT 16
//  team labels are stored in AITeam struct
typedef struct {
    char label[KAS_MAX_LABEL_LENGTH+1];
    Path *path;
} LabelledPath;
typedef struct {
    char label[KAS_MAX_LABEL_LENGTH+1];
    hvector *hvector;
} LabelledVector;
typedef struct {
    char label[KAS_MAX_LABEL_LENGTH+1];
    Volume *volume;
} LabelledVolume;


/*=============================================================================
    Functions
=============================================================================*/
//  to fill in table of labelled mission layout entities
void kasLabelsInit();
//void kasLabelledAITeamAdd(const char *label);
Path *kasLabelledPathAdd(const char *label, sdword numPoints, sdword closed);
hvector *kasLabelledVectorAdd(const char *label, real32 x, real32 y, real32 z,real32 w);
Volume *kasLabelledVolumeAdd(const char *label);

void kasMissionStart(const char *name, KASInitFunction initFunction, KASWatchFunction watchFunction);
void kasExecute(void);

// keywords of KAS language
void kasJump(const char *stateName, KASInitFunction initFunction, KASWatchFunction watchFunction);
void kasFSMCreate(const char *fsmName, KASInitFunction initFunction, KASWatchFunction watchFunction, struct AITeam *team);

// labels: resolves references from script to mission layout file
struct AITeam *kasAITeamPtr(const char *label);
GrowSelection *kasAITeamShipsPtr(const char *label);
hvector *kasShipsVectorPtr(const char *label);
hvector *kasTeamsVectorPtr(const char *label);
hvector *kasVolumeVectorPtr(const char *label);
hvector *kasThisTeamsVectorPtr(void);
Path   *kasPathPtr(const char *label);
Path *kasPathPtrNoErrorChecking(const char *label);
Volume *kasVolumePtr(const char *label);
hvector *kasVectorPtr(const char *label);
hvector *kasVectorPtrIfExists(const char *label);
GrowSelection *kasGrowSelectionPtr(const char *label);

GrowSelection *kasGetGrowSelectionPtrIfExists(const char *label);

void kasShipDied(Ship *ship);

void kasGrowSelectionClear(GrowSelection *ships);

void kasLabelledEntitiesDestroy(void);

void kasAddShipToTeam(Ship *ship,const char *str);

#define KAS_TEAM_NAME_MAX_LENGTH 47
char *kasAITeamName(struct AITeam *team, char *teamName);

void kasTakeADump(void);
void kasDebugDraw(void);
#define KAS_DEBUG_TEXTCOLOR            colRGB(64, 255, 196)

void kasTeamDied(struct AITeam *team);

void kasClose();
void kasInit();

// Save Game Stuff
void kasSave(void);
void kasLoad(void);
const void *kasConvertOffsetToFuncPtr(sdword offset);
sdword kasConvertFuncPtrToOffset(void *func);


#endif
