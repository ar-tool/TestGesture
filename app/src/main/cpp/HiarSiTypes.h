#pragma once

#include <stddef.h>
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

/// supported image types
typedef enum
{
    HIARSI_IMAGE_TYPE_8UC1 = 0, // gray image, 8 unsigned char channel 1
    HIARSI_IMAGE_TYPE_8UC3 = 1, // bgr image, 8 unsigned char channel 3
    HIARSI_IMAGE_TYPE_NV12 = 2, // yuv NV12 color image
    HIARSI_IMAGE_TYPE_NV21 = 3  // yuv NV21 color image
} HiarSiImageType;

/// a type representing an image object. data is not managed - user manages data.
typedef struct
{
    HiarSiImageType type;       // image type
    int             width;      // number of columns in pixels : only support 720p image (1280x720) at present.
    int             height;     // number of rows in pixels
    unsigned char*  data;       // point to the first pixel in first row
    int             stride;     // bytes between each two neighboring row heads, no padding allowed in this version (== width)
    unsigned int    timestamp;  // the timestamp of the frame when captured in milliseconds (ms).
} HiarSiImage;

/// representing a rectangle in the image, unit in pixels.
typedef struct
{
    int     x;          // horizontal coordinate of the top left corner
    int     y;          // vertical coordinate of the top left corner
    int     width;      // length in horizontal direction.
    int     height;     // length in vertical direction.
} HiarSiRect;

/// HiarSi bool type
typedef enum
{
    HIARSI_FALSE = 0,
    HIARSI_TRUE  = 1
} HiarSiBool;

/// possible trace patterns
/// all the trace patterns are defined as follows:
///   1. user faces the camera.
///   2. trace pattern is viewed from the perspective of user.
typedef enum
{
    HIARSI_TRACE_PATTERN_LONG_TIME_NO_MOVE  = -1,   // long time no move
    HIARSI_TRACE_PATTERN_NONE               = 0,    // no trace
    HIARSI_TRACE_PATTERN_LEFT               = 1,    // moving left
    HIARSI_TRACE_PATTERN_RIGHT              = 2,    // moving right
    HIARSI_TRACE_PATTERN_UP                 = 3,    // moving up
    HIARSI_TRACE_PATTERN_DOWN               = 4     // moving down
} HiarSiTracePattern;

/// representing the jobs did during processing the most current frame
typedef enum
{
    HIARSI_JOB_MOTIONDETECTOR   = 1,
    HIARSI_JOB_HEADCOUNTER      = 2,
    HIARSI_JOB_HANDDETECTOR     = 4,
    HIARSI_JOB_HANDTRACKING     = 8,
    HIARSI_JOB_TRACERECOGNIZER  = 16
} HiarSiJob;

typedef enum
{
    HIARSI_MODE_MOTIONDETECTOR_ONLY                 = 0,
    HIARSI_MODE_MOTIONDETECTOR_AND_HEADCOUNTER_ONLY = 1,
    HIARSI_MODE_ALL_ON                              = 2
} HiarSiMode;

typedef enum
{
    HIARSI_HAND_DETECTION_PALM_ONLY         = 0,
    HIARSI_HAND_DETECTION_FIST_ONLY         = 1,
    HIARSI_HAND_DETECTION_PALM_THEN_FIST    = 2
} HiarSiHandDetectionType;

typedef enum
{
    HIARSI_HAND_TRACKING_NONE       = 0,      // nothing is under tracking
    HIARSI_HAND_TRACKING_BY_PALM    = 1,
    HIARSI_HAND_TRACKING_BY_FIST    = 2
} HiarSiHandTrackingType;

typedef enum
{
    HIARSI_DISTANCE_SHORT   = 0,
    HIARSI_DISTANCE_MID     = 1,
    HIARSI_DISTANCE_LONG    = 2
} HiarSiDistanceType;

/// a type representing the processing option of hiarsi.
typedef struct
{
    // smart interaction option needed from algorithm
    HiarSiMode              mode;                       // algorithm modules to perform.
    HiarSiHandDetectionType handDetectionType;          // what kind of hand want to detected
} HiarSiOptions;

/// a type representing the processing result of hiarsi.
typedef struct
{
    // smart interaction result and supporting evidence
    int                     jobsPerformed;              // [output] in this frame, which algorithm modules were performed. it is a bit_or of HiarSiJob.

    HiarSiBool              hasMotion;                  // [output] in this frame, whether there is new object enter

    size_t                  headBBoxesCount;            // [input, output] how many bboxes in the buffer. The algorithm will at most fill this many items in headBBoxes.
    HiarSiRect*             headBBoxes;                 // [output] buffer pointer holds output for bboxes.
    HiarSiDistanceType*     headBBoxesDistance;         // [output] buffer pointer holds distance of all bboxes to camera.

    HiarSiBool              hasHandDetected;            // [output] if hand is detected. If true, handBBox has the bounding box.
    HiarSiRect              handBBox;                   // [output] hand bbox (only holds one single one)

    HiarSiHandTrackingType  handTrackingType;           // [output] in this frame, which one (palm/fist) is tracked

    HiarSiTracePattern      tracePattern;               // [output] in this frame, the pattern of trace
} HiarSiResult;
