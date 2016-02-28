/*********************************************************************
 This is an example for our Feather WIFI modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <adafruit_feather.h>

#define MAX_SCAN_NUM   20
wl_ap_info_t scan_result[MAX_SCAN_NUM];

void setup()
{
  Serial.begin(115200);

  // wait for serial port to connect. Needed for native USB port only
  while (!Serial) delay(1);

  Serial.println("Scan Network Example\r\n");
}

void loop()
{
  Serial.println();
  Serial.println("Scanning available networks...");
  listNetworks();

  Serial.println();
  Serial.println("Try again in 10 seconds");
  delay(10000);
}

void listNetworks()
{
  int numSsid = Feather.scanNetworks(scan_result, MAX_SCAN_NUM);

  // print the list of networks seen:
  Serial.print("Number of available networks:");
  Serial.println(numSsid);

  if (numSsid == 0) return;

  // print the network number and name for each network found:
  Serial.printf("ID SSID                 Enc  Ch Signal\n");
  for (int i = 0; i < numSsid; i++)
  {
    Serial.printf("%02d %-20s %-04s %02d %02d (dBm)", 
                  i,
                  (scan_result[i].ssid[i] == 0) ? "*" : scan_result[i].ssid, // hidden SSID display as "*"
                  getEncryptionStr( scan_result[i].security ),
                  scan_result[i].channel,
                  scan_result[i].rssi);

    Serial.println();
  }
}

char const* getEncryptionStr(int32_t encType)
{
  // read the encryption type and print out the name:
  switch (encType)
  {
    case ENC_TYPE_WEP:
    case ENC_TYPE_WEP_SHARED:
      return "WEP";
    break;
      
    case ENC_TYPE_WPA_TKIP:
    case ENC_TYPE_WPA_AES:
    case ENC_TYPE_WPA_MIXED:
      return "WPA";
    break;
    
    case ENC_TYPE_WPA2_AES:
    case ENC_TYPE_WPA2_TKIP:
    case ENC_TYPE_WPA2_MIXED:
      return "WPA2";
    break;
      
    case ENC_TYPE_OPEN:
      return "OPEN";
    break;
      
    default:
      return "OTHER";
    break;
  }
}


