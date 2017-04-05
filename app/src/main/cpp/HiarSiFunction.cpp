#include "HiarSiFunction.h"
#include "HiarSiTypes.h"
#include "HiarSi.h"

HiarSi HiarSiHandle;
std::vector<HiarSiRect> showHeadCountBox;
std::vector<HiarSiRect> showHandBox;
std::string pattern_text;
std::string img_text;
int continuous_pattern_count = 0;
HiarSiRect* headBBoxesBuffer_global;
HiarSiTracePattern prior_pattern;
HiarSiOptions options;

int left_right_value = 50;
int up_down_value = 50;
int long_time_no_move = 0;

int type = 0;

std::string get_pattern_text()
{
    return pattern_text;
}

std::string get_img_text()
{
    return img_text;
}

std::vector<HiarSiRect> getHeadCountBox()
{
    return showHeadCountBox;
}

std::vector<HiarSiRect> getHandBox()
{
    return showHandBox;
}

int get_left_right_value(){
    return left_right_value;
}

int get_up_down_value(){
    return up_down_value;
}

int get_long_time_no_move_value(){
    return long_time_no_move;
}

int get_event_type()
{
    return type;
}

void logCallback(const char *msg) {
    LOGI("%s", msg);
}

void init_HiarSi()
{
    int ret;

    hiarsInitLogCallback(logCallback);

    ret = hiarsiCreate(CONFIG_FILE_HUAWEI,&HiarSiHandle);
    if(ret != 0){
        return;
    }

    options.handDetectionType = HIARSI_HAND_DETECTION_PALM_THEN_FIST;
    options.mode = HIARSI_MODE_MOTIONDETECTOR_AND_HEADCOUNTER_ONLY;
    hiarsiSetOptions(HiarSiHandle, &options);
    hiarsiGetOptions(HiarSiHandle, &options);

    headBBoxesBuffer_global = new HiarSiRect[HEADCOUNT_BBOX_SIZE];

    prior_pattern = HIARSI_TRACE_PATTERN_NONE;
}

void process_image(const HiarSiImage* image)
{
    HiarSiRect* headBBoxesBuffer = headBBoxesBuffer_global;
    HiarSiResult Result;
    Result.headBBoxesCount = HEADCOUNT_BBOX_SIZE;
    Result.headBBoxes = headBBoxesBuffer;

    showHeadCountBox.clear();
    showHandBox.clear();
    img_text.clear();
    pattern_text.clear();

    hiarsiRun(HiarSiHandle, image, &Result);

    if(Result.hasMotion==HIARSI_TRUE){
        img_text = std::string("YES! motion");
    }else {
        img_text = std::string("NO! motion");
    }

    for (int i=0; i<Result.headBBoxesCount; ++i)
    {
        showHeadCountBox.push_back(Result.headBBoxes[i]);
    }

    if (Result.hasHandDetected)
    {
        showHandBox.push_back(Result.handBBox);
    }

    switch (Result.handTrackingType)
    {
        case (HIARSI_HAND_TRACKING_BY_PALM):
            img_text += " PALM!";
            break;
        case (HIARSI_HAND_TRACKING_BY_FIST):
            img_text += " FIST!";
            break;
        default:
            break;
    }

    if (prior_pattern == HIARSI_TRACE_PATTERN_NONE)
    {
        prior_pattern = Result.tracePattern;
        continuous_pattern_count = 1;
    }
    else
    {
        if (Result.tracePattern != HIARSI_TRACE_PATTERN_NONE && prior_pattern != Result.tracePattern)
        {
            prior_pattern = Result.tracePattern;
            continuous_pattern_count = 1;
        }
        else if (prior_pattern == Result.tracePattern){
            continuous_pattern_count++;
        }
    }

    char continuous_pattern_count_text[9];
    sprintf(continuous_pattern_count_text, "%d", continuous_pattern_count);
    switch (Result.tracePattern)
    {
        case HIARSI_TRACE_PATTERN_LEFT:                 // moving left
            pattern_text = "left x " + std::string(continuous_pattern_count_text);
            left_right_value--;
            long_time_no_move = 0;
            type = EventType::left;
            break;
        case HIARSI_TRACE_PATTERN_RIGHT:                // moving right
            pattern_text = "right x " + std::string(continuous_pattern_count_text);
            left_right_value++;
            long_time_no_move = 0;
            type = EventType::right;
            break;
        case HIARSI_TRACE_PATTERN_UP:                   // moving up
            pattern_text = "up x " + std::string(continuous_pattern_count_text);
            up_down_value++;
            long_time_no_move = 0;
            type = EventType::up;
            break;
        case HIARSI_TRACE_PATTERN_DOWN:                 // moving down
            pattern_text = "down x " + std::string(continuous_pattern_count_text);
            up_down_value--;
            long_time_no_move = 0;
            type = EventType::down;
            break;
        case HIARSI_TRACE_PATTERN_LONG_TIME_NO_MOVE:    // long time no move
            pattern_text = "LTNM x " + std::string(continuous_pattern_count_text);
            long_time_no_move++;
            type = EventType::longtime_nomve;
            break;
        default:
            type = EventType::none;
            break;
    }
}

void exit_HiarSi()
{
    delete []headBBoxesBuffer_global;
    hiarsiDestroy(HiarSiHandle);
}

