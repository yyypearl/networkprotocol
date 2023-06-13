#include "mbed.h"
#include "L3_msg.h"

uint8_t L3_encodePARINFO(uint8_t* msg, uint8_t numpar)
{
    uint8_t size;

    msg[0] = 0; //type
    msg[1] = numpar; //참가자 수 알림
    size = 2;

    return size; //사이즈 생략 가능
}

uint8_t L3_getPARINFO_numpar(uint8_t* msg)
{
    return msg[1]; /참가자 수 알림
}


uint8_t L3_encodePARCNF(uint8_t* msg, uint8_t* str)
{
    uint8_t size;

    msg[0] = 2; //type
    strcpy(str, &msg[1]); //확정ID 알림
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

    msg[0] = 3; //type
    strcpy(str, &msg[1]); //룰 알림
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

    msg[0] = 6; //type
    strcpy(str, &msg[1]); //정답 설명 알림
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

    msg[0] = 8; //type
    msg[1] = subcnf; //정답제출 확인 알림
    size = 2;

    return size;
}

uint8_t L3_getSUBCNF_subcnf(uint8_t* msg)
{
    return msg[1]; //정답제출 확인 알림
}


uint8_t L3_encodeRESREQ(uint8_t* msg, uint8_t end, uint8_t* str)
{
    uint8_t size;

    msg[0] = 9; //type
    msg[1] = end; //게임종료 알림
    strcpy(str, &msg[2]);
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




uint8_t L3_decodePARREQ(uint8_t* msg, uint8_t* str1)
// PAR_REQ: 희망 ID
{
    uint8_t offset, size;

    if (str1 == NULL)
    {
        debug("[WARNING] null pointer!!! \n");
        return 0;
    }

    msg[0] = 1; //type
    //1번 : 희망 ID
    size = msg[1]; //희망 ID string 길이
    offset = 2; // 시작점
    strcpy(str1, &msg[offset]); //첫번째 data

    return size;
}

uint8_t* L3_getPARREQ_result1(uint8_t* msg)
{
    return &msg[1]; //첫번째 data 알림
}

uint8_t L3_decodeRSCNF(uint8_t* msg, uint8_t* str1, uint8_t* str2, uint8_t* str3)
// RS_CNF: 출제자 룰 확인, 출제 문제 정답, 정답 설명
{
    uint8_t offset, size; //offset은 위치(시작점), size는 크기값

    if (str1 == NULL || str2 == NULL || str3 == NULL)
    {
        debug("[WARNING] null pointer!!! \n");
        return 0;
    }

    msg[0] = 4; //type
    //1번 : 출제자 룰 확인 추출
    size = msg[1]; //출제자 룰 확인 string 길이
    offset = 2; // 시작점
    strcpy(str1, &msg[offset]); //첫번째 data

    //2번 : 출제 문제 정답 추출
    offset = offset + size + 2;//strlen 동작 확인 후 수정
    size = msg[offset - 1]; //size=len이라는 배열값 의미함.
    strcpy(str2, &msg[offset]); //두번째 data

    //3번 : 정답 설명
    offset = offset + size + 2;
    size = msg[offset - 1];
    strcpy(str3, &msg[offset]); //세번째 data

    
    //size = msg[1 + size + 1]; //strlen 동작 확인 후 수정
    //strcpy(&msg[3], str3); //세번째 data
    //size = strlen(str1)+ strlen(str2)+ strlen(str3) + 1;

    return size;
}

uint8_t* L3_getRSCNF_result1(uint8_t* msg)
{
    return &msg[1]; //첫번째 data 알림
}

uint8_t* L3_getRSCNF_result2(uint8_t* msg)
{
    return &msg[2]; //두번째 data 알림
}

uint8_t* L3_getRSCNF_result3(uint8_t* msg)
{
    return &msg[3]; //세번째 data 알림
}


uint8_t L3_decodeRULCNF(uint8_t* msg, uint8_t* str1)
// RUL_CNF: 참가자 룰 확인
{
    uint8_t offset, size;

    if (str1 == NULL)
    {
        debug("[WARNING] null pointer!!! \n");
        return 0;
    }

    msg[0] = 5; //type
    //1번 : 참가자 룰 확인
    size = msg[1]; //참가자 룰 확인 string 길이
    offset = 2; // 시작점
    strcpy(str1, &msg[offset]); //첫번째 data

    return size;
}

uint8_t* L3_getRULCNF_result1(uint8_t* msg)
{
    return &msg[1]; //첫번째 data 알림
}

uint8_t L3_decodeESCNF(uint8_t* msg, uint8_t* str1)
// ES_CNF: 참가자 제출 정답
{
    uint8_t offset, size;

    if (str1 == NULL)
    {
        debug("[WARNING] null pointer!!! \n");
        return 0;
    }

    msg[0] = 7; //type 
    //1번 : 참가자 제출 정답 추출
    size = msg[1]; //참가자 제출 정답 string 길이
    offset = 2; // 시작점
    strcpy(str1, &msg[offset]); //첫번째 data

    return size;
}

uint8_t* L3_getESCNF_result1(uint8_t* msg)
{
    return &msg[1]; //첫번째 data 알림
}

uint8_t L3_decodeRESCNF(uint8_t* msg, uint8_t* str1)
// RES_CNF: 종료 확인
{
    uint8_t offset, size;

    if (str1 == NULL)
    {
        debug("[WARNING] null pointer!!! \n");
        return 0;
    }

    msg[0] = 10 //type 
    //1번 : 종료 확인 추출
    size = msg[1]; //종료 확인 string 길이
    offset = 2; // 시작점
    strcpy(str1, &msg[offset]); //첫번째 data

    return size;
}

uint8_t* L3_getRESCNF_result1(uint8_t* msg)
{
    return &msg[1]; //첫번째 data 알림
}




