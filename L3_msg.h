#include "mbed.h"

uint8_t L3_encodePARINFO(uint8_t* msg, uint8_t numpar);
uint8_t L3_getPARINFO_numpar(uint8_t* msg)
uint8_t L3_encodePARCNF(uint8_t* msg, uint8_t* str)
uint8_t L3_getPARCNF_cnfID(uint8_t* msg);
uint8_t L3_encodeRSREQ(uint8_t* msg, uint8_t* str);
uint8_t* L3_getRSREQ_rule(uint8_t* msg);
uint8_t L3_encodeEXPREQ(uint8_t* msg, uint8_t* str)
uint8_t* L3_getEXPREQ_exp(uint8_t* msg)
uint8_t L3_encodeSUBCNF(uint8_t* msg, uint8_t subcnf);
uint8_t L3_getSUBCNF_subcnf(uint8_t* msg)
uint8_t L3_encodeRESREQ(uint8_t* msg, uint8_t end, uint8_t* str);
uint8_t L3_getRESREQ_end(uint8_t* msg);
uint8_t* L3_getRESREQ_result(uint8_t* msg);

uint8_t L3_decodePARREQ(uint8_t* msg, uint8_t* str1);
uint8_t* L3_getPARREQ_result1(uint8_t* msg);
uint8_t L3_decodeRSCNF(uint8_t* msg, uint8_t* str1, uint8_t* str2, uint8_t* str3);
uint8_t* L3_getRSCNF_result1(uint8_t* msg);
uint8_t* L3_getRSCNF_result2(uint8_t* msg);
uint8_t* L3_getRSCNF_result3(uint8_t* msg);
uint8_t L3_decodeRULCNF(uint8_t* msg, uint8_t* str1);
uint8_t* L3_getRULCNF_result1(uint8_t* msg);
uint8_t L3_decodeESCNF(uint8_t* msg, uint8_t* str1);
uint8_t* L3_getESCNF_result1(uint8_t* msg);
uint8_t L3_decodeRESCNF(uint8_t* msg, uint8_t* str1);
uint8_t* L3_getRESCNF_result1(uint8_t* msg);