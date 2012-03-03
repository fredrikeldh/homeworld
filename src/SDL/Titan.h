/*=============================================================================
    Name    : Titan.h
    Purpose : Definitions for Titan.c

    Created 4/20/1998 by gshaw
    Copyright Relic Entertainment, Inc.  All rights reserved.
=============================================================================*/

#ifndef ___TITAN_H
#define ___TITAN_H

#ifdef __cplusplus
extern "C" {
#endif

void titanDebug(const char *format, ...);
void titanLogFileOpen();
void titanLogFileClose();

#ifdef __cplusplus
}
#endif

#endif

