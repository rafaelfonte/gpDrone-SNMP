/*
GPDRONE-agent-X implementation

	Rafael da Fonte Lopes da Silva

	This file contains the implementation of a MIB module for managing an aircraft from
	Flight-Gear, by making use of its http daemon feature as an interface.

	This agent module makes use of a few shell scripts for making this interface easier to
	implement.
*/

/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <unistd.h>
#include "gpDroneMIB.h"

/*
 * The variables we want to tie the relevant OIDs to.
 * The agent will handle all GET and (if applicable) SET requests
 * to these variables automatically, changing the values as needed.
 */

u_long    sysTimeUp = 0;  /* XXX: set default value */
u_long    instClTimeToDest = 0;  /* XXX: set default value */
long    engNum = 0;  /* XXX: set default value */
long    flapsNum = 0;  /* XXX: set default value */
long    lightNum = 5;  /* XXX: set default value */
u_long    comOctetsRecvd = 0;  /* XXX: set default value */
u_long    comOctetSent = 0;  /* XXX: set default value */
u_long    comOctetsError = 0;  /* XXX: set default value */
long    lgCurState = 0;  /* XXX: set default value */
long    lgSetLock = 0;  /* XXX: set default value */
long    lgSetPosition = 0;  /* XXX: set default value */

//Extra variables
char sysAircraftID[] = "GP-DRONE v0.1";
char sysAircraftType[256];
char instPosGpsLatitude[5] = "0000";
char instPosGpsLongitude[5] = "0000";
char instPosAltitude[5] = "0000";
char instClTime[6] = "00:00";

char instSpeedGround[5] = "0000";
char instSpeedVertical[5] = "0000";

char instTotalFuel[5] = "0000";


//The following variables are used to populate the lightingTable table.
struct tb_entry *my_table;
LIGHT_TABLE_ENTRY l_table[] =	{{"beacon", "beacon"},
				{"landing-light-left", "landing-light"},
				{"landing-light-center", "landing-light[1]"},
				{"landing-light-right", "landing-light[2]"},
				{"logo-lights", "logo-lights"}};

/*
 * Our initialization routine, called automatically by the agent 
 * (Note that the function name must match init_FILENAME()) 
 */
void
init_gpDroneMIB(void)
{
  netsnmp_handler_registration *reg;

	//Series of OIDs and variable watchers. Not all of them are fully implemented thought :(
    const oid sysAircraftID_oid[] = {1,3,6,1,4,1,12620,1,1 };
  static netsnmp_watcher_info sysAircraftID_winfo;
    const oid sysAircraftType_oid[] = {1,3,6,1,4,1,12620,1,2 };
  static netsnmp_watcher_info sysAircraftType_winfo;
    const oid sysTimeUp_oid[] = { 1,3,6,1,4,1,12620,1,4 };
  static netsnmp_watcher_info sysTimeUp_winfo;
 //static netsnmp_watcher_info instPosMagneticCompass_winfo;
    const oid instPosGpsLatitude_oid[] = { 1,3,6,1,4,1,12620,2,1,5 };
  static netsnmp_watcher_info instPosGpsLatitude_winfo;
     const oid instPosGpsLongitude_oid[] = { 1,3,6,1,4,1,12620,2,1,6 };
  static netsnmp_watcher_info instPosGpsLongitude_winfo;
    const oid instPosAltitude_oid[] = { 1,3,6,1,4,1,12620,2,1,7 };
  static netsnmp_watcher_info instPosAltitude_winfo;
    const oid instClTime_oid[] = { 1,3,6,1,4,1,12620,2,2,1 };
  static netsnmp_watcher_info instClTime_winfo;
   const oid instSpeedGround_oid[] = { 1,3,6,1,4,1,12620,2,3,3 };
  static netsnmp_watcher_info instSpeedGround_winfo;
   const oid instSpeedVertical_oid[] = { 1,3,6,1,4,1,12620,2,3,4 };
   static netsnmp_watcher_info instSpeedVertical_winfo;
   const oid lgSetPosition_oid[] = { 1,3,6,1,4,1,12620,7,3 };
  static netsnmp_watcher_info lgSetPosition_winfo;
    const oid lightNum_oid[] = { 1,3,6,1,4,1,12620,5,1 };
  static netsnmp_watcher_info lightNum_winfo;
//New variable (not in the original MIB definition)...
    const oid instTotalFuel_oid[] = { 1,3,6,1,4,1,12620,2,5 };
  static netsnmp_watcher_info instTotalFuel_winfo;


  DEBUGMSGTL(("gpDroneMIB", "Initializing the gpDroneMIB module\n"));

/*
	Now we register the variables of the MIB...
*/

/*sysAircraftID*/
    DEBUGMSGTL(("gpDroneMIB",
                "Initializing sysAircraftID scalar octet string.  Default value = %s\n",
                sysAircraftID));
    reg = netsnmp_create_handler_registration(
             "sysAircraftID", NULL,
              sysAircraftID_oid, OID_LENGTH(sysAircraftID_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&sysAircraftID_winfo, sysAircraftID, strlen(sysAircraftID),
			      ASN_OCTET_STR, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &sysAircraftID_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched sysAircraftID" );
    }
/*end sysAircraftID*/

    fetch_string("sysAircraftType",sysAircraftType);
/*sysAircraftType*/
    DEBUGMSGTL(("gpDroneMIB",
                "Initializing sysAircraftType scalar octet string.  Default value = %s\n",
                sysAircraftType));
    reg = netsnmp_create_handler_registration(
             "sysAircraftType", NULL,
              sysAircraftType_oid, OID_LENGTH(sysAircraftType_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&sysAircraftType_winfo, sysAircraftType, strlen(sysAircraftType),
			      ASN_OCTET_STR, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &sysAircraftType_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched sysAircraftID" );
    }
/*end sysAircraftType*/


    DEBUGMSGTL(("gpDroneMIB",
                "Initializing sysTimeUp scalar integer.  Default value = %d\n",
                sysTimeUp));
    reg = netsnmp_create_handler_registration(
             "sysTimeUp", sysTimeUpHandler,
              sysTimeUp_oid, OID_LENGTH(sysTimeUp_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&sysTimeUp_winfo, &sysTimeUp, sizeof(u_long),
			      ASN_TIMETICKS, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &sysTimeUp_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched sysTimeUp" );
    }

/*instPosGpsLatitude*/
    DEBUGMSGTL(("gpDroneMIB",
                "Initializing instPosGpsLatitude scalar octet string.  Default value = %s\n",
                instPosGpsLatitude));
    reg = netsnmp_create_handler_registration(
             "instPosGpsLatitude", instPosGpsLatitudeHandler,
              instPosGpsLatitude_oid, OID_LENGTH(instPosGpsLatitude_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&instPosGpsLatitude_winfo, instPosGpsLatitude, strlen(instPosGpsLatitude),
			      ASN_OCTET_STR, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &instPosGpsLatitude_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched instPosGpsLatitude" );
    }
/*end instPosGpsLatitude*/
/*instPosGpsLongitude*/
    DEBUGMSGTL(("gpDroneMIB",
                "Initializing instPosGpsLongitude scalar octet string.  Default value = %s\n",
                instPosGpsLongitude));
    reg = netsnmp_create_handler_registration(
             "instPosGpsLongitude", instPosGpsLongitudeHandler,
              instPosGpsLongitude_oid, OID_LENGTH(instPosGpsLongitude_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&instPosGpsLongitude_winfo, instPosGpsLongitude, strlen(instPosGpsLongitude),
                              ASN_OCTET_STR, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &instPosGpsLongitude_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched instPosGpsLongitude" );
    }
/*end instPosGpsLongitude*/

/*instPosAltitude*/
    DEBUGMSGTL(("gpDroneMIB",
                "Initializing instPosAltitude scalar octet string.  Default value = %s\n",
                instPosAltitude));
    reg = netsnmp_create_handler_registration(
             "instPosAltitude", instPosAltitudeHandler,
              instPosAltitude_oid, OID_LENGTH(instPosAltitude_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&instPosAltitude_winfo, instPosAltitude, strlen(instPosAltitude),
                              ASN_OCTET_STR, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &instPosAltitude_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched instPosGpsLongitude" );
    }
/*end instPosAltitude*/

/*instSpeedGround*/
    DEBUGMSGTL(("gpDroneMIB",
                "Initializing instSpeedGround scalar octet string.  Default value = %s\n",
                instSpeedGround));
    reg = netsnmp_create_handler_registration(
             "instSpeedGround", instSpeedGroundHandler,
              instSpeedGround_oid, OID_LENGTH(instSpeedGround_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&instSpeedGround_winfo, instSpeedGround, strlen(instSpeedGround),
                              ASN_OCTET_STR, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &instSpeedGround_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched instPosGpsLongitude" );
    }
/*end instSpeedGround*/

/*instSpeedVertical*/
    DEBUGMSGTL(("gpDroneMIB",
                "Initializing instSpeedVertical scalar octet string.  Default value = %s\n",
                instSpeedVertical));
    reg = netsnmp_create_handler_registration(
             "instSpeedVertical", instSpeedVerticalHandler,
              instSpeedVertical_oid, OID_LENGTH(instSpeedVertical_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&instSpeedVertical_winfo, instSpeedVertical, strlen(instSpeedVertical),
                              ASN_OCTET_STR, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &instSpeedVertical_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched instPosGpsLongitude" );
    }
/*end instSpeedVertical*/



/*instClTime*/
    DEBUGMSGTL(("gpDroneMIB",
                "Initializing instClTime scalar octet string.  Default value = %s\n",
                instClTime));
    reg = netsnmp_create_handler_registration(
             "instClTime", instClTimeHandler,
              instClTime_oid, OID_LENGTH(instClTime_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&instClTime_winfo, instClTime, strlen(instClTime),
                              ASN_OCTET_STR, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &instClTime_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched instPosGpsLongitude" );
    }
/*end instClTime*/

    DEBUGMSGTL(("gpDroneMIB",
                "Initializing lightNum scalar integer.  Default value = %d\n",
                lightNum));
    reg = netsnmp_create_handler_registration(
             "lightNum", NULL,
              lightNum_oid, OID_LENGTH(lightNum_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&lightNum_winfo, &lightNum, sizeof(long),
			      ASN_INTEGER, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &lightNum_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched lightNum" );
    }

    DEBUGMSGTL(("gpDroneMIB",
                "Initializing lgSetPosition scalar integer.  Default value = %d\n",
                lgSetPosition));
    reg = netsnmp_create_handler_registration(
             "lgSetPosition", lgSetPositionHandler,
              lgSetPosition_oid, OID_LENGTH(lgSetPosition_oid),
              HANDLER_CAN_RWRITE);
    netsnmp_init_watcher_info(&lgSetPosition_winfo, &lgSetPosition, sizeof(long),
			      ASN_INTEGER, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &lgSetPosition_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched lgSetPosition" );
    }


//New fuel variable...

    DEBUGMSGTL(("gpDroneMIB",
                "Initializing instTotalFuel scalar octet string.  Default value = %s\n",
                instTotalFuel));
    reg = netsnmp_create_handler_registration(
             "instTotalFuel", instTotalFuelHandler,
              instTotalFuel_oid, OID_LENGTH(instTotalFuel_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&instTotalFuel_winfo, instTotalFuel, strlen(instTotalFuel),
                              ASN_OCTET_STR, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &instTotalFuel_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched instPosGpsLongitude" );
    }






  /* here we initialize all the tables we're planning on supporting */
  initialize_table_lightingTable();

  DEBUGMSGTL(("gpDroneMIB",
              "Done initalizing gpDroneMIB module\n"));
}

void mkLock(){
	FILE * mutex = fopen("lock","w");
	fprintf(mutex,"%d",1);
	fclose(mutex);
}

void runGetScript(const char * arg){
	char * l_args[] = {"./script_fetch.sh",arg,NULL};
	char *newenviron[] = { NULL };
	mkLock();
	int pid = fork();
	if(pid == 0)
		execve(l_args[0],l_args,newenviron);
	while(1){
		int m_val;
		FILE * mutex = fopen("lock","r");
		if(!mutex)
			continue;
		fscanf(mutex,"%d",&m_val);
		fclose(mutex);
		if(m_val == 0)
			break;
	}
	
}

void runSetScript(const char * arg,const char * val){
	char * l_args[] = {"./script_set.sh",arg,val,NULL};
	char *newenviron[] = { NULL };
	mkLock();
	int pid = fork();
	if(pid == 0)
		execve(l_args[0],l_args,newenviron);	
	//sleep(1);
	while(1){
		int m_val;
		FILE * mutex = fopen("lock","r");
		if(!mutex)
			continue;
		fscanf(mutex,"%d",&m_val);
		fclose(mutex);
		if(m_val == 0)
			break;
	}
}

void fetch_integer(const char * arg, long * var){
	runGetScript(arg);
	FILE * f = fopen("output","r");
	fscanf(f,"%ld",var);
	fclose(f);
}
void fetch_string_of_float(const char * arg, char * var){
	float fl;
	char *flptr;
	int i;
	runGetScript(arg);
	flptr = (char*)&fl;
	flptr[0] = 0;
	flptr[1] = 0;
	flptr[2] = 0;
	flptr[3] = 0;

	FILE *f = fopen("output","r");
	fscanf(f,"%e",&fl);
	fclose(f);
	flptr = (char*) &fl;
	for(i = 0; i < 4; i++)
		var[i] = flptr[i];
	
	if(strlen(var) == 0){//In this case, we have to re-fetch it for the number was in base-10 notation...
		FILE *f = fopen("output","r");
		fscanf(f,"%e",&fl);
		fclose(f);
		flptr = (char*) &fl;
		for(i = 0; i < 4; i++)
			var[i] = flptr[i];
	}

}

void fetch_string(const char * arg, char * var){
	int i;
	runGetScript(arg);
	FILE *f = fopen("output","r");
	i = fread(var,1,256,f);
	var[i-1] = '\0';
	fclose(f);
}

int sysTimeUpHandler(netsnmp_mib_handler *handler,
		     netsnmp_handler_registration *reginfo,
		     netsnmp_agent_request_info *reqinfo,
		     netsnmp_request_info *requests){
	DEBUGMSGTL(("gpDroneMIB", "Got request, mode is %d:\n", reqinfo->mode));
	switch(reqinfo->mode){
		case MODE_GET:
			fetch_integer("sysTimeUp",&sysTimeUp);
			sysTimeUp *= 100;
			snmp_set_var_typed_value(requests->requestvb,ASN_TIMETICKS,&sysTimeUp,sizeof(sysTimeUp));
			break;
		default:
			printf("ERROR - Something wrong happened!");
	}
	
}

int instPosGpsLatitudeHandler(netsnmp_mib_handler *handler,
		     netsnmp_handler_registration *reginfo,
		     netsnmp_agent_request_info *reqinfo,
		     netsnmp_request_info *requests){
	DEBUGMSGTL(("gpDroneMIB", "Got request, mode is %d:\n", reqinfo->mode));
	switch(reqinfo->mode){
		case MODE_GET:
			fetch_string_of_float("instPosGpsLatitude",instPosGpsLatitude);
			snmp_set_var_typed_value(requests->requestvb,ASN_OCTET_STR,instPosGpsLatitude,strlen(instPosGpsLatitude));
			break;
		default:
			printf("ERROR - Something wrong happened!");
	}
	
}

int instPosGpsLongitudeHandler(netsnmp_mib_handler *handler,
		     netsnmp_handler_registration *reginfo,
		     netsnmp_agent_request_info *reqinfo,
		     netsnmp_request_info *requests){
	DEBUGMSGTL(("gpDroneMIB", "Got request, mode is %d:\n", reqinfo->mode));
	switch(reqinfo->mode){
		case MODE_GET:
			DEBUGMSGTL(("gpDroneMIB", "Old val is: %s\n", instPosGpsLongitude));
			fetch_string_of_float("instPosGpsLongitude",instPosGpsLongitude);
			DEBUGMSGTL(("gpDroneMIB", "New val is: %s\n", instPosGpsLongitude));

			snmp_set_var_typed_value(requests->requestvb,ASN_OCTET_STR,instPosGpsLongitude,strlen(instPosGpsLongitude));
			break;
		default:
			printf("ERROR - Something wrong happened!");
	}
	
}

int instPosAltitudeHandler(netsnmp_mib_handler *handler,
		     netsnmp_handler_registration *reginfo,
		     netsnmp_agent_request_info *reqinfo,
		     netsnmp_request_info *requests){
	DEBUGMSGTL(("gpDroneMIB", "Got request, mode is %d:\n", reqinfo->mode));
	switch(reqinfo->mode){
		case MODE_GET:
			DEBUGMSGTL(("gpDroneMIB", "Old val is: %s\n", instPosAltitude));
			fetch_string_of_float("instPosAltitude",instPosAltitude);
			DEBUGMSGTL(("gpDroneMIB", "New val is: %s\n", instPosAltitude));

			snmp_set_var_typed_value(requests->requestvb,ASN_OCTET_STR,instPosAltitude,strlen(instPosAltitude));
			break;
		default:
			printf("ERROR - Something wrong happened!");
	}
	
}

int instSpeedGroundHandler(netsnmp_mib_handler *handler,
		     netsnmp_handler_registration *reginfo,
		     netsnmp_agent_request_info *reqinfo,
		     netsnmp_request_info *requests){
	DEBUGMSGTL(("gpDroneMIB", "Got request, mode is %d:\n", reqinfo->mode));
	switch(reqinfo->mode){
		case MODE_GET:
			DEBUGMSGTL(("gpDroneMIB", "Old val is: %s\n", instSpeedGround));
			fetch_string_of_float("instSpeedGround",instSpeedGround);
			DEBUGMSGTL(("gpDroneMIB", "New val is: %s\n", instSpeedGround));

			snmp_set_var_typed_value(requests->requestvb,ASN_OCTET_STR,instSpeedGround,strlen(instSpeedGround));
			break;
		default:
			printf("ERROR - Something wrong happened!");
	}
	
}

int instSpeedVerticalHandler(netsnmp_mib_handler *handler,
		     netsnmp_handler_registration *reginfo,
		     netsnmp_agent_request_info *reqinfo,
		     netsnmp_request_info *requests){
	DEBUGMSGTL(("gpDroneMIB", "Got request, mode is %d:\n", reqinfo->mode));
	switch(reqinfo->mode){
		case MODE_GET:
			DEBUGMSGTL(("gpDroneMIB", "Old val is: %s\n", instSpeedVertical));
			fetch_string_of_float("instSpeedVertical",instSpeedVertical);
			DEBUGMSGTL(("gpDroneMIB", "New val is: %s\n", instSpeedVertical));

			snmp_set_var_typed_value(requests->requestvb,ASN_OCTET_STR,instSpeedVertical,strlen(instSpeedVertical));
			break;
		default:
			printf("ERROR - Something wrong happened!");
	}
	
}

int instTotalFuelHandler(netsnmp_mib_handler *handler,
		     netsnmp_handler_registration *reginfo,
		     netsnmp_agent_request_info *reqinfo,
		     netsnmp_request_info *requests){
	DEBUGMSGTL(("gpDroneMIB", "Got request, mode is %d:\n", reqinfo->mode));
	switch(reqinfo->mode){
		case MODE_GET:
			DEBUGMSGTL(("gpDroneMIB", "Old val is: %s\n", instTotalFuel));
			fetch_string_of_float("instTotalFuel",instTotalFuel);
			DEBUGMSGTL(("gpDroneMIB", "New val is: %s\n", instTotalFuel));

			snmp_set_var_typed_value(requests->requestvb,ASN_OCTET_STR,instTotalFuel,strlen(instTotalFuel));
			break;
		default:
			printf("ERROR - Something wrong happened!");
	}
	
}

int instClTimeHandler(netsnmp_mib_handler *handler,
		     netsnmp_handler_registration *reginfo,
		     netsnmp_agent_request_info *reqinfo,
		     netsnmp_request_info *requests){
	DEBUGMSGTL(("gpDroneMIB", "Got request, mode is %d:\n", reqinfo->mode));
	switch(reqinfo->mode){
		case MODE_GET:
			DEBUGMSGTL(("gpDroneMIB", "Old val is: %s\n", instClTime));
			fetch_string("instClTime",instClTime);
			DEBUGMSGTL(("gpDroneMIB", "New val is: %s\n", instClTime));

			snmp_set_var_typed_value(requests->requestvb,ASN_OCTET_STR,instClTime,strlen(instClTime));
			break;
		default:
			printf("ERROR - Something wrong happened!");
	}
	
}


int lgSetPositionHandler(netsnmp_mib_handler *handler,
		     netsnmp_handler_registration *reginfo,
		     netsnmp_agent_request_info *reqinfo,
		     netsnmp_request_info *requests){
	char buf_val[32];
	DEBUGMSGTL(("gpDroneMIB", "Got request, mode is %d:\n", reqinfo->mode));
	switch(reqinfo->mode){
		case MODE_SET_UNDO: //TODO
			DEBUGMSGTL(("gpDroneMIB", "lgSetPosition UNDO\n"));
			break;
		case MODE_SET_COMMIT:
			DEBUGMSGTL(("gpDroneMIB", "lgSetPosition COMMIT\n"));
			break;
		case MODE_SET_RESERVE1:
			DEBUGMSGTL(("gpDroneMIB", "lgSetPosition RESERVE1\n"));
		case MODE_SET_RESERVE2:
			DEBUGMSGTL(("gpDroneMIB", "lgSetPosition RESERVE2\n"));
			if(requests->requestvb->type != ASN_INTEGER){
				DEBUGMSGTL(("gpDroneMIB", "Got inside IF!!! type is %d\n",requests->requestvb->type));
				//netsnmp_set_request_error(reqinfo,requests,SNMP_ERR_WRONGTYPE);
			}
			DEBUGMSGTL(("gpDroneMIB", "Great success!\n"));
			break;
		case MODE_SET_FREE:
			DEBUGMSGTL(("gpDroneMIB", "lgSetPosition FREE\n"));
			break;
		case MODE_SET_ACTION:
			DEBUGMSGTL(("gpDroneMIB", "lgSetPosition ACTION\n"));
			lgSetPosition = *(requests->requestvb->val.integer);//Setting the variable
			sprintf(buf_val,"%ld",lgSetPosition);
			DEBUGMSGTL(("gpDroneMIB", "lgSetPosition val: %ld:\n", buf_val));
			runSetScript("lgSetPosition",buf_val);
			break;			
		case MODE_GET:
			fetch_integer("lgSetPosition",&lgSetPosition);
			snmp_set_var_typed_value(requests->requestvb,ASN_INTEGER,&lgSetPosition,sizeof(lgSetPosition));
			break;
		default:
			DEBUGMSGTL(("gpDroneMIB", "lgSetPosition DEFAULT\n"));
	}
	
}


/*char ** fetch_all_ligths(int * qnt){
	FILE *f = fopen("lights_descr.txt","r");
	char ** lights;
	int i,qnt_entries;

	fscanf(f,"%d",&qnt_entries);
	DEBUGMSGTL(("gpDroneMIB","Table entries: %d\n",qnt_entries));	
	lights = (char**)malloc(qnt_entries*sizeof(char*));
	
	for(i = 0; i < qnt_entries; i++){
		fscanf(f,"%s %s", );
	}
}
*/
/** Initialize the lightingTable table by defining its contents and how it's structured */
void
initialize_table_lightingTable(void)
{
    const oid lightingTable_oid[] = {1,3,6,1,4,1,12620,5,2};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("lightingTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_lightingTable",
                "adding indexes to table lightingTable\n"));
    //netsnmp_table_set_add_indexes(table_set,
    //                       ASN_INTEGER,  /* index: lightIndex */
    //                       0);
    //DEBUGMSGTL(("gpDroneMIB","pt-1\n"));
	netsnmp_table_dataset_add_index(table_set,
                           ASN_INTEGER);  /* index: lightIndex */
                       

    DEBUGMSGTL(("initialize_table_lightingTable",
                "adding column types to table lightingTable\n"));
    //DEBUGMSGTL(("gpDroneMIB","pt1\n"));			 
    /*netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_LIGHTDESCRIPTION, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_LIGHTTOGGLE, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_LIGHTINDEX, ASN_INTEGER, 0,
                                            NULL, 0,
                              0);
    */
	netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_LIGHTINDEX, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_LIGHTDESCRIPTION, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_LIGHTTOGGLE, ASN_INTEGER, 1,
                                            NULL, 0,
                              0);
    //DEBUGMSGTL(("gpDroneMIB","pt2\n"));			 
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change lightingTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("lightingTable", lightingTable_handler,
                                                        lightingTable_oid,
                                                        OID_LENGTH(lightingTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
	my_table = (struct tb_entry*)malloc(sizeof(struct tb_entry)*5);
	int i;
	for(i = 1; i <= 5; i++){
		my_table[i-1].index = (long)i;
		strncpy(my_table[i-1].descr,l_table[i-1].descr,256);
		my_table[i-1].toggle = 0;//TODO: initialize
		int index = i;
		netsnmp_table_row *row = netsnmp_create_table_data_row();
		netsnmp_table_row_add_index(row,ASN_INTEGER,&index,sizeof(index));
		netsnmp_set_row_column(row,1,ASN_INTEGER,&index,sizeof(index));
		netsnmp_mark_row_column_writable(row,1,0);	
		netsnmp_set_row_column(row,2,ASN_OCTET_STR,l_table[i-1].descr,strlen(l_table[i-1].descr));
		netsnmp_mark_row_column_writable(row,2,0);
		netsnmp_set_row_column(row,3,ASN_INTEGER,&index,sizeof(index));
		netsnmp_mark_row_column_writable(row,3,1);
		netsnmp_table_dataset_add_row(table_set,row);
	}
	/*FILE *f = fopen("result.txt","w");
	fprintf(f,"Index\t\tDescr\t\tToggle\n");
	for(i = 1; i <= 5; i++){
		fprintf(f,"%d\t\t%s\t\t%d\n",my_table[i-1].index,my_table[i-1].descr,my_table[i-1].toggle);
	}
	fclose(f);
	*/
}

/** handles requests for the lightingTable table, if anything else needs to be done */

int
lightingTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
//struct tb_entry{
//	int index;
//	char descr[256];
//	int toggle;
//};
    DEBUGMSGTL(("gpDroneMIB","got into the handler...., reqinfo is %d\n",reqinfo->mode));
	//struct light_table_entry *temp;
	netsnmp_table_request_info *table_info = netsnmp_extract_table_info(requests);
	int colnum = table_info->colnum,index = *(table_info->indexes->val.integer);
	char buf_val[32];
	//my_table
	//my_table[i-1].index = i;
	//strncpy(my_table[i-1].descr,l_table[i-1].descr,256);
	//my_table[i-1].toggle = 0;//TODO: initialize
	//temp = (struct light_table_entry*)netsnmp_tdata_extract_entry(requests);
	//for(i = 0; i < 20; i++){
	//DEBUGMSGTL(("gpDroneMIB","This is the column we got: %d\n", table_info->colnum));
	//DEBUGMSGTL(("gpDroneMIB","This is the column we got: %p %p\n", table_info, requests));
	//DEBUGMSGTL(("gpDroneMIB","This is the value of the first index: %d\n", *(table_info->indexes->val.integer)));

	DEBUGMSGTL(("gpDroneMIB","Request was col %d idx %d\n",colnum, index));

	switch(reqinfo->mode){
		case MODE_SET_RESERVE1:
			if(index < 1 || index > 5){
				netsnmp_set_request_error(reqinfo,requests,SNMP_NOSUCHINSTANCE);
				break;
			}
		case MODE_SET_RESERVE2:
		case MODE_SET_FREE:
		case MODE_SET_COMMIT:
			break;
		case MODE_SET_ACTION:
			DEBUGMSGTL(("gpDroneMIB", "tableSetToggle ACTION\n"));
			my_table[index-1].toggle = *(requests->requestvb->val.integer);//Setting the variable
			sprintf(buf_val,"%ld",my_table[index-1].toggle);
			DEBUGMSGTL(("gpDroneMIB", "lgSetPosition val: %ld:\n", buf_val));
			runSetScript(my_table[index-1].descr,buf_val);
			break;
		case MODE_GET:
		case MODE_GETNEXT:
			if(index < 1 || index > 5){
				netsnmp_set_request_error(reqinfo,requests,SNMP_NOSUCHINSTANCE);
				break;
			}
			switch(colnum){
				case 1:
					snmp_set_var_typed_value(requests->requestvb,ASN_INTEGER,&(my_table[index-1].index),sizeof(long));
	DEBUGMSGTL(("gpDroneMIB","Returning INTEGER<idx=%d,col=%d> : %ld\n", index,colnum,my_table[index-1].index));
					break;
				case 2:
					snmp_set_var_typed_value(requests->requestvb,ASN_OCTET_STR,my_table[index-1].descr,strlen(my_table[index-1].descr));
	DEBUGMSGTL(("gpDroneMIB","Returning OCTET_STR<idx=%d,col=%d> : %s\n", index,colnum,my_table[index-1].descr));
					break;
				case 3:
					fetch_integer(my_table[index-1].descr,&(my_table[index-1].toggle));
					snmp_set_var_typed_value(requests->requestvb,ASN_INTEGER,&(my_table[index-1].toggle),sizeof(long));
	DEBUGMSGTL(("gpDroneMIB","Returning INTEGER<idx=%d,col=%d> : %ld\n", index,colnum,my_table[index-1].toggle));
					break;
				default:
					DEBUGMSGTL(("gpDroneMIB","Unknown request...\n"));
			}
			break;
	}

    return SNMP_ERR_NOERROR;
}









