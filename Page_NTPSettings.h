#ifndef PAGE_NTPSETTINGS_H
#define PAGE_NTPSETTINGS_H

void NTPConfiguration_Page() {
if (server.args() > 0 )  // Save Settings
  {
    config.isDayLightSaving = false;
	config.displaySec = false;
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "ntpserver") config.ntpServerName = urldecode( server.arg(i));
      if (server.argName(i) == "update") config.Update_Time_Via_NTP_Every =  server.arg(i).toInt();
      if (server.argName(i) == "tz") config.timeZone =  server.arg(i).toInt();
      if (server.argName(i) == "dst") config.isDayLightSaving = true;
	  if (server.argName(i) == "sets") config.displaySec = true;
      if (server.argName(i) == "starth") config.displaySecStart =  server.arg(i).toInt();
      if (server.argName(i) == "stoph") config.displaySecStop =  server.arg(i).toInt();
      if (server.argName(i) == "minbr") config.brightnessMin =  server.arg(i).toInt();
      if (server.argName(i) == "maxbr") config.brightnessMax =  server.arg(i).toInt();
      if (server.argName(i) == "clrs") config.colorSecPrint = strtol( &server.arg(i)[1], NULL, 16);
      if (server.argName(i) == "clrm") config.colorMinPrint = strtol( &server.arg(i)[1], NULL, 16);
      if (server.argName(i) == "clrh") config.colorHourPrint = strtol( &server.arg(i)[1], NULL, 16);
      if (server.argName(i) == "clrcf1") config.colorCif1Print = strtol( &server.arg(i)[1], NULL, 16);
      if (server.argName(i) == "clrcf2") config.colorCif2Print = strtol( &server.arg(i)[1], NULL, 16);
      if (server.argName(i) == "clrlgh") config.colorLight = strtol( &server.arg(i)[1], NULL, 16);
	  if (server.argName(i) == "lghbr") config.colorLightBr =  server.arg(i).toInt();
	  if (server.argName(i) == "lghtm") config.colorLightTm =  server.arg(i).toInt();
    }
    WriteConfig();
    firstStart = true;
  }	
	
	char PAGE_NTPConfiguration[5000];
	char buffer[16];
	
	int str_len = config.ntpServerName.length() + 1;				// convert string to chat
	char x1[str_len];	
	config.ntpServerName.toCharArray(x1, str_len);


String  x2 = (String) config.Update_Time_Via_NTP_Every;
//String  x3 = (String) config.timeZone;
String  x4 = (String) (config.isDayLightSaving ? "checked" : "");
String  x5 = (String) (config.displaySec ? "checked" : "");
String  x6 = (String) config.displaySecStart;
String  x7 = (String) config.displaySecStop;
String  x8 = (String) config.brightnessMin;
String  x9 = (String) config.brightnessMax;
sprintf(buffer, "%06X", config.colorSecPrint);  
String  x10 = (String) buffer;
sprintf(buffer, "%06X", config.colorMinPrint);  
String  x11 = (String) buffer; 
sprintf(buffer, "%06X", config.colorHourPrint);  
String  x12 = (String) buffer; 
sprintf(buffer, "%06X", config.colorCif1Print);  
String  x13 = (String) buffer;
sprintf(buffer, "%06X", config.colorCif2Print);  
String  x14 = (String) buffer;
sprintf(buffer, "%06X", config.colorLight);  
String  x15 = (String) buffer;
String  x16 = (String) config.colorLightBr;  
String  x17 = (String) config.colorLightTm;
String  y[33];
int z = 0;
for (int i = -120; i <= 130; i += 10) {
	if (config.timeZone == i) {y[z] = "selected";} else {{y[z] = "";}}
	z++;
}
	if (config.timeZone == -35) {y[26] = "selected";} else {{y[26] = "";}}
	if (config.timeZone == 35) {y[27] = "selected";} else {{y[27] = "";}}
	if (config.timeZone == 45) {y[28] = "selected";} else {{y[28] = "";}}
	if (config.timeZone == 55) {y[29] = "selected";} else {{y[29] = "";}}
	if (config.timeZone == 57) {y[30] = "selected";} else {{y[30] = "";}}
	if (config.timeZone == 65) {y[31] = "selected";} else {{y[31] = "";}}	
	if (config.timeZone == 95) {y[32] = "selected";} else {{y[32] = "";}}
snprintf(PAGE_NTPConfiguration, 5000,
"<meta name='viewport' content='width=device-width, initial-scale=1' />\
<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />\
<link rel='stylesheet' href='style.css' type='text/css' />\
<a href='/'  class='btn btn--s btn--grey'>&#9664;</a>&nbsp;&nbsp;<strong>NTP Settings</strong>\
<hr><form action='/ntp.html' method='get'>\
<table border='0'  cellspacing='0' cellpadding='3'>\
<tr><td align='right'>NTP Server:</td><td><input type='text' id='ntpserver' name='ntpserver' maxlength='32' value='%s'></td></tr>\
<tr><td align='right'>Update:</td><td><input type='number' id='update' name='update' min='0' max='1440' value='%s'> minutes (0=disable)</td></tr>\
<tr><td>Timezone</td><td><select  id='tz' name='tz'>\
  <option value='-120' %s>(GMT-12:00)</option>\
  <option value='-110' %s>(GMT-11:00)</option>\
  <option value='-100' %s>(GMT-10:00)</option>\
  <option value='-90' %s>(GMT-09:00)</option>\
  <option value='-80' %s>(GMT-08:00)</option>\
  <option value='-70' %s>(GMT-07:00)</option>\
  <option value='-60' %s>(GMT-06:00)</option>\
  <option value='-50' %s>(GMT-05:00)</option>\
  <option value='-40' %s>(GMT-04:00)</option>\
  <option value='-35' %s>(GMT-03:30)</option>\
  <option value='-30' %s>(GMT-03:00)</option>\
  <option value='-20' %s>(GMT-02:00)</option>\
  <option value='-10' %s>(GMT-01:00)</option>\
  <option value='0' %s>(GMT+00:00)</option>\
  <option value='10' %s>(GMT+01:00)</option>\
  <option value='20' %s>(GMT+02:00)</option>\
  <option value='30' %s>(GMT+03:00)</option>\
  <option value='35' %s>(GMT+03:30)</option>\
  <option value='40' %s>(GMT+04:00)</option>\
  <option value='45' %s>(GMT+04:30)</option>\
  <option value='50' %s>(GMT+05:00)</option>\
  <option value='55' %s>(GMT+05:30)</option>\
  <option value='57' %s>(GMT+05:45)</option>\
  <option value='60' %s>(GMT+06:00)</option>\
  <option value='65' %s>(GMT+06:30)</option>\
  <option value='70' %s>(GMT+07:00)</option>\
  <option value='80' %s>(GMT+08:00)</option>\
  <option value='90' %s>(GMT+09:00)</option>\
  <option value='95' %s>(GMT+09:30)</option>\
  <option value='100' %s>(GMT+10:00)</option>\
  <option value='110' %s>(GMT+11:00)</option>\
  <option value='120' %s>(GMT+12:00)</option>\
  <option value='130' %s>(GMT+13:00)</option>\
</select></td></tr>\
<tr><td align='right'>Daylight saving:</td><td><input type='checkbox' id='dst' name='dst' %s></td></tr>\
<tr><td align='right'>&nbsp;</td><td>&nbsp;</td></tr>\
<tr><td align='right'>Display seconds:</td><td><input type='checkbox' id='sets' name='sets' %s></td></tr>\
<tr><td align='right'>Show time start:</td><td><input type='number' id='starth' name='starth' min='0' max='23' value='%s'> hour (0 - 23)</td></tr>\
<tr><td align='right'>Show time stop:</td><td><input type='number' id='stoph' name='stoph' min='0' max='24' value='%s'> hour (0 - 24)</td></tr>\
<tr><td align='right'>&nbsp;</td><td>&nbsp;</td></tr>\
<tr><td align='right'>Brightness min.:</td><td><input type='number' id='minbr' name='minbr' min='1' max='254' value='%s'> (1 - 254)</td></tr>\
<tr><td align='right'>Brightness max.:</td><td><input type='number' id='maxbr' name='maxbr' min='2' max='255' value='%s'> (2 - 255)</td></tr>\
<tr><td align='right'>&nbsp;</td><td>&nbsp;</td></tr>\
<tr><td align='right'>Color seconds: </td><td><input type='color' id='clrs' name='clrs' value='#%s'></td></tr>\
<tr><td align='right'>Color minits: </td><td><input type='color' id='clrm' name='clrm' value='#%s'></td></tr>\
<tr><td align='right'>Color hours: </td><td><input type='color' id='clrh' name='clrh' value='#%s'></td></tr>\
<tr><td align='right'>Color clock face: </td><td><input type='color' id='clrcf1' name='clrcf1' value='#%s'></td></tr>\
<tr><td align='right'>Color cl. face s.: </td><td><input type='color' id='clrcf2' name='clrcf2' value='#%s'></td></tr>\
<tr><td align='right'>&nbsp;</td><td>&nbsp;</td></tr>\
<tr><td align='right'>Color Light: </td><td><input type='color' id='clrlgh' name='clrlgh' value='#%s'></td></tr>\
<tr><td align='right'>Brightness Light:</td><td><input type='number' id='lghbr' name='lghbr' min='1' max='255' value='%s'> (1 - 255)</td></tr>\
<tr><td align='right'>Time Light:</td><td><input type='number' id='lghtm' name='lghtm' min='0' max='60' value='%s'> (0 - 60) min.</td></tr>\
<tr><td colspan='2' align='center'><input type='submit' style='width:150px' class='btn btn--m btn--grey' value='Save'></td></tr>\
</table></form>", x1, x2, y[0], y[1], y[2], y[3], y[4], y[5], y[6], y[7], y[8], y[26], y[9], y[10], y[11], y[12], y[13], y[14], y[15], y[27], y[16], y[28], y[17], y[29], y[30], y[18], y[31], y[19], y[20], y[21], y[32], y[22], y[23], y[24], y[25], x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17 );

server.send_P ( 200, "text/html", PAGE_NTPConfiguration );
}


#endif
