#ifndef ETHERNET_FRAME_H
#define ETHERNET_FRAME_H

#include <iostream>
#include <string>

#include "Utils.h"

#define SPACE ' '
#define ETHERNET_SEPERATOR "%"
#define SRC_ADDR_IDX 0
#define DST_ADDR_IDX 1
#define CONTENT_IDX 2

class EthernetFrame
{
public:
    EthernetFrame(int src_address, int dst_address, std::string content);

    static EthernetFrame decode(const std::string ethernet_message);
    static std::string encode(const EthernetFrame ethernet_frame);

private:
    int src_address;
    int dst_address;
    std::string content;
};

#endif
