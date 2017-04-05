#pragma once

#include "HiarSiTypes.h"
#include "HiarSi.h"
#include "HiarLog.h"
#include <string>
#include <vector>

#define CONFIG_FILE_R58 "/mnt/sdcard/Android/data/hiar.gesture/cache/HiarSi.conf"
#define CONFIG_FILE_XIAOMI "/storage/emulated/0/Android/data/hiar.gesture/cache/HiarSi.conf"
#define CONFIG_FILE_HUAWEI "/storage/emulated/0/Android/data/hiscene.com.hiscenegesture/cache/HiarSi.conf"
#define HEADCOUNT_BBOX_SIZE 10

//std::string hand_type;
//std::string hand_event;
void init_HiarSi();
void process_image(const HiarSiImage* image);
void exit_HiarSi();

std::string get_pattern_text();
std::string get_img_text();
std::vector<HiarSiRect> getHeadCountBox();
std::vector<HiarSiRect> getHandBox();

int get_left_right_value();
int get_up_down_value();
int get_long_time_no_move_value();
int get_event_type();

typedef enum EventType{
    none = 0,
    left = 1,
    right = 2,
    up = 3,
    down = 4,
    longtime_nomve=5
}EventType;
