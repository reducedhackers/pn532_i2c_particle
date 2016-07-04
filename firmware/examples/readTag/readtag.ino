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
                int i;
                for (i = 0; i < tagMessage.getRecordCount()   ; i++)  {
                         //
                         NdefRecord tagRecord = tagMessage.getRecord(i);
                         tagRecord.print();
                         int payloadLength = tagRecord.getPayloadLength();
                         byte payload[payloadLength];
                         tagRecord.getPayload(payload);
                         
                }
        }
    }
    delay(5000);
    Particle.process();
}
