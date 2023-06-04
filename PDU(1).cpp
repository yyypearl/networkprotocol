//PDU 정의
class PAR_INFO {
public:
    uint8_t type;  // 타입 필드
    uint8_t participants;  // 참가자 수 필드

    PAR_INFO(uint8_t numParticipants) {
        type = 0;  // 타입 필드 설정
        length = sizeof(PAR_INFO);
        participants = numParticipants;  // 참가자 수 필드 설정
    }
};

class PAR_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t cnfID; // 확정 ID 필드

    PAR_CNF(uint8_t numcnfID) {
        type = 0;  // 타입 필드 설정
        length = sizeof(PAR_CNF);
        confID = numcnfID;  // 확정 ID 필드 설정
    }
};

class RS_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t rule_send;  // 룰 내용 필드

    RS_REQ(uint8_t ruletext) {
        type = 1;  // 타입 필드 설정
        length = sizeof(RS_REQ);
        rule_send = ruletext;  // 룰 내용 필드 설정
    }
};

class EXP_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t explain;  // 정답 설명 필드

    EXP_REQ(uint8_t explaintext) {
        type = 2;  // 타입 필드 설정
        length = sizeof(EXP_REQ);
        explain = explaintext; // 정답 설명 필드
    }
};

class SUB_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t subcnf; // 정답 제출 확인 필드

    SUB_CNF(uint8_t subcnftext) {
        type = 2;  // 타입 필드 설정
        length = sizeof(SUB_CNF);
        subcon = subcnftext; // 정답 제출 확인 필드 설정
    }
};

class RES_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t result;  // 결과 필드
    uint8_t end; // 종료 알림 필드

    RES_REQ(uint8_t resulttext, uint8_t endtext) {
        type = 3;  // 타입 필드 설정
        length = sizeof(RES_REQ);
        result = resulttext;
        end = endtext;  // 종료 알림 필드 설정
    }
};

class MSG_RCVD { //PAR_REQ, RS_CNF, RUL_CNF, ES_CNF, RES_CNF
public:
    uint8_t type;  // 타입 필드
    uint8_t msg;   // 메세지

    MSG_RCVD(uint8_t msgtext) {
        type = 1;  // 타입 필드 설정
        length = sizeof(MSG_RCVD);
        msg = msgtext; 
        // PAR_REQ: 희망 ID
        // RS_CNF: 출제자 룰 확인, 출제 문제 정답, 정답 설명
        // RUL_CNF: 참가자 룰 확인
        // ES_CNF: 참가자 제출 정답
        // RES_CNF: 종료 확인
    }
    // 문자열 어떻게 끊어서 받을 것인가..? 그건 아직 못함
    // DATA_CNF?
    // length 수정 중.. sizeof(x)
};