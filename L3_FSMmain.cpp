#include "L3_FSMevent.h"
#include "L3_msg.h"
#include "L3_timer.h"
#include "L3_LLinterface.h"
#include "protocol_parameters.h"
#include "mbed.h"


//FSM state -------------------------------------------------
#define L3STATE_Information              0


//state variabl
static uint8_t main_state = L3STATE_Information; //protocol state
static uint8_t prev_state = main_state;

//SDU (input)
static uint8_t originalWord[1030];
static uint8_t wordLen=0;

static uint8_t sdu[1030];

//serial port interface
static Serial pc(USBTX, USBRX);
static uint8_t myDestId;

static uint8_t assignIDexaminer = 1;
static uint8_t assignIDparticipant = 2;

//application event handler : generating SDU from keyboard input
static void L3service_processInputWord(void)
{
    char c = pc.getc();
    if (!L3_event_checkEventFlag(L3_event_dataToSend))
    {
        if (c == '\n' || c == '\r')
        {
            originalWord[wordLen++] = '\0';
            L3_event_setEventFlag(L3_event_dataToSend);
            debug_if(DBGMSG_L3,"word is ready! ::: %s\n", originalWord);
        }
        else
        {
            originalWord[wordLen++] = c;
            if (wordLen >= L3_MAXDATASIZE-1)
            {
                originalWord[wordLen++] = '\0';
                L3_event_setEventFlag(L3_event_dataToSend);
                pc.printf("\n max reached! word forced to be ready :::: %s\n", originalWord);
            }
        }
    }
}


// ID 추출 함수
int getAssignedID(uint8_t* msg, int cnt) {
    int assignIDparticipant = 123; // 임의의 값 할당
    int assignIDexaminer = 456;
    int assignedID = -1; // 할당된 ID를 저장할 변수, 초기값 -1

    char* str = (char*)L3_getPARREQ_result1(msg);
    assignIDparticipant = atoi(str);

    if (cnt == 1) { //참가자일 때
        assignedID = assignIDparticipant;
    }

    else if (cnt == 2) { //출제자일 때
        assignIDexaminer = atoi(str);
        if (assignIDexaminer == assignIDparticipant) {
            assignIDexaminer++;
        }
        assignedID = assignIDexaminer;
    }

    return assignedID;
}



void L3_initFSM(uint8_t destId)
{
    myDestId = destId;
    //initialize service layer
    pc.attach(&L3service_processInputWord, Serial::RxIrq);

    L3_timer_startTimer(); //initial timer for 심판찾기
    
    pc.printf("Give a word to send : ");
}



void L3_FSMrun(void)
{   
    if (prev_state != main_state)
    {
        debug_if(DBGMSG_L3, "[L3] State transition from %i to %i\n", prev_state, main_state);
        prev_state = main_state;
    }

   switch (main_state)
    {
        case L3STATE_SRCH: //심판 찾는 중
            
            cnt = 0;   
            
            if (L3_event_checkEventFlag(L3_event_timeout1))
            {
                L3_timer_startTimer(3); //timer for broadcasting PAR_INFO

                strcpy((char*)sdu, (char*)originalWord);
                debug("[L3] msg length : %i\n", wordLen);
                L3_LLI_dataReqFunc(sdu, wordLen, 255);

                debug_if(DBGMSG_L3, "[L3] sending msg....\n");
                wordLen = 0;

                pc.printf("Give a word to send : ");

                main_state = L3STATE_PAR;
                
                
                L3_event_clearEventFlag(L3_event_timeout1);
            }
            break;
            

        case L3STATE_PAR: //구성 중

            cnt = 0;
            int myDestId_part;
            int myDestId_exam;

            if (L3_event_checkEventFlag(L3_event_timeout1)) //event a
            {
                strcpy((char*)sdu, (char*)originalWord);
                debug("[L3] msg length : %i\n", wordLen);
                L3_LLI_dataReqFunc(sdu, wordLen, 255);

                debug_if(DBGMSG_L3, "[L3] sending msg....\n");
                wordLen = 0;

                pc.printf("Give a word to send : ");        //send PAR_ INFO

                L3_startTimer(5); //timer for broadcasting PAR_INFO

                L3_event_clearEventFlag(L3_event_timeout1);
            }
            else if (L3_event_checkEventFlag(L3_event_msgRcvd)) //PAR_REQ 수신받았을 때 PAR_CNF 송신 = event b
            {
                cnt++;

                if (cnt == 1)
                {
                    myDestId_part = getAssignedID(msg, 1);
                    std::cout << "Assigned ID for participant: " << myDestId_part << std::endl;
                    
                    debug("[L3] msg length : %i\n", wordLen);
                    L3_LLI_dataReqFunc(sdu, wordLen, myDestId_part);

                    debug_if(DBGMSG_L3, "[L3] sending msg....\n");    
                    wordLen = 0;
                }   
                else if(cnt == 2)
                {
                    myDestId_exam = getAssignedID(msg, 2);
                    std::cout << "Assigned ID for examiner: " << myDestId_exam << std::endl;
                    
                    debug("[L3] msg length : %i\n", wordLen);
                    L3_LLI_dataReqFunc(sdu, wordLen, myDestId_exam);

                    debug_if(DBGMSG_L3, "[L3] sending msg....\n");    
                    wordLen = 0;
                }
                L3_event_clearEventFlag(L3_event_msgRcvd);                                             
            }

            else if (L3_event_checkEventFlag(L3_event_dataSendCnf)) // event d
            {       
                if (cnt >= 2)
                {  
                    L3_timer_stopTimer();
                    strcpy((char*)sdu, (char*)originalWord);
                    debug("[L3] msg length : %i\n", wordLen);
                    L3_LLI_dataReqFunc(sdu, wordLen, 255);

                    debug_if(DBGMSG_L3, "[L3] sending msg....\n"); //RS_REQ 방송
                    wordLen = 0;                                    

                    main_state = L3STATE_EXAM;
                }

                L3_event_clearEventFlag(L3_event_msgRcvd);
            }     
            break;

        case L3STATE_EXAM: //문제 출제 중
            
            cnt = 0; 
            
            if (L3_event_checkEventFlag(L3_event_msgRcvd)) 
            {
                cnt++;  
                                                // c1 = False 일 때 event e,f
                if (cnt >= 2)
                {
                    strcpy((char*)sdu, (char*)originalWord);
                    debug("[L3] msg length : %i\n", wordLen);
                    L3_LLI_dataReqFunc(sdu, wordLen, myDestId);

                    debug_if(DBGMSG_L3, "[L3] sending msg....\n");      // c1 = False 일 때 event e,f (심판 -> 참가자)
                    wordLen = 0;

                    main_state = L3STATE_ANS;
                }

                L3_event_clearEventFlag(L3_event_msgRcvd);
            }
            break; 

        case L3STATE_ANS: //답변 중
            
            cnt = 0;
            
            if (L3_event_checkEventFlag(L3_event_msgRcvd)) 
            {
                strcpy((char*)sdu, (char*)originalWord);      
                debug("[L3] msg length : %i\n", wordLen);
                L3_LLI_dataReqFunc(sdu, wordLen, myDestId);

                debug_if(DBGMSG_L3, "[L3] sending msg....\n");
                wordLen = 0;                                     //심판이 RES_REQ 전송

                main_state = L3STATE_FIN;                        


                L3_event_clearEventFlag(L3_event_msgRcvd);
            }
            /*else if (L3_event_checkEventFlag(L3_event_RESCNF)) //Send to msg about RES_REQ with RES_CNF
            {
                strcpy((char*)sdu, (char*)originalWord);
                debug("[L3] msg length : %i\n", wordLen);
                L3_LLI_dataReqFunc(sdu, wordLen, myDestId);


                debug_if(DBGMSG_L3, "[L3] sending msg....\n");
                wordLen = 0;


               
                pc.printf("Check MSG about Ending : ");
 
               
                L3_event_clearEventFlag(L3_event_RESCNF);
            }*/
            break;
        
        case L3STATE_FIN: //결과 발표 중
           
            cnt = 0;

            if (L3_event_checkEventFlag(L3_event_msgRcvd)) //참가자, 출제자로부터 RES_CNF 받을 때
            {                                       
                cnt++;
                
                if (cnt >= 2)
                {
                    main_state = L3STATE_PAR;
                }

                L3_event_clearEventFlag(L3_event_msgRcvd);
            }
            /*else if (L3_event_checkEventFlag(L3_event_RESCNF)) //Send to msg about RES_REQ with RES_CNF
            {
                strcpy((char*)sdu, (char*)originalWord);
                debug("[L3] msg length : %i\n", wordLen);
                L3_LLI_dataReqFunc(sdu, wordLen, myDestId);


                debug_if(DBGMSG_L3, "[L3] sending msg....\n");
                wordLen = 0;


               
                pc.printf("Check MSG about Ending : ");
 
               
                L3_event_clearEventFlag(L3_event_RESCNF);
            }*/
            break;

    }
}    
    
   
   