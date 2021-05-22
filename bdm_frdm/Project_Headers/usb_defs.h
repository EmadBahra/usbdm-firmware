/**
 * @file     usb_defs.h (180.ARM_Peripherals/Project_Headers/usb_defs.h)
 * @brief    Universal Serial Bus definitions
 *
 * @version  V4.12.1.210
 * @date     13 April 2016
 *      Author: podonoghue
 */

#ifndef HEADER_USB_DEFS_H
#define HEADER_USB_DEFS_H
/*
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */
#include <stdint.h>
#define NEED_ENDIAN_CONVERSIONS 1
#include "utilities.h"

/**
 * @addtogroup USB_Group USB, USB OTG Controller
 * @brief Abstraction for USB OTG Controller
 * @{
 */

#pragma pack(push, 1)

//! Endpoint direction masks
enum {
//   EP_OUT =0x00, //!< Endpoint is OUT (host -> node)
//   EP_IN  =0x80  //!< Endpoint is IN (node -> host)
};

/**
 * USB Status Codes
 */
enum UsbStatus {
   UsbStatus_ATTACHED     = 0x00,
   UsbStatus_POWERED      = 0x01,
   UsbStatus_DEFAULT      = 0x02,
   UsbStatus_ADDRESSED    = 0x03,
   UsbStatus_CONFIGURED   = 0x04,
   UsbStatus_SUSPENDED    = 0x80,
};

/**
 * USB Recipient Type (bmRequestType.recipient)
 */
enum UsbRequestRecipient {
   UsbRequestRecipient_DEVICE     = 0,
   UsbRequestRecipient_INTERFACE  = 1,
   UsbRequestRecipient_ENDPOINT   = 2,
   UsbRequestRecipient_OTHER      = 3,
};

/**
 * USB Request Type (bmRequestType.type)
 */
enum UsbRequestType {
   UsbRequestType_STANDARD    = 0,
   UsbRequestType_CLASS       = 1,
   UsbRequestType_VENDOR      = 2,
   UsbRequestType_OTHER       = 3,
};

/**
 * USB Request Direction (bmRequestType.direction)
 */
enum UsbRequestDirection {
   UsbRequestDirection_OUT    = 0,
   UsbRequestDirection_IN     = 1,
};

/**
 * Extract Recipient from bmRequestType
 *
 * @param  bmRequestType
 *
 * @return UsbRequestRecipient
 */
constexpr inline UsbRequestRecipient REQ_RECIPIENT(uint8_t bmRequestType) {
   return (UsbRequestRecipient)((bmRequestType>>0) & 0b11111);
}

/**
 * Extract Request type from bmRequestType
 *
 * @param  bmRequestType
 *
 * @return UsbRequestType
 */
constexpr inline UsbRequestType REQ_TYPE(uint8_t bmRequestType) {
   return (UsbRequestType)((bmRequestType>>5)&0b11);
}

/**
 * Extract Request direction from bmRequestType
 *
 * @param  bmRequestType
 *
 * @return UsbRequestDirection
 */
constexpr inline UsbRequestDirection REQ_DIRECTION(uint8_t bmRequestType) {
   return (UsbRequestDirection)((bmRequestType>>7)&0b1);
}

/**
 * Create bmRequestType from recipient, type and direction
 *
 * @param usbRequestDirection
 * @param usbRequestType
 * @param usbRequestRecipient
 *
 * @return
 */
constexpr uint8_t REQUEST_TYPE(
      UsbRequestDirection  usbRequestDirection,
      UsbRequestType       usbRequestType,
      UsbRequestRecipient  usbRequestRecipient
      ) {
   return ((usbRequestDirection<<7)|(usbRequestType<<2)|(usbRequestRecipient<<0));
}

/*----------------------------------------------------------------------------
 ** USB Standard Device Request Codes (bRequest)
 */
enum UsbRequestCodes {
   GET_STATUS        =  0x00,
   CLEAR_FEATURE     =  0x01,
   SET_FEATURE       =  0x03,
   SET_ADDRESS       =  0x05,
   GET_DESCRIPTOR    =  0x06,
   SET_DESCRIPTOR    =  0x07,
   GET_CONFIGURATION =  0x08,
   SET_CONFIGURATION =  0x09,
   GET_INTERFACE     =  0x0a,
   SET_INTERFACE     =  0x0b,
   SYNCH_FRAME       =  0x0c,

   /*----------------------------------------------------------------------------
    ** CDC Class requests
    */
   SEND_ENCAPSULATED_COMMAND = 0x00,
   GET_ENCAPSULATED_COMMAND  = 0x01,
   SET_LINE_CODING           = 0x20,
   GET_LINE_CODING           = 0x21,
   SET_CONTROL_LINE_STATE    = 0x22,
   SEND_BREAK                = 0x23,

   /*----------------------------------------------------------------------------
    ** MS special
    */
   GET_MS_FEATURE_DESCRIPTOR = 0x30,
};

/**
 * Structure of Setup Packet sent during SETUP Stage of Standard Device Requests
 */
typedef struct {
   union {
      uint8_t      bmRequestType;       //!<  Characteristics (Direction,Type,Recipient)
      struct {
         UsbRequestRecipient  recipient:5;  //!< Device, Interface ..
         UsbRequestType       type:2;       //!< Standard, CLoass, Vendor..
         UsbRequestDirection  direction:1;  //!< In, Out
      };
   };
   UsbRequestCodes  bRequest:8;          //!<  Standard Request Code
   uint16_le        wValue;              //!<  Value Field
   uint16_le        wIndex;              //!<  Index or Offset Field
   uint16_le        wLength;             //!<  Number of bytes to transfer (Data Stage)
} SetupPacket;

/*----------------------------------------------------------------------------
 ** Descriptor Types
 */
enum DescriptorTypes {
   DT_DEVICE                  =   1,
   DT_CONFIGURATION           =   2,
   DT_STRING                  =   3,
   DT_INTERFACE               =   4,
   DT_ENDPOINT                =   5,
   DT_DEVICEQUALIFIER         =   6,
   DT_OTHERSPEEDCONFIGURATION =   7,
   DT_INTERFACEPOWER          =   8,
   DT_INTERFACEASSOCIATION    = 0xB,
};

/*----------------------------------------------------------------------------
 ** USB Tokens
 */
enum UsbPids {
   SOFToken     = 0x5, //!< Start of Frame token
   SETUPToken   = 0xD, //!< Setup token
   OUTToken     = 0x1, //!< Out token
   INToken      = 0x9, //!< In token
   DATA0Token   = 0x3, //!< Data 0
   DATA1Token   = 0xB, //!< Data 1
   DATA2Token   = 0x7, //!< Data 2
   MDATAToken   = 0xF, //!< M data
   ACKToken     = 0x2, //!< Acknowledge
   NAKToken     = 0xA, //!< Negative Acknowledge
   NYETToken    = 0x6, //!< No Response Yet
   STALLToken   = 0xE, //!< Stall
   PREToken     = 0xC, //!< Preamble
};

//! Device Descriptor
typedef struct {
   uint8_t           bLength;             //!<  Size of this Descriptor in Bytes
   uint8_t           bDescriptorType;     //!<  Descriptor Type (=1)
   uint16_t          bcdUSB;              //!<  USB Spec Release Number in BCD
   uint8_t           bDeviceClass;        //!<  Device Class Code
   uint8_t           bDeviceSubClass;     //!<  Device Subclass Code
   uint8_t           bDeviceProtocol;     //!<  Device Protocol Code
   uint8_t           bMaxPacketSize0;     //!<  Maximum Packet Size for EP0
   uint16_t          idVendor;            //!<  Vendor ID
   uint16_t          idProduct;           //!<  Product ID
   uint16_t          bcdDevice;           //!<  Device Release Number in BCD
   uint8_t           iManufacturer;       //!<  Index of String Desc for Manufacturer
   uint8_t           iProduct;            //!<  Index of String Desc for Product
   uint8_t           iSerialNumber;       //!<  Index of String Desc for SerNo
   uint8_t           bNumConfigurations;  //!<  Number of possible Configurations
} DeviceDescriptor;

//! USB Configuration Descriptor
typedef struct {
   uint8_t           bLength;             //!<  Size of this Descriptor in Bytes
   uint8_t           bDescriptorType;     //!<  Descriptor Type (=2)
   uint16_t          wTotalLength;        //!<  Total Length of Data for this Configuration
   uint8_t           bNumInterfaces;      //!<  No of Interfaces supported by this Configuration
   uint8_t           bConfigurationValue; //!<  Designator Value for this Configuration
   uint8_t           iConfiguration;      //!<  Index of String Desc for this Configuration
   uint8_t           bmAttributes;        //!<  Configuration Characteristics
   uint8_t           bMaxPower;           //!<  Max. Power Consumption in this Configuration (in 2mA steps)
} ConfigurationDescriptor;

//! USB Interface Descriptor
typedef struct {
   uint8_t           bLength;             //!<  Size of this Descriptor in Bytes
   uint8_t           bDescriptorType;     //!<  Descriptor Type (=4)
   uint8_t           bInterfaceNumber;    //!<  Number of this Interface (0..)
   uint8_t           bAlternateSetting;   //!<  Alternative for this Interface (if any)
   uint8_t           bNumEndpoints;       //!<  No of EPs used by this IF (excl. EP0)
   uint8_t           bInterfaceClass;     //!<  Interface Class Code
   uint8_t           bInterfaceSubClass;  //!<  Interface Subclass Code
   uint8_t           bInterfaceProtocol;  //!<  Interface Protocol Code
   uint8_t           iInterface;          //!<  Index of String Desc for this Interface
} InterfaceDescriptor;

//! Endpoint Descriptor
typedef struct {
   uint8_t           bLength;             //!<  Size of this Descriptor in Bytes
   uint8_t           bDescriptorType;     //!<  Descriptor Type (=5)
   uint8_t           bEndpointAddress;    //!<  Endpoint Address (Number + Direction)
   uint8_t           bmAttributes;        //!<  Endpoint Attributes (Transfer Type)
   uint16_t          wMaxPacketSize;      //!<  Max. Endpoint Packet Size
   uint8_t           bInterval;           //!<  Polling Interval (Interrupt) in ms
} EndpointDescriptor;

//! Structure of Device Qualifier Descriptor
typedef struct {
   uint8_t           bLength;             //!<  Size of this Descriptor in Bytes
   uint8_t           bDescriptorType;     //!<  Descriptor Type (=6)
   uint16_t          bcdUSB;              //!<  USB Spec Release Number in BCD
   uint8_t           bDeviceClass;        //!<  Device Class Code
   uint8_t           bDeviceSubClass;     //!<  Device Subclass Code
   uint8_t           bDeviceProtocol;     //!<  Device Protocol Code
   uint8_t           bMaxPacketSize0;     //!<  Maximum Packet Size for EP0
   uint8_t           bNumConfigurations;  //!<  Number of possible Configurations
   uint8_t           bReserved;           //!<  Reserved
} DeviceQualifierDescriptor;

//! Endpoint direction masks
enum {
   EP_OUT=0x00, //!< Endpoint is OUT (host -> node)
   EP_IN=0x80   //!< Endpoint is IN (node -> host)
};

/*----------------------------------------------------------------------------
 ** Feature selector values (for Clear/Set feature)
 */
#define ENDPOINT_HALT         (0x00)
#define DEVICE_REMOTE_WAKEUP  (0x01)
#define TEST_MODE             (0x02)

/*----------------------------------------------------------------------------
 ** bmRequest types
 */
#define RT_DEVICE          (0x00)
#define RT_INTERFACE       (0x01)
#define RT_ENDPOINT        (0x02)

/*----------------------------------------------------------------------------
 ** bmAttributes types
 */
#define ATTR_CONTROL	    (0x00)
#define ATTR_ISOCHRONOUS 	(0x01)
#define ATTR_BULK  			(0x02)
#define ATTR_INTERRUPT  	(0x03)

#define USBMilliamps(x)     ((x)/2)
#define USBMilliseconds(x)  (x)

//============================================================================
// IAD Stuff (Composite devices)
//============================================================================
typedef struct {
   uint8_t bLength;                //!< Size of this Descriptor in Bytes
   uint8_t bDescriptorType;        //!< Descriptor Type (=0B)
   uint8_t bFirstInterface;        //!< First interface #
   uint8_t bInterfaceCount;		   //!< Number of interfaces
   uint8_t bFunctionClass;         //!< bInterfaceClass;
   uint8_t bFunctionSubClass;      //!< bInterfaceSubClass;
   uint8_t bFunctionProtocol;      //!< Protocol
   uint8_t iFunction;			   //!< Function
} InterfaceAssociationDescriptor;

//============================================================================
// CDC Stuff
//============================================================================

// bDescriptorType
#define CS_INTERFACE  (0x24)
#define CS_ENDPOINT   (0x25)

//
#define ST_HEADER     (0x00)
#define ST_INTERFACE  (0x01)

// bDescriptorSubtype
#define DST_HEADER                      (0x00)
#define DST_CALL_MANAGEMENT             (0x01)
#define DST_ABSTRACT_CONTROL_MANAGEMENT (0x02)
#define DST_UNION_MANAGEMENT            (0x06)

//! USB CDC Header Functional Descriptor
typedef struct {
   uint8_t  bFunctionLength;		//!< Size
   uint8_t  bDescriptorType;		//!< Type
   uint8_t  bDescriptorSubtype;	    //!< Sub-type
   uint16_t bcdCDC;					//!< ??
} CDCHeaderFunctionalDescriptor;

//! USB CDC Call Management Functional Descriptor
typedef struct {
   uint8_t  bFunctionLength;		//!< Length
   uint8_t  bDescriptorType;		//!< Type
   uint8_t  bDescriptorSubtype;	    //!< Sub-type
   uint8_t  bmCapabilities;		    //!< Capabilities
   uint8_t  bDataInterface;		    //!< Data interface
} CDCCallManagementFunctionalDescriptor;

//! USB CDC Abstract Control Management Descriptor
typedef struct {
   uint8_t  bFunctionLength;		//!< Length
   uint8_t  bDescriptorType;		//!< Type
   uint8_t  bDescriptorSubtype;	    //!< Sub-type
   uint8_t  bmCapabilities;		    //!< Capabilities
} CDCAbstractControlManagementDescriptor;

//! USB CDC Union Functional Descriptor
typedef struct {
   uint8_t  bFunctionLength;       //!< Length
   uint8_t  bDescriptorType;	   //!< Type
   uint8_t  bDescriptorSubtype;    //!< Sub-type
   uint8_t  bMasterInterface;	   //!< Interface
   uint8_t  bSlaveInterface[1];	   //!< Slave interface
} CDCUnionFunctionalDescriptor;

//! USB CDC Notification
typedef struct {
   uint8_t  bmRequestType;	//!< Request type
   uint8_t  bNotification;	//!< Notification
   uint16_t wValue;		    //!< Value
   uint16_t wIndex;	        //!< Index
   uint16_t wLength;        //!< Length
} CDCNotification;

#define CDC_NOTIFICATION   (0xA1)
#define RESPONSE_AVAILABLE (0x01)
#define SERIAL_STATE       (0x20)

// Bit masks for SetControlLineState value
#define DTR_MASK (1<<0)
#define RTS_MASK (1<<1)

struct MS_CompatibleIdFeatureDescriptor {
   uint32_t lLength;                 //!< Size of this Descriptor in Bytes
   uint16_t wVersion;                //!< Version
   uint16_t wIndex;                  //!< Index (must be 4)
   uint8_t  bnumSections;            //!< Number of sections
   uint8_t  bReserved1[7];           //!<
   //------------- Section ----------//
   uint8_t  bInterfaceNum;           //!<
   uint8_t  bReserved2;              //!<
   uint8_t  bCompatibleId[8];        //!<
   uint8_t  bSubCompatibleId[8];     //!<
   uint8_t  bReserved3[6];
};

struct MS_PropertiesFeatureDescriptor;

// Data packet odd/even indicator
enum DataToggle : bool {
   DataToggle_0=false, //!< DATA0 indicator
   DataToggle_1=true,  //!< DATA1 indicator
};

/**
 * Toggle DATA0/1 value
 *
 * @param data0_1
 *
 * @return Toggled value
 */
inline DataToggle __attribute__((always_inline)) operator!(DataToggle volatile const& data0_1) {
    return data0_1==DataToggle::DataToggle_0?DataToggle::DataToggle_1:DataToggle::DataToggle_0;
}

// Data packet odd/even indicator
enum BufferToggle : bool {
   BufferToggle_Even = false, //!< Even Buffer
   BufferToggle_Odd  = true,  //!< Odd Buffer
};

/**
 * Toggle BufferToggle value
 *
 * @param evenOdd
 *
 * @return Toggled value
 */
constexpr BufferToggle __attribute__((always_inline)) operator!(BufferToggle const& evenOdd) {
   return evenOdd==BufferToggle::BufferToggle_Even?BufferToggle::BufferToggle_Odd:BufferToggle::BufferToggle_Even;
}

// BDT ownership indicator
enum BdtOwner : bool {
   BdtOwner_MCU = false, //!< BDT available for modification bye MCU
   BdtOwner_SIE = true,  //!< BDT being used by SIE
};


/**
 * Structure representing a BDT entry in USB controller
 */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
// Little-endian on Kinetis
struct BdtEntry {
   union {
      volatile uint8_t raw:8;    //!< Access as bit masks
      struct {          //!< BDT setup access
         uint8_t     :2;
         volatile bool        bdt_stall:1;  //!< Stall End point
         volatile bool        dts:1;        //!< Enable Data toggle
         volatile bool        ninc:1;       //!< Disable DMA address increment
         volatile bool        keep:1;       //!< BDT is 'kept' by SIE, used for FIFO w/o MCU intervention
         uint8_t     :2;
      } setup;
      struct {          //!< BDT result access
         uint8_t     :2;
         volatile UsbPids     tok_pid:4;  //!< Token PID is written back by SIE
         uint8_t     :2;
      } result;
      struct {          //!< BDT common access
         uint8_t     :6;
         volatile DataToggle  data0_1:1;  //!< Data 0/1 toggle
         volatile BdtOwner    own:1;      //!< Ownership of the BDT.  MCU only modifies BDT if owned.
      };
   };
   volatile uint8_t  :8;
   volatile uint16_t bc;          //!< Byte count for transaction
   volatile uint32_t addr;        //!< Buffer address for transaction

   constexpr BdtEntry() :
      raw(0), bc(0), addr(0) {};

   constexpr BdtEntry(uint8_t value, uint16_t byteCount, uint32_t address) :
      raw(value), bc(byteCount), addr(address) {};

   void initialise(uint8_t value, uint16_t byteCount, uint32_t address) volatile {
      raw  = value;
      bc   = byteCount;
      addr = address;
   }

   void setByteCount(uint16_t byteCount) volatile {
      bc = byteCount;
   }

   void setAddress(uint32_t address) volatile {
      addr = address;
   }

   void setControl(uint8_t value) volatile {
      raw = value;
   }
};
#else
#error FIX ME!
// Big-endian (Used on Coldfire)
struct BdtEntry {
   union {
      struct {
         uint8_t     :2;
         bool        bdt_stall:1;
         bool        dts:1;
         bool        ninc:1;
         bool        keep:1;
         DataToggle  data0_1:1;
         BdtOwner    own:1;
      } setup;           // BDT setup access
      struct {
         uint8_t     :2;
         uint8_t     tok_pid:4;
         DataToggle  data0_1:1;
         BdtOwner    own:1;
      } result;          // BDT result access
      uint8_t raw;       // Access as bit masks
   };
   uint8_t  :8;
   uint16_t bc:16;       // Byte count
   uint32_t addr;        // Buffer address
};
#endif

struct EndpointBdtEntry {
   BdtEntry rxEven;
   BdtEntry rxOdd;
   BdtEntry txEven;
   BdtEntry txOdd;
} ;

// Bit masks for fields in BdtEntry
constexpr uint8_t BDTEntry_OWN_MASK   = (1<<7);   //!< Mask for OWN bit in BDT
constexpr uint8_t BDTEntry_DATA0_MASK = (0<<6);   //!< Mask for DATA1 bit in BDT (dummy)
constexpr uint8_t BDTEntry_DATA1_MASK = (1<<6);   //!< Mask for DATA0 bit in BDT
constexpr uint8_t BDTEntry_KEEP_MASK  = (1<<5);   //!< KEEP
constexpr uint8_t BDTEntry_NINC_MASK  = (1<<4);   //!< NINC
constexpr uint8_t BDTEntry_DTS_MASK   = (1<<3);   //!< Mask for DTS bit in BDT
constexpr uint8_t BDTEntry_STALL_MASK = (1<<2);   //!< Stall endpoint

/**
 * USB device states
 */
enum DeviceConnectionStates {
   USBpowered,
   USBattached,
   USBdefault,
   USBaddressed,
   USBconfigured,
   USBsuspended
};

/**
 * Structure for SetLineCoding/GetLineCoding
 */
struct LineCodingStructure {
   uint32_t dwDTERate;     //!< data rate (littleEndian format)
   uint8_t  bCharFormat;   //!< character format
   uint8_t  bParityType;   //!< parity type
   uint8_t  bDataBits;     //!< number of bits
};

struct CdcLineState {
   union {
      uint8_t bits;
      struct {
         uint8_t dcd:1;
         uint8_t dsr:1;
         uint8_t brk:1;
         uint8_t ri:1;
         uint8_t frame:1;
         uint8_t parity:1;
         uint8_t overrun:1;
      };
   };
   constexpr CdcLineState(uint8_t state) : bits(state) {}
};

/**
 * Structure representing USB STAT register value
 */
union UsbStat {
      uint8_t raw;
      struct {
         unsigned      :2;
         BufferToggle  odd:1;
         bool          tx:1;
         unsigned      endp:4;
      };
   constexpr UsbStat(uint8_t status) : raw(status) {
   }
};

#pragma pack(pop)

/**
 * End USB_Group
 * @}
 */

#endif /* HEADER_USB_DEFS_H  */
