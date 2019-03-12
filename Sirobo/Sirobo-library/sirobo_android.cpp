#include "Arduino.h"
#include "sirobo_android.h"

SiRoboAndroid::SiRoboAndroid(HardwareSerial* port){
  serialPort = port;
  incoming.bufferLength = 0;
  outgoing.bufferLength = 0;
  time_now = 0;
  time_start = 0;
}
    
bool SiRoboAndroid::pushFunc(uint8_t target, HandlerFunction f){
  bool result;
  switch(target){
    case __SIROBO_REGHANDLER__ :
      result = pushRegHandler(f);
      break;
    
    case __SIROBO_STOREDFUNC__ :
      result = pushStoredFunc(f);
      break;
  }
  
  return result;
}

bool SiRoboAndroid::pushRegHandler(HandlerFunction f){
  if(registerHandlers_size + 1 > __SIROBO_MAX_REGHANDLER_SIZE__) return false;
  registerHandlers[registerHandlers_size++] = f;
  return true;
}
bool SiRoboAndroid::pushStoredFunc(HandlerFunction f){
  if(storedFunctions_size + 1 > __SIROBO_MAX_STOREDFUNC_SIZE__) return false;
  storedFunctions[storedFunctions_size++] = f;
  return true;
}

bool SiRoboAndroid::setFunc(uint8_t target, uint8_t index , HandlerFunction f){
  bool result;
  switch(target){
    case __SIROBO_REGHANDLER__ :
      result = setRegHandler(index, f);
      break;
    
    case __SIROBO_STOREDFUNC__ :
      result = setStoredFunc(index, f);
      break;
  }
  
  return result;
}

bool SiRoboAndroid::setRegHandler(uint8_t index, HandlerFunction f){
  if(index >= __SIROBO_MAX_REGHANDLER_SIZE__) return false;
  registerHandlers[index] = f;
  return true;
}

bool SiRoboAndroid::setStoredFunc(uint8_t index , HandlerFunction f){
  if(index >= __SIROBO_MAX_STOREDFUNC_SIZE__) return false;
  storedFunctions[index] = f;
  return true;
}

void SiRoboAndroid::handleAndroidData(){
  while (serialPort->available())
  {
    // get the new byte:
    uint8_t ch = serialPort->read();
    time_now = millis();

    if (time_now - time_start > __SIROBO_ANDROID_COMM_TIMEOUT__) {
      time_start = 0;
      dataLength = 0;
      incoming.bufferLength = 0;
    }

    if (time_start == 0) {
      if (ch == 's') {
        time_start = time_now;
        dataLength = 0;
        incoming.bufferLength = 0;
      }
    } else {
      if (dataLength == 0) {
        dataLength = ch;
        if (dataLength < 1) {
          time_start = 0;
          dataLength = 0;
          incoming.bufferLength = 0;
        } else {
          time_start = time_now;
        }
      } else {
        incoming.dataBuffer[incoming.bufferLength++] = ch;
        if (--dataLength == 0) {
          time_start = 0;

          incoming.cur = 0;
          handleIncomingRequest();
        } else {
          time_start = time_now;
        }
      }
    }
  }
}

void SiRoboAndroid::handleIncomingRequest(){
  incoming.reqCode = incoming.dataBuffer[incoming.cur];
  outgoing.cur = 0;
  outgoing.bufferLength = 0;

  if (incoming.reqCode != 255) {
    incoming.reqCode = incoming.dataBuffer[incoming.cur] >> 1;
    incoming.writeAccess = ((incoming.dataBuffer[incoming.cur++] & 1) ? true : false);

    registerHandlers[incoming.reqCode]();

    outgoing.bufferLength = outgoing.cur;

    serialPort->write('s');
    serialPort->write(outgoing.bufferLength + 1);
    serialPort->write(incoming.dataBuffer[0]);
  } else {
    incoming.reqCode = incoming.dataBuffer[++incoming.cur];
    ++incoming.cur;

    storedFunctions[incoming.reqCode]();

    outgoing.bufferLength = outgoing.cur;

    serialPort->write('s');
    serialPort->write(outgoing.bufferLength + 2);
    serialPort->write(255);
    serialPort->write(incoming.dataBuffer[1]);
  }

  for (int i = 0; i < outgoing.bufferLength; ++i) {
    serialPort->write(outgoing.dataBuffer[i]);
  }
}

uint8_t SiRoboAndroid::getByte() {
  return incoming.dataBuffer[incoming.cur++];
}

int16_t SiRoboAndroid::getInt16() {
  int16_t tmp = 0;
  for (int i = 0; i < 2; ++i) {
    tmp |= (int16_t)(getByte() << (8 * i));
  }
  return tmp;
}

int8_t SiRoboAndroid::getInt8() {
  return (int8_t) getByte();
}

char SiRoboAndroid::getChar() {
  return (char) getByte();
}

void SiRoboAndroid::getString(char *dest) {
  uint8_t len = getByte();
  for (int i = 0; i < len; ++i) {
    dest[i] = (char) getByte();
  }
  dest[len] = '\0';
}

void SiRoboAndroid::getByteStream(uint8_t *dest, uint8_t len) {
  for (int i = 0; i < len; ++i) {
    dest[i] = getByte();
  }
  dest[len] = '\0';
}

void SiRoboAndroid::putByte(uint8_t data) {
  outgoing.dataBuffer[outgoing.cur++] = data;
}

void SiRoboAndroid::putInt16(int16_t data) {
  for (int i = 0; i < 2; ++i) {
    putByte((int16_t)((data >> (8 * i)) & 0xFF));
  }
}

void SiRoboAndroid::putInt8(int8_t data) {
  putByte(data);
}

void SiRoboAndroid::putString(char *data) {
  uint8_t len = strlen(data);
  putByte(len & 0xFF);
  for (int i = 0; i < len; ++i) {
    putByte(data[i]);
  }
}

void SiRoboAndroid::putByteStream(uint8_t *data, uint8_t len) {
  putByte(len & 0xFF);
  for (int i = 0; i < len; ++i) {
    putByte(data[i]);
  }
}