#define DEBUG=false
#include "application.h"
#include "pn532_i2c_particle/pn532_i2c_particle.h"
#include "pn532_i2c_particle/PN532.h"
#include "pn532_i2c_particle/NfcAdapter.h"

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

void setup(void) {
    Serial.begin(9600);
    Serial.println("NDEF Reader");
    nfc.begin();
    }


void loop(void) {
    Serial.println("\nScan a NFC tag\n");
    if (nfc.tagPresent())
    {
        NfcTag tag = nfc.read();
        if(tag.hasNdefMessage()){
                NdefMessage tagMessage = tag.getNdefMessage();
                 // at this point tag.print() will dump a NDefMessage for every record.
                int i;
                for (i = 0; i < tagMessage.getRecordCount()   ; i++)  {
                    NdefRecord tagRecord = tagMessage.getRecord(i);
                    int payloadLength = tagRecord.getPayloadLength();
                    byte payload[payloadLength];
                    tagRecord.getPayload(payload);
                    char tagMessage[payloadLength + 1];
                    memcpy(tagMessage, payload , payloadLength);
                    tagMessage[payloadLength + 1] =  '\0';
                    Serial.println(tagMessage);
                }
        }
    }
    delay(5000);
    // I have noticed that without the call to Particle Process 
    // I can end up with the code giving me a pusling green; Wifi working but 
    // no communication with the cloud; it will have made one connection 
    // and then it stops listeing to the cloud
    Particle.process();
}

