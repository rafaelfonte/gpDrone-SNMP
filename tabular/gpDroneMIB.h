/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */
#ifndef GPDRONEMIB_H
#define GPDRONEMIB_H

/* function declarations */
void init_gpDroneMIB(void);
void initialize_table_lightingTable(void);
Netsnmp_Node_Handler lightingTable_handler;

/* column number definitions for table lightingTable */
       #define COLUMN_LIGHTDESCRIPTION		1
       #define COLUMN_LIGHTTOGGLE		2
       #define COLUMN_LIGHTINDEX		3
#endif /* GPDRONEMIB_H */
