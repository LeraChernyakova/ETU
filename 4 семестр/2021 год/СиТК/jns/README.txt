Ó###################################
##### Java Network Simulator  #####
###################################

Version:        Public Release Version 0.41
Website:        http://sf.net/projects/javanetsim
Authors:        See 'About' menu.

If you found a bug, please post it to: http://sourceforge.net/tracker/?atid=784685&group_id=152576

***********************
******* Install *******
***********************

All Platforms
-------


1.      If you do not have the Java Runtime Environment (JRE) installed on your Operating System, the program will not be 
        able to run. You must install the Java Runtime Environment 1.5.0 or later. This can be downloaded from www.java.com
	

2.      If you have downloaded the pre-compiled zip version, find where you extracted the contents and run windows.bat/linux.sh
        to start the Graphical User Interface. 

        Note: The Java Network Simulator has only been fully tested under WinXP/WinVista, OpenBSD and Linux (Gentoo/Fedora). 
        While there should be no problem running on other platforms, unexpected results may possibly occur.


*********************
***** ChangeLog *****
*********************

***** Release Version 0.41  12 February 2009 *****

Fixed
-----

GUI Issues -

	1. Fixed some console bugs.
	
Simulation Issues -
	
	1. Fixed bugs with console interfaces.

New Features
------------

    1. OSPF.


***** Release Version 0.40  1st November 2008 *****

Fixed
-----

GUI Issues -

	1. Fixed some bugs with interface and console.
	
Simulation Issues -
	
	1. Fixed DHCP bugs.

New Features
------------

    1. Added wireless interfaces and wireless APs.
    2. New ICMP packets: TIME_EXCEEDED, DEST_UNREACH.
    3. New application protocols: RIP, DNS (with server and client).
    4. New link type: fiber.
    5. Dynamic and Static NAT added.
    6. New device: laptop.
    7. Added Export to PNG & JPEG.
    8. Added VLANs and Multilayer switches.


***** Release Version 0.39  20rd November 2007 *****

New Features
------------

    1. CSU/DSU unit new connection types: RMI, CORBA, UDP.
    2. Added printers.
    3. Added access-lists.
    4. New devices subtypes for Hubs, Switches and Routers.    

***** Release Version 0.38  3rd November 2007 *****

New Features
------------

    1. New command line (console).
    2. Added new link types (Console, Serial).
    3. New savefile format.
    4. New protocols: DHCP
    5. New devices: CSU/DSU unit   

***** Release Version 0.34  1th October 2007 *****

Fixed
-----

GUI Issues -
    
    1. More Java 6 related diaglog fixes.

New Features
------------

    1. TCP & UDP protocol fully rewritten with socket layer.

***** Release Version 0.33  16th September 2007 *****

Fixed
-----

GUI Issues -
    
    1. Fixed Java 6 related bugs with some dialogs.

New Features
------------

    1. Text packet log console replaced with nice color table.
    2. Print ARP Cache/Print Route Table results now shows in a separate window(insted of log console).
    3. New Turn On/Off network device function.
    4. Finally moved to Java 6 (1.6). (but still 1.5 compartible)

***** Release Version 0.32.3  16th November 2006 *****

Fixed
-----

GUI Issues -
    
    1. Fixed Set TCP/IP Dialog Properties.
    2. Fixed 'Send UDP Echo' dialogs.
    2. Fixed 'Send TCP Echo' dialogs.

New Features
------------

    1. Added scrollbars to main window.
    2. *EXPERIMENTAL* Added Proxy/Gateway to external networks.

***** Release Version 0.32.2  10th November 2006 *****

Fixed
-----

GUI Issues - 

    1. Set TCP/IP Dialog window completely rewritten.
    2. Fixed not showing transport level counters for Application layer devices (e.g. PCs).

Simulation Issues - 

    1. Strange behaviour of hubs on lines with sieving coefficients.

New Features
------------

    1. *EXPERIMENTAL* New telnet client (RFC-Compatible).

***** Release Version 0.32.1  26th October 2006 *****

Fixed
-----

GUI Issues - 
    
    1. Fixed "route removed" message in console.
    2. Removed feature, that disables adding arp entry when ip is not on local network and/or incorrect.   
    3. Fixed removing default gateway in "Set TCP/IP Properties" dialog.
    4. Fixed bug of no changing default gateway when clicking enter on text field in "Set TCP/IP Properties" dialog.

Simulation Issues - 

    1. Fixed "no gateway" route bug: when no default gw set, no packet forwarding was processed.

New Features
------------

    1. Added tooltips with node information.
    2. Added status bar.

***** Release Version 0.32  12th October 2006 *****

Fixed
-----

GUI Issues - 
    
    1. Fixed changing mask when changing IP and existing mask isn't null/illegal.
    2. Added confirm when deleting an object.
    3. Fixed showing counters on router.
    4. Added version label to the splash screen.

Simulation Issues - 

    1. Now showing information about accepting/dropping ethernet packet on interface (it depends on dest MAC comparison).
    2. Fixed resetting counters on router.    

New Features
------------

    1. Added hotkeys.
    2. Added 'readme/changelog' window and menu item.
    3. Added switches(experimental).
    4. Added routing.
    5. Added TCP/UDP and some Applications (Telnet, TCP/UDP Echo and SNMP).
    6. Added console for network level devices.
    7. Added lines sieve feature.

***** Release Version 0.22.1  6th November 2005 *****

Fixed
-----

GUI Issues - 

    1. Fixed gateway save/load crash.
    2. Fixed null IP save/load crash.

Simulation Issues - 

    1. Fixed IP And Subnet calculation engine.
    2. Fixed some text messages.
    3. Fixed static entries in ARP tables.
    4. Now catching "hub flooding".

New Features
------------

    1. Hub now have 5 nics.
    2. Hubs now have state: you can show state and reset habs.
    3. Add static entries to ARP tables.
    4. Removing entries from ARP tables.


***** Release Version 0.22  5th November 2005 *****

Project got new maintainer and new name! The fork calls javaNetSim (Java Network Simulator).

Fixed
-----

GUI Issues - 

    1. Temporarely removed switches.

Simulation Issues - 

    1. Error in calculating Network by IP and SubNet Mask.

New Features
------------

    1. Breaking links feature in GUI.
    2. Save/Load in GUI (new jfst file format).
    3. Random length subnet masks.


***** Release Version 0.20  November 2004 *****

Fixed
-----

GUI Issues -
The Graphical User Interface has been completely re-written, thus all old known issues are no longer applicable.

Command Line Interface Issues -
All previously known Command Line issues has been resolved.

Simulation Issues - 

Previous Issue 5 :Subnet masks have now been implemented and basic routing is performed within nodes with more than 
1 interface.

Previous Issue 6 : Have implemented a "Hop Count" into data packets.  The packet will no longer infintely be sent
between 2 routers till java crashes with a stack overflow.  After 20 unsucessful attempts, the packet will time out.

Previous Issue 7 : Similar fix to number 5.

Previous Issue 8 : In redevelopment of the Core, application layer protocols are no longer implemented. This issue
will need to be address again once the new group starts developing additional layers.

Previous Issue 9 : There are no routing tables.

Previous Issue 10 : Deleting Nodes and Links in both the CLI and GUI work correctly.

Previous Issue 11 : The protocol stack has been completely redesigned.

Previous Issue 12 :  jFirewallSim is now packaged in such a way that the core classes are seperate from the Command
Line Interface and Graphical User Interface.  This means that either can be dumped without affecting any core classes.


New Features
------------

1 : Brand new Graphical User Interface.

2 : ARP

3 : Subnet Masks

4 : Default Gateways

5 : MAC Address Randomization

6 : Basic routing

7 : Redevelopment of Protocol Stack

8 : Redvelopment of Command Line Interface

Known Issues
------------

1 : Pinging between 2 PC's linked but on different subnets has some issues.   This relates to the RecievePacket method 
	of the ProtocolStack class, an additional check should be made to check if the nodes are on the same subnet.

2 : Implementation of Loop back and Local IP Address has not yet been addressed.  This means currently the Loop Back
	address (127.0.0.1) can not be pinged and recieve a reply.
	
3 : Pinging yourself will yourself will result in a "Unable to resolve destination MAC Address"

4 : Console output is not in a True Space font, resulting in some funny output occasionally.


***** Release Version V 0.10  June 2004 *****

Fixed
-----

1. A NullPointerException no longer results when a script is run with an incomplete network environment.
2. The Simulation now fully supports real IP Addresses (as opposed to integers). This also fixes any NumberFormatExceptions that may have resulted when dealing with the old integer IPs.
3. Script problems are checked before the script is run. The script does not run if there are errors in the script commands.
4. Simulation problems such as nodes without links or duplicate IP addresses are checked before a script is run.
5. The CLI now outputs error messages if the user enters incorrect commands or command parameters.



New Features
------------


*** Simulation Related

1. Routers can now be added and used by the Simulation.
2. The TcpIp class has been replaced with two separate classes UDP and IP. The UDP and IP classes have been implemented as per real world TCP/IP specifications.
3. The IP class also supports IP Forwarding / Routing.
4. Nodes now contain routing tables which are used by IP when routing. The routing tables are configured automatically by the Simulation using a method that mimics the way RIP functions. However, no actual RIP packets are sent between routers, the Simulation configures them dynamically before a script is run.
5. New IPAddress class for IP Address validation and type conversion.


*** Command Line Interface (CLI) Related

6. New Commands:

	* ADDROUTER - Adds a Router to the Simulation.
	* ADDINTERFACE - Adds an interface to a Router (and in the future, other Nodes).
	* SETADDRESS - Now supports real IP Addresses and you must now specify an interfacename as a parameter.
	* REMOVECOMMAND - Removes a command (or line) from the Simulation's script.
	* CONFIGUREROUTERS - Configures all Routers in the Simulation.
	* DISPLAYROUTINGTABLES - Displays the Routing Tables in each Router.
	
	For more information on the above commands use the help facility in the CLI. (type 'help')

7. Script and/or environment problems in the Simulation are checked and displayed before a script is run.



