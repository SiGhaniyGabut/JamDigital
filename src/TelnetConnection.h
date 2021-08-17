// (optional) callback functions for telnet events
void onTelnetConnect(String ip) {
    telnet.println("");
    telnet.println(" ~~ CONNECTED ~~");
    telnet.println("");
    telnet.println("Your Local IP is: " + telnet.getIP());
    telnet.println("(Use CTRL + ] and q to disconnect.)");
    telnet.println("");
    telnet.println("");
}

void setupTelnet() {  
  // passing on functions for various telnet events
  telnet.onConnect(onTelnetConnect);
  telnet.begin();
}
