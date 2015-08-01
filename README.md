# gpDrone-SNMP
SNMP Project for the Network Management class UFRGS 2014/2

This project implements an agent MIB module to control aircrafts in Flight-Gear. It leverages the module addition featured in NETSNMP, and interacts with the http daemon bundled with Flight-Gear to fetch infromation from the aircraft and perform some actions (turning lights on/off, bringing the landing gear up/down etc.).
The manager portion of the project provides a clean html interface with which one can visualize the published variables, as well as interact with the aircraft commands.

Preferrable aircraft: Boeing 777-200ER
