typedef enum L3_event
{
    L3_event_msgRcvd = 0, //PAR_REQ, RS_CNF, RUL_CNF, RES_CNF, ES_CNF 수신
    //L3_event_PARREQ = 1,
    L3_event_PARCNF = 2,
    L3_event_RSREQ = 3,
    //L3_event_RSCNF= 4,
    //L3_event_RESCNF= 5,
    L3_event_RESREQ= 6,
    L3_event_recfgSrcIdCnf = 7,
    L3_event_timer1 = 8,
    L3_event_timeout1=9,
    L3_event_timer2 = 10,
    L3_event_timeout2 = 11,
    L3_event_DATACNF =12,
    L3_event_dataToSend = 13


} L3_event_e;


void L3_event_setEventFlag(L3_event_e event);
void L3_event_clearEventFlag(L3_event_e event);
void L3_event_clearAllEventFlag(void);
int L3_event_checkEventFlag(L3_event_e event);