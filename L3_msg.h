#include "mbed.h"

#define L3_PDU_TYPE_PARINFO     0
#define L3_PDU_TYPE_PARREQ      1
#define L3_PDU_TYPE_PARCNF      2
#define L3_PDU_TYPE_RSREQ       3
#define L3_PDU_TYPE_RSCNF       4
#define L3_PDU_TYPE_RULCNF      5
#define L3_PDU_TYPE_EXPREQ      6
#define L3_PDU_TYPE_ESCNF       7
#define L3_PDU_TYPE_SUBCNF      8
#define L3_PDU_TYPE_RESREQ      9
#define L3_PDU_TYPE_RESCNF      10
#define L3_PDU_TYPE_DATACNF     11

uint8_t L3_getMsgType(uint8_t* msg);
uint8_t L3_encodePARINFO(uint8_t* msg, uint8_t numpar);
uint8_t L3_getPARINFO_numpar(uint8_t* msg);
char* L3_LLI_getParInfoMsg(uint8_t* dataPtr);

uint8_t L3_encodePARREQ(uint8_t* msg, uint8_t numpar);
char* L3_LLI_getParReqMsg(uint8_t* dataPtr);


uint8_t L3_encodePARCNF(uint8_t* msg, uint8_t role);
char* L3_LLI_getParCnfMsg(uint8_t* dataPtr);
uint8_t L3_LLI_getParCnfRole(uint8_t* dataPtr);

uint8_t L3_encodeDATACNF(uint8_t* msg);
char* L3_LLI_getDataCnfPMsg(uint8_t* dataPtr);
char* L3_LLI_getDataCnfQMsg(uint8_t* dataPtr);

uint8_t L3_encodeRSREQ(uint8_t* msg);
char* L3_LLI_getRsReqMsg(uint8_t* dataPtr);

uint8_t L3_encodeRSCNF(uint8_t* msg, uint8_t* answer, uint8_t* explain);
char* L3_LLI_getRsCnfRuleCHeckMsg(uint8_t* dataPtr);
char* L3_LLI_getRsCnfAnswerMsg(uint8_t* dataPtr);
char* L3_LLI_getRsCnfExplainMsg(uint8_t* dataPtr);

uint8_t L3_encodeRULCNF(uint8_t* msg);
char* L3_LLI_getRulCnfRuleCHeckMsg(uint8_t* dataPtr);


uint8_t L3_encodeEXPREQ(uint8_t* msg, uint8_t* str);
char* L3_LLI_getExpReqGuideMsg(uint8_t* dataPtr);
char* L3_LLI_getExpReqExplainMsg(uint8_t* dataPtr);

uint8_t L3_encodeESCNF(uint8_t* msg, uint8_t* subanswer);
char* L3_LLI_getEsCnfRuleCHeckMsg(uint8_t* dataPtr);
//

uint8_t L3_encodeSUBCNF(uint8_t* msg);
char* L3_LLI_getSubCnfMsg(uint8_t* dataPtr);


uint8_t L3_encodeRESREQ(uint8_t* msg, uint8_t end, uint8_t* str);
char* L3_LLI_getResReqAnswerMsg(uint8_t* dataPtr);
uint8_t L3_getRESREQ_end(uint8_t* dataPtr);
char* L3_LLI_getResReqEndMsg(uint8_t* dataPtr);

uint8_t L3_encodeRESCNF(uint8_t* msg);
char* L3_LLI_getResCnfEndMsg(uint8_t* dataPtr);