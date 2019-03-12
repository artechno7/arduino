#ifndef sirobo_android_h
#define sirobo_android_h

#include "Arduino.h"

#define __SIROBO_MAX_REGHANDLER_SIZE__ 15
#define __SIROBO_MAX_STOREDFUNC_SIZE__ 16
#define __SIROBO_REGHANDLER__ 1
#define __SIROBO_STOREDFUNC__ 2
#define __SIROBO_ANDROID_COMM_TIMEOUT__ 50

class SiRoboAndroid{
  
	private:
		struct Request {
			uint8_t dataBuffer[255];
			uint8_t bufferLength = 0;
			uint8_t cur = 0;
			uint8_t reqCode = 0;
			bool writeAccess = false;
		};
    
    Request incoming, outgoing;
    uint8_t dataLength = 0;
    uint16_t time_start = 0, time_now = 0;
    
    HardwareSerial* serialPort;
    
    typedef void (*HandlerFunction)();
    HandlerFunction registerHandlers[__SIROBO_MAX_REGHANDLER_SIZE__];
    HandlerFunction storedFunctions[__SIROBO_MAX_STOREDFUNC_SIZE__];
    
    uint16_t registerHandlers_size = 0;
    uint16_t storedFunctions_size = 0;
    
    void handleIncomingRequest();
    
  public:
    SiRoboAndroid(HardwareSerial* port);
    
    void handleAndroidData();
  
    bool pushFunc(uint8_t target, HandlerFunction f);
    bool pushRegHandler(HandlerFunction f);
    bool pushStoredFunc(HandlerFunction f);
    
    bool setFunc(uint8_t target, uint8_t index, HandlerFunction f);
    bool setRegHandler(uint8_t index, HandlerFunction f);
    bool setStoredFunc(uint8_t index, HandlerFunction f);
    
    uint8_t getReqCode() { return incoming.reqCode; }
    uint8_t getBufferLength() { return incoming.bufferLength; }
    uint8_t getWriteAccess() { return incoming.writeAccess; }
    
    uint8_t getByte();

    int16_t getInt16();
    int8_t getInt8();
    char getChar();
    void getString(char* dest);
    void getByteStream(uint8_t* dest, uint8_t len);

    void putByte(uint8_t data);
    void putInt16(int16_t data);
    void putInt8(int8_t data);
    void putString(char* data);
    void putByteStream(uint8_t* data, uint8_t len);
};

#endif