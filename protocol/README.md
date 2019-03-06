# Protocol M

## Revision History:
Version | Date | Edited by | Changes
-|-|-|-
1.0.0 | 2017 June 28 | Nico Mesas | First Release
1.0.1 | 2018 June 05 | Ignasi Serra | Add type file at [Get files list](#get-files-list)
1.1.0 | 2018 July  25 | Ignasi Serra | Adds [shot mode](#status-and-configuration) for multiprinting by trigger

## Introduction
This repository contains the code and documentation of Macsa Tij communication protocol.

_Main Brains: José Antonio Bou and Marc Soleda_

_Validated By: José Antonio Bou and Marc Soleda_

---

This protocol uses xml as a language to create the payload. Payloads sent and received must be wrapped as follows:
```xml
<WIND id="[Command ID]">
    <COMMAND_NAME>
        {content}
    </COMMAND_NAME>
</WIND>
```
## Data types
>Note BOOL values must be string literals "true" or "false"

Field | Type | Description
-|-|-
Command Id | unsigned int | Unique identifier of a command sent, this identifier links command sent with the response.
Error Code | unsigned int | Integer with the error code. NOTE: Depending the error, the MAIN element maybe returned empty ([error codes](#error-codes))
Logical file path | string | The logical File path for a physical file (see [files management](#files-management))
Logical Active Unit Name  | string | Name of active drive on server. This must be __`//`__ or  __`USB//`__ (see [files management](#files-management))
File Content | string | Content of file codified in base64
Message type | enum | String with the type of file ([message types](#message-types)).
User field name | string | String with the name of the user field
User field value | string | String with the value of the user field
Date time | date time | Format ddMMyyyyHHmmss
Firmware controller | string | String that contains the firmware controller version
Firmware FPGA | string | String that contains the firmware fpga version
API Version | string | String that contains the API version
Speed Value | double | Decimal value with one digit precision and the '.' as separator
Board Id | unsigned int | Unsigned char with the index value
Board Type | string | literal String SM190, SM200, ...
Printing Status | bool | True whether the printhead(board) is printing or False otherwise
Autostart value | bool | Enable printer when its power-on
Printhead Enabled | bool | True=Automatic mode. False=Manual mode
Counter Id | string | Name of the counter. Can be 'BCD.01' etc 
Counter Value | unsigned int |  
Total Counter | unsigned int | Total Counter of the printhead (board)
BCD mode value | enum | Defines the Bcd Mode ([bcd modes](#bcd-modes)).
BCD value | unsigned int | Unsigned char with the decimal value.
Printer Error Type | enum | Defines the [error type](#printer-error-types).
Printer Error Priority | unsigned int | Ordinal number that defines the severity of the error message.
Printer Error Code | string | Unique alphanumeric code for an error
Input Id | unsigned int | Unique input identifier.
Input descriptor | string | Description of input type.
Input value | bool | Input status value

---
### Enumartions:
#### Message types:
Value | Name | Description
-|-|-
0 | Message | Message files
1 | Configuration | Configuration files
2 | Application | Executable files (printer software)
3 | Firmware | Binary file (FPGA firmware)

#### BCD modes:
Value | Name | Description
-|-|-
Mode0 | No BCD | Manual - **No** BCD Mode
Mode1 | One direction | Bcd selects only the inputs 0-3 current message
Mode2 | Double direction | Bcd selects only the inputs 0-2 current message, and input 3 and strobe selects print direcction

#### Printer error types:
Value | Name | Description
-|-|-
0 | Information | Information message.
1 | Warning | Warning allow printing status but show that somethings happens.
2 | Error | Errors doesn't allow printing status as they make a printer to stop.



## List of available commands:

1. [Files management](#files-management)
    - [Get files list](#get-files-list)
    - [Copy file](#copy-file)
    - [Move file](#move-file)
    - [Delete file](#delete-file)
    - [Get file](#get-file)
    - [Set file](#set-file)
    - [Get Message value](#get-message-value)
    - [Set Message value](#set-message-value)
1. [Status and configuration](#status-and-configuration) 
1. [Error codes](#error-codes)

---

---
## Files management
The protocol have the capability to send and receive files inside the payload using the following commands. 

In order to reference files through this protocol all files must be defined with two strings *logical drive* (`<UNIT name="//" />`) and *logical path* (`<FILE path="foo file.jpg" />`).

The protocol is **not** the responsible of how drives and files are mapped. The logical path mapping depends on the code implementation.

**idTIJ project implementation**

In idTIJ project the drives contains three subfolders in order to allocate and organize all different type of files.

__drive //__

- messages
- fonts
- images

**TIJ project current used drives implementation**

Logical drive|Description|Physical path
-------------|-----------|-------------
//| Internal storage | /home/root
USB//| External storage | /home/root/usb

---
### Get files list
This command request for a list of files with a desired extension. In order to define what kind of files are requested the extension is the **"type"** attribute. This attribute is a comma separated string (`type=".jpg,.png"`).

The idTIJ project currently support the file extensions defined in the table below.

Type of file|Supported extension
------------|-------------------
Messages | .nisx
Fonts| .ttf
Images | .bmp, .jpg, .png

**Request**
```xml
<WIND id="[Command ID]">
    <GETFILESLIST type="[requested type]"/>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <GETFILESLIST type="[requested type]">
        <UNIT Name="[Logical Active Unit Name]"/> <!-- one item for each active drive -->
        <FILE Path="[Logical File Path]"/> <!-- one item for each file-->
    </GETFILESLIST>
</WIND>
```
---
### Copy file

**Request**
```xml
<WIND id="[Command ID]">
    <COPYFILE SourceFilePath="[Logical File Path]" TargetFilePath="[Logical File Path]"/>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <COPYFILE/>
</WIND>
```
---

### Move file

**Request**
```xml
<WIND id="[Command ID]">
    <MOVEFILE SourceFilePath="[Logical File Path]" TargetFilePath="[Logical File Path]"/>
</WIND> 
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <MOVEFILE/>
</WIND>
```
---
### Delete file

**Request**
```xml
<WIND id="[Command ID]">
    <DELETEFILE FilePath="[Logical File Path]"/>
</WIND> 
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <DELETEFILE/>
</WIND> 
```
---
### Get file

**Request**
```xml
<WIND id="[Command ID]">
    <GETFILE FilePath="[Logical File Path]"/>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <GETFILE FilePath="[Logical File Path]">
        <CONTENT>[File Content]</CONTENT>
    </GETFILE>
</WIND> 
```
---
### Set file

**Request**
```xml
<WIND id="[Command ID]">
    <SETFILE FilePath="[Logical File Path]" Type="[Message Type]">
        <CONTENT>[File Content]</CONTENT>
    </SETFILE>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <SETFILE FilePath="[Logical File Path]"/>
</WIND>
```
---
### Get Message value

**Request**
```xml
<WIND id="[Command ID]">
    <GETMESSAGEVALUES FilePath="[Logical File Path]"/>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <GETMESSAGEVALUES FilePath="[Logical File Path]">
        <UI_FIELD Name="[User Field Name]" Value="[User Field Value]"/>
    </GETMESSAGEVALUES>
</WIND>
```
---
### Set Message value

**Request**
```xml
<WIND id="[Command ID]">
    <SETMESSAGEVALUES FilePath="[Logical File Path]">
        <UI_FIELD Name="[User Field Name]" Value="[User Field Value]"/>
    </SETMESSAGEVALUES>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <SETMESSAGEVALUES/>
</WIND>
```
---

---
## Status and configuration
---
### Get Status
Get Status command return all available status parameters and information like:

- DateTime
- Software versions
- Printer status (Board)
    - Board type _(SM200 by default)_
    - Printing status

**Request**
```xml
<WIND id="[Command ID]">
    <STATUS/>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <DATETIME>[Date Time]</DATETIME>
    <VERSIONS>
        <CONTROLLER>[Firmware controller]</CONTROLLER>
        <FPGA>[Firmware FPGA]</FPGA>
        <API>[API Version]</API>
    </VERSIONS>
    <BOARDS>
        <BOARD id="[Board Id]">
            <TYPE>[Board Type]</TYPE>
            <PRINTING>[Printing Status]</PRINTING>
            <ENABLED>[Printhead Enabled]</ENABLED>
                <CURRENT_MESSAGE FilePath="[Logical File Path]"/>
                <BCD_MODE>[BcdMode value]</BCD_MODE>
                <BCD_STATUS>[BCD Value]</BCD_STATUS>
                <COUNTERS>
                    <COUNTER id="[Counter Id]" Value="[Counter Value]"/>
</WIND>
```
---
## Error codes

The response frames always contain and error code. The currently implemented errors in **idTij** Project are defined below:

1. [[01 - 11] File operation errors](#files-errors)
1. [[12 - 23] Params related errors](#params-related-errors)
1. [[24 - 26] Generic errors](#generic-errors)
1. [[27 - 37] NeoTIJ related errors](#neotij-related-errors)

### Files errors
Value | Error code | Description
------|------------|------------
01 | FileNotFound | The specified file doesn't exist
02 | FileAlreadyExist | in move or copy operations, if the file already exist...
03 | FileCopyFail | copy file operation error
04 | FileDeleteFail | delete file operation error
05 | FileMoveFail | move operation error
06 | FileMoveIncomplete | move operation has copied the source to target, but not delete the source
07 | FileReadCanNot | can't read the file
08 | FileWriteCanNot | can't write the file
09 | FileWriteIncomplete | the write on the file is not complete
10 | FileUserDataNotFound | the name of a user-name-value is not found
11 | FileInUse | the file is currenty in use

### Params related errors
Value | Error code | Description
------|------------|------------
12 | ParamBoardIdNotFound | The BoardId specified by the command was not found
13 | ParamCounterIdNotFound | The CounterId specified by the command was not found
14 | ParamCounterValueRejected | The device has rejected the counter modification
15 | ParamOutputIdNotFound | The output id specified by the command was not found
16 | ParamCantSetMsgInBcdMode | Is not posible set a manual current message if the board is in Bcd mode
17 | ParamBoardIsEnabled	| the command requires a enabled board
18 | ParamBoardIsNotEnabled | the command requires a disabled board
19 | ParamCannotChangeAdapter | The server can not change the adapter settings
20 | ParamInvalidIpAddress | The ip is invalid
21 | ParamInvalidMaskAddress | The mask is invalid
22 | ParamInvalidGatewayAddress | The Gateway is invalid
23 | ParamInvalidPropCount | The client can not change the number of properties

### Generic errors
Value | Error code | Description
------|------------|------------
24 | GenUnexpectedTag | generic xml error
25 | GenNotImplemented | informs that operation is not implemented on the server
26 | GenLockTimeout | Lock data fail

### NeoTIJ related issues
Value | Issue Type | Display Priority | Error code | Description
------|------------|------------------|------------|------------
27 | Error | 1 | PcaNotdetected | "PCA.NOTDETECTED"		    "No connection with PCA"
28 | Error | 2 | PhOvertemp | "PH.OVERTEMP"			    "Printhead over temperature"
29 | Error | 20 | GenOverspeed | "GEN.OVERSPEED"			"Overspeed"
30 | Error | 30 | MsgFormaterror | "MSG.FORMATERROR"		    "NISX format error"
31 | Error | 31 | MsgNoexist | "MSG.NOEXIST"			    "Message doesn't exist"
32 | Error | 5 | PhNocartridge | "PH.NOCARTRIDGE"			"No cartridge loaded"
33 | Error | 4 | SmcInvalid | "SMC.INVALID"			    "No valid smartcard on cartridge. Unreadable"
34 | Error | 3 | PhGenfault | "PH.GENFAULT"			    "Cartridge fault - not valid"
35 | Error | 11 | SmcCartridgeEmpty | "SMC.CARTRIDGE_EMPTY"	    "Cartridge empty"
36 | Warning | 1 | SmcCartridgeOutofdate | "SMC.CARTRIDGE_OUTOFDATE"  "Cartridge out of expiration date"
37 | Warning | 2 | SmcCartridgeNearend | "SMC.CARTRIDGE_NEAREND"	"Cartridge near empty"
38 | Error | 5 | SmcInvalidCartridgeManufacturer | "SMC.INVALID_CARTRIDGE_MANIFACTURER"	"Cartridge near empty"
39 | Info | 1 | PhInitializingCartridge | "PH.INITIALIZING_CARTRIDGE"  "Initializing cartridge"
