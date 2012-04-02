// =============================================================================
//  AIVar.h
// =============================================================================
//  Copyright Relic Entertainment, Inc. All rights reserved.
// =============================================================================

#ifndef ___AIVAR_H
#define ___AIVAR_H

#include "Types.h"


// INTERFACE -------------------------------------------------------------------

#define AIVAR_LABEL_MAX_LENGTH 47

typedef struct AIVar
{
    sdword value;
    char label[AIVAR_LABEL_MAX_LENGTH+1];
} AIVar;

void aivarStartup(void);
void aivarShutdown(void);
AIVar *aivarCreate(const char *label);
AIVar *aivarFind(const char *label);
AIVar *aivarFindAnyFSM(const char *label);
char *aivarLabelGenerate(char *label);
char *aivarLabelGet(AIVar *var);
void aivarLabelSet(AIVar *var, const char *label);
void aivarDestroy(AIVar *var);
void aivarDestroyAll(void);
void aivarValueSet(AIVar *var, sdword value);
sdword aivarValueGet(AIVar *var);
void aivarSave(void);
void aivarLoad(void);
sdword AIVarToNumber(AIVar *aivar);
AIVar *NumberToAIVar(sdword number);

extern AIVar *aivRenderMainScreen;

#endif
