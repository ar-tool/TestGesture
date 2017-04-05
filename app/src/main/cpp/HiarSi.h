#pragma once

/*******************************************************************************************
*
* Copyright 2016, HiScene
*
* This file is HiScene's property. It contains HiScene's proprietary and confidential
* information and trade secret. The information and code contained in this file is only
* intended for authorized HiScene employees and customers.
*
* DO NOT DISTRIBUTE, DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER AUTHORIZATION FROM
* HISCENE.
*
* If you are not an intended recipient of this file, you must not copy, distribute, modify,
* or take any action in reliance on it. If you have received this file in error, please
* immediately notify HiScene, and permanently delete the original and any copy of it and
* any printout thereof.
*
******************************************************************************************/

#include "HiarSiTypes.h"

/// an opaque handle representing the Hiar Smart Interaction that does all the processing
struct tag_HiarSi;
typedef struct tag_HiarSi* HiarSi;

typedef void (*LOG_CALLBACK)(const char* message);

void hiarsInitLogCallback(LOG_CALLBACK func);

/// return 0 if no error
int hiarsiCreate(const char* configFilePath, HiarSi* hiarsi);

/// return 0 if no error
int hiarsiSetOptions(HiarSi hiarsi, const HiarSiOptions* options);
int hiarsiGetOptions(HiarSi hiarsi, HiarSiOptions* options);

/// return 0 if no error
int hiarsiRun(HiarSi hiarsi, const HiarSiImage* image, HiarSiResult* result);

/// return 0 if no error
int hiarsiDestroy(HiarSi hiarsi);
