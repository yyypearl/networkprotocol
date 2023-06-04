#include "mbed.h"
#include "L3_msg.h"

uint8_t L3_encodePARINFO(uint8_t* msg, uint8_t numpar)
{
    uint8_t size;

    msg[0] = 0; //type
    msg[1] = numpar; //참가자 수 알림
    size = 2;

    return size;
}

uint8_t L3_getPARINFO_cnfID(uint8_t* msg)
{
    return msg[1]; /참가자 수 알림
}


uint8_t L3_encodePARCNF(uint8_t* msg, uint8_t* str)
{
    uint8_t size;

    msg[0] = 0; //type
    strcpy(&msg[1], str); //확정ID 알림
    size = strlen(str) + 1;

    return size;
}

uint8_t* L3_getPARCNF_cnfID(uint8_t* msg)
{
    return &msg[1]; //확정ID 알림
}


uint8_t L3_encodeRSREQ(uint8_t* msg, uint8_t* str)
{
    uint8_t size;

    msg[0] = 1; //type
    strcpy(&msg[1], str); //룰 알림
    size = strlen(str) + 1;

    return size;
}

uint8_t* L3_getRSREQ_rule(uint8_t* msg)
{
    return &msg[1]; //룰 알림
}


uint8_t L3_encodeEXPREQ(uint8_t* msg, uint8_t* str)
{
    uint8_t size;

    msg[0] = 2; //type
    strcpy(&msg[1], str); //정답 설명
    size = strlen(str) + 1;

    return size;
}

uint8_t* L3_getEXPREQ_exp(uint8_t* msg)
{
    return &msg[1]; //정답 설명 알림
}


uint8_t L3_encodeSUBCNF(uint8_t* msg, uint8_t subcnf) //subcnf="정답 제출 완료"
{
    uint8_t size;

    msg[0] = 2; //type
    msg[1] = subcnf; //정답제출 확인 알림
    size = 2;

    return size;
}

uint8_t L3_getSUBCNF_end(uint8_t* msg)
{
    return msg[1]; //정답제출 확인 알림
}


uint8_t L3_encodeRESREQ(uint8_t* msg, uint8_t end, uint8_t* str)
{
    uint8_t size;

    msg[0] = 1; //type
    msg[1] = end; //게임종료 알림
    strcpy(&msg[2], str);
    size = strlen(str) + 2;

    return size;
}

uint8_t L3_getRESREQ_end(uint8_t* msg)
{
    return msg[1]; //게임종료 알림
}

uint8_t* L3_getRESREQ_result(uint8_t* msg)
{
    return &msg[2]; //게임결과 알림
}


uint8_t L3_decodeMSGRCVD(uint8_t* msg, uint8_t* str1, uint8_t* str2, uint8_t* str3)
// PAR_REQ: 희망 ID
// RS_CNF: 출제자 룰 확인, 출제 문제 정답, 정답 설명
// RUL_CNF: 참가자 룰 확인
// ES_CNF: 참가자 제출 정답
// RES_CNF: 종료 확인
{
    uint8_t size;

    msg[0] = 1; //type (pcu를 합쳐서.. 일단 type 1로)
    strcpy(&msg[1], str); //첫번째 data
    strcpy(&msg[2], str); //두번째 data
    strcpy(&msg[3], str); //세번째 data
    size = strlen(str1)+ strlen(str2)+ strlen(str3) + 1;

    return size;
}

uint8_t* L3_getMSGRCVD_result1(uint8_t* msg)
{
    return &msg[1]; //첫번째 data 알림
}

uint8_t* L3_getMSGRCVD_result2(uint8_t* msg)
{
    return &msg[2]; //두번째 data 알림
}

uint8_t* L3_getMSGRCVD_result3(uint8_t* msg)
{
    return &msg[3]; //세번째 data 알림
}

// 문자열 어떻게 끊어서 받을 것인가..? 그건 아직 못함
