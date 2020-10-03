#ifndef PAGE_NTPSETTINGS_H
#define PAGE_NTPSETTINGS_H

const char PAGE_NTPConfiguration[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s btn--grey">&#9664;</a>&nbsp;&nbsp;<strong>NTP Settings</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">NTP Server:</td><td><input type="text" id="ntpserver" name="ntpserver" maxlength="172" value=""></td></tr>
<tr><td align="right">Update:</td><td><input type="text" id="update" name="update" size="3"maxlength="6" value=""> minutes (0=disable)</td></tr>
<tr><td>Timezone</td><td>
<select  id="tz" name="tz">
  <option value="-120">(GMT-12:00)</option>
  <option value="-110">(GMT-11:00)</option>
  <option value="-100">(GMT-10:00)</option>
  <option value="-90">(GMT-09:00)</option>
  <option value="-80">(GMT-08:00)</option>
  <option value="-70">(GMT-07:00)</option>
  <option value="-60">(GMT-06:00)</option>
  <option value="-50">(GMT-05:00)</option>
  <option value="-40">(GMT-04:00)</option>
  <option value="-35">(GMT-03:30)</option>
  <option value="-30">(GMT-03:00)</option>
  <option value="-20">(GMT-02:00)</option>
  <option value="-10">(GMT-01:00)</option>
  <option value="0">(GMT+00:00)</option>
  <option value="10">(GMT+01:00)</option>
  <option value="20" selected>(GMT+02:00)</option>
  <option value="30">(GMT+03:00)</option>
  <option value="35">(GMT+03:30)</option>
  <option value="40">(GMT+04:00)</option>
  <option value="45">(GMT+04:30)</option>
  <option value="50">(GMT+05:00)</option>
  <option value="55">(GMT+05:30)</option>
  <option value="57">(GMT+05:45)</option>
  <option value="60">(GMT+06:00)</option>
  <option value="65">(GMT+06:30)</option>
  <option value="70">(GMT+07:00)</option>
  <option value="80">(GMT+08:00)</option>
  <option value="90">(GMT+09:00)</option>
  <option value="95">(GMT+09:30)</option>
  <option value="100">(GMT+10:00)</option>
  <option value="110">(GMT+11:00)</option>
  <option value="120">(GMT+12:00)</option>
  <option value="120">(GMT+12:00)</option>
  <option value="130">(GMT+13:00)</option>
</select>
</td></tr>
<tr><td align="right">Daylight saving:</td><td><input type="checkbox" id="dst" name="dst"></td></tr>
<tr><td align="right">&nbsp;</td><td>&nbsp;</td></tr>
<tr><td align="right">Display seconds:</td><td><input type="checkbox" id="sets" name="sets"></td></tr>
<tr><td align="right">Show time start:</td><td><input type="text" id="starth" name="starth" size="2" maxlength="2" value=""> hour (0 - 23)</td></tr>
<tr><td align="right">Show time stop:</td><td><input type="text" id="stoph" name="stoph" size="2" maxlength="2" value=""> hour (0 - 24)</td></tr>
<tr><td align="right">&nbsp;</td><td>&nbsp;</td></tr>
<tr><td align="right">Brightness min.:</td><td><input type="text" id="minbr" name="minbr" size="3" maxlength="3" value=""> (0 - 255)</td></tr>
<tr><td align="right">Brightness max.:</td><td><input type="text" id="maxbr" name="maxbr" size="3" maxlength="3" value=""> (0 - 255)</td></tr>
<tr><td align="right">&nbsp;</td><td>&nbsp;</td></tr>
<tr><td align="right">Color seconds: </td><td><input type="color" id="clrs" name="clrs" value=""></td></tr>
<tr><td align="right">Color minits: </td><td><input type="color" id="clrm" name="clrm" value=""></td></tr>
<tr><td align="right">Color hours: </td><td><input type="color" id="clrh" name="clrh" value=""></td></tr>
<tr><td align="right">Color clock face: </td><td><input type="color" id="clrcf1" name="clrcf1" value=""></td></tr>
<tr><td align="right">Color cl. face s.: </td><td><input type="color" id="clrcf2" name="clrcf2" value=""></td></tr>
<tr><td align="right">&nbsp;</td><td>&nbsp;</td></tr>
<tr><td align="right">Color Light: </td><td><input type="color" id="clrlgh" name="clrlgh" value=""></td></tr>
<tr><td align="right">Brightness Light:</td><td><input type="text" id="lghbr" name="lghbr" size="3" maxlength="3" value=""> (0 - 255)</td></tr>
<tr><td align="right">Time Light:</td><td><input type="text" id="lghtm" name="lghtm" size="3" maxlength="3" value=""> (0 - 60) min.</td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--grey" value="Save"></td></tr>
</table>
</form>
<script>
  

window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/ntpvalues");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}



</script>
)=====";


void send_NTP_configuration_html()
{
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
  server.send_P ( 200, "text/html", PAGE_NTPConfiguration );
  Serial.println(__FUNCTION__);

}


void send_NTP_configuration_values_html()
{
  char buffer[16];
  
  String values ="";
  values += "ntpserver|" + (String) config.ntpServerName + "|input\n";
  values += "update|" + (String) config.Update_Time_Via_NTP_Every + "|input\n";
  values += "tz|" + (String) config.timeZone + "|input\n";
  values += "dst|" + (String) (config.isDayLightSaving ? "checked" : "") + "|chk\n";
  values += "sets|" + (String) (config.displaySec ? "checked" : "") + "|chk\n";
  values += "starth|" + (String) config.displaySecStart + "|input\n";
  values += "stoph|" + (String) config.displaySecStop + "|input\n";
  values += "minbr|" + (String) config.brightnessMin + "|input\n";
  values += "maxbr|" + (String) config.brightnessMax + "|input\n";
  sprintf(buffer, "%06X", config.colorSecPrint);  
  values += "clrs|#" + (String) buffer + "|input\n";
  sprintf(buffer, "%06X", config.colorMinPrint);  
  values += "clrm|#" + (String) buffer + "|input\n"; 
  sprintf(buffer, "%06X", config.colorHourPrint);  
  values += "clrh|#" + (String) buffer + "|input\n"; 
  sprintf(buffer, "%06X", config.colorCif1Print);  
  values += "clrcf1|#" + (String) buffer + "|input\n";
  sprintf(buffer, "%06X", config.colorCif2Print);  
  values += "clrcf2|#" + (String) buffer + "|input\n";
  sprintf(buffer, "%06X", config.colorLight);  
  values += "clrlgh|#" + (String) buffer + "|input\n";
  values += "lghbr|" + (String) config.colorLightBr + "|input\n";  
  values += "lghtm|" + (String) config.colorLightTm + "|input\n";  
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  AdminTimeOutCounter=0;
}

#endif
