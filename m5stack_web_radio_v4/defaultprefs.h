// Default preferences in raw data format for PROGMEM
//
#define defaultprefs_version 1808016
const char defprefs_txt[] PROGMEM = R"=====(
# Example configuration

# Programmable input pins:
gpio_39 = uppreset = 1
gpio_38 = upvolume = 2
gpio_37 = downvolume = 2
#

# MQTT settings
mqttbroker = none
mqttport = 1883
mqttuser = none
mqttpasswd = none
mqqprefix = none

# Enter your WiFi network specs here:
wifi_00 = SSID1/PASSWD1
wifi_01 = SSID2/PASSWD2

#
volume = 72
#
toneha = 0
tonehf = 0
tonela = 0
tonelf = 0

#
preset = 5
# Some preset examples
preset_00 = bbcmedia.ic.llnwd.net/stream/bbcmedia_radio1_mf_p          # 0 - BBC1
preset_01 = bbcmedia.ic.llnwd.net/stream/bbcmedia_radio1xtra_mf_p      # 1 - BBC1 Extra
preset_02 = bbcmedia.ic.llnwd.net/stream/bbcmedia_radio4fm_mf_p        # 2 - BBC4 FM
preset_03 = bbcmedia.ic.llnwd.net/stream/bbcmedia_radio4extra_mf_p     # 3 - BBC4 Extra
preset_04 = 198.178.123.5:7336/                                        # 4 - Soulectic
preset_05 = stream.srg-ssr.ch/m/rsj/mp3_128                            # 5 - Radio Swiss Jazz
preset_06 = ice4.somafm.com/sonicuniverse-128-mp3                      # 6 - Sonic Universe
preset_07 = icecast.omroep.nl/radio1-bb-mp3                            # 7 - Radio 1
preset_08 = icecast.omroep.nl/radio4-bb-mp3                            # 8 - Radio 4
#

# Clock offset and daylight saving time
clk_server = pool.ntp.org                            # Time server to be used
clk_offset = 1                                       # Offset with respect to UTC in hours
clk_dst = 1                                          # Offset during daylight saving time (hours)

# Dual Digital Potmeter
pin_ddp_cs = 12
#

# M5Stack OLED Display
pin_tft_cs = 14                                      # GPIO Pin number for TFT "CS"
pin_tft_dc = 27                                      # GPIO Pin number for TFT "DC"

# SD Card
pin_sd_cs = 4                                        # GPIO Pin number for SD card "CS"

#
pin_vs_cs = 5                                        # GPIO Pin number for VS1053 "CS"
pin_vs_dcs = 2                                       # GPIO Pin number for VS1053 "DCS"
pin_vs_dreq = 16                                     # GPIO Pin number for VS1053 "DREQ"

)=====" ;
