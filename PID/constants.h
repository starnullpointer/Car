#ifndef CONSTANTS
#define CONSTANTS

/* *****************
 * PIN DEFINITIONS
 * *****************
 */
 
#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
// WINC_EN goes to 5v.

#define TCAADDR 0x70 //for multiplexor


//                                        "---------x---------x---------x"
const char CAR_CON_REACHED_DEST[30]     = "{ Car Con ReachedDestin }";
const char CAR_CON_LIGHT_ON[30]         = "{ Car Con LightIsOn }";
const char CAR_CON_REQ_POS[30]          = "{ Car Con ReqCurrentPos }";

const char CON_CAR_TURN_LIGHT_ON[30]    = "{ Car Con TurnLightOn }";
const char CON_CAM_REQ_CAR_POS[30]      = "{ Con Cam ReqPosition }";

//

//const char OPEN_BRAK

const int port = 3142;
const char ssid[] = "Mac's iPhone";     //  your network SSID (name)
const char pass[] = "helloworld";    // your network password (use for WPA, or use as key for WEP)

//PID CONSTANTS
const double P_GAIN_DEFAULT=1;
const double D_GAIN_DEFAULT=1;
const double I_GAIN_DEFAULT=1;

#endif // CONSTANTS
