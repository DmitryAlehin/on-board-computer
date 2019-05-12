#ifndef MCP41_42XXX_H
#define MCP41_42XXX_H

#include "spi.h"

void MCP41_Write(uint8_t value);
void MCP42_Write(uint8_t value, uint8_t channel);
void MCP_Idle(uint8_t channel);
#endif