// =============================================================================
//  AIAttackMan.c
//  - Attack manager
// =============================================================================
//  Copyright Relic Entertainment, Inc. All rights reserved.
//  Created 1998/05/28 by gshaw
// =============================================================================

#include <vector>
#include "AIAttackMan.h"

#include "AIFeatures.h"
#include "AIHandler.h"
#include "AIMoves.h"
#include "AIOrders.h"
#include "MultiplayerGame.h"
#include "Randy.h"
#include "Select.h"
#include "Stats.h"


#define MAX_NUM_HARASS_TEAMS    2

/*-----------------------------------------------------------------------------
    Name        : aiaPriorityShipsConstraints
    Description : Decides which ship should be a priority to take out
                  Note: only prioritizes with respect to dangerous combat ships,
                        other risky non-combat ships will be dealt with in different
                        ways.
    Inputs      : shipstatic - the static info of the shiptype to constraint
    Outputs     :
    Return      : TRUE if the ship is one to take out
----------------------------------------------------------------------------*/
static bool aiaPriorityShipsConstraints(Ship *ship)
{
    ShipStaticInfo *shipstatic = ship->staticinfo;
    bool dangerous = false;

    if (aiuShipIsntAnEnemyMothership(ship))
    {
        switch (shipstatic->shipclass)
        {
            case CLASS_HeavyCruiser:
                //oh yeah... this one's dangerous
            case CLASS_Carrier:
                //take out this one
            case CLASS_Destroyer:
                //dangerous as hell
                dangerous = TRUE;
                break;
            case CLASS_Frigate:
                if ((shipstatic->shiptype != AdvanceSupportFrigate) && (shipstatic->shiptype != ResourceController) && (shipstatic->shiptype != DFGFrigate))
                {
                    dangerous = TRUE;
                }
                break;
            case CLASS_Corvette:
            case CLASS_Fighter:
            case CLASS_Resource:
            case CLASS_NonCombat:
            default:
                break;
        }
    }

    if (dangerous)
        return !aitAnyTeamOfPlayerAttackingThisShip(aiCurrentAIPlayer,ship);
    else
        return false;
}



/*-----------------------------------------------------------------------------
    Name        : aiaSendRecon
    Description : Sends a recon mission to check out a selection of ships
    Inputs      : ships - the ships to check out
    Outputs     : Creates a few new moves for the recon team
    Return      : A pointer to the recon team if it was sent off
----------------------------------------------------------------------------*/
AITeam *aiaSendRecon(SelectCommand *ships)
{
    udword i = 0;
    real32 distsq = 0, min_distsq = REALlyBig, avg_size = 0;
    vector ships_location = selCentrePointComputeGeneral((MaxSelection *)ships, &avg_size), team_location;
    AITeam *team = NULL, *best_team = NULL;
    AITeamMove *newMove = NULL;

    // find the closest recon team
    for (i=0;i < aiCurrentAIPlayer->numReconTeams;i++)
    {
        team = aiCurrentAIPlayer->reconTeam[i];

        if (team->shipList.selection->numShips)
            team_location = team->shipList.selection->ShipPtr[0]->posinfo.position;
        else
            continue;


        distsq = aiuFindDistanceSquared(ships_location, team_location);

        if (distsq < min_distsq)
        {
            best_team  = team;
            min_distsq = distsq;
        }
    }

    if (min_distsq < REALlyBig)
    {
        newMove = aimCreateShipReconNoAdd(best_team, ships, NO_FORMATION, Evasive, TRUE, TRUE);
        aieHandlerSetFuelLow(newMove, 15, TRUE, TRUE, aihGenericFuelLowHandler);
        aieHandlerSetTeamDied(newMove, aihReconShipTeamDiedHandler);
        aimInsertMove(best_team, newMove);
        return best_team;
    }
    else
    {
        //maybe later check for harass teams as well...
        //or maybe even build a new ship for the task
        return NULL;
    }
}


/*-----------------------------------------------------------------------------
    Name        : aiaArmada
    Description : Finds the best target for armada ships and coordinates
                  armada teams for attack
    Inputs      :
    Outputs     : Lots of blowing up of enemy ships
    Return      : void
----------------------------------------------------------------------------*/
void aiaArmada(void)
{
    vector dest_target;
    AITeam *recon_team;
    AITeamMove *recon_move;
    SelectCommand *sel_target = NULL;
    bool visibility;
    udword num_armada = aitFindNumTeamsWithFlag(TEAM_ARMADA);

    //build up armada strength more if enemy player doesn't have many battle
    //ships away from the mothership.  Then do a coordinated attack on mothership.
    //Otherwise, smaller coordinated attacks on enemy buildups (other than the mothership)

    if ((num_armada > aiCurrentAIPlayer->aiaArmada.numTeams) && (!aiCurrentAIPlayer->aiaArmada.targets))
    {
        visibility = aiuFindArmadaTarget(&dest_target, &sel_target, NULL/*team->shipList.selection*/);

        aiCurrentAIPlayer->aiaArmada.targets    = sel_target;
        aiCurrentAIPlayer->aiaArmada.visibility = visibility;

        if (!visibility && sel_target)
        {
            aiCurrentAIPlayer->aiaArmada.recon_team = aiaSendRecon(sel_target);
            return;
        }
    }
    else if (num_armada <= aiCurrentAIPlayer->aiaArmada.numTeams)
    {
        return;
    }

    //if the visibility flag is set, the armada targets are considered
    //viable targets.
    //if no visibility, check if the ships have been identified
    if (aiCurrentAIPlayer->aiaArmada.targets && !aiCurrentAIPlayer->aiaArmada.visibility)
    {
        //check status of the recon team
        recon_team = aiCurrentAIPlayer->aiaArmada.recon_team;
        if (recon_team)
        {
            recon_move = recon_team->curMove;

            if (recon_move->type == MOVE_SHIPRECON)
            {
                //check the ships the recon team has found to see if they are good
                //enough to kill
                if ((!recon_move->params.shiprecon.ships->numShips) &&
                    (recon_move->params.shiprecon.foundships->numShips))
                {
//                    visibility = aiaAnalyseTargets(recon_move->params.shiprecon.foundships);
                }
                else if (recon_team->curMove->params.shiprecon.foundships->numShips)
                {
//                    visibility = aiaAnalysePartialTargets(recon_move->params.shiprecon.foundships);
                }
            }
        }
        else
        {
            //the recon team has died, create a new one
            aiCurrentAIPlayer->aiaArmada.recon_team = aiaSendRecon(aiCurrentAIPlayer->aiaArmada.targets);
            return;
        }
    }

    //analyse ships, then decide what to send their way, if at all...

}




/*-----------------------------------------------------------------------------
    Name        : aiaGetTakeoutTarget
    Description : Looks through EnemyShipsIamAwareOf and finds the most dangerous of them
    Inputs      : none
    Outputs     :
    Return      : The most dangerous enemy ship the computer player has seen
----------------------------------------------------------------------------*/
ShipPtr aiaGetTakeoutTarget(void)
{
    udword i;
    SelectCommand *temp_sel;

    std::vector<Ship> target_sel(TOTAL_NUM_SHIPS);

    for (i=0;i<TOTAL_NUM_SHIPS;i++)
    {
        temp_sel = aiCurrentAIPlayer->primaryEnemyShipsIAmAwareOf[i].selection;
        if (temp_sel->numShips)
            selSelectionAddSingleShip(target_sel, *temp_sel->ShipPtr[0]);
    }

    ShipPtr targetship = statsGetMostDangerousShipNonStatConstraints(target_sel,aiaPriorityShipsConstraints);
    return targetship;
}



/*-----------------------------------------------------------------------------
    Name        : aiaGenerateAttackType
    Description : Generates a team with a certain attack type
    Inputs      : newteam - the new attack team
                  attacktype - the type of attack
                  ForceBig - whether or not to force building ships that require a Mothership
    Outputs     : Creates a new team or two
    Return      : void
----------------------------------------------------------------------------*/
bool aiaGenerateAttackType(AITeam *newteam, AttackType attacktype, bool ForceBig)
{
    ShipPtr ship;
    bool return_value = false;

    switch (attacktype)
    {
        case ATTACK_FLEET_FAST:
            if (aiuAttackFeatureEnabled(AIA_ATTACK_FLEET_FAST))
            {
                ship = aiuFindEnemyMothership(aiCurrentAIPlayer->player); //temporary
                if (ship)
                {
                    aioCreateTakeoutMothershipFast(newteam,ship);
                    return_value = TRUE;
                }
            }
            break;
        case ATTACK_FLEET_GUARD:
            if (aiuAttackFeatureEnabled(AIA_ATTACK_FLEET_GUARD))
            {
                ship = aiuFindEnemyMothership(aiCurrentAIPlayer->player); //temporary
                if (ship)
                {
                    aioCreateTakeoutMothershipGuard(newteam,ship);
                    return_value = TRUE;
                }
            }
            break;
        case ATTACK_FLEET_BIG:
            if (aiuAttackFeatureEnabled(AIA_ATTACK_FLEET_BIG))
            {
                ship = aiuFindEnemyMothership(aiCurrentAIPlayer->player); //temporary
                if (ship)
                {
                    aioCreateTakeoutMothershipBig(newteam,ship, ForceBig);
                    return_value = TRUE;
                }
            }
            break;
        case ATTACK_FLEET_HUGE:
            if (aiuAttackFeatureEnabled(AIA_ATTACK_FLEET_HUGE) &&
                ((aiCurrentAIPlayer->player->PlayerMothership && aiCurrentAIPlayer->player->PlayerMothership->shiptype == Mothership) || ForceBig))
            {
                ship = aiuFindEnemyMothership(aiCurrentAIPlayer->player); //temporary
                if (ship)
                {
                    aioCreateTakeoutMothershipHuge(newteam, ship);
                    return_value = TRUE;
                }
            }
            break;
        case TAKEOUT_TARGET:
            if (aiuAttackFeatureEnabled(AIA_TAKEOUT_TARGET))
            {
                ship = aiaGetTakeoutTarget();
                if (ship)
                {
                    aioCreateTakeoutTarget(newteam, ship);
                    return_value = TRUE;
                }
            }
            break;
        case FANCY_TAKEOUT_TARGET:
            if (aiuAttackFeatureEnabled(AIA_FANCY_TAKEOUT_TARGET))
            {
                ship = aiaGetTakeoutTarget();
                if (ship)
                {
                    aioCreateFancyTakeoutTarget(newteam, ship);
                    return_value = TRUE;
                }
            }
            break;
        case FIGHTER_STRIKE:
            if (aiuAttackFeatureEnabled(AIA_FIGHTER_STRIKE))
            {
                aioCreateFighterStrike(newteam);
                return_value = TRUE;
            }
            break;
        case CORVETTE_STRIKE:
            if (aiuAttackFeatureEnabled(AIA_CORVETTE_STRIKE))
            {
                aioCreateCorvetteStrike(newteam);
                return_value = TRUE;
            }
            break;
        case FRIGATE_STRIKE:
            if (aiuAttackFeatureEnabled(AIA_FRIGATE_STRIKE))
            {
                aioCreateFrigateStrike(newteam);
                return_value = TRUE;
            }
            break;
//later differentiate between harass small/big
        case HARASS_SMALL:
            if (aiuAttackFeatureEnabled(AIA_HARASS))
            {
                aioCreateHarass(newteam);
                return_value = TRUE;
            }
            break;
        case HARASS_BIG:
            if (aiuAttackFeatureEnabled(AIA_HARASS))
            {
                aioCreateHarass(newteam);
                return_value = TRUE;
            }
            break;
        case CAPTURE:
            if (aiuAttackFeatureEnabled(AIA_CAPTURE) && aiuGameTimePassed(600/*AIA_CAPTURE_TIME_DELAY*/))
            {
                aioCreateCapture(newteam);
                return_value = TRUE;
            }
            break;
        case MINE:
            if (aiuAttackFeatureEnabled(AIA_MINE))
            {
                aioCreateMine(newteam);
                return_value = TRUE;
            }
            break;
        case CLOAKGEN:
            if (aiuAttackFeatureEnabled(AIA_CLOAKGEN))
            {
                aioCreateSpecialDefense(newteam, CloakGenerator);
                return_value = TRUE;
            }
            break;
        case GRAVWELL:
            if (aiuAttackFeatureEnabled(AIA_GRAVWELL))
            {
                aioCreateSpecialDefense(newteam, GravWellGenerator);
                return_value = TRUE;
            }
            break;
        default:
            aiplayerLog((aiIndex,"Error - Attack Type Not Found"));
    }
    return return_value;
}


/*-----------------------------------------------------------------------------
    Name        : aiaGenerateNewAttackOrder
    Description : Creates a team and generates an order (assumes the ships already exist)
    Inputs      : attack type
    Outputs     : Creates a team and an order
    Return      : TRUE if the team was created
----------------------------------------------------------------------------*/
bool aiaGenerateNewAttackOrder(AttackType attacktype)
{
    aiCurrentAIPlayer->attackTeam.emplace_back(aitCreate(AttackTeam));

    if( aiaGenerateAttackType(aiCurrentAIPlayer->attackTeam.back(), attacktype, true) )
    	return true;

    aitDestroy(aiCurrentAIPlayer, aiCurrentAIPlayer->attackTeam.back(), true);
    return false;
}



/*-----------------------------------------------------------------------------
    Name        : aiaGenerateNewAttackTeam
    Description : Generates a team with the task to attack the enemy in some way
    Inputs      : AttackTeamNumber - the ID number of the attack team
    Outputs     : Creates new teams
    Return      : void
----------------------------------------------------------------------------*/
void aiaGenerateNewAttackTeam()
{
    AttackType randomAttack;
    udword probability_of_attack;
    bool attack_type_found = false;
    udword i=0;

    aiCurrentAIPlayer->attackTeam.emplace_back(aitCreate(AttackTeam));

    //repeat until an attack team is found
    //upper limit to avoid weird infinite loops
    while ((!attack_type_found) && (i<100))
    {
        randomAttack = (AttackType)(ranRandom(RANDOM_AI_PLAYER)%NUM_ATTACK_TYPES);
        probability_of_attack = ranRandom(RANDOM_AI_PLAYER)&255;

        if (probability_of_attack < aiCurrentAIPlayer->aiaAttackProbability[randomAttack])
            attack_type_found = aiaGenerateAttackType(aiCurrentAIPlayer->attackTeam.back(), randomAttack, false);
        else
            i++;
    }
}


/*-----------------------------------------------------------------------------
    Name        : aiaProcessAttackTeams
    Description : Creates and directs the normal attack teams
    Inputs      : None
    Outputs     : Creates and modifies teams
    Return      : void
----------------------------------------------------------------------------*/
void aiaProcessAttackTeams(void)
{
    sdword num_getships;
    Ship *ship;
    SelectCommand *enemyships;

    //when special attack teams are finished forming, they check with Attackman to
    //find out if they can go ahead and takeout their target.  If not, they become
    //temporary defense teams, then attack when the order is given from the attackman

    for( auto& team : aiCurrentAIPlayer->attackTeam )
    {
    	if (!aitTeamIsDone(team))
    		continue;

    	if (team->shipList.selection->numShips > 0)
		{
			enemyships = aiuFindNearbyEnemyShips(team->shipList.selection->ShipPtr[0],3000.0f);
			MakeShipsOnlyFollowConstraints(enemyships,aiuShipIsntAnEnemyMothership);
			if (enemyships->numShips)
			{
				// raise hell
				aiplayerLog(aiIndex, "%x Taking Out with current team", (AITeam*)team);
				aitDeleteAllTeamMoves(team);
				aioCreateTakeoutTargetsWithCurrentTeam(team,enemyships);
			}
			else
			{
				memFree(enemyships);
				// no enemy ships nearby!  Let's take out mothership
				ship = aiuFindEnemyMothership(aiCurrentAIPlayer->player);
				if (ship != NULL)
				{
					aiplayerLog(aiIndex, "%x Taking Out Mothership with current team", (AITeam*)team);
					aitDeleteAllTeamMoves(team);
					aioCreateTakeoutTargetWithCurrentTeam(team, ship);
				}
			}
		}
		else
		{
			// delete team for sure since there are no ships in it
			aitDestroy(aiCurrentAIPlayer, team, true);
			auto it = std::find
			(
				aiCurrentAIPlayer->attackTeam.begin(),
				aiCurrentAIPlayer->attackTeam.end(),
				team
			);
			aiCurrentAIPlayer->attackTeam.erase(it);
		}
    }

    for( size_t i = aiCurrentAIPlayer->attackTeam.size(); i < AIPLAYER_NUM_ATTACKTEAMS; i++)
    {
		num_getships = aitCountTeamsWaitingForShips(AttackTeam);

		if ((num_getships < 4) || ((num_getships < 10) && (aiCurrentAIPlayer->player->resourceUnits > 12000)))
			aiaGenerateNewAttackTeam();
    }
    aiaArmada();
}



/*-----------------------------------------------------------------------------
    Name        : aiaProcessSpecialTeams
    Description : Creates special teams if they are needed.
                  Special teams take care of themselves and need little
                  directing from the AttackMan
    Inputs      : None
    Outputs     : Creates teams
    Return      : void
----------------------------------------------------------------------------*/
void aiaProcessSpecialTeams(void)
{
    udword harass_probability, i = 0;

    if (!aiCurrentAIPlayer->numReconTeams)
    {
        if (aiuAttackFeatureEnabled(AIA_STATIC_RECONAISSANCE))
        {
            aiCurrentAIPlayer->reconTeam[i] = aitCreate(AttackTeam);
            aioCreateReconaissance(aiCurrentAIPlayer->reconTeam[i], RECON_MOTHERSHIP);
            i++;
        }

        if (aiuAttackFeatureEnabled(AIA_ACTIVE_RECONAISSANCE))
        {
            aiCurrentAIPlayer->reconTeam[i] = aitCreate(AttackTeam);
            aioCreateReconaissance(aiCurrentAIPlayer->reconTeam[i], RECON_ACTIVE_ENEMY);
            i++;
        }
        aiCurrentAIPlayer->numReconTeams = i;
    }

    if ((!aiCurrentAIPlayer->harassTeam) && (aiuAttackFeatureEnabled(AIA_HARASS)))
    {
        //large harass
        harass_probability = ranRandom(RANDOM_AI_PLAYER)&255;

        if (harass_probability < aiCurrentAIPlayer->aiaAttackProbability[HARASS_BIG])
        {
            aiCurrentAIPlayer->harassTeam = aitCreate(AttackTeam);
            aioCreateHarass(aiCurrentAIPlayer->harassTeam);
        }

        //large harass
//        harass_probability = ranRandom(RANDOM_AI_PLAYER)&255;

//        if (harass_probability < aiCurrentAIPlayer->aiaAttackProbability[HARASS_BIG])
//        {
//            aiCurrentAIPlayer->harassTeam = aitCreate(AttackTeam);
//            aioCreateHarass(aiCurrentAIPlayer->harassTeam);
//        }

    }
}


/*-----------------------------------------------------------------------------
    Name        : aiaTimeAttack
    Description : Times the attack moves so that all big ships go for it at
                  the same time.
                  Each attacking team is waiting on the aivar with the label
                  "attackVarLabel" in the aiplayer structure.  This aivar counts
                  the number of attack teams that are ready.  When the number is
                  at a certain point, the value is set to -1 which is the attack order
    Inputs      :
    Outputs     :
    Return      : void
----------------------------------------------------------------------------*/
void aiaTimeAttack(void)
{
    sdword varValue;
	AITeam *team = NULL;

    switch (aiCurrentAIPlayer->aiplayerDifficultyLevel)
    {
        case AI_BEGINNER:
            aivarValueSet(aivarFind(aiCurrentAIPlayer->attackVarLabel), -1);
            break;
        case AI_INTERMEDIATE:
		case AI_ADVANCED:
					// if there are no resources left
            if (!aiCurrentAIPlayer->airEasilyAccesibleRUsInWorld)
            {
				// force any tempguarding team to armada
				team = aitFindNextTeamWithFlag(team, TEAM_TempGuard);

				while (team)
				{
					aiplayerLog((aiIndex, "%x, Forcing out of tempguard, no resources", team));
					aitDeleteMovesUntilMoveType(team, MOVE_TEMPGUARD);
					team = aitFindNextTeamWithFlag(team, TEAM_TempGuard);
				}

                aivarValueSet(aivarFind(aiCurrentAIPlayer->attackVarLabel), -1);
            }
			else if (aiCurrentAIPlayer->aiaTimeout < universe.totaltimeelapsed)
			{
				aivarValueSet(aivarFind(aiCurrentAIPlayer->attackVarLabel),-1);
				aiCurrentAIPlayer->aiaTimeout += frandyrandombetween(RANDOM_AI_PLAYER, 3400.0f, 3800.0f);
			}
            else
            {
                varValue = aivarValueGet(aivarFind(aiCurrentAIPlayer->attackVarLabel));

                if ((varValue < -300) && (aiCurrentAIPlayer->airEasilyAccesibleRUsInWorld))
                {
                    varValue = randyrandombetween(RANDOM_AI_PLAYER, 2,4);

                    aiplayerLog((aiIndex, "Resetting VarValue up %i", varValue));
                    aivarValueSet(aivarFind(aiCurrentAIPlayer->attackVarLabel),varValue);
                }
                else if (varValue < -1)
                {
					// force any tempguarding team to armada
					team = aitFindNextTeamWithFlag(team, TEAM_TempGuard);

					while (team)
					{
						aiplayerLog((aiIndex, "%x, Forcing out of tempguard", team));
						aitDeleteMovesUntilMoveType(team, MOVE_TEMPGUARD);
						team = aitFindNextTeamWithFlag(team, TEAM_TempGuard);
					}
                    // gives a 3 frame delay to get all tempguarding ships to attack
                    varValue -= 100;
                    aivarValueSet(aivarFind(aiCurrentAIPlayer->attackVarLabel),varValue);
                }
            }
        default:
            break;
    }


}


/*-----------------------------------------------------------------------------
    Name        : aiaProcessHarassTeams
    Description : Directs harass teams - first gets all of them into a list
                  then checks to see if they are in a mothership blob.  If so,
                  pulls them away.
    Inputs      :
    Outputs     : Modifies team moves
    Return      : void
----------------------------------------------------------------------------*/
void aiaProcessHarassTeams(void)
{
    AITeam *harassTeams[MAX_NUM_HARASS_TEAMS], *team;
    AITeamMove *move;
    udword i, team_num = 0, numAttTeams = aiCurrentAIPlayer->attackTeam.size(), retreat_probability;
    ShipPtr teamShip;
    SelectCommand *shipList;
    vector destination;

    //put all harass teams into an array
    if (aiCurrentAIPlayer->harassTeam)
    {
        harassTeams[team_num] = aiCurrentAIPlayer->harassTeam;
        team_num++;
    }

    for (i=0;i<numAttTeams;i++)
    {
        team = aiCurrentAIPlayer->attackTeam[i];

        if (bitTest(team->teamFlags, HARASS_TEAM))
        {
            harassTeams[team_num] = team;
            team_num++;
        }
    }

    //for each harass team, check how close it is to the enemy mothership
    //if it's close, move it away - later: ignore if attacking research ships
    for (i=0;i<team_num;i++)
    {
        shipList = harassTeams[i]->shipList.selection;

        if ((shipList) && (shipList->numShips) &&
            (!bitTest(harassTeams[i]->teamFlags, TEAM_RETREATING)) &&
            (aiuShipsCloseToEnemyMothership(aiCurrentAIPlayer->player, shipList, 5500)))
        {
            retreat_probability = ranRandom(RANDOM_AI_PLAYER)&255;

            if (retreat_probability < 200)
            {
                teamShip = shipList->ShipPtr[0];

                //find a move location away from the mothership
                destination = aiuFindSafestStandoffPoint(shipList, 20000);

                //delete attack move if there is one
                //clear moves until "harass attack"
                aitDeleteMovesUntilMoveType(harassTeams[i], MOVE_HARASSATTACK);

                move = aimCreateMoveTeamNoAdd(harassTeams[i], destination, SAME_FORMATION, true, false);
                move->tactics = Evasive;    //temporary

                aimInsertMove(harassTeams[i], move);

                bitSet(harassTeams[i]->teamFlags, TEAM_RETREATING);
            }
        }
    }
}



/*-----------------------------------------------------------------------------
    Name        : aiaProcessReconTeams
    Description : Creates and directs reconaissance teams
    Inputs      : nothing
    Outputs     : Creates and modifies teams
    Return      : void
----------------------------------------------------------------------------*/
void aiaProcessReconTeams(void)
{
    udword numEnemyBlobs = aiuGetNumEnemyBlobs();

    if ((!aiCurrentAIPlayer->numReconTeams) ||
        ((aiCurrentAIPlayer->numReconTeams < AIPLAYER_NUM_RECONTEAMS) &&
         (numEnemyBlobs/aiCurrentAIPlayer->numReconTeams > AIA_ENEMYBLOBS_PER_RECON)))
    {
        aiCurrentAIPlayer->reconTeam[aiCurrentAIPlayer->numReconTeams] = aitCreate(AttackTeam);
        aioCreateReconaissance(aiCurrentAIPlayer->reconTeam[aiCurrentAIPlayer->numReconTeams], RECON_ACTIVE_ENEMY);
        aiCurrentAIPlayer->numReconTeams++;
    }
}


/*-----------------------------------------------------------------------------
    Name        : aiaDivideNewShips
    Description : Divides the new ships available into nice neat and tidy teams
    Inputs      :
    Outputs     : Creates some orders
    Return      : void
----------------------------------------------------------------------------*/
bool aiaDivideNewShips(void)
{
    SelectCommand *NewShips = aiCurrentAIPlayer->newships.selection;
    udword numShipType[TOTAL_NUM_SHIPS];
    sdword i;
    bool done = false, newteam = false;

    for (i=0;i<TOTAL_NUM_SHIPS;i++)
    {
        numShipType[i] = 0;
    }

    for (i=0;i<NewShips->numShips;i++)
    {
        numShipType[NewShips->ShipPtr[i]->shiptype]++;
    }

    while (!done)
    {
        //for now, just go for the basics.  Later expand for everything
        //look for takeout Mo'ship huge
        if (numShipType[HeavyCruiser] && ((numShipType[MissileDestroyer])))
        {
            newteam = aiaGenerateNewAttackOrder(ATTACK_FLEET_HUGE);

            numShipType[HeavyCruiser]--;
            numShipType[MissileDestroyer]--;
            break;
        }

        if (numShipType[StandardDestroyer] && (numShipType[StandardFrigate] > 1))
        {
            newteam = aiaGenerateNewAttackOrder(ATTACK_FLEET_BIG);

            numShipType[StandardDestroyer]--;
            numShipType[StandardFrigate]--;
            numShipType[StandardFrigate]--;
            break;
        }

        if (numShipType[GravWellGenerator])
        {
            newteam = aiaGenerateNewAttackOrder(GRAVWELL);

            numShipType[GravWellGenerator]--;
            break;
        }

        if (numShipType[CloakGenerator])
        {
            newteam = aiaGenerateNewAttackOrder(CLOAKGEN);

            numShipType[CloakGenerator]--;
            break;
        }
        done = TRUE;
    }
    return newteam;
}



/*-----------------------------------------------------------------------------
    Name        : aiaCleanupTeams
    Description : Cleans up the messiness of the teams
    Inputs      :
    Outputs     : Deletes a few teams sometimes
    Return      : void
----------------------------------------------------------------------------*/
void aiaCleanupTeams(void)
{
    for( auto& team : aiCurrentAIPlayer->attackTeam )
    {
        if (aitTeamIsDone(team) && (!team->shipList.selection->numShips))
        {
//            for (j=0;j<team->shipList.selection->numShips;j++)
//            {
//                growSelectAddShip(&aiCurrentAIPlayer->newships, team->shipList.selection->ShipPtr[j]);
//            }

            aitDestroy(aiCurrentAIPlayer, team, TRUE);

            continue;
        }
        //later figure out if we need to do something if the team still has ships
    }
}



/*-----------------------------------------------------------------------------
    Name        : aiaAttackManager
    Description : Deals with all attack related tasks of the computer player
    Inputs      : None
    Outputs     : Lotsa stuff
    Return      : void
----------------------------------------------------------------------------*/
void aiaAttackManager(void)
{
    bool newteams = false;

    aiaCleanupTeams();

    if (aiCurrentAIPlayer->newships.selection->numShips)
    {
        newteams = aiaDivideNewShips();
    }

    if (aiuAttackFeatureEnabled(AIA_ACTIVE_RECONAISSANCE))
    {
        aiaProcessReconTeams();
    }

    if (aiuAttackFeatureEnabled(AIA_HARASS))
    {
//        aiaProcessHarassTeams();
    }

    if (aiCurrentAIPlayer->AttackFeatures && !newteams) aiaProcessAttackTeams();

    aiaTimeAttack();
}



/*=============================================================================
    P2 Specific Functions:
=============================================================================*/
/*-----------------------------------------------------------------------------
    Name        : aiaCleanUpSwarmers
    Description : Cleans up the swarm teams: deletes groups that have no ships or only pods left.  Puts the pods back into the newships selection
    Inputs      : nah-zink
    Outputs     : deleting of teams and such
    Return      : void
----------------------------------------------------------------------------*/
void aiaCleanUpSwarmers(void)
{
    udword i;
    AITeam *team;

    for (i=0;i<aiCurrentAIPlayer->numSupportTeams;i++)
    {
        team = aiCurrentAIPlayer->supportTeam[i];

//        if (team->teamType == ResourceTeam)
        {
            //if the attack team and the defense team are dead
            if ((!team->cooperatingTeam->shipList.selection->numShips) &&
                 (!team->cooperatingTeam->cooperatingTeam->shipList.selection->numShips))
            {
                //move the pod (if it still exists) back to the newships selection
                while (team->shipList.selection->numShips)
                {
                    growSelectAddShip(&aiCurrentAIPlayer->newships, team->shipList.selection->ShipPtr[0]);
                    growSelectRemoveShip(&team->shipList, team->shipList.selection->ShipPtr[0]);
                }
                aitDestroy(aiCurrentAIPlayer, team->cooperatingTeam->cooperatingTeam, TRUE);
                aitDestroy(aiCurrentAIPlayer, team->cooperatingTeam, TRUE);
                aitDestroy(aiCurrentAIPlayer, team, TRUE);
            }
        }
    }
}



/*-----------------------------------------------------------------------------
    Name        : aiaProcessSwarm
    Description : Controls the attacks of the P2 swarmers
    Inputs      : None
    Outputs     : Creates a bunch of teams
    Return      : void
----------------------------------------------------------------------------*/
void aiaProcessSwarm(void)
{
    SelectCommand *newShips = aiCurrentAIPlayer->newships.selection, *pods;
    MaxSelection newPods, newSwarmers, newLeaders, newAdvSwarmers, newMultiBeams, newMothership;
    udword
        numNewAttackTeams, numSwarmersPerTeam, numExtraSwarmers,
        numNewSwarmGroups, numAdvPerTeam, numExtraAdv, numPodsPerTeam,
        numExtraPods, i, j, k, l, m;
    bool fuelpod = false, mothership = false;
    ShipPtr ship;

    if (aiCurrentAIPlayer->newships.selection->numShips)
    {
        aiaCleanUpSwarmers();

        newShips = aiCurrentAIPlayer->newships.selection;

        //scan for pods in newShips
        //later consider new Multibeams and mothership even though no new pods are around
        for (i=0; (int)i < newShips->numShips; i++)
        {
            ship = newShips->ShipPtr[i];
            if (ship->shiptype == P2FuelPod)
            {
                fuelpod = TRUE;
            }
            if (ship->shiptype == P2Mothership)
            {
                mothership = TRUE;
            }
        }

        //if there's no new pods in the selection, wait until we have a pod
        if ((!fuelpod)&&(!mothership))
            return;

        newPods.numShips        = 0;
        newSwarmers.numShips    = 0;
        newLeaders.numShips     = 0;
        newAdvSwarmers.numShips = 0;
        newMultiBeams.numShips  = 0;
        newMothership.numShips  = 0;

        for (i=0; (int)i < newShips->numShips;)
        {
            ship = newShips->ShipPtr[i];

            switch (ship->shiptype)
            {
                case P2FuelPod:
                    selSelectionAddSingleShip(&newPods, ship);
                    growSelectRemoveShipIndex(&aiCurrentAIPlayer->newships, i);
                    break;
                case P2AdvanceSwarmer:
                    if (bitTest(ship->attributes, ATTRIBUTES_TeamLeader))
                    {
                        selSelectionAddSingleShip(&newLeaders, ship);
                    }
                    else
                    {
                        selSelectionAddSingleShip(&newAdvSwarmers, ship);
                    }
                    growSelectRemoveShipIndex(&aiCurrentAIPlayer->newships, i);
                    break;
                case P2Swarmer:
                    if (bitTest(ship->attributes, ATTRIBUTES_TeamLeader))
                    {
                        selSelectionAddSingleShip(&newLeaders, ship);
                    }
                    else
                    {
                        selSelectionAddSingleShip(&newSwarmers, ship);
                    }
                    growSelectRemoveShipIndex(&aiCurrentAIPlayer->newships, i);
                    break;
                case P2MultiBeamFrigate:
                    selSelectionAddSingleShip(&newMultiBeams, ship);
                    growSelectRemoveShipIndex(&aiCurrentAIPlayer->newships, i);
                    break;
                case P2Mothership:
                    selSelectionAddSingleShip(&newMothership, ship);
                    growSelectRemoveShipIndex(&aiCurrentAIPlayer->newships, i);
                    break;
                default:
                    i++;
                    break;
            }
        }
    }
    else
    {
        //for now, no control is exerted by the attack manager.  Once the
        //ships are given to the team, that's it.
        return;
    }

    //1 team per leader, or just 1 team if there isn't a leader
    if (newLeaders.numShips)
        numNewSwarmGroups = newLeaders.numShips;
    else
        numNewSwarmGroups = 1;

    numNewAttackTeams = aiCurrentAIPlayer->attackTeam.size() + numNewSwarmGroups;

    dbgAssertOrIgnore(numNewSwarmGroups > 0);

    numSwarmersPerTeam = newSwarmers.numShips/numNewSwarmGroups;
    numExtraSwarmers   = newSwarmers.numShips%numNewSwarmGroups;
    numAdvPerTeam      = newAdvSwarmers.numShips/numNewSwarmGroups;
    numExtraAdv        = newAdvSwarmers.numShips%numNewSwarmGroups;
    numPodsPerTeam     = newPods.numShips/numNewSwarmGroups;
    numExtraPods       = newPods.numShips%numNewSwarmGroups;

    if (!numPodsPerTeam)
    {
        //wait until pods have been added to the team
        return;
    }

    for (i=aiCurrentAIPlayer->attackTeam.size(),
         j=aiCurrentAIPlayer->numGuardTeams,
         k=aiCurrentAIPlayer->numSupportTeams;
         i < numNewAttackTeams; i++, j++, k++)
    {
        //create the pod selection
        aiuNewSelection(pods, numPodsPerTeam+1, "swarmpods");
        for (l=0;l<numPodsPerTeam;l++)
        {
            selSelectionAddSingleShip((MaxSelection *)pods, newPods.ShipPtr[0]);
            clRemoveShipFromSelection(&newPods, newPods.ShipPtr[0]);
        }
        if (numExtraPods)
        {
            selSelectionAddSingleShip((MaxSelection *)pods, newPods.ShipPtr[0]);
            clRemoveShipFromSelection(&newPods, newPods.ShipPtr[0]);
            numExtraPods--;
        }

        //setup the basic teams
        //setup the swarm attack team
        aiCurrentAIPlayer->attackTeam.emplace_back(aitCreate(AttackTeam));
        aioCreateSwarmAttack(aiCurrentAIPlayer->attackTeam.back());
        if (bitTest(aiCurrentAIPlayer->AlertStatus, ALERT_SWARMER_TARGETS))
        {
            bitSet(aiCurrentAIPlayer->attackTeam.back()->teamFlags, TEAM_SwarmTarget);
        }
        //setup the swarm defense team
        aiCurrentAIPlayer->guardTeams[j] = aitCreate(DefenseTeam);
        aioCreateSwarmDefense(aiCurrentAIPlayer->guardTeams[j], pods);
        aiCurrentAIPlayer->numGuardTeams++;
        //setup the swarm support team
        aiCurrentAIPlayer->supportTeam[k] = aitCreate(ResourceTeam);
        aioCreateSwarmSupport(aiCurrentAIPlayer->supportTeam[k]);
        aiCurrentAIPlayer->numSupportTeams++;

        //transfer the pods to the pod team
        for (l=0; (int)l < pods->numShips; l++)
        {
            aitAddShip(aiCurrentAIPlayer->supportTeam[k], pods->ShipPtr[l]);
        }

        //set the cooperating teams
        aiCurrentAIPlayer->attackTeam.back()->cooperatingTeam  = aiCurrentAIPlayer->guardTeams[j];
        aiCurrentAIPlayer->guardTeams[j]->cooperatingTeam  = aiCurrentAIPlayer->attackTeam.back();
        aiCurrentAIPlayer->supportTeam[k]->cooperatingTeam = aiCurrentAIPlayer->attackTeam.back();

        //give the team a leader
        if (newLeaders.numShips)
        {
            aitAddShip(aiCurrentAIPlayer->guardTeams[j], newLeaders.ShipPtr[0]);
            clRemoveShipFromSelection(&newLeaders, newLeaders.ShipPtr[0]);
        }

        //give the teams ships
        //initially the defense team gets all the swarmers
        //the Pod team divides the ships later
//        if (newAdvSwarmers.numShips > )
//        {
        /* newAdvSwarmers.numShips gets decremented automatically */
        for (m=0; (int)m < newAdvSwarmers.numShips;)
            {
                aitAddShip(aiCurrentAIPlayer->guardTeams[j], newAdvSwarmers.ShipPtr[0]);
                clRemoveShipFromSelection(&newAdvSwarmers, newAdvSwarmers.ShipPtr[0]);
            }
//        }
//        else
//        {
            for (m = 0; m < numSwarmersPerTeam + numExtraSwarmers;m++)
            {
                aitAddShip(aiCurrentAIPlayer->guardTeams[j], newSwarmers.ShipPtr[0]);
                clRemoveShipFromSelection(&newSwarmers, newSwarmers.ShipPtr[0]);
            }
            numExtraSwarmers = 0;
//        }
    }

    dbgAssertOrIgnore(newLeaders.numShips == 0);

    for (i=0; (int)i < newMultiBeams.numShips;)
    {
        aiCurrentAIPlayer->attackTeam.emplace_back(aitCreate(AttackTeam));
        aioCreateMultiBeamAttack(aiCurrentAIPlayer->attackTeam.back());
        aitAddShip(aiCurrentAIPlayer->attackTeam.back(), newMultiBeams.ShipPtr[0]);
        clRemoveShipFromSelection((MaxSelection *)&newMultiBeams, newMultiBeams.ShipPtr[0]);
    }

    if (newMothership.numShips)
    {
        aiCurrentAIPlayer->attackTeam.emplace_back(aitCreate(AttackTeam));
        aioCreateP2MothershipAttack(aiCurrentAIPlayer->attackTeam.back());
        aitAddShip(aiCurrentAIPlayer->attackTeam.back(), newMothership.ShipPtr[0]);
    }

    bitClear(aiCurrentAIPlayer->AlertStatus, ALERT_SWARMER_TARGETS);
}



/*-----------------------------------------------------------------------------
    Name        : aiaP2AttackManager
    Description : Deals with all attack related tasks of the P2 Pirates
    Inputs      : None
    Outputs     : A whole whack of things
    Return      : void
----------------------------------------------------------------------------*/
void aiaP2AttackManager(void)
{
    aiaProcessSwarm();
}



/*=============================================================================
    Non AI Related Stuff:
=============================================================================*/
//temporary bug fixin'
bool aiaPlayerCanBuildShipType(ShipType shiptype, AIPlayer *aiplayer)
{
    ShipStaticInfo *teststatic;
    ShipRace race;

    race = aiplayer->player->race;

    if ((RacesAllowedForGivenShip[shiptype] & RaceToRaceBits(race)) == 0)
    {
        // Can't build this shiptype for this race
        return false;
    }

    teststatic = GetShipStaticInfo(shiptype,race);
    if (!bitTest(teststatic->staticheader.infoFlags, IF_InfoLoaded))
        return false;       // this ship static info not loaded, so can't build

    if ((shiptype == ResourceCollector) && (!singlePlayerGame) && (!bitTest(tpGameCreated.flag,MG_HarvestinEnabled)))
        return false;

    return true;     // later set to TRUE to take into account research
}






void aiaTeamDied(struct AIPlayer *aiplayer,struct AITeam *team)
{
    if (team == aiplayer->harassTeam)
    {
        aiplayer->harassTeam = NULL;
    }
    //temporary... later we'll have a bigger array
    else if (team == aiplayer->reconTeam[0])
    {
        aiplayer->reconTeam[0] = NULL;
    }
    else if (team == aiplayer->reconTeam[1])
    {
        aiplayer->reconTeam[1] = NULL;
    }
    else if (team == aiplayer->aiaArmada.recon_team)
    {
        aiplayer->aiaArmada.recon_team = NULL;
    }
    else
    {
    	auto it = std::find
    	(
    		aiplayer->attackTeam.begin(),
    		aiplayer->attackTeam.end(),
    		*team
    	);

    	if( it != aiplayer->attackTeam.end() )
    		aiplayer->attackTeam.erase(it);
    }
}

bool aiaShipDied(struct AIPlayer *aiplayer, ShipPtr ship)
{
    if ((aiplayer->aiaArmada.targets) && (clRemoveShipFromSelection(aiplayer->aiaArmada.targets, ship)))
    {
        aiplayerLog((aiplayer->player->playerIndex, "Ship removed from Armada Targets"));

        if (!aiplayer->aiaArmada.targets->numShips)
        {
            memFree(aiplayer->aiaArmada.targets);
            aiplayer->aiaArmada.targets = NULL;
        }
    }

    if ((aiplayer->Targets) && (clRemoveShipFromSelection(aiplayer->Targets, ship)))
    {
        aiplayerLog((aiplayer->player->playerIndex, "Ship removed from Swarm Targets"));

        if (!aiplayer->Targets->numShips)
            aiumemFree(aiplayer->Targets);
    }
    return false;
}

void aiaInit(struct AIPlayer *aiplayer)
{
    sdword i;

//    growSelectInit(&aiplayer->newattackships);

    for (i=0;i<AIPLAYER_NUM_RECONTEAMS;i++)
    {
        aiplayer->reconTeam[i] = NULL;
    }
    aiplayer->numReconTeams = 0;

    aiplayer->harassTeam = NULL;

    aiplayer->attackTeam.reserve(AIPLAYER_NUM_ATTACKTEAMS);

    aiplayer->haveAttackedMothership = 0;
    aivarLabelGenerate(aiplayer->attackVarLabel);
    aivarValueSet(aivarCreate(aiplayer->attackVarLabel), randyrandombetween(RANDOM_AI_PLAYER, 2, 4));
	aiplayer->aiaTimeout = frandyrandombetween(RANDOM_AI_PLAYER, 2900.0f, 3400.0f);

    //init attack type array
    aiplayer->aiaAttackProbability[ATTACK_FLEET_FAST]    = aiuRandomRange(AIA_ATTACK_FLEET_FAST_PROB[aiplayer->aiplayerDifficultyLevel], AIA_ATTACK_FLEET_FAST_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[ATTACK_FLEET_GUARD]   = aiuRandomRange(AIA_ATTACK_FLEET_GUARD_PROB[aiplayer->aiplayerDifficultyLevel], AIA_ATTACK_FLEET_GUARD_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[ATTACK_FLEET_BIG]     = aiuRandomRange(AIA_ATTACK_FLEET_BIG_PROB[aiplayer->aiplayerDifficultyLevel], AIA_ATTACK_FLEET_BIG_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[ATTACK_FLEET_HUGE]    = aiuRandomRange(AIA_ATTACK_FLEET_HUGE_PROB[aiplayer->aiplayerDifficultyLevel], AIA_ATTACK_FLEET_HUGE_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[TAKEOUT_TARGET]       = aiuRandomRange(AIA_TAKEOUT_TARGET_PROB[aiplayer->aiplayerDifficultyLevel], AIA_TAKEOUT_TARGET_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[FANCY_TAKEOUT_TARGET] = aiuRandomRange(AIA_FANCY_TAKEOUT_TARGET_PROB[aiplayer->aiplayerDifficultyLevel], AIA_FANCY_TAKEOUT_TARGET_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[FIGHTER_STRIKE]       = aiuRandomRange(AIA_FIGHTER_STRIKE_PROB[aiplayer->aiplayerDifficultyLevel], AIA_FIGHTER_STRIKE_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[CORVETTE_STRIKE]      = aiuRandomRange(AIA_CORVETTE_STRIKE_PROB[aiplayer->aiplayerDifficultyLevel], AIA_CORVETTE_STRIKE_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[FRIGATE_STRIKE]       = aiuRandomRange(AIA_FRIGATE_STRIKE_PROB[aiplayer->aiplayerDifficultyLevel], AIA_FRIGATE_STRIKE_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[HARASS_BIG]           = aiuRandomRange(AIA_HARASS_BIG_PROB[aiplayer->aiplayerDifficultyLevel], AIA_HARASS_BIG_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[HARASS_SMALL]         = aiuRandomRange(AIA_HARASS_SMALL_PROB[aiplayer->aiplayerDifficultyLevel], AIA_HARASS_SMALL_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[CAPTURE]              = aiuRandomRange(AIA_CAPTURE_PROB[aiplayer->aiplayerDifficultyLevel], AIA_CAPTURE_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[MINE]                 = aiuRandomRange(AIA_MINE_PROB[aiplayer->aiplayerDifficultyLevel], AIA_MINE_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[CLOAKGEN]             = aiuRandomRange(AIA_CLOAKGEN_PROB[aiplayer->aiplayerDifficultyLevel], AIA_CLOAKGEN_RANGE[aiplayer->aiplayerDifficultyLevel]);
    aiplayer->aiaAttackProbability[GRAVWELL]             = aiuRandomRange(AIA_GRAVWELL_PROB[aiplayer->aiplayerDifficultyLevel], AIA_GRAVWELL_RANGE[aiplayer->aiplayerDifficultyLevel]);

    if ((!singlePlayerGame) && bitTest(tpGameCreated.flag,MG_CaptureCapitalShip))
    {
        aiplayer->aiaAttackProbability[CAPTURE] = aiuRandomRange(180, 25);
    }

    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Attack Fleet Fast    = %i", aiplayer->aiaAttackProbability[ATTACK_FLEET_FAST]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Attack Fleet Guard   = %i", aiplayer->aiaAttackProbability[ATTACK_FLEET_GUARD]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Attack Fleet Big     = %i", aiplayer->aiaAttackProbability[ATTACK_FLEET_BIG]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Attack Fleet Huge    = %i", aiplayer->aiaAttackProbability[ATTACK_FLEET_HUGE]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Takeout Target       = %i", aiplayer->aiaAttackProbability[TAKEOUT_TARGET]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Fancy Takeout Target = %i", aiplayer->aiaAttackProbability[FANCY_TAKEOUT_TARGET]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Fighter Strike       = %i", aiplayer->aiaAttackProbability[FIGHTER_STRIKE]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Corvette Strike      = %i", aiplayer->aiaAttackProbability[CORVETTE_STRIKE]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Frigate Strike       = %i", aiplayer->aiaAttackProbability[FRIGATE_STRIKE]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Harass Big           = %i", aiplayer->aiaAttackProbability[HARASS_BIG]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Harass Small         = %i", aiplayer->aiaAttackProbability[HARASS_SMALL]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Capture              = %i", aiplayer->aiaAttackProbability[CAPTURE]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability Mine                 = %i", aiplayer->aiaAttackProbability[MINE]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability CloakGen             = %i", aiplayer->aiaAttackProbability[CLOAKGEN]));
    aiplayerLog((aiplayer->player->playerIndex, "Attack Probability GravWell             = %i\n", aiplayer->aiaAttackProbability[GRAVWELL]));

    aiplayer->aiaArmada.numTeams   = AIA_NUM_ARMADA_TEAMS[aiplayer->aiplayerDifficultyLevel];
    aiplayer->aiaArmada.targets    = NULL;
    aiplayer->aiaArmada.recon_team = NULL;

    aiplayer->Targets = NULL;

    if ((!singlePlayerGame) && (bitTest(tpGameCreated.flag,MG_CaptureCapitalShip)))
    {
        aiplayer->aiaAttackProbability[CAPTURE] += 120;
    }

    switch (aiplayer->aiplayerDifficultyLevel)
    {
        case AI_ADVANCED:
            aiuEnableAttackFeature(AIA_ACTIVE_RECONAISSANCE);

            if (aiaPlayerCanBuildShipType(HeavyCruiser, aiplayer))
            {
                aiuEnableAttackFeature(AIA_ATTACK_FLEET_HUGE);
            }

            aiuEnableAttackFeature(AIA_FANCY_TAKEOUT_TARGET);
            aiuEnableAttackFeature(AIA_FIGHTER_STRIKE);
            aiuEnableAttackFeature(AIA_CORVETTE_STRIKE);
            aiuEnableAttackFeature(AIA_HARASS);

            if (aiaPlayerCanBuildShipType(SalCapCorvette, aiplayer))
            {
                aiuEnableAttackFeature(AIA_CAPTURE);
            }
            if (aiaPlayerCanBuildShipType(MinelayerCorvette, aiplayer))
            {
                aiuEnableAttackFeature(AIA_MINE);
            }
            if (aiaPlayerCanBuildShipType(CloakGenerator, aiplayer))
            {
                aiuEnableAttackFeature(AIA_CLOAKGEN);
            }
            if (aiaPlayerCanBuildShipType(GravWellGenerator, aiplayer))
            {
                aiuEnableAttackFeature(AIA_GRAVWELL);
            }
        case AI_INTERMEDIATE:
            aiuEnableAttackFeature(AIA_STATIC_RECONAISSANCE);
            aiuEnableAttackFeature(AIA_ATTACK_FLEET_FAST);
            aiuEnableAttackFeature(AIA_TAKEOUT_TARGET);
            aiuEnableAttackFeature(AIA_FRIGATE_STRIKE);
        case AI_BEGINNER:
            aiuEnableAttackFeature(AIA_ATTACK_FLEET_BIG);
            aiuEnableAttackFeature(AIA_ATTACK_FLEET_GUARD);

            if ((!singlePlayerGame) && bitTest(tpGameCreated.flag,MG_CaptureCapitalShip))
            {
                aiuEnableAttackFeature(AIA_CAPTURE);
            }
            break;
        default:
            dbgAssertOrIgnore(false);
    }

    if (randyrandombetween(RANDOM_AI_PLAYER, 0, 100) < aiuRandomRange(AIA_KAMIKAZE_PROB[aiplayer->aiplayerDifficultyLevel], AIA_KAMIKAZE_RANGE[aiplayer->aiplayerDifficultyLevel]))
    {
        aiuEnableAttackFeature(AIA_KAMIKAZE);
    }
}

void aiaClose(struct AIPlayer *aiplayer)
{
    sdword i;

//    growSelectClose(&aiplayer->newattackships);
    for (i=0;i<AIPLAYER_NUM_RECONTEAMS;i++)
    {
        if (aiplayer->reconTeam[i] != NULL)
        {
            aitDestroy(aiplayer, aiplayer->reconTeam[i],false);
            aiplayer->reconTeam[i] = NULL;
        }
    }
    if (aiplayer->harassTeam != NULL)
    {
        aitDestroy(aiplayer, aiplayer->harassTeam,false);
        aiplayer->harassTeam = NULL;
    }

    for (i=0;i<AIPLAYER_NUM_ATTACKTEAMS;i++)
    {
        if (aiplayer->attackTeam[i] != NULL)
        {
            aitDestroy(aiplayer, aiplayer->attackTeam[i],false);
            aiplayer->attackTeam[i] = NULL;
        }
    }

    aiumemFree(aiplayer->aiaArmada.targets);
    aiumemFree(aiplayer->Targets);
}
