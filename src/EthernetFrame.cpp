#include "../include/EthernetFrame.h"

using namespace std;

EthernetFrame::EthernetFrame(int src_address, int dst_address, string content)
: src_address(src_address)
, dst_address(dst_address)
, content(content) {
}

EthernetFrame EthernetFrame::decode(const std::string ethernet_message) {
    vector<string> frame_parts = split(ethernet_message, ETHERNET_SEPERATOR);
    return EthernetFrame(stoi(frame_parts[SRC_ADDR_IDX]), stoi(frame_parts[DST_ADDR_IDX]), frame_parts[CONTENT_IDX]);
}

std::string EthernetFrame::encode(const EthernetFrame ethernet_frame) {
    return to_string(ethernet_frame.src_address)
            + ETHERNET_SEPERATOR
            + to_string(ethernet_frame.dst_address)
            + ETHERNET_SEPERATOR
            + ethernet_frame.content;
}

std::string EthernetFrame::getContent() {
    return content;
}

int EthernetFrame::getSourceAddress() {
    return src_address;
}
