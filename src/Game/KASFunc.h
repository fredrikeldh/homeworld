#ifndef ___KASFUNC_H
#define ___KASFUNC_H

#include "AIUtilities.h"
#include "ShipSelect.h"
#include "Volume.h"

//
//  --------------------------------
//  these are for the placeholder for a real fleet intelligence message window
//
//
//  PETER:  we can nuke all this now, right?
//

// seconds
#define POPUPTEXT_DURATION_PER_LINE  4

// chars
#define POPUPTEXT_MAX_LINE_LENGTH  128
#define POPUPTEXT_MAX_LINES  16

// pixels
#define POPUPTEXT_BOX_WIDTH  200

void kasfPopupTextDraw(void);
void kasfPopupText(const char *line);
void kasfPopupTextClear(void);

//
//  --------------------------------
//


//
//  new function prototypes also need to go into KAS2C.C so the
//  translator will recognize them
//

void kasfMissionCompleted(void);
void kasfMissionFailed(void);

void kasfFadeToWhite(void);

void kasfVarCreate(const char *name);
void kasfVarValueSet(const char *name, sdword value);
void kasfVarCreateSet(const char *name, sdword value);
void kasfVarValueInc(const char *name);
void kasfVarValueDec(const char *name);
sdword kasfVarValueGet(const char *name);
void kasfVarDestroy(const char *name);

void kasfCommandMessage(const char *message);

void kasfTimerCreate(const char *name);
void kasfTimerSet(const char *name, sdword duration);
void kasfTimerStart(const char *name);
void kasfTimerCreateSetStart(const char *name, sdword duration);
void kasfTimerStop(const char *name);
void kasfHarvest(void);
sdword kasfTimerRemaining(const char *name);
sdword kasfTimerExpired(const char *name);
sdword kasfTimerExpiredDestroy(const char *name);
void kasfTimerDestroy(const char *name);

sdword kasfMsgReceived(const char *msg);

void kasfAttackMothership(void);
void kasfAttack(GrowSelection *targets);
void kasfAttackFlank(GrowSelection *targets);
void kasfAttackHarass(void);
void kasfAttackSpecial(GrowSelection *targets);
void kasfMoveAttack(GrowSelection *targets);
sdword kasfBulgeAttack(GrowSelection *targets, GrowSelection *bulgetargets, GrowSelection *attackers, sdword radius);
void kasfIntercept(GrowSelection *targets);
void kasfTargetDrop(void);
void kasfSetSwarmerTargets(GrowSelection *targets);
void kasfSwarmMoveTo(GrowSelection *targets);
void kasfShipsAttack(GrowSelection *targets, GrowSelection *attackers);

void kasfFormationDelta(void);
void kasfFormationBroad(void);
void kasfFormationDelta3D(void);
void kasfFormationClaw(void);
void kasfFormationWall(void);
void kasfFormationSphere(void);
void kasfFormationCustom(GrowSelection *shipsg);

sdword kasfRandom(sdword lowestNum, sdword highestNum);

void kasfGuardMothership(void);
void kasfGuardShips(GrowSelection *ships);

void kasfPatrolPath(Path *path);
void kasfPatrolActive(void);

void kasfLog(const char *string);
void kasfLogInteger(const char *string, sdword integer);

sdword kasfTeamHealthAverage(void);
sdword kasfTeamHealthLowest(void);
sdword kasfTeamFuelAverage(void);
sdword kasfTeamFuelLowest(void);
sdword kasfTeamCount(void);
sdword kasfTeamCountOriginal(void);
sdword kasfNewShipsAdded(void);

void kasfGrowSelectionClear(GrowSelection *ships);

void kasfTeamAttributesBitSet(sdword attributes);
void kasfTeamAttributesBitClear(sdword attributes);
void kasfTeamAttributesSet(sdword attributes);

void kasfShipsAttributesBitSet(GrowSelection *ships,sdword attributes);
void kasfShipsAttributesBitClear(GrowSelection *ships,sdword attributes);
void kasfShipsAttributesSet(GrowSelection *ships,sdword attributes);

sdword kasfShipsDisabled(GrowSelection *ships);

sdword kasfShipsCount(GrowSelection *ships);

sdword kasfPointInside(Volume *volume, hvector *location);

sdword kasfFindShipsInside(Volume *volume, GrowSelection *ships);
sdword kasfFindEnemiesInside(Volume *volume, GrowSelection *ships, sdword neighborRadius);
sdword kasfFindEnemiesNearby(GrowSelection *ships, sdword radius);
sdword kasfFindEnemiesNearTeam(GrowSelection *ships, sdword radius);
sdword kasfFindEnemyShipsOfType(GrowSelection *ships, const char *shipType);
sdword kasfFindFriendlyShipsOfType(GrowSelection *ships, const char *shipType);
sdword kasfFindEnemyShipsOfClass(GrowSelection *ships, const char *shipClass);
sdword kasfFindFriendlyShipsOfClass(GrowSelection *ships, const char *shipClass);
sdword kasfFindShipsNearPoint(GrowSelection *ships, hvector *location, sdword radius);

void kasfTeamSkillSet(sdword skillLevel);
sdword kasfTeamSkillGet(void);

void kasfDisablePlayerHyperspace(void);
void kasfHoldHyperspaceWindow(bool hold);
void kasfTeamHyperspaceIn(hvector *destination);
void kasfTeamHyperspaceInNear(hvector *destination, sdword distance);
void kasfTeamHyperspaceOut(void);
void kasfHyperspaceDelay(sdword milliseconds);

void kasfGateDestroy(hvector *gatePoint);
void kasfGateShipsIn(GrowSelection *ships, hvector *gatePoint);
void kasfGateShipsOut(GrowSelection *ships, hvector *gatePoint);
void kasfGateMoveToNearest(void);
sdword kasfGateShipsOutNearest(GrowSelection *ships);

void kasfMissionSkillSet(sdword skillLevel);
sdword kasfMissionSkillGet(void);

void kasfRequestShips(const char *shipType, sdword numShips);
void kasfRequestShipsOriginal(sdword percentOriginal);

void kasfReinforce(struct AITeam *team);

void kasfTeamGiveToAI(void);

void kasfDisableAIFeature(sdword feature, sdword type);
void kasfEnableAIFeature(sdword feature, sdword type);
void kasfDisableAllAIFeatures(void);
void kasfEnableAllAIFeatures(void);

void kasfTeamSwitchPlayerOwner(void);
void kasfShipsSwitchPlayerOwner(GrowSelection *ships);

void kasfReinforceTeamWithShips(struct AITeam *teamtoreinforce,GrowSelection *shipstoadd);
void kasfTeamMakeCrazy(sdword makecrazy);

void kasfForceCombatStatus(GrowSelection *ships, sdword on);

sdword kasfThisTeamIs(struct AITeam *team);

void kasfMoveTo(hvector *destination);
void kasfShipsMoveTo(GrowSelection *ships, hvector *destination);

void kasfTacticsAggressive(void);
void kasfTacticsNeutral(void);
void kasfTacticsEvasive(void);

sdword kasfNearby(hvector *location, sdword distance);
sdword kasfFindDistance(hvector *location1, hvector *location2);

sdword kasfUnderAttack(GrowSelection *attackers);
sdword kasfUnderAttackElsewhere(struct AITeam *otherTeam, GrowSelection *attackers);

sdword kasfShipsCountType(GrowSelection *ships, const char *shipType);

void kasfDock(struct AITeam *withTeam);
void kasfDockSupport();
void kasfDockSupportWith(struct AITeam * withTeam);
void kasfShipsDockSupportWith(GrowSelection *ships, GrowSelection *withShips);
void kasfDockStay(struct AITeam * withTeam);
void kasfShipsDockStay(GrowSelection *ships, GrowSelection *withShips);
void kasfDockStayMothership(void);
void kasfDockInstant(struct AITeam * withTeam);
void kasfLaunch();

sdword kasfTeamDocking(void);
sdword kasfTeamDockedReadyForLaunch(void);
sdword kasfTeamFinishedLaunching(void);

void kasfMsgSend(struct AITeam *team, const char *msg);
void kasfMsgSendAll(const char *msg);

sdword kasfRUsEnemyCollected(void);

sdword kasfPathNextPoint(void);

sdword kasfNISRunning(void);

void kasfTeamSetMaxVelocity(sdword maxVelocity);
void kasfTeamClearMaxVelocity(void);
void kasfShipsSetMaxVelocity(GrowSelection *ships, sdword maxVelocity);
void kasfShipsClearMaxVelocity(GrowSelection *ships, sdword maxVelocity);
void kasfShipsSetDamageFactor(GrowSelection *ships, sdword damagePercent);
void kasfShipsClearDamageFactor(GrowSelection *ships);
void kasfTeamSetPercentDamaged(sdword percentDamaged);
void kasfTeamSetPercentFueled(sdword percentFueled);

sdword kasfShipsSelectEnemy(GrowSelection *newShips, GrowSelection *originalShips);
sdword kasfShipsSelectFriendly(GrowSelection *newShips, GrowSelection *originalShips);
sdword kasfShipsSelectClass(GrowSelection *newShips, GrowSelection *originalShips, const char *shipClass);
sdword kasfShipsSelectType(GrowSelection *newShips, GrowSelection *originalShips, const char *shipType);
sdword kasfShipsSelectDamaged(GrowSelection *newShips, GrowSelection *originalShips, sdword maxHealthPercent);
sdword kasfShipsSelectMoving(GrowSelection *newShips, GrowSelection *originalShips);
sdword kasfShipsSelectCapital(GrowSelection *newShips, GrowSelection *originalShips);
sdword kasfShipsSelectNonCapital(GrowSelection *newShips, GrowSelection *originalShips);
sdword kasfShipsSelectNotDocked(GrowSelection *newShips, GrowSelection *originalShips);
sdword kasfShipsSelectIndex(GrowSelection *newShips, GrowSelection *originalShips, sdword Index);
sdword kasfShipsSelectNearby(GrowSelection *newShips, GrowSelection *originalShips, hvector *location, sdword distance);

sdword kasfShipsOrder(GrowSelection *ships);
sdword kasfShipsOrderAttributes(GrowSelection *ships);

#define kasSpecial_ReturningTechnology  1  //ships are salcapcorvettes returning technology
#define kasSpecial_ShipsDisabled        2  //ships have been disabled (salcapcorvette has locked on)
#define kasSpecial_ShipsAreArmed        3  //ships have arms on them - includes GravWellGenerator as an armed ship
#define kasSpecial_ShipsDefected        4  //ships have defected to the other side
sdword kasfShipsSelectSpecial(GrowSelection *newShips, GrowSelection *originalShips, sdword SpecialFlag);


sdword kasfShipsAdd(GrowSelection *shipsA, GrowSelection *shipsB);
sdword kasfShipsRemove(GrowSelection *shipsA, GrowSelection *shipsB);

void kasfShipsSetNonRetaliation(GrowSelection *ships);
void kasfShipsSetRetaliation(GrowSelection *ships);

void kasfPingAddSingleShip(GrowSelection *ships, const char *label);
void kasfPingAddShips(GrowSelection *ships, const char *label);
void kasfPingAddPoint(hvector *point, const char *label);
void kasfPingRemove(const char *label);

void kasfBuildControl(sdword on);
void kasfBuildingTeam(struct AITeam *builder);

void kasfStop(void);

void kasfKamikaze(GrowSelection *targets);
void kasfKamikazeEveryone(GrowSelection *targets);

void kasfPopup(const char *text);
void kasfPopupInteger(const char *text, sdword integer);

void kasfObjectiveCreate(const char *label, const char *briefText, const char *fullText);
void kasfObjectiveCreateSecondary(const char *label, const char * briefText, const char * fullText);
void kasfObjectiveSet(const char *label, sdword status);
//void kasfObjectivePopupAll(void);
sdword kasfObjectiveGet(const char *label);
sdword kasfObjectiveGetAll(void);
void kasfObjectiveDestroy(const char *label);
void kasfObjectiveDestroyAll(void);

void kasfSpecialToggle(void);

void kasfShipsDamage(GrowSelection *ships, sdword points);

void kasfForceTaskbar(void);

// Tutorial helper functions for kas ------------
void kasfBuilderRestrictShipTypes(const char *shipTypes);
void kasfBuilderUnrestrictShipTypes(const char *shipTypes);
void kasfBuilderRestrictAll(void);
void kasfBuilderRestrictNone(void);
void kasfBuilderCloseIfOpen(void);
void kasfForceBuildShipType(const char *shipType);

sdword kasfCameraGetAngleDeg(void);
sdword kasfCameraGetDeclinationDeg(void);
sdword kasfCameraGetDistance(void);

sdword kasfSelectNumSelected(void);
sdword kasfSelectIsSelectionShipType(sdword Index, const char *shipType);
sdword kasfSelectContainsShipTypes(const char *shipTypes);
sdword kasfSelectedShipsInFormation(sdword formation);
sdword kasfShipsInFormation(GrowSelection *ships, sdword formation);

void kasfTutSetPointerTargetXY(const char *name, sdword x, sdword y);
void kasfTutSetPointerTargetXYRight(const char *name, sdword x, sdword y);
void kasfTutSetPointerTargetXYBottomRight(const char *name, sdword x, sdword y);
void kasfTutSetPointerTargetXYTaskbar(const char *name, sdword x, sdword y);
void kasfTutSetPointerTargetXYFE(const char *name, sdword x, sdword y);
void kasfTutSetPointerTargetShip(const char *name, GrowSelection *ships);
void kasfTutSetPointerTargetShipSelection(const char *name, GrowSelection *ships);
void kasfTutSetPointerTargetShipHealth(const char *name, GrowSelection *ships);
void kasfTutSetPointerTargetShipGroup(const char *name, GrowSelection *ships);
void kasfTutSetPointerTargetFERegion(const char *name, const char *pAtomName);
void kasfTutSetPointerTargetRect(const char *name, sdword x0, sdword y0, sdword x1, sdword y1);
void kasfTutSetPointerTargetAIVolume(const char *name, Volume *volume);
void kasfTutRemovePointer(const char *name);
void kasfTutRemoveAllPointers(void);

void kasfTutSetTextDisplayBoxGame(sdword x, sdword y, sdword width, sdword height);
void kasfTutSetTextDisplayBoxFE(sdword x, sdword y, sdword width, sdword height);
void kasfTutSetTextDisplayBoxToSubtitleRegion(void);
void kasfTutShowText(const char *szText);
void kasfTutHideText(void);
void kasfTutShowNextButton(void);
void kasfTutHideNextButton(void);
sdword kasfTutNextButtonClicked(void);
void kasfTutShowBackButton(void);
void kasfTutHideBackButton(void);
void kasfTutShowPrevButton(void);
void kasfTutSaveLesson(sdword Num, const char *pName);

void kasfTutShowImages(const char *szImages);
void kasfTutHideImages(void);

void kasfTutEnableEverything(void);
void kasfTutDisableEverything(void);
void kasfTutEnableFlags(const char *pFlags);
void kasfTutDisableFlags(const char *pFlags);
void kasfTutForceUnpaused(void);

sdword kasfTutGameSentMessage(const char *commandNames);
void kasfTutResetGameMessageQueue(void);
sdword kasfTutContextMenuDisplayedForShipType(const char *shipType);
void  kasfTutResetContextMenuShipTypeTest(void);
void kasfTutRedrawEverything(void);

sdword kasfBuildManagerShipTypeInBatchQueue(const char *shipType);
sdword kasfBuildManagerShipTypeInBuildQueue(const char *shipType);
sdword kasfBuildManagerShipTypeSelected(const char *shipType);

sdword kasfTutCameraFocusedOnShipType(const char *shipTypes);
void kasfTutCameraFocus(GrowSelection *ships);
void kasfTutCameraFocusDerelictType(const char *derelictType);
void kasfTutCameraFocusFar(GrowSelection *ships);
void kasfTutCameraFocusCancel(void);

void kasfDisablePlayer(bool toggle);

sdword kasfTutShipsInView(GrowSelection *ships);
sdword kasfTutShipsTactics(GrowSelection *ships);

sdword kasfTutPieDistance(void);
sdword kasfTutPieHeight(void);

void kasfForceFISensors(void);
void kasfOpenSensors(sdword flag);
void kasfCloseSensors(sdword flag);
sdword kasfSensorsIsOpen(sdword flag);
void kasfSensorsWeirdness(sdword flag);

void kasfAllowPlayerToResearch(const char *name);
void kasfAllowPlayerToPurchase(const char *name);
void kasfPlayerAcquiredTechnology(const char *name);
sdword kasfCanPlayerResearch(const char *name);
sdword kasfCanPlayerPurchase(const char *name);
sdword kasfDoesPlayerHave(const char *name);
void kasfSetBaseTechnologyCost(const char *name, sdword cost);
sdword kasfGetBaseTechnologyCost(const char *name);
sdword kasfTechIsResearching(void);

void kasfEnableTraderGUI(void);
sdword kasfTraderGUIActive(void);
void kasfSetTraderDialog(sdword dialogNum, const char *text);
void kasfSetTraderPriceScale(sdword percent);
sdword kasfGetTraderPriceScale(void);
void kasfSetTraderDisabled(sdword disable);

sdword kasfRUsGet(sdword player);
void kasfRUsSet(sdword player, sdword RUs);

sdword kasfGetWorldResources(void);

void kasfSoundEvent(sdword event);
void kasfSoundEventShips(GrowSelection *ships, sdword event);

void kasfSpeechEvent(sdword event, sdword variable);
void kasfSpeechEventShips(GrowSelection *ships, sdword event, sdword variable);

void kasfToggleActor(sdword Actor, sdword on);

void kasfMusicPlay(sdword trackNum);
void kasfMusicStop(sdword fadeTime);

sdword kasfRenderedShips(GrowSelection *ships, sdword LOD);
void kasfResetShipRenderFlags(GrowSelection *ships);
sdword kasfRenderedDerelicts(const char *derelictType, sdword LOD);
void kasfResetDerelictRenderFlags(const char *derelicttype);

udword kasfFindSelectedShips(GrowSelection *ships);

void kasfSaveLevel(sdword num, const char *name);

void kasfClearScreen(void);

void kasfWideScreenIn(sdword frames);
void kasfWideScreenOut(sdword frames);
void kasfSubtitleSimulate(sdword actor, sdword milliseconds, const char *speech);
void kasfLocationCard(sdword milliseconds, const char *location);
void kasfHideShips(GrowSelection *ships);
void kasfUnhideShips(GrowSelection *ships);

void kasfDeleteShips(GrowSelection *ships);

void kasfRotateDerelictType(const char *derelictType, sdword rot_x, sdword rot_y, sdword rot_z, sdword variation);

sdword kasfRaceOfHuman(void);
void kasfUniversePause(void);
void kasfUniverseUnpause(void);
void kasfPauseBuildShips(void);
void kasfUnpauseBuildShips(void);
void kasfOtherKASPause(void);
void kasfOtherKASUnpause(void);

sdword kasfIntelEventEnded(void);
void kasfIntelEventNotEnded(void);
void kasfForceIntelEventEnded(void);

//turn sensors manager static on/off
void kasfSensorsStaticOn(void);
void kasfSensorsStaticOff(void);

//end the game right now and start plugscreens
void kasfGameEnd(void);

void kasfSpawnEffect(GrowSelection *ships, const char *effectName, sdword parameter);

#endif
