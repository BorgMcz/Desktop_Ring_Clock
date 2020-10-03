#ifndef PAGE_INFOMATION_H
#define PAGE_INFOMATION_H


//
//   The HTML PAGE
//
void Information_Page() {
	char PAGE_Information[2000];
	uint8_t mac[6];
	WiFi.macAddress(mac);	
	
snprintf(PAGE_Information, 1950,
"<meta name='viewport' content='width=device-width, initial-scale=1' />\
<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />\
<link rel='stylesheet' href='style.css' type='text/css' />\
<a href='/'  class='btn btn--s btn--grey'>&#9664;</a>&nbsp;&nbsp;<strong>Network Information</strong>\
<hr>\
<table border='0'  cellspacing='0' cellpadding='3' style='width:310px' >\
<tr><td align='right'>SSID :</td><td><span id='x_ssid'>%s</span></td></tr>\
<tr><td align='right'>IP :</td><td><span id='x_ip'>%d.%d.%d.%d</span></td></tr>\
<tr><td align='right'>Netmask :</td><td><span id='x_netmask'>%d.%d.%d.%d</span></td></tr>\
<tr><td align='right'>Gateway :</td><td><span id='x_gateway'>%d.%d.%d.%d</span></td></tr>\
<tr><td align='right'>Mac :</td><td><span id='x_mac'>%02X:%02X:%02X:%02X:%02X:%02X</span></td></tr>\
</table>", WiFi.SSID(), WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3], WiFi.subnetMask()[0], WiFi.subnetMask()[1], WiFi.subnetMask()[2], WiFi.subnetMask()[3], WiFi.gatewayIP()[0], WiFi.gatewayIP()[1], WiFi.gatewayIP()[2], WiFi.gatewayIP()[3], mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5] );

server.send_P ( 200, "text/html", PAGE_Information );
}
//<tr><td colspan="2" align="center"><a href="javascript:GetState()" class="btn btn--m btn--grey">Scanare</a></td></tr>

//
// FILL WITH INFOMATION
//

void send_information_values_html ()
{


}


#endif
