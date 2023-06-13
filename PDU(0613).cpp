//PDU 정의
class PAR_INFO {
public:
    uint8_t type;  // 타입 필드
    uint8_t participants;  // 참가자 수 필드

    PAR_INFO(uint8_t numParticipants) {
        type = 0;  // 타입 필드 설정
        length = 50;
        participants = numParticipants;  // 참가자 수 필드 설정
    }
};

class PAR_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t wantID;   // 희망 ID

    PAR_REQ(uint8_t numwantID) {
        type = 1;  // 타입 필드 설정
        length = 50;
        wantID = numwantID;
    }
};

class PAR_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t cnfID; // 확정 ID 필드

    PAR_CNF(uint8_t numcnfID) {
        type = 2;  // 타입 필드 설정
        length = 50;
        confID = numcnfID;  // 확정 ID 필드 설정
    }
};

class RS_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t rule_send;  // 룰 내용 필드

    RS_REQ(uint8_t ruletext) {
        type = 3;  // 타입 필드 설정
        length = 50;
        rule_send = ruletext;  // 룰 내용 필드 설정
    }
};

class RS_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t qrulcnf;   // 출제자 룰 확인
    uint8_t answer; // 출제 문제 정답
    uint8_t explain; // 정답 설명

    RS_CNF(uint8_t qrulcnftext, uint8_t qanswertext, uint8_t qexplaintext) {
        type = 4;  // 타입 필드 설정
        length = 100;
        qrulcnf = qrulcnftext;
        answer = answertext;
        explain = explaintext;
    }
};

class RUL_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t prulcnf;   // 참가자 룰 확인

    RUL_CNF(uint8_t prulcnftext) {
        type = 5;  // 타입 필드 설정
        length = 50;
        prulcnf = prulcnftext;
    }
};

class EXP_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t explain;  // 정답 설명 필드

    EXP_REQ(uint8_t explaintext) {
        type = 6;  // 타입 필드 설정
        length = 50;
        explain = explaintext; // 정답 설명 필드
    }
};

class ES_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t subanswer;   // 참가자 제출 정답

    ES_CNF(uint8_t subanswertext) {
        type = 7;  // 타입 필드 설정
        length = 50;
        subanswer = subanswertext;
    }
};

class SUB_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t subcnf; // 정답 제출 확인 필드

    SUB_CNF(uint8_t subcnftext) {
        type = 8;  // 타입 필드 설정
        length = 50;
        subcon = subcnftext; // 정답 제출 확인 필드 설정
    }
};

class RES_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t result;  // 결과 필드
    uint8_t end; // 종료 알림 필드

    RES_REQ(uint8_t resulttext, uint8_t endtext) {
        type = 9;  // 타입 필드 설정
        length = 50;
        result = resulttext;
        end = endtext;  // 종료 알림 필드 설정
    }
};

class RES_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t endcnf;   // 종료 확인

    RES_CNF(uint8_t endcnftext) {
        type = 10;  // 타입 필드 설정
        length = 50;
        endcnf = endcnftext;
    }
};