class PAR_INFO {
public:
    uint8_t type;  // 타입 필드
    uint8_t participants;  // 참가자 수 필드

    // 생성자
    PAR_INFO(uint8_t numParticipants) {
        type = 0;  // 타입 필드 설정
        participants = numParticipants;  // 참가자 수 필드 설정
    }

    // 메서드 예시
    void setType(uint8_t newType) {
        type = newType;
    }

    uint8_t getType() const {
        return type;
    }

    // 추가 기능 및 메서드 정의
    // ...
};

class PAR_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t wantID; // 희망 ID 필드

    // 생성자
    PAR_REQ(uint8_t numwantID) {
        type = 0;  // 타입 필드 설정
        wantID = numwantID;  // 희망 ID 필드 설정
    }
};

class PAR_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t confID; // 확정 ID 필드

    // 생성자
     PAR_CNF(uint8_t numconfID) {
        type = 0;  // 타입 필드 설정
        confID = numconfID;  // 확정 ID 필드 설정
    }
};

class RS_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t rule_send;  // 룰 내용 필드

    // 생성자
    RS_REQ(uint8_t ruletext) {
        type = 1;  // 타입 필드 설정
        rule_send = ruletext;  // 룰 내용 필드 설정
    }
};

class RS_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t rule_con; // 룰 확인 필드
    uint8_t answer; // 출제 문제 정답
    uint8_t explain; // 정답 설명

    // 생성자
    RS_CNF(uint8_t rulecon, uint8_t answertext, uint8_t explaintext)  {
        type = 1;  // 타입 필드 설정
        rule_con = rulecon;  // 룰 확인 필드 설정
        answer=answertext; // 출제 문제 정답
        explain=explaintext; // 정답 설명
    }
};

class EXP_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t explain;  // 정답 설명 필드

    // 생성자
    EXP_REQ(uint8_t explaintext) {
        type = 2;  // 타입 필드 설정
        explain=explaintext; // 정답 설명 필드
    }
};

class ES_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t subanswer; // 참가자 제출 정답 필드

    // 생성자
    ES_CNF(uint8_t subanswertext) {
        type = 2;  // 타입 필드 설정
        subanswer = subanswertext;  // 참가자 제출 정답 필드 설정
    }
};

class SUB_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t subcon; // 정답 제출 확인 필드

    // 생성자

    SUB_CNF(uint8_t subcontext) {
        type = 2;  // 타입 필드 설정
        subcon = subcontext; // 정답 제출 확인 필드 설정
    }
};

class RES_REQ {
public:
    uint8_t type;  // 타입 필드
    uint8_t result;  // 결과 필드
    uint8_t endal; // 종료 알림 필드

    // 생성자
    RES_REQ(uint8_t resulttext, uint8_t endaltext) {
        type = 3;  // 타입 필드 설정
        result=resulttext;
        endal = endaltext;  // 종료 알림 필드 설정
    }
};

class RES_CNF {
public:
    uint8_t type;  // 타입 필드
    uint8_t endcon; // 종료 확인 필드

    // 생성자

    RES_CNF(uint8_t endcontext)  {
        type = 3;  // 타입 필드 설정
        endcon = endcontext;  // 종료 확인 필드 설정
    }
};