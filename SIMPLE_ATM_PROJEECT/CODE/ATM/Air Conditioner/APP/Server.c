
#include "database.h"

 EN_serverError_t _isValidAccount ;
 EN_serverError_t _isBlockedAccount ;
 EN_serverError_t _isAmountAvailable ;
 EN_serverError_t _saveTransaction ;
ST_accountsDB_t *p_account = accountsDB;

uint8_t t = 0;
uint8_t trans_num=0;







/** REQUIRMENTS :-
 1- check pan given with pan in database   --- (done)
 2- if exists  --> SEREVER_OK           ----> return reference to this account in the DB    --- (done)
 3- if not     --> ACCOUNT_NOT_FOUND    ----> return ACCOUNT_NOT_FOUND
                                        ----> account reference will be NULL


/******************************************* isValidAccount **********************************************/
//calling database and card data

EN_serverError_t isValidAccount(uint8_t *pan )
{

    uint8_t exist_flag = 0 ;
    EN_serverError_t server_status ;

    for(uint8_t account_num= 0 ; account_num< 10 ; account_num++) // num of accounts
    {
        for(uint8_t counter = 0 ; counter < 18 ; counter++)
        {
            if( pan[counter] == (p_account)->primaryAccountNumber[counter] )
            {
                exist_flag =1 ;
				
            }
            else
            {
                p_account++;
                exist_flag =0;
                break ;
            }
        }
		
		if (exist_flag)
		{
			break;
		}
		
		
    }

    if(exist_flag)
    {
        server_status = SERVER_OK ;
    }
    else
    {
        server_status =ACCOUNT_NOT_FOUND  ;
        p_account = NULL ;

    }




    return server_status ;
}

// implement test function here



/*************************************** END OF isValidAccount ***********************************************/






/******************************************* isBlockedAccount **********************************************/
//calling pointer to account


EN_serverError_t isBlockedAccount()
{

    if(_isValidAccount== SERVER_OK)
    {
        if (p_account->state==BLOCKED)
        {


            return BLOCKED_ACCOUNT ;

        }
        else
        {

            return SERVER_OK;

        }

    }

}


/*************************************** END OF isBlockedAccount ***********************************************/










/******************************************* isAmountAvailable **********************************************/
// calling terminal data and database
EN_serverError_t isAmountAvailable(float *termData)
{

    if(_isValidAccount==SERVER_OK && _isBlockedAccount == SERVER_OK)
    {
        if ((p_account->balance)<(*termData))
        {
            return LOW_BALANCE;
        }
        else
        {
            return SERVER_OK;
        }

    }
}



/*************************************** END OF isAmountAvailable ***********************************************/










/******************************************* saveTransaction **********************************************/


/*
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{

//Card data
    for(uint8_t cardHolderName = 0 ; cardHolderName<25 ; cardHolderName++)
    {
        p_trancNum->cardHolderData.cardHolderName[cardHolderName] = transData->cardHolderData.cardHolderName[cardHolderName];

    }


    for(uint8_t C_PrimaryNum = 0 ; C_PrimaryNum <20 ; C_PrimaryNum++)
    {
        p_trancNum->cardHolderData.primaryAccountNumber[C_PrimaryNum] = transData->cardHolderData.primaryAccountNumber[C_PrimaryNum];

    }


    for(uint8_t C_ExpireDate = 0 ; C_ExpireDate <6 ; C_ExpireDate++)
    {
        p_trancNum->cardHolderData.cardExpirationDate[C_ExpireDate] = transData->cardHolderData.cardExpirationDate[C_ExpireDate];

    }


//terminal data
    p_trancNum->terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
    p_trancNum->terminalData.transAmount = transData->terminalData.transAmount;

    for(uint8_t C_transDate=0 ; C_transDate<11 ; C_transDate++)
    {
        p_trancNum->terminalData.transactionDate[C_transDate] = transData->terminalData.transactionDate[C_transDate];
    }



    if(_isValidAccount == ACCOUNT_NOT_FOUND)
    {
        p_trancNum->transState=FRAUD_CARD;

    }
    else if (_isBlockedAccount==BLOCKED_ACCOUNT)
    {

        p_trancNum->transState=DECLINED_STOLEN_CARD;
    }
    else if(_isAmountAvailable == LOW_BALANCE)
    {

        p_trancNum->transState=DECLINED_INSUFFECIENT_FUND;
    }

    else
    {
        p_trancNum->transState=APPROVED;
    }


    if(p_trancNum == &transaction[0])
    {
        p_trancNum->transactionSequenceNumber = 1;
    }
    else
    {
        p_trancNum->transactionSequenceNumber = p_trancNum->transactionSequenceNumber=((p_trancNum-1)->transactionSequenceNumber)+1;

    }
    listSavedTransactions();
    t++;
    p_trancNum=transaction+t;
    return SERVER_OK ;
}

// implement test function here



*/


/*************************************** END OF saveTransaction ***********************************************/




/******************************************* listSavedTransactions **********************************************/

/*
void listSavedTransactions(void)
{

    printf("-------------------------------------\n");
    printf("Card Holder Name : ");

    p_trancNum=transaction+trans_num;

    for(uint8_t cardHolderName = 0 ; cardHolderName<24 ; cardHolderName++)
    {
        printf("%c",p_trancNum->cardHolderData.cardHolderName[cardHolderName]) ;

    }
    printf("\t ");

    printf("PAN: ");

    for(uint8_t C_PrimaryNum = 0 ; C_PrimaryNum <18 ; C_PrimaryNum++)
    {
        printf("%c", p_trancNum->cardHolderData.primaryAccountNumber[C_PrimaryNum] );

    }
    printf("\t");

    printf("ExpireDate : ");

    for(uint8_t C_ExpireDate = 0 ; C_ExpireDate <6 ; C_ExpireDate++)
    {
        printf("%c", p_trancNum->cardHolderData.cardExpirationDate[C_ExpireDate]);

    }

    printf("\n");
    printf("MaxTransAmount : ");
    printf("%.2f", p_trancNum->terminalData.maxTransAmount) ;

    printf("\t\t\t ");
    printf("TransAmount : ");
    printf("%.2f",p_trancNum->terminalData.transAmount );

    printf("\t\t");
    printf("TransactionDate : ");
    for(uint8_t C_transDate=0 ; C_transDate<11 ; C_transDate++)
    {
        printf("%c",p_trancNum->terminalData.transactionDate[C_transDate] );
    }
    printf("\n");
    printf("TransState : ");

    if(p_trancNum->transState == APPROVED) printf("APPROVED");
    else if(p_trancNum->transState == DECLINED_INSUFFECIENT_FUND) printf("DECLINED_INSUFFECIENT_FUND");
    else if(p_trancNum->transState == DECLINED_STOLEN_CARD) printf("DECLINED_STOLEN_CARD");
    else if(p_trancNum->transState == FRAUD_CARD) printf("FRAUD_CARD");
    else  printf("INTERNAL_SERVER_ERROR");


    printf("\n");
    printf("Current balance  : ");
    if(p_account!=NULL)
        printf("%.2f",p_account->balance);

    printf("\n");
    printf("Sequence Number : ");
    printf("%d",p_trancNum->transactionSequenceNumber);


    printf("\n-------------------------------------\n");

    trans_num++;




}

*/

/******************************************* End of listSavedTransactions **********************************************/





