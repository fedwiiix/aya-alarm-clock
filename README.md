# Aya alarm clock

**This project is part of the Aya project**
This is a synchronized alarm clock with a voice assistant. It is an autonomous system when the assistant is absent

### Functions



### Composed by
- Aarduino Mega 2560
- DS3231 RTC
- [240X400 TFT LCD Touch Screen ](https://fr.aliexpress.com/item/3-2-3-2-pouce-240X400-TFT-LCD-Tactile-cran-Bouclier-D-extension-LED-Module-D/32892795591.html?spm=a2g0w.search0104.3.71.b7524316Fg2dtG&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_319_10892_317_10696_10924_453_10084_454_10083_10618_10920_10921_10304_10307_10922_10820_10821_537_10302_536_10843_10059_10884_10887_100031_321_322_10103_10930-10892,searchweb201603_51,ppcSwitch_0&algo_pvid=a5f36d32-b0d0-4414-8dda-8ae5069bd1d5&algo_expid=a5f36d32-b0d0-4414-8dda-8ae5069bd1d5-10 "240X400 TFT LCD Touch Screen ")
- HC-12 radio module
- BMP280 (temperatue & pressure)
- DHT22 (temperature & humidity)
- USB connector (5v outpout)


### Communication
 get alarms in same format with HC-12 signal command.
 
- set the alarm at 2 o'clock am: "2OCLOCK"
- get alarms: "GETALARMS"
	- answer if the alarms have not been modified: "NOALARMSCHANGE"
	- or json alarm format response withs alarms
- confirm and save get alarms: "GETALARMSOK"
	- answer: "SENDALARMSOK"
- good respons: alarms in json
	- resend alarms in json format to compare and valid send
	- error no alarms: "NOALARMS"
	- transmission error: "GETALARMSERROR"
- valid alarms: "SENDALARMSOK"
	- answer: "GETALARMSOK"

#### Json format
```json
{
	"alarmes": [{
		"action": "sonnerie",		// type of alarm
		"repeter": "0000010",		// day: sun mon tues...
		"heure": "09:00",
		"status": "1",
		"appareil": "33",		// switch device id
		"cmd": "On",			// switch on
		"modDate": "27-12-18"		// date of last change
	}, {
		"action": "sonnerie",
		"repeter": "0111110",
		"heure": "08:30",
		"status": "1",
		"appareil": "",
		"cmd": "",
		"modDate": ""
	}]
}
```